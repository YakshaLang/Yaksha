package org.intellij.sdk.language.psi.impl;

import com.intellij.lang.ASTNode;
import com.intellij.navigation.ItemPresentation;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiFile;
import com.intellij.psi.PsiReference;
import org.intellij.sdk.language.YakshaIcons;
import org.intellij.sdk.language.YakshaReference;
import org.intellij.sdk.language.psi.*;
import org.jetbrains.annotations.NotNull;

import javax.annotation.Nullable;
import javax.swing.*;
import java.util.LinkedList;
import java.util.List;

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

//    public static int getTextOffset(final YakshaDefStatement statement) {
//        return statement.getNode().getFirstChildNode().getTextLength()
//                + statement.getNode().getFirstChildNode().getTreeNext().getTextLength();
//    }

    public static PsiElement setName(final YakshaDefStatement statement, String newName) {
        ASTNode nameNode = statement.getNode().findChildByType(YakshaTypes.IDENTIFIER);
        if (nameNode != null) {

        }
        return statement;
    }

    public static ItemPresentation getPresentation(final YakshaDefStatement element) {
        return new ItemPresentation() {
            @Override
            public @NotNull String getPresentableText() {
                final StringBuilder def = new StringBuilder();
                def.append(element.getName()).append("(");
                final YakshaDefParams params = element.getDefParams();
                if (params != null && params.getDefParamList() != null) {
                    boolean first = true;
                    for (YakshaDefParam param : params.getDefParamList()) {
                        ASTNode ident = param.getNode().findChildByType(YakshaTypes.IDENTIFIER);
                        if (ident != null && param.getDataType() != null) {
                            if (first) {
                                first = false;
                            } else {
                                def.append(", ");
                            }
                            def.append(ident.getText()).append(": ").append(param.getDataType().getText());
                        }
                    }
                }
                def.append(") -> ");
                if (element.getDataType() != null) {
                    def.append(element.getDataType().getText());
                }
                return def.toString();
            }

            @Nullable
            @Override
            public String getLocationString() {
                PsiFile containingFile = element.getContainingFile();
                return containingFile == null ? null : containingFile.getName();
            }

            @Override
            public Icon getIcon(boolean unused) {
                return YakshaIcons.DEF;
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
                final StringBuilder classStruct = new StringBuilder();
                boolean fieldFound = false;
                boolean first = true;
                classStruct.append(element.getName()).append(" { ");
                final List<YakshaClassBits> bits = element.getClassBitsList();
                if (bits != null) {
                    for (YakshaClassBits bit : bits) {
                        final YakshaClassField field = bit.getClassField();
                        if (field != null) {
                            ASTNode ident = field.getNode().findChildByType(YakshaTypes.IDENTIFIER);
                            if (ident != null && field.getDataType() != null) {
                                fieldFound = true;
                                if (first) {
                                    first = false;
                                } else {
                                    classStruct.append(", ");
                                }
                                classStruct.append(ident.getText()).append(": ").append(field.getDataType().getText());
                            }
                        }
                    }
                }
                classStruct.append(" }");
                if (!fieldFound) {
                    return element.getName();
                }
                return classStruct.toString();
            }

            @Nullable
            @Override
            public String getLocationString() {
                PsiFile containingFile = element.getContainingFile();
                return containingFile == null ? null : containingFile.getName();
            }

            @Override
            public Icon getIcon(boolean unused) {
                return YakshaIcons.CLASS;
            }
        };
    }

    public static PsiElement getNameIdentifier(final YakshaClassStatement statement) {
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
        return identifiers.getLast().getText();
    }

    public static String getFullName(final YakshaFncall fncallExpr) {
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
        final StringBuilder b = new StringBuilder();
        boolean first = true;
        for (ASTNode n : identifiers) {
            if (first) {
                first = false;
            } else {
                b.append(".");
            }
            b.append(n.getText());
        }
        return b.toString();
    }

    public static PsiReference getReference(final YakshaFncall fnCallExpr) {
        final String def = fnCallExpr.getDefOrClassName();
        if (def == null) {
            return null;
        }
        return new YakshaReference(fnCallExpr, fnCallExpr.getIdentifierExp().getTextRangeInParent());
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
            identifiers.removeLast();
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
        return identifiers.getLast().getText();
    }

    public static PsiElement setName(final YakshaImportStatement statement, String newName) {
        ASTNode nameNode = statement.getNode().findChildByType(YakshaTypes.IDENTIFIER);
        if (nameNode != null) {

        }
        return statement;
    }
    public static PsiElement getNameIdentifier(final YakshaImportStatement statement) {
        final LinkedList<ASTNode> identifiers = new LinkedList<>();
        for (ASTNode element = statement.getNode().getFirstChildNode(); element != null; element = element.getTreeNext()) {
            if (element.getElementType() == YakshaTypes.IDENTIFIER) {
                identifiers.add(element);
            }
        }
        if (identifiers.isEmpty()) {
            return null;
        }
        return identifiers.getLast().getPsi();
    }

    public static ItemPresentation getPresentation(final YakshaImportStatement element) {
        return new ItemPresentation() {
            @Nullable
            @Override
            public String getPresentableText() {
                return element.getName() + " <-- " + element.getImportPath();
            }

            @Nullable
            @Override
            public String getLocationString() {
                PsiFile containingFile = element.getContainingFile();
                return containingFile == null ? null : containingFile.getName();
            }

            @Override
            public Icon getIcon(boolean unused) {
                return YakshaIcons.IMPORT;
            }
        };
    }


    /* ============================================================== */
    // const
    /* ============================================================== */

    public static String getName(final YakshaConstStatement statement) {
        ASTNode nameNode = statement.getNode().findChildByType(YakshaTypes.IDENTIFIER);
        if (nameNode != null) {
            return nameNode.getText();
        }
        return null;
    }

    public static PsiElement setName(final YakshaConstStatement statement, String newName) {
        ASTNode nameNode = statement.getNode().findChildByType(YakshaTypes.IDENTIFIER);
        if (nameNode != null) {

        }
        return statement;
    }

    public static ItemPresentation getPresentation(final YakshaConstStatement element) {
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
                return YakshaIcons.CONSTANT;
            }
        };
    }

    public static PsiElement getNameIdentifier(final YakshaConstStatement statement) {
        ASTNode nameNode = statement.getNode().findChildByType(YakshaTypes.IDENTIFIER);
        if (nameNode != null) {
            return nameNode.getPsi();
        }
        return null;
    }
}