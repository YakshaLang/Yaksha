package org.intellij.sdk.language;

import com.intellij.lang.ASTNode;
import com.intellij.lang.annotation.AnnotationHolder;
import com.intellij.lang.annotation.Annotator;
import com.intellij.lang.annotation.HighlightSeverity;
import com.intellij.psi.PsiElement;
import org.intellij.sdk.language.psi.YakshaAnnotation;
import org.intellij.sdk.language.psi.YakshaDataType;
import org.intellij.sdk.language.psi.YakshaFncall;
import org.intellij.sdk.language.psi.YakshaTypes;
import org.intellij.sdk.language.yaksha_docs.YakshaDocs;
import org.jetbrains.annotations.NotNull;

public class YakshaAnnotator implements Annotator {

    @Override
    public void annotate(@NotNull final PsiElement element, @NotNull AnnotationHolder holder) {
        if (element instanceof YakshaDataType) {
            holder.newSilentAnnotation(HighlightSeverity.INFORMATION)
                    .range(element.getTextRange())
                    .textAttributes(YakshaSyntaxHighlighter.DATA_TYPE)
                    .create();
        } else if (element instanceof YakshaAnnotation) {
            final ASTNode node = element.getNode().findChildByType(YakshaTypes.IDENTIFIER);
            if (node != null) {
                holder.newSilentAnnotation(HighlightSeverity.INFORMATION)
                        .range(node.getTextRange())
                        .textAttributes(YakshaSyntaxHighlighter.KEYWORD)
                        .create();
            }
        } else if (element instanceof YakshaFncall) {
            YakshaFncall fncall = (YakshaFncall) element;
            final String fullName = fncall.getFullName();
            if (fullName != null && !fullName.contains(".") && YakshaDocs.BUILTIN_FUNCTION_NAMES.contains(fullName)) {
                holder.newSilentAnnotation(HighlightSeverity.INFORMATION)
                        .range(fncall.getIdentifierExp().getTextRange())
                        .textAttributes(YakshaSyntaxHighlighter.KEYWORD)
                        .create();
            }
        }
    }

}