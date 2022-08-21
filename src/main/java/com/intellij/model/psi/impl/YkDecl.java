package com.intellij.model.psi.impl;

import com.intellij.model.Symbol;
import com.intellij.model.psi.PsiSymbolDeclaration;
import com.intellij.openapi.util.TextRange;
import com.intellij.psi.PsiElement;
import org.jetbrains.annotations.NotNull;

public class YkDecl implements PsiSymbolDeclaration {
    private final PsiElement element;
    private final YkPsi2Symbol target;
    private final TextRange range;

    public YkDecl(PsiElement element, PsiElement target, TextRange range) {
        this.element = element;
        this.target = new YkPsi2Symbol(target);
        this.range = range;
    }


    @Override
    public @NotNull PsiElement getDeclaringElement() {
        return element;
    }

    @Override
    public @NotNull TextRange getRangeInDeclaringElement() {
        return range;
    }

    @Override
    public @NotNull YkPsi2Symbol getSymbol() {
        return target;
    }
}
