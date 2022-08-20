package org.intellij.sdk.language.psi;

import org.intellij.sdk.language.YakshaLanguage;
import com.intellij.psi.tree.IElementType;
public class YakshaTokenType extends IElementType {
    public YakshaTokenType(String debugName) {
        super(debugName, YakshaLanguage.INSTANCE);
    }


    @Override
    public String toString() {
        return "YakshaTokenType." + super.toString();
    }
}
