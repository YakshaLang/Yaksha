package org.intellij.sdk.language.psi.impl;

import com.intellij.lang.ASTNode;
import com.intellij.navigation.ItemPresentation;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiFile;
import org.intellij.sdk.language.YakshaIcons;
import org.intellij.sdk.language.psi.*;

import javax.annotation.Nullable;
import javax.swing.*;
import java.util.LinkedList;

public class YakshaPsiImplUtil {

    /* ============================================================== */
    // defs
    /* ============================================================== */

    public static String getName(final YakshaDefStatement statement) {
        ASTNode nameNode = statement.getNode().findChildByType(YakshaTypes.IDENTIFIER);
        if (nameNode != null) {
            return nameNode.getText();
        }
        return null;
    }

    public static PsiElement setName(final YakshaDefStatement statement, String newName) {
        ASTNode nameNode = statement.getNode().findChildByType(YakshaTypes.IDENTIFIER);
        if (nameNode != null) {

        }
        return statement;
    }

    public static ItemPresentation getPresentation(final YakshaDefStatement element) {
        return new ItemPresentation() {
            @Nullable
            @Override
            public String getPresentableText() {
                return element.getName();
            }

            @Nullable
            @Override
            public String getLocationString() {
                PsiFile containingFile = element.getContainingFile();
                return containingFile == null ? null : containingFile.getName();
            }

            @Override
            public Icon getIcon(boolean unused) {
                return YakshaIcons.D;
            }
        };
    }

    public static PsiElement getNameIdentifier(final YakshaDefStatement statement) {
        ASTNode nameNode = statement.getNode().findChildByType(YakshaTypes.IDENTIFIER);
        if (nameNode != null) {
            return nameNode.getPsi();
        }
        return null;
    }

    /* ============================================================== */
    // classes
    /* ============================================================== */
    public static PsiElement setName(final YakshaClassStatement statement, String newName) {
        ASTNode nameNode = statement.getNode().findChildByType(YakshaTypes.IDENTIFIER);
        if (nameNode != null) {

        }
        return statement;
    }

    public static String getName(final YakshaClassStatement statement) {
        ASTNode nameNode = statement.getNode().findChildByType(YakshaTypes.IDENTIFIER);
        if (nameNode != null) {
            return nameNode.getText();
        }
        return null;
    }


    public static ItemPresentation getPresentation(final YakshaClassStatement element) {
        return new ItemPresentation() {
            @Nullable
            @Override
            public String getPresentableText() {
                return element.getName();
            }

            @Nullable
            @Override
            public String getLocationString() {
                PsiFile containingFile = element.getContainingFile();
                return containingFile == null ? null : containingFile.getName();
            }

            @Override
            public Icon getIcon(boolean unused) {
                return YakshaIcons.C;
            }
        };
    }

    public static PsiElement getNameIdentifier(final YakshaImportStatement statement) {
        ASTNode nameNode = statement.getNode().findChildByType(YakshaTypes.IDENTIFIER);
        if (nameNode != null) {
            return nameNode.getPsi();
        }
        return null;
    }

    /* ============================================================== */
    // function call
    /* ============================================================== */

    public static String getDefOrClassName(final YakshaFncall fncallExpr) {
        final YakshaIdentifierExp identifierExp = fncallExpr.getIdentifierExp();
        final LinkedList<ASTNode> identifiers = new LinkedList<>();
        for (ASTNode element = identifierExp.getNode().getFirstChildNode(); element != null; element = element.getTreeNext()) {
            if (element.getElementType() == YakshaTypes.IDENTIFIER) {
                identifiers.add(element);
            }
        }
        if (identifiers.isEmpty()) {
            return null;
        }
        return identifiers.pop().getText();
    }

    /* ============================================================== */
    // import
    /* ============================================================== */

    public static String getImportPath(final YakshaImportStatement statement) {
        ASTNode kwAS = statement.getNode().findChildByType(YakshaTypes.KW_AS);
        final LinkedList<ASTNode> identifiers = new LinkedList<>();
        for (ASTNode element = statement.getNode().getFirstChildNode(); element != null; element = element.getTreeNext()) {
            if (element.getElementType() == YakshaTypes.IDENTIFIER) {
                identifiers.add(element);
            }
        }
        if (identifiers.isEmpty()) {
            return null;
        }
        if (kwAS != null) {
            identifiers.pop();
        }
        StringBuilder sb = new StringBuilder();
        boolean first = true;
        for (ASTNode element: identifiers) {
            if (first) {
                first = false;
            } else {
                sb.append(".");
            }
            sb.append(element.getText());
        }
        return sb.toString();
    }

    public static String getName(final YakshaImportStatement statement) {
        final LinkedList<ASTNode> identifiers = new LinkedList<>();
        for (ASTNode element = statement.getNode().getFirstChildNode(); element != null; element = element.getTreeNext()) {
            if (element.getElementType() == YakshaTypes.IDENTIFIER) {
                identifiers.add(element);
            }
        }
        if (identifiers.isEmpty()) {
            return null;
        }
        return identifiers.pop().getText();
    }
}