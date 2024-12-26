package org.intellij.sdk.language;

import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.JsonSyntaxException;
import com.intellij.lang.annotation.AnnotationHolder;
import com.intellij.lang.annotation.ExternalAnnotator;
import com.intellij.lang.annotation.HighlightSeverity;
import com.intellij.openapi.editor.Document;
import com.intellij.openapi.editor.Editor;
import com.intellij.openapi.util.Pair;
import com.intellij.openapi.util.TextRange;
import com.intellij.openapi.vfs.LocalFileSystem;
import com.intellij.openapi.vfs.VirtualFile;
import com.intellij.psi.PsiFile;
import org.intellij.sdk.language.tw.YakshaToolWindow;
import org.intellij.sdk.language.utilities.FileLogger;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.TimeUnit;

public class YakshaCompilerAnnotator extends ExternalAnnotator<Pair<Editor, PsiFile>, List<YakshaCompilerAnnotator.CompilerError>> {

    private static final FileLogger LOGGER = FileLogger.getInstance();
    public static final int MAX_DEPTH = 5;
    private final ConcurrentLinkedQueue<String> queue = new ConcurrentLinkedQueue<>();
    private final YakshaService service = new YakshaService(queue);

    public YakshaCompilerAnnotator() {
        super();
    }

    @Override
    public @Nullable Pair<Editor, PsiFile> collectInformation(@NotNull PsiFile file, @NotNull Editor editor, boolean hasErrors) {
        return Pair.create(editor, file);
    }

    @Override
    public @NotNull List<CompilerError> doAnnotate(@Nullable Pair<Editor, PsiFile> collectedInfo) {
        if (collectedInfo == null) {
            return List.of();
        }
        final var editor = collectedInfo.first;
        final var psiFile = collectedInfo.second;
        final var virtualFile = psiFile.getVirtualFile();

        File f = new File(virtualFile.getPath());
        final File cleanup;
        final File directory = f.getParentFile();

        if (f.getName().startsWith("_.")) {
            LOGGER.info("You are editing a scratch file: " + f.getPath());
            return List.of();
        }

        if (f.getName().equals("main.yaka")) {
            final var scratch = Paths.get(directory.getAbsolutePath(), "_.main.yaka");
            LOGGER.info("Wrote scratch file:" + scratch);
            final var temp = createSyncedFile(editor.getDocument(), scratch);
            if (temp == null) {
                f = Paths.get(directory.getAbsolutePath(), "_.main.yaka").toFile();
            } else {
                f = new File(temp.getPath());
            }
            cleanup = f;
        } else {
            final var name = "_." + f.getName();
            final var scratch = Paths.get(f.getAbsoluteFile().getParent(), name);
            cleanup = scratch.toFile();
            createSyncedFile(editor.getDocument(), scratch);
            LOGGER.info("Wrote scratch file:" + scratch);
            f = findMainFile(new File(directory.getPath()));
            if (f == null) {
                deleteScratch(cleanup);
                return List.of();
            }
        }

        final var result = runCompiler(f);
        deleteScratch(cleanup);
        return result;
    }

    private static void deleteScratch(@NotNull File f) {
        try {
            final var success = f.delete();
            LOGGER.info("Deleted " + f.getPath() + " success = " + success);
        } catch (Exception ignored) {
            LOGGER.info("Failed to delete " + f.getPath());
        }
    }

    private static VirtualFile createSyncedFile(Document doc, Path tmp) {
        try {
            try (BufferedWriter out = Files.newBufferedWriter(tmp, StandardCharsets.UTF_8)) {
                out.write(doc.getText());
            }
            File f = tmp.toFile();
            return LocalFileSystem.getInstance().refreshAndFindFileByIoFile(f);
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
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
        final var f = new File(file.getVirtualFile().getPath());
        if (f.getName().startsWith("_.")) {
            return;
        }

        final var givenFile = f.getAbsolutePath();
        final var givenFileScratch = Paths.get(Paths.get(givenFile).getParent().toString(), "_." + f.getName()).toFile().getAbsolutePath();

        for (CompilerError error : annotationResult) {
            var line = error.line - 1;
            if (line < 0 || line >= document.getLineCount()) continue;

            var startOffset = document.getLineStartOffset(line) + error.column - 1;
            var endOffset = startOffset + error.length;

            final var absPath = new File(error.file).getAbsolutePath();

            if (absPath.equals(givenFile) || absPath.equals(givenFileScratch)) {
                holder.newAnnotation(HighlightSeverity.ERROR, error.message).range(new TextRange(startOffset, endOffset)).create();
            }
        }
    }

    @SuppressWarnings("unused")
    public YakshaService getService() {
        return service;
    }

    public static class CompilerError {
        final String file;
        final String message;
        final int line;
        final int column;
        final int length;

        private CompilerError(final String file, final String message, final int line, final int column, final int length) {
            this.file = file;
            this.message = message;
            this.line = line;
            this.column = column;
            this.length = length;
        }
    }

    private File findMainFile(final File dir) {
        File currentDir = dir;
        for (int i = 0; i <= YakshaCompilerAnnotator.MAX_DEPTH; i++) {
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
        final List<CompilerError> errors = new ArrayList<>();
        final var compiler = YakshaToolWindow.YAKSHA_EXE_PATH;
        if (compiler.isBlank()) {
            LOGGER.error("Yaksha compiler path is not set");
            return errors;
        }

        LOGGER.info("Yaksha compiler: " + compiler);

        final List<String> command = List.of(compiler, "compile", "-d", "-e", mainFile.getAbsolutePath());

        try {
            final Process process = new ProcessBuilder(command).directory(mainFile.getParentFile()).redirectErrorStream(true).start();

            process.waitFor(60, TimeUnit.SECONDS);

            String output = new String(process.getInputStream().readAllBytes());
            final var result = parseCompilerErrors(output, mainFile.getAbsolutePath());
            LOGGER.info("Found errors " + result.size());
            errors.addAll(result);
            if (result.isEmpty()) {
                queue.add(mainFile.getAbsolutePath());
            }
        } catch (IOException | InterruptedException ex) {
            LOGGER.error("Error when executing yaksha compile ", ex.getLocalizedMessage());
        }

        return errors;
    }

    private List<CompilerError> parseCompilerErrors(String output, String mainFilePath) {
        List<CompilerError> errors = new ArrayList<>();
        String[] lines = output.split("\\R");

        for (String line : lines) {
            if (!line.trim().isEmpty()) {
                final JsonObject json;
                try {
                    json = JsonParser.parseString(line).getAsJsonObject();
                } catch (JsonSyntaxException exception) {
                    continue;
                }
                String file = json.has("file") ? json.get("file").getAsString() : mainFilePath;
                int lineNumber = json.has("line") ? json.get("line").getAsInt() : 0;
                int columnNumber = json.has("pos") ? json.get("pos").getAsInt() : 0;
                String message = json.get("message").getAsString();
                int tokenLength = json.has("token") ? json.get("token").getAsString().length() : 1;

                errors.add(new CompilerError(file, message, lineNumber, columnNumber, tokenLength));
            }
        }

        return errors;
    }
}
