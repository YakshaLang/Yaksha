package org.intellij.sdk.language;

import com.intellij.openapi.util.TextRange;
import com.intellij.patterns.PlatformPatterns;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiReference;
import com.intellij.psi.PsiReferenceContributor;
import com.intellij.psi.PsiReferenceProvider;
import com.intellij.psi.PsiReferenceRegistrar;
import com.intellij.util.ProcessingContext;
import org.intellij.sdk.language.psi.YakshaClassStatement;
import org.intellij.sdk.language.psi.YakshaConstStatement;
import org.intellij.sdk.language.psi.YakshaDefStatement;
import org.intellij.sdk.language.psi.YakshaImportStatement;
import org.intellij.sdk.language.psi.YakshaTypes;
import org.jetbrains.annotations.NotNull;

public class YakshaReferenceContributor extends PsiReferenceContributor {

    @Override
    public void registerReferenceProviders(@NotNull PsiReferenceRegistrar registrar) {
        registrar.registerReferenceProvider(PlatformPatterns.psiElement(),
                new MyPsiReferenceProvider());
    }

    private static class MyPsiReferenceProvider extends PsiReferenceProvider {
        @Override
        public PsiReference @NotNull [] getReferencesByElement(@NotNull PsiElement element,
                                                               @NotNull ProcessingContext context) {
            try {
                if (element instanceof YakshaDefStatement) {
                    return getDefReference((YakshaDefStatement) element);
                }
                if (element instanceof YakshaImportStatement) {
                    return getImportReference((YakshaImportStatement) element);
                }
                if (element instanceof YakshaConstStatement) {
                    return getConstDeclRefrence((YakshaConstStatement) element);
                }
                if (element instanceof YakshaClassStatement) {
                    return getClassReference((YakshaClassStatement) element);
                }
            } catch (Exception ignored) {
            }
            return PsiReference.EMPTY_ARRAY;
        }

        private PsiReference[] getClassReference(YakshaClassStatement element) {
            final String name = element.getName();
            int startPos = element.getNode().findChildByType(YakshaTypes.IDENTIFIER).getStartOffsetInParent();
            int endPos = startPos + name.length();
            return new PsiReference[]{new YakshaReference(element, new TextRange(startPos, endPos))};
        }

        private PsiReference[] getConstDeclRefrence(YakshaConstStatement element) {
            final String name = element.getName();
            int startPos = element.getNode().findChildByType(YakshaTypes.IDENTIFIER).getStartOffsetInParent();
            int endPos = startPos + name.length();
            return new PsiReference[]{new YakshaReference(element, new TextRange(startPos, endPos))};
        }

        private PsiReference[] getImportReference(YakshaImportStatement element) {
            return PsiReference.EMPTY_ARRAY;
        }

        @NotNull
        private PsiReference[] getDefReference(@NotNull YakshaDefStatement def) {
            final String name = def.getName();
            int startPos = def.getNode().findChildByType(YakshaTypes.IDENTIFIER).getStartOffsetInParent();
            int endPos = startPos + name.length();
            return new PsiReference[]{new YakshaReference(def, new TextRange(startPos, endPos))};
        }
    }
}