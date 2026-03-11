package org.intellij.sdk.language;

import com.intellij.codeInsight.hints.*;
import com.intellij.codeInsight.hints.presentation.InlayPresentation;
import com.intellij.lang.ASTNode;
import com.intellij.lang.Language;
import com.intellij.openapi.editor.Document;
import com.intellij.openapi.editor.Editor;
import com.intellij.openapi.fileTypes.FileType;
import com.intellij.openapi.project.Project;
import com.intellij.openapi.vfs.VirtualFile;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiFile;
import com.intellij.psi.PsiManager;
import org.intellij.sdk.language.psi.*;
import org.intellij.sdk.language.yaksha_docs.YakshaDocs;
import org.jetbrains.annotations.Nls;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import javax.swing.*;
import java.util.List;

public class YakshaParameterHintsProvider implements InlayHintsProvider<NoSettings> {

    private static final SettingsKey<NoSettings> KEY = new SettingsKey<>("yaksha.parameter.hints");

    private static YakshaDefStatement findDefForCall(YakshaFncall fncall, String fullName) {
        try {
            String moduleName = null;
            String funcName;
            if (fullName.contains(".")) {
                int dot = fullName.indexOf('.');
                moduleName = fullName.substring(0, dot);
                String rest = fullName.substring(dot + 1);
                funcName = rest.contains(".") ? rest.substring(rest.lastIndexOf('.') + 1) : rest;
            } else {
                funcName = fullName;
            }

            if (moduleName != null) {
                PsiFile containingFile = fncall.getContainingFile();
                if (containingFile == null) return null;
                List<YakshaImportStatement> imports = ExtractUtils.getChildrenOfTypeAsList(
                        containingFile, YakshaImportStatement.class);
                for (YakshaImportStatement imp : imports) {
                    if (!moduleName.equals(imp.getName())) continue;
                    String importPath = imp.getImportPath();
                    if (importPath == null) break;
                    VirtualFile cvf = containingFile.getVirtualFile();
                    if (cvf == null) break;
                    VirtualFile dir = cvf.getParent();
                    if (dir == null) break;
                    VirtualFile targetVF = dir.findFileByRelativePath(importPath.replace(".", "/") + ".yaka");
                    if (targetVF == null) targetVF = YakshaUtil.findLibsFile(importPath);
                    if (targetVF == null) break;
                    YakshaFile yakaFile = (YakshaFile) PsiManager.getInstance(fncall.getProject()).findFile(targetVF);
                    if (yakaFile == null) break;
                    for (YakshaDefStatement def : ExtractUtils.getChildrenOfTypeAsList(yakaFile, YakshaDefStatement.class)) {
                        if (funcName.equals(def.getName())) return def;
                    }
                    break;
                }
                return null;
            }

            // Search current file first
            PsiFile containingFile = fncall.getContainingFile();
            for (YakshaDefStatement def : ExtractUtils.getChildrenOfTypeAsList(containingFile, YakshaDefStatement.class)) {
                if (funcName.equals(def.getName())) return def;
            }
            // Project-wide fallback
            List<YakshaDefStatement> defs = YakshaUtil.findDefs(fncall.getProject(), funcName);
            return defs.isEmpty() ? null : defs.get(0);
        } catch (Exception ignored) {
            return null;
        }
    }

    @NotNull
    @Override
    public SettingsKey<NoSettings> getKey() {
        return KEY;
    }

    @NotNull
    @Override
    public String getName() {
        return "Parameter name hints";
    }

    @Nullable
    @Override
    public String getPreviewText() {
        return null;
    }

    @NotNull
    @Override
    public ImmediateConfigurable createConfigurable(@NotNull NoSettings settings) {
        return listener -> new JPanel();
    }

    @NotNull
    @Override
    public NoSettings createSettings() {
        return new NoSettings();
    }

    @Override
    public boolean isVisibleInSettings() {
        return true;
    }

    @Nullable
    @Override
    public InlayHintsCollector getCollectorFor(@NotNull PsiFile file, @NotNull Editor editor,
                                               @NotNull NoSettings settings, @NotNull InlayHintsSink sink) {
        if (!(file instanceof YakshaFile)) return null;
        return new FactoryInlayHintsCollector(editor) {
            @Override
            public boolean collect(@NotNull PsiElement element, @NotNull Editor editor, @NotNull InlayHintsSink sink) {
                if (!(element instanceof YakshaFncall)) return true;
                YakshaFncall fncall = (YakshaFncall) element;
                String fullName = fncall.getFullName();
                if (fullName == null) return true;
                // Skip builtins — they have their own docs
                if (!fullName.contains(".") && YakshaDocs.BUILTIN_FUNCTION_NAMES.contains(fullName)) return true;

                List<YakshaArguments> argsList = fncall.getArgumentsList();
                if (argsList.isEmpty()) return true;
                List<YakshaExp> args = argsList.get(0).getExpList();
                if (args.isEmpty()) return true;

                YakshaDefStatement def = findDefForCall(fncall, fullName);
                if (def == null) return true;

                YakshaDefParams defParams = def.getDefParams();
                if (defParams == null) return true;
                List<YakshaDefParam> params = defParams.getDefParamList();
                if (params == null || params.isEmpty()) return true;

                for (int i = 0; i < Math.min(args.size(), params.size()); i++) {
                    ASTNode nameNode = params.get(i).getNode().findChildByType(YakshaTypes.IDENTIFIER);
                    if (nameNode == null) continue;
                    String paramName = nameNode.getText();
                    if (paramName == null || paramName.isEmpty()) continue;
                    int offset = args.get(i).getTextRange().getStartOffset();
                    InlayPresentation hint = getFactory().smallText(paramName + ":");
                    sink.addInlineElement(offset, true, hint, false);
                }
                return true;
            }
        };
    }

    @Override
    public @Nullable String getDescription() {
        return "Shows parameter names from the function definition inline at each call site.";
    }

    @Override
    public @NotNull InlayGroup getGroup() {
        return InlayGroup.PARAMETERS_GROUP;
    }

    @Override
    public @NotNull PsiFile createFile(@NotNull Project project, @NotNull FileType fileType, @NotNull Document document) {
        return InlayHintsProvider.super.createFile(project, fileType, document);
    }

    @Override
    public @Nls @Nullable String getProperty(@NotNull String key) {
        return null;
    }

    @Override
    public boolean isLanguageSupported(@NotNull Language language) {
        return language.getID().equals("Yaksha");
    }
}
