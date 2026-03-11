package org.intellij.sdk.language;

import com.intellij.codeInsight.editorActions.enter.EnterHandlerDelegate;
import com.intellij.openapi.actionSystem.DataContext;
import com.intellij.openapi.command.WriteCommandAction;
import com.intellij.openapi.editor.Document;
import com.intellij.openapi.editor.Editor;
import com.intellij.openapi.editor.actionSystem.EditorActionHandler;
import com.intellij.openapi.util.Ref;
import com.intellij.openapi.util.TextRange;
import com.intellij.psi.PsiFile;
import org.intellij.sdk.language.psi.YakshaFile;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

public class YakshaEnterHandler implements EnterHandlerDelegate {

    @Override
    public Result preprocessEnter(@NotNull PsiFile file, @NotNull Editor editor,
                                  @NotNull Ref<Integer> caretOffsetRef,
                                  @NotNull Ref<Integer> caretAdvanceRef,
                                  @NotNull DataContext dataContext,
                                  @Nullable EditorActionHandler originalHandler) {
        return com.intellij.codeInsight.editorActions.enter.EnterHandlerDelegate.Result.Continue;
    }

    @Override
    public Result postProcessEnter(@NotNull PsiFile file, @NotNull Editor editor,
                                   @NotNull DataContext dataContext) {
        if (!(file instanceof YakshaFile)) return Result.Continue;
        try {
            Document doc = editor.getDocument();
            int caretOffset = editor.getCaretModel().getOffset();
            int currentLine = doc.getLineNumber(caretOffset);
            if (currentLine == 0) return Result.Continue;

            // Check whether the previous line ends with ':'
            int prevLineStart = doc.getLineStartOffset(currentLine - 1);
            int prevLineEnd = doc.getLineEndOffset(currentLine - 1);
            String prevLineText = doc.getText(new TextRange(prevLineStart, prevLineEnd));
            if (!prevLineText.stripTrailing().endsWith(":")) return Result.Continue;

            // Measure the previous line's leading whitespace
            int prevIndent = 0;
            for (char c : prevLineText.toCharArray()) {
                if (c == ' ') prevIndent++;
                else break;
            }
            int targetIndent = prevIndent + 4;

            // Measure current line's existing leading whitespace (IntelliJ may auto-match prev line)
            int curLineStart = doc.getLineStartOffset(currentLine);
            int curLineEnd = doc.getLineEndOffset(currentLine);
            String curLineText = doc.getText(new TextRange(curLineStart, curLineEnd));
            int curIndent = 0;
            for (char c : curLineText.toCharArray()) {
                if (c == ' ') curIndent++;
                else break;
            }

            if (curIndent >= targetIndent) return Result.Continue;

            String extra = " ".repeat(targetIndent - curIndent);
            int insertAt = curLineStart + curIndent;
            WriteCommandAction.runWriteCommandAction(file.getProject(), () -> {
                doc.insertString(insertAt, extra);
                editor.getCaretModel().moveToOffset(insertAt + extra.length());
            });
        } catch (Exception ignored) {
        }
        return Result.Continue;
    }
}
