package org.intellij.sdk.language;


import com.intellij.codeInsight.lookup.LookupElement;
import com.intellij.codeInsight.lookup.LookupElementBuilder;
import com.intellij.openapi.project.Project;
import com.intellij.openapi.util.TextRange;
import com.intellij.psi.*;
import com.intellij.util.ReflectionUtil;
import org.intellij.sdk.language.psi.YakshaClassStatement;
import org.intellij.sdk.language.psi.YakshaDefStatement;
import org.intellij.sdk.language.psi.YakshaFncall;
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
        final PsiFile file = myElement.getNode().getPsi().getContainingFile();
        final List<YakshaFncall> calls = ExtractUtils.getChildrenOfTypeAsList(file, YakshaFncall.class);;
        List<ResolveResult> results = new ArrayList<>();
        for (YakshaFncall st : calls) {
            final String name = st.getDefOrClassName();
            if (name != null && key != null && key.equals(name)) {
                results.add(new PsiElementResolveResult(st));
            }
        }
        System.out.println("Returned for [" + key + "] -> " + results.size());
        return results.toArray(new ResolveResult[results.size()]);
    }

    @Nullable
    @Override
    public PsiElement resolve() {
        final PsiFile file = myElement.getNode().getPsi().getContainingFile();
        List<YakshaDefStatement> defs = ExtractUtils.getChildrenOfTypeAsList(file, YakshaDefStatement.class);
        for (YakshaDefStatement d : defs) {
            if (d.getName() != null && key != null && key.equals(d.getName())) {
                System.out.println("Single resolve -> " + key + " -- found");
                return d;
            }
        }
        return null;
    }

    @Override
    public boolean canResolveTo(Class<? extends PsiElement> elementClass) {
        System.out.println("canResolveTo");
        return ReflectionUtil.isAssignable(PsiFile.class, elementClass);
    }

    @Override
    public boolean isReferenceTo(@NotNull PsiElement element) {
        System.out.println("Is reference to " + key + " -> " + element.getText());
        return super.isReferenceTo(element);
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