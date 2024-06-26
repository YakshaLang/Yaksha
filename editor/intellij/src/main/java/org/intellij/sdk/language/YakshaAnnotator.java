package org.intellij.sdk.language;

import com.intellij.lang.ASTNode;
import com.intellij.lang.annotation.AnnotationHolder;
import com.intellij.lang.annotation.Annotator;
import com.intellij.lang.annotation.HighlightSeverity;
import com.intellij.openapi.util.TextRange;
import com.intellij.psi.PsiElement;
import org.intellij.sdk.language.psi.*;
import org.intellij.sdk.language.yaksha_docs.YakshaDocs;
import org.jetbrains.annotations.NotNull;

public class YakshaAnnotator implements Annotator {

    @Override
    public void annotate(@NotNull final PsiElement element, @NotNull AnnotationHolder holder) {

        if (element instanceof YakshaDataTypeBit) {
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
                        .range(fncall.getFirstChild().getTextRange())
                        .textAttributes(YakshaSyntaxHighlighter.KEYWORD)
                        .create();
                if ((fullName.equals("cast") || fullName.equals("arrnew") || fullName.equals("array") || fullName.equals("fixedarr")) && fncall.getArgumentsList() != null
                        && !fncall.getArgumentsList().isEmpty() && fncall.getArgumentsList().get(0).getExpList() != null
                        && fncall.getArgumentsList().get(0).getExpList().size() > 0) {
                    YakshaExp dt = fncall.getArgumentsList().get(0).getExpList().get(0);
                    holder.newSilentAnnotation(HighlightSeverity.INFORMATION)
                            .range(dt.getTextRange())
                            .textAttributes(YakshaSyntaxHighlighter.DATA_TYPE)
                            .create();
                }

            } else if (fncall.getStructArgumentsList() != null && !fncall.getStructArgumentsList().isEmpty()) {
                TextRange tr = fncall.getTextRange();
                holder.newSilentAnnotation(HighlightSeverity.INFORMATION)
                        .range(new TextRange(tr.getStartOffset(), tr.getStartOffset() + fncall.getFullName().length()))
                        .textAttributes(YakshaSyntaxHighlighter.DATA_TYPE)
                        .create();
            }
        } else if (element instanceof YakshaRuntimefeatureStatement) {
            holder.newSilentAnnotation(HighlightSeverity.INFORMATION)
                    .range(element.getTextRange())
                    .textAttributes(YakshaSyntaxHighlighter.COMMENT)
                    .create();
        } else if (element instanceof YakshaAllAllowedSymbols) {
            YakshaAllAllowedSymbols symbol = (YakshaAllAllowedSymbols) element;
            final String method = symbol.getText();
            if (YakshaDocs.LISP_BUILTIN_NAMES.contains(method)) {
                holder.newSilentAnnotation(HighlightSeverity.INFORMATION)
                        .range(symbol.getTextRange())
                        .textAttributes(YakshaSyntaxHighlighter.KEYWORD)
                        .create();
            }
        } else if (element instanceof YakshaMacroCall | element instanceof YakshaMacroDeclarationStatement |
                element instanceof YakshaDslInnerBlock | element instanceof YakshaDslOuterBlock) {
            PsiElement method = element.getFirstChild();
            if (method != null) {
                holder.newSilentAnnotation(HighlightSeverity.INFORMATION)
                        .range(method.getTextRange())
                        .textAttributes(YakshaSyntaxHighlighter.META_PROGRAMMING)
                        .create();
                boolean target_found = false;
                while (!target_found) {
                    final PsiElement notSign = method.getNextSibling();
                    if (notSign != null) {
                        holder.newSilentAnnotation(HighlightSeverity.INFORMATION)
                                .range(notSign.getTextRange())
                                .textAttributes(YakshaSyntaxHighlighter.META_PROGRAMMING)
                                .create();
                        if (notSign.getText().strip().equals("!")) {
                            target_found = true;
                        }
                    } else {
                        target_found = true;
                    }
                    method = notSign;
                }
            }

        }
    }

}