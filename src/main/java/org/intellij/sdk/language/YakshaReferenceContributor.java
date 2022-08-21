package org.intellij.sdk.language;

import com.intellij.openapi.util.TextRange;
import com.intellij.patterns.PlatformPatterns;
import com.intellij.psi.*;
import com.intellij.util.ProcessingContext;
import org.intellij.sdk.language.psi.YakshaDefStatement;
import org.jetbrains.annotations.NotNull;

public class YakshaReferenceContributor extends PsiReferenceContributor {

    @Override
    public void registerReferenceProviders(@NotNull PsiReferenceRegistrar registrar) {
        registrar.registerReferenceProvider(PlatformPatterns.psiElement(),
                new PsiReferenceProvider() {
                    @Override
                    public PsiReference @NotNull [] getReferencesByElement(@NotNull PsiElement element,
                                                                           @NotNull ProcessingContext context) {
                        System.out.println("get reference by element -> " + element);
                        try {
                            if (element instanceof YakshaDefStatement) {
                                YakshaDefStatement def = (YakshaDefStatement) element;
                                final String name = def.getName();
                                // 'def' + ' '
                                int startPos = element.getNode().getFirstChildNode().getTextLength() + element.getNode().getFirstChildNode().getTreeNext().getTextLength();
                                // add name length
                                int endPos = startPos + name.length();
                                return new PsiReference[]{new YakshaReference(element, new TextRange(startPos, endPos))};
                            }
                        } catch (Exception ex) {
                            ex.printStackTrace();
                        }
                        return PsiReference.EMPTY_ARRAY;
                    }
                });
    }

}