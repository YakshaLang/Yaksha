package org.intellij.sdk.language;


import com.intellij.codeInsight.lookup.LookupElement;
import com.intellij.codeInsight.lookup.LookupElementBuilder;
import com.intellij.openapi.project.Project;
import com.intellij.openapi.util.TextRange;
import com.intellij.openapi.vfs.VirtualFile;
import com.intellij.psi.*;
import com.intellij.util.ReflectionUtil;
import org.intellij.sdk.language.psi.*;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.ArrayList;
import java.util.List;

public class YakshaReference extends PsiReferenceBase<PsiElement> implements PsiPolyVariantReference, ResolvingHint {

    private final String key;

    public YakshaReference(@NotNull PsiElement element, TextRange textRange) {
        super(element, textRange);
        key = element.getText().substring(textRange.getStartOffset(), textRange.getEndOffset());
    }

    @Override
    public ResolveResult @NotNull [] multiResolve(boolean incompleteCode) {
        final Project p = myElement.getNode().getPsi().getProject();
        if (key.contains(".")) {
            String[] t = key.split("\\.");
            String moduleName = t[0];
            String symbolName = t[t.length - 1];
            List<ResolveResult> moduleResults = resolveFromLocalModule(moduleName, symbolName);
            if (!moduleResults.isEmpty()) {
                return moduleResults.toArray(new ResolveResult[0]);
            }
            final List<ResolveResult> fallback = new ArrayList<>();
            YakshaUtil.findDefs(p, symbolName).stream().map(PsiElementResolveResult::new).forEach(fallback::add);
            YakshaUtil.findClasses(p, symbolName).stream().map(PsiElementResolveResult::new).forEach(fallback::add);
            return fallback.toArray(new ResolveResult[0]);
        }
        final List<ResolveResult> results = new ArrayList<>();
        YakshaUtil.findDefs(p, key).stream().map(PsiElementResolveResult::new).forEach(results::add);
        YakshaUtil.findClasses(p, key).stream().map(PsiElementResolveResult::new).forEach(results::add);
        YakshaUtil.findConsts(p, key).stream().map(PsiElementResolveResult::new).forEach(results::add);
        return results.toArray(new ResolveResult[0]);
    }

    private List<ResolveResult> resolveFromLocalModule(String moduleName, String symbolName) {
        List<ResolveResult> results = new ArrayList<>();
        try {
            PsiFile containingFile = myElement.getContainingFile();
            if (containingFile == null) return results;
            List<YakshaImportStatement> imports = ExtractUtils.getChildrenOfTypeAsList(containingFile, YakshaImportStatement.class);
            for (YakshaImportStatement imp : imports) {
                if (!moduleName.equals(imp.getName())) continue;
                String importPath = imp.getImportPath();
                if (importPath == null) break;
                VirtualFile currentVF = containingFile.getVirtualFile();
                if (currentVF == null) break;
                VirtualFile dir = currentVF.getParent();
                if (dir == null) break;
                VirtualFile targetVF = dir.findFileByRelativePath(importPath.replace(".", "/") + ".yaka");
                if (targetVF == null) targetVF = YakshaUtil.findLibsFile(importPath);
                if (targetVF == null) break;
                YakshaFile yakaFile = (YakshaFile) PsiManager.getInstance(myElement.getProject()).findFile(targetVF);
                if (yakaFile == null) break;
                ExtractUtils.getChildrenOfTypeAsList(yakaFile, YakshaDefStatement.class).stream()
                        .filter(d -> symbolName.equals(d.getName()))
                        .map(PsiElementResolveResult::new).forEach(results::add);
                ExtractUtils.getChildrenOfTypeAsList(yakaFile, YakshaClassStatement.class).stream()
                        .filter(c -> symbolName.equals(c.getName()))
                        .map(PsiElementResolveResult::new).forEach(results::add);
                ExtractUtils.getChildrenOfTypeAsList(yakaFile, YakshaEnumStatement.class).stream()
                        .filter(e -> symbolName.equals(e.getName()))
                        .map(PsiElementResolveResult::new).forEach(results::add);
                break;
            }
        } catch (Exception ignored) {
        }
        return results;
    }

    @Nullable
    @Override
    public PsiElement resolve() {
        if (key.contains(".")) {
            ResolveResult[] a = multiResolve(false);
            if (a.length == 1) {
                return a[0].getElement();
            }
        }
        final PsiFile file = myElement.getNode().getPsi().getContainingFile();
        List<YakshaDefStatement> defs = ExtractUtils.getChildrenOfTypeAsList(file, YakshaDefStatement.class);
        for (YakshaDefStatement d : defs) {
            if (d.getName() != null && key != null && key.equals(d.getName())) {
                return d;
            }
        }
        List<YakshaClassStatement> classes = ExtractUtils.getChildrenOfTypeAsList(file, YakshaClassStatement.class);
        for (YakshaClassStatement c : classes) {
            if (c.getName() != null && key != null && key.equals(c.getName())) {
                return c;
            }
        }
        List<YakshaConstStatement> consts = ExtractUtils.getChildrenOfTypeAsList(file, YakshaConstStatement.class);
        for (YakshaConstStatement co : consts) {
            if (co.getName() != null && key != null && key.equals(co.getName())) {
                return co;
            }
        }
        List<YakshaEnumStatement> enums = ExtractUtils.getChildrenOfTypeAsList(file, YakshaEnumStatement.class);
        for (YakshaEnumStatement en : enums) {
            if (en.getName() != null && key != null && key.equals(en.getName())) {
                return en;
            }
        }
        return null;
    }

    @Override
    public boolean canResolveTo(Class<? extends PsiElement> elementClass) {
        return ReflectionUtil.isAssignable(PsiFile.class, elementClass);
    }


    @Override
    public Object @NotNull [] getVariants() {
        Project project = myElement.getProject();
        List<LookupElement> variants = new ArrayList<>();

        // Functions
        List<YakshaDefStatement> defs = YakshaUtil.findDefs(project);
        for (final YakshaDefStatement st : defs) {
            if (st.getName() != null && st.getName().length() > 0) {
                variants.add(LookupElementBuilder
                        .create(st).withIcon(YakshaIcons.DEF)
                        .withTypeText(st.getContainingFile().getName())
                );
            }
        }

        // Classes
        List<YakshaClassStatement> classes = YakshaUtil.findClasses(project);
        for (final YakshaClassStatement st : classes) {
            if (st.getName() != null && st.getName().length() > 0) {
                variants.add(LookupElementBuilder
                        .create(st).withIcon(YakshaIcons.CLASS)
                        .withTypeText(st.getContainingFile().getName())
                );
            }
        }

        // Enums
        List<YakshaEnumStatement> enums = YakshaUtil.findEnums(project);
        for (final YakshaEnumStatement st : enums) {
            if (st.getName() != null && st.getName().length() > 0) {
                variants.add(LookupElementBuilder
                        .create(st).withIcon(YakshaIcons.CLASS)
                        .withTypeText(st.getContainingFile().getName())
                );
            }
        }

        return variants.toArray();
    }

}