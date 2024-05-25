package org.intellij.sdk.language;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.intellij.lang.annotation.AnnotationHolder;
import com.intellij.lang.annotation.ExternalAnnotator;
import com.intellij.lang.annotation.HighlightSeverity;
import com.intellij.openapi.editor.Document;
import com.intellij.openapi.project.DumbAware;
import com.intellij.openapi.project.Project;
import com.intellij.openapi.util.TextRange;
import com.intellij.openapi.vfs.VirtualFile;
import com.intellij.psi.PsiDocumentManager;
import com.intellij.psi.PsiFile;
import com.intellij.psi.PsiManager;
import org.intellij.sdk.language.psi.YakshaFile;
import org.intellij.sdk.language.tw.YakshaToolWindow;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.TimeUnit;

public class YakshaCompilerAnnotator extends ExternalAnnotator<YakshaFile, List<YakshaCompilerAnnotator.CompilerError>> implements DumbAware {
    @Override
    public @Nullable YakshaFile collectInformation(@NotNull PsiFile file) {
        if (file instanceof YakshaFile) {
            return (YakshaFile) file;
        }
        return null;
    }

    @Override
    public @NotNull List<CompilerError> doAnnotate(@Nullable YakshaFile collectedInfo) {
        if (collectedInfo == null) {
            return List.of();
        }
        final var project = collectedInfo.getProject();
        final var virtualFile = collectedInfo.getVirtualFile();
        File mainFile = findMainFile(new File(virtualFile.getPath()), 5);
        if (mainFile == null) {
            return List.of();
        }


        return runCompiler(mainFile);
    }

    @Override
    public void apply(@NotNull PsiFile file, List<CompilerError> annotationResult, @NotNull AnnotationHolder holder) {
        if (annotationResult == null || annotationResult.isEmpty()) {
            return;
        }

        final var document = file.getViewProvider().getDocument();
        if (document == null) {
            return;
        }

        for (CompilerError error : annotationResult) {
            var line = error.line - 1;
            if (line < 0 || line >= document.getLineCount()) continue;

            var startOffset = document.getLineStartOffset(line) + error.column - 1;
            var endOffset = startOffset + error.length;

            holder.newAnnotation(HighlightSeverity.ERROR, error.message).range(new TextRange(startOffset, endOffset)).create();
        }
    }

    private @Nullable Document getDoc(Project project, VirtualFile file) {
        final var psiFile = PsiManager.getInstance(project).findFile(file);
        if (psiFile == null) {
            return null;
        }
        return PsiDocumentManager.getInstance(project).getDocument(psiFile);
    }

    public static class CompilerError {
        final String message;
        final int line;
        final int column;
        final int length;

        private CompilerError(final String message, final int line, final int column, final int length) {
            this.message = message;
            this.line = line;
            this.column = column;
            this.length = length;
        }
    }

    private File findMainFile(File dir, int maxDepth) {
        File currentDir = dir;
        for (int i = 0; i <= maxDepth; i++) {
            File mainCFile = new File(currentDir, "main.yaka");
            if (mainCFile.exists() && mainCFile.isFile()) {
                return mainCFile;
            }
            currentDir = currentDir.getParentFile();
            if (currentDir == null) break;
        }
        return null;
    }

    private List<CompilerError> runCompiler(File mainFile) {
        List<CompilerError> errors = new ArrayList<>();
        final var compiler = YakshaToolWindow.YAKSHA_EXE_PATH;
        if (compiler.isBlank()) {
            System.out.println("------ yaksha compiler path is not set -----");
            return errors;
        }

        System.out.println("----- yaksha compiler: " + compiler);

        List<String> command = List.of(compiler, "compile", "-d", mainFile.getAbsolutePath());

        try {
            Process process = new ProcessBuilder(command)
                    .directory(mainFile.getParentFile())
                    .redirectErrorStream(true)
                    .start();

            process.waitFor(60, TimeUnit.SECONDS);

            String output = new String(process.getInputStream().readAllBytes());
            int exitCode = process.exitValue();

            errors.addAll(parseCompilerErrors(output, mainFile.getAbsolutePath()));
        } catch (IOException | InterruptedException e) {
            e.printStackTrace();
        }

        return errors;
    }

    private List<CompilerError> parseCompilerErrors(String output, String mainFilePath) {
        List<CompilerError> errors = new ArrayList<>();
        String[] lines = output.split("\\R");

        for (String line : lines) {
            if (!line.trim().isEmpty()) {
                JsonObject json = JsonParser.parseString(line).getAsJsonObject();
                String file = json.has("file") ? json.get("file").getAsString() : mainFilePath;
                int lineNumber = json.has("line") ? json.get("line").getAsInt() : 0;
                int columnNumber = json.has("pos") ? json.get("pos").getAsInt() : 0;
                String message = json.get("message").getAsString();
                int tokenLength = json.has("token") ? json.get("token").getAsString().length() : 1;

                if (mainFilePath.equals(file)) {
                    errors.add(new CompilerError(message, lineNumber, columnNumber, tokenLength));
                }
            }
        }

        return errors;
    }
}
