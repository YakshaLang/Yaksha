package org.intellij.sdk.language.psi;

import com.intellij.extapi.psi.PsiFileBase;
import com.intellij.openapi.fileTypes.FileType;
import com.intellij.psi.FileViewProvider;
import org.intellij.sdk.language.YakaFileType;
import org.intellij.sdk.language.YakshaLanguage;
import org.jetbrains.annotations.NotNull;

public class YakshaFile extends PsiFileBase {

    public YakshaFile(@NotNull FileViewProvider viewProvider) {
        super(viewProvider, YakshaLanguage.INSTANCE);
    }

    @NotNull
    @Override
    public FileType getFileType() {
        return YakaFileType.INSTANCE;
    }

    @Override
    public String toString() {
        return "Yaka File";
    }

}