package org.intellij.sdk.language;

import com.intellij.openapi.util.TextRange;
import com.intellij.patterns.PlatformPatterns;
import com.intellij.psi.*;
import com.intellij.util.ProcessingContext;
import org.intellij.sdk.language.psi.YakshaFncall;
import org.jetbrains.annotations.NotNull;

public class YakshaReferenceContributor extends PsiReferenceContributor {

    @Override
    public void registerReferenceProviders(@NotNull PsiReferenceRegistrar registrar) {
        registrar.registerReferenceProvider(PlatformPatterns.psiElement(YakshaFncall.class),
                new PsiReferenceProvider() {
                    @Override
                    public PsiReference @NotNull [] getReferencesByElement(@NotNull PsiElement element,
                                                                           @NotNull ProcessingContext context) {
                        YakshaFncall call = (YakshaFncall) element;
                        String value = call.getDefOrClassName();
                        if ((value != null)) {
                            TextRange property = new TextRange(0, value.length() + 1);
                            return new PsiReference[]{new YakshaReference(element, property)};
                        }
                        return PsiReference.EMPTY_ARRAY;
                    }
                });
    }

}