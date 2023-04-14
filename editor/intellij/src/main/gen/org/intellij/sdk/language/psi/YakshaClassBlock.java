// This is a generated file. Not intended for manual editing.
package org.intellij.sdk.language.psi;

import java.util.List;
import org.jetbrains.annotations.*;
import com.intellij.psi.PsiElement;

public interface YakshaClassBlock extends PsiElement {

  @NotNull
  List<YakshaClassBits> getClassBitsList();

  @Nullable
  YakshaSingleLineClassBits getSingleLineClassBits();

}
