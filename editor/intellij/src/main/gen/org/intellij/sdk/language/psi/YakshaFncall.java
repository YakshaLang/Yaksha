// This is a generated file. Not intended for manual editing.
package org.intellij.sdk.language.psi;

import java.util.List;
import org.jetbrains.annotations.*;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiReference;

public interface YakshaFncall extends PsiElement {

  @NotNull
  List<YakshaArguments> getArgumentsList();

  @NotNull
  List<YakshaExp> getExpList();

  @NotNull
  List<YakshaStructArguments> getStructArgumentsList();

  String getDefOrClassName();

  String getFullName();

  PsiReference getReference();

}
