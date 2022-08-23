package org.intellij.sdk.language;


import com.intellij.codeInsight.lookup.LookupElement;
import com.intellij.codeInsight.lookup.LookupElementBuilder;
import com.intellij.openapi.project.Project;
import com.intellij.openapi.util.TextRange;
import com.intellij.psi.*;
import com.intellij.util.ReflectionUtil;
import org.intellij.sdk.language.psi.YakshaClassStatement;
import org.intellij.sdk.language.psi.YakshaConstStatement;
import org.intellij.sdk.language.psi.YakshaDefStatement;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.ArrayList;
import java.util.List;

public class YakshaReference extends PsiReferenceBase<PsiElement> implements PsiPolyVariantReference, ResolvingHint  {

    private final String key;

    public YakshaReference(@NotNull PsiElement element, TextRange textRange) {
        super(element, textRange);
        key = element.getText().substring(textRange.getStartOffset(), textRange.getEndOffset());
    }

    @Override
    public ResolveResult @NotNull [] multiResolve(boolean incompleteCode) {
        String thisK = key;
        if (key.contains(".")) {
            String[] t  = key.split("\\.");
            thisK = t[t.length - 1];
        }
        final Project p = myElement.getNode().getPsi().getProject();
        final List<ResolveResult> results = new ArrayList<>();
        YakshaUtil.findDefs(p, thisK).stream().map(PsiElementResolveResult::new).forEach(results::add);
        YakshaUtil.findClasses(p, thisK).stream().map(PsiElementResolveResult::new).forEach(results::add);
        YakshaUtil.findConsts(p, thisK).stream().map(PsiElementResolveResult::new).forEach(results::add);
        return results.toArray(new ResolveResult[0]);
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


        return variants.toArray();
    }

}