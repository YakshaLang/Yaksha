package org.intellij.sdk.language.psi;

import com.intellij.psi.tree.IElementType;
import org.intellij.sdk.language.YakshaLanguage;
import org.jetbrains.annotations.NonNls;
import org.jetbrains.annotations.NotNull;

public class YakshaElementType extends IElementType {

    public YakshaElementType(@NotNull @NonNls String debugName) {
        super(debugName, YakshaLanguage.INSTANCE);
    }

}