package org.intellij.sdk.language.psi;

import com.intellij.psi.tree.IElementType;
import org.intellij.sdk.language.YakshaLanguage;

public class YakshaTokenType extends IElementType {
    public YakshaTokenType(String debugName) {
        super(debugName, YakshaLanguage.INSTANCE);
    }


    @Override
    public String toString() {
        return "YakshaTokenType." + super.toString();
    }
}
