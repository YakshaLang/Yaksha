package org.intellij.sdk.language;

import com.intellij.openapi.fileTypes.LanguageFileType;
import com.intellij.openapi.util.NlsContexts;
import com.intellij.openapi.util.NlsSafe;
import org.jetbrains.annotations.NonNls;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import javax.swing.*;

public class YakaFileType extends LanguageFileType {
    public static final YakaFileType INSTANCE = new YakaFileType();

    private YakaFileType() {
        super(YakshaLanguage.INSTANCE);
    }

    @Override
    public @NonNls @NotNull String getName() {
        return "Yaka File";
    }

    @Override
    public @NlsContexts.Label @NotNull String getDescription() {
        return "Yaksha Programming Language Code File";
    }

    @Override
    public @NlsSafe @NotNull String getDefaultExtension() {
        return "yaka";
    }

    @Override
    public @Nullable Icon getIcon() {
        return YakshaIcons.FILE;
    }
}
