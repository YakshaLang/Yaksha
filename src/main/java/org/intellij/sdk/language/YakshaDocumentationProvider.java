package org.intellij.sdk.language;

import com.google.common.base.CharMatcher;
import com.intellij.lang.ASTNode;
import com.intellij.lang.documentation.AbstractDocumentationProvider;
import com.intellij.psi.PsiElement;
import com.intellij.psi.presentation.java.SymbolPresentationUtil;
import org.intellij.sdk.language.psi.*;
import org.intellij.sdk.language.yaksha_docs.Loader;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.List;

public class YakshaDocumentationProvider extends AbstractDocumentationProvider {

    @Override
    public @Nullable String generateDoc(PsiElement element, @Nullable PsiElement originalElement) {
        if (element instanceof YakshaFncall) {
            final String ident = ((YakshaFncall)element).getFullName();
            final String name = ((YakshaFncall)element).getDefOrClassName();
            int count = CharMatcher.is('.').countIn(ident);
            if (count == 1) {
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
                    return Loader.INSTANCE.generateDoc(importPath, name);
                }
            }
        }
        if (element instanceof YakshaClassStatement) {
            DocBuilder b = new DocBuilder();
            YakshaClassStatement c = (YakshaClassStatement)element;
            b.title(c.getName());
            b.keyValue("<b>Kind</b>", "Class");
            final List<YakshaClassBits> bitsList = c.getClassBitsList();
            if (bitsList != null) {
                for (YakshaClassBits bit: bitsList) {
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
            b.description("");
            return b.build();
        }
        if (element instanceof YakshaDefStatement) {
            DocBuilder b = new DocBuilder();
            YakshaDefStatement c = (YakshaDefStatement)element;
            b.title(c.getName());
            b.keyValue("<b>Kind</b>", "Function");
            final YakshaDefParams paramsList = c.getDefParams();
            if (paramsList != null && paramsList.getDefParamList() != null) {
                for (YakshaDefParam param: paramsList.getDefParamList()) {
                    final ASTNode paramName = param.getNode().findChildByType(YakshaTypes.IDENTIFIER);;
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
            b.description("");
            YakshaDataType returnType = c.getDataType();
            String rt = "?";
            if (returnType != null) {
                rt = returnType.getText();
            }
            b.keyValue("Return Type", rt);
            return b.build();
        }
        return null;
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
