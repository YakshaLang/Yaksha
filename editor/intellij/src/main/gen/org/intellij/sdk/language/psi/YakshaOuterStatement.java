// This is a generated file. Not intended for manual editing.
package org.intellij.sdk.language.psi;

import java.util.List;
import org.jetbrains.annotations.*;
import com.intellij.psi.PsiElement;

public interface YakshaOuterStatement extends PsiElement {

  @NotNull
  List<YakshaAnnotation> getAnnotationList();

  @Nullable
  YakshaClassStatement getClassStatement();

  @Nullable
  YakshaConstStatement getConstStatement();

  @Nullable
  YakshaDefStatement getDefStatement();

  @Nullable
  YakshaImportStatement getImportStatement();

  @Nullable
  YakshaRuntimefeatureStatement getRuntimefeatureStatement();

}
