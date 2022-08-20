// This is a generated file. Not intended for manual editing.
package org.intellij.sdk.language.psi;

import java.util.List;
import org.jetbrains.annotations.*;
import com.intellij.psi.PsiElement;
import com.intellij.navigation.ItemPresentation;

public interface YakshaClassStatement extends YakshaNamedElement {

  @NotNull
  List<YakshaClassBits> getClassBitsList();

  String getName();

  PsiElement setName(String newName);

  //WARNING: getNameIdentifier(...) is skipped
  //matching getNameIdentifier(YakshaClassStatement, ...)
  //methods are not found in YakshaPsiImplUtil

  ItemPresentation getPresentation();

}
