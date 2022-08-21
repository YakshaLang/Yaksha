package com.intellij.model.psi.impl;

import com.google.common.collect.ImmutableList;
import com.intellij.model.psi.PsiSymbolDeclaration;
import com.intellij.model.psi.PsiSymbolDeclarationProvider;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiFile;
import org.intellij.sdk.language.ExtractUtils;
import org.intellij.sdk.language.psi.YakshaClassStatement;
import org.intellij.sdk.language.psi.YakshaDefStatement;
import org.intellij.sdk.language.psi.YakshaFncall;
import org.jetbrains.annotations.NotNull;

import java.util.Collection;
import java.util.List;

public class YakshaPsiSymbolDeclarationProvider implements PsiSymbolDeclarationProvider {
    @Override
    public @NotNull Collection<? extends @NotNull PsiSymbolDeclaration> getDeclarations(
            @NotNull PsiElement element, int offsetInElement) {
        if (element instanceof YakshaFncall) {
            YakshaFncall call = ((YakshaFncall)element);
            final String df = call.getDefOrClassName();
            if (df != null) {
                final PsiFile file = call.getNode().getPsi().getContainingFile();
                final List<YakshaDefStatement> defs = ExtractUtils.getChildrenOfTypeAsList(file, YakshaDefStatement.class);
                for (YakshaDefStatement st: defs) {
                    if (df.equals(st.getName())) {
                          return ImmutableList.of(
                                new YkDecl(element, st, ((YakshaFncall) element).getIdentifierExp().getTextRangeInParent()));
                    }
                }
                final List<YakshaClassStatement> classes = ExtractUtils.getChildrenOfTypeAsList(file, YakshaClassStatement.class);
                for (YakshaClassStatement st: classes) {
                    if (df.equals(st.getName())) {
                        return ImmutableList.of(
                                new YkDecl(element, st, ((YakshaFncall) element).getIdentifierExp().getTextRangeInParent()));
                    }
                }
                System.out.println("Not found -> " + df);
            }
        }
        return ImmutableList.of();
    }

}
