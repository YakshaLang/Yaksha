package org.intellij.sdk.language;

import com.google.common.base.CharMatcher;
import com.intellij.lang.ASTNode;
import com.intellij.lang.documentation.AbstractDocumentationProvider;
import com.intellij.psi.PsiElement;
import com.intellij.psi.presentation.java.SymbolPresentationUtil;
import org.intellij.sdk.language.psi.YakshaClassBits;
import org.intellij.sdk.language.psi.YakshaClassField;
import org.intellij.sdk.language.psi.YakshaClassStatement;
import org.intellij.sdk.language.psi.YakshaDataType;
import org.intellij.sdk.language.psi.YakshaDataTypeBit;
import org.intellij.sdk.language.psi.YakshaDataTypeIdentifier;
import org.intellij.sdk.language.psi.YakshaDefParam;
import org.intellij.sdk.language.psi.YakshaDefParams;
import org.intellij.sdk.language.psi.YakshaDefStatement;
import org.intellij.sdk.language.psi.YakshaFncall;
import org.intellij.sdk.language.psi.YakshaImportStatement;
import org.intellij.sdk.language.psi.YakshaTypes;
import org.intellij.sdk.language.yaksha_docs.YakshaDocs;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.List;

public class YakshaDocumentationProvider extends AbstractDocumentationProvider {

    private static String extractComments(PsiElement element) {
        StringBuilder sb = new StringBuilder();
        ASTNode node = element.getNode().findChildByType(YakshaTypes.NL);
        while (node != null) {
            node = node.getTreeNext();
            if (node.getElementType().equals(YakshaTypes.COMMENT)) {
                try {
                    final String comment = node.getText();
                    sb.append(comment.trim().substring(1).trim());
                    sb.append("<br />");
                } catch (NullPointerException | StringIndexOutOfBoundsException ignored) {
                }
            } else {
                break;
            }
        }
        return sb.toString();
    }

    @Override
    public @Nullable String generateDoc(PsiElement element, @Nullable PsiElement originalElement) {
        if (element instanceof YakshaFncall) {
            final String ident = ((YakshaFncall) element).getFullName();
            final String name = ((YakshaFncall) element).getDefOrClassName();
            int count = CharMatcher.is('.').countIn(ident);
            if (count == 1) {
                return getImportedDoc(element, ident, name);
            } else if (count == 0 && YakshaDocs.BUILTIN_FUNCTION_NAMES.contains(ident)) {
                final DocBuilder b = new DocBuilder();
                b.title(ident);
                b.description(YakshaDocs.BUILTIN_FUNCTIONS.get(ident));
                b.keyValue("<b>Kind</b>", "Builtin Function");
                return b.build();
            }
        }
        if (element instanceof YakshaClassStatement) {
            DocBuilder b = new DocBuilder();
            YakshaClassStatement c = (YakshaClassStatement) element;
            b.title(c.getName());
            b.keyValue("<b>Kind</b>", "Class");
            final List<YakshaClassBits> bitsList = c.getClassBitsList();
            if (bitsList != null) {
                for (YakshaClassBits bit : bitsList) {
                    YakshaClassField field = bit.getClassField();
                    if (field != null) {
                        final ASTNode node = field.getNode().findChildByType(YakshaTypes.IDENTIFIER);
                        if (node != null) {
                            String dt = "?";
                            if (field.getDataType() != null) {
                                dt = field.getDataType().getText();
                            }
                            b.typeKeyValue("Member", node.getText(), dt);
                        }
                    }
                }
            }
            b.description(extractComments(element));
            return b.build();
        }
        if (element instanceof YakshaDefStatement) {
            DocBuilder b = new DocBuilder();
            YakshaDefStatement c = (YakshaDefStatement) element;
            b.title(c.getName());
            b.keyValue("<b>Kind</b>", "Function");
            final YakshaDefParams paramsList = c.getDefParams();
            if (paramsList != null && paramsList.getDefParamList() != null) {
                for (YakshaDefParam param : paramsList.getDefParamList()) {
                    final ASTNode paramName = param.getNode().findChildByType(YakshaTypes.IDENTIFIER);
                    YakshaDataType dataType = param.getDataType();
                    if (paramName != null) {
                        String dt = "?";
                        if (dataType != null) {
                            dt = dataType.getText();
                        }
                        b.typeKeyValue("Param", paramName.getText(), dt);
                    }
                }
            }
            b.description(extractComments(element));
            YakshaDataType returnType = c.getDataType();
            String rt = "?";
            if (returnType != null) {
                rt = returnType.getText();
            }
            b.keyValue("Return Type", rt);
            return b.build();
        }
        if (element instanceof YakshaDataTypeBit) {
            final YakshaDataTypeBit bit = (YakshaDataTypeBit) element;
            final YakshaDataTypeIdentifier identifier = bit.getDataTypeIdentifier();
            if (identifier != null) {
                final String ident = identifier.getText();
                if (ident != null) {
                    String name = ident;
                    if (ident.contains(".")) {
                        name = ident.split("\\.")[1];
                    }
                    return getImportedDoc(element, ident, name);
                }
            }
        }
        System.out.println("Doc gen failed --> " + element);

        return null;
    }

    private static String getImportedDoc(PsiElement element, String ident, String name) {
        String documentation = null;
        final String importingName = ident.split("\\.")[0];
        YakshaImportStatement whichImport = null;
        List<YakshaImportStatement> imps = ExtractUtils.getChildrenOfTypeAsList(element.getContainingFile(), YakshaImportStatement.class);
        for (YakshaImportStatement i : imps) {
            if (importingName.equals(i.getName())) {
                // Found the import
                whichImport = i;
                break;
            }
        }
        if (whichImport != null && name != null) {
            final String importPath = whichImport.getImportPath();
            documentation = YakshaDocs.INSTANCE.generateDoc(importPath, name);
        }
        return documentation;
    }


    @Override
    public @Nullable String generateHoverDoc(@NotNull PsiElement element, @Nullable PsiElement originalElement) {
        return generateDoc(element, originalElement);
    }

    @Override
    public @Nullable String getQuickNavigateInfo(PsiElement element, PsiElement originalElement) {
        if (element instanceof YakshaDefStatement) {
            final String key = ((YakshaDefStatement) element).getName();
            final String file = SymbolPresentationUtil.getFilePathPresentation(element.getContainingFile());
            return "\"" + key + "\" in " + file;
        }
        if (element instanceof YakshaClassStatement) {
            final String key = ((YakshaClassStatement) element).getName();
            final String file = SymbolPresentationUtil.getFilePathPresentation(element.getContainingFile());
            return "\"" + key + "\" in " + file;
        }
        return null;
    }
}
