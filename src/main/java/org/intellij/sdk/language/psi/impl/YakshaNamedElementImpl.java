package org.intellij.sdk.language.psi.impl;

import com.intellij.extapi.psi.ASTWrapperPsiElement;
import com.intellij.lang.ASTNode;
import com.intellij.psi.PsiReference;
import com.intellij.psi.impl.source.resolve.reference.ReferenceProvidersRegistry;
import org.intellij.sdk.language.psi.YakshaNamedElement;
import org.jetbrains.annotations.NotNull;

public abstract class YakshaNamedElementImpl extends ASTWrapperPsiElement implements YakshaNamedElement {

    public YakshaNamedElementImpl(@NotNull ASTNode node) {
        super(node);
    }


    @Override
    public PsiReference getReference() {
        PsiReference[] referencesFromProviders = ReferenceProvidersRegistry.getReferencesFromProviders(this);
        if (referencesFromProviders.length == 1)
            return referencesFromProviders[0];
        else
            return null;
    }

    @Override
    public PsiReference @NotNull [] getReferences() {
        return ReferenceProvidersRegistry.getReferencesFromProviders(this);
    }
}
