package org.intellij.sdk.language;

import com.intellij.lang.BracePair;
import com.intellij.lang.PairedBraceMatcher;
import com.intellij.psi.PsiFile;
import com.intellij.psi.tree.IElementType;
import org.intellij.sdk.language.psi.YakshaTypes;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

public class YakshaBraceMatcher implements PairedBraceMatcher {
    private static final BracePair[] PAIRS = {
            new BracePair(YakshaTypes.OPERATOR_OPEN_P, YakshaTypes.OPERATOR_CLOSE_P, true),
            new BracePair(YakshaTypes.OPERATOR_OPEN_SQB, YakshaTypes.OPERATOR_CLOSE_SQB, true),
            new BracePair(YakshaTypes.OPERATOR_CURLY_OPEN, YakshaTypes.OPERATOR_CURLY_CLOSE, true)
    };

    @Override
    public BracePair @NotNull [] getPairs() {
        return PAIRS;
    }

    @Override
    public boolean isPairedBracesAllowedBeforeType(@NotNull IElementType lbraceType, @Nullable IElementType contextType) {
        return true;
    }

    @Override
    public int getCodeConstructStart(PsiFile file, int openingBraceOffset) {
        return openingBraceOffset;
    }
}
