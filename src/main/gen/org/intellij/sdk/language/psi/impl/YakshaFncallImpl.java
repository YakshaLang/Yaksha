// This is a generated file. Not intended for manual editing.
package org.intellij.sdk.language.psi.impl;

import java.util.List;
import org.jetbrains.annotations.*;
import com.intellij.lang.ASTNode;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiElementVisitor;
import com.intellij.psi.util.PsiTreeUtil;
import static org.intellij.sdk.language.psi.YakshaTypes.*;
import com.intellij.extapi.psi.ASTWrapperPsiElement;
import org.intellij.sdk.language.psi.*;

public class YakshaFncallImpl extends ASTWrapperPsiElement implements YakshaFncall {

  public YakshaFncallImpl(@NotNull ASTNode node) {
    super(node);
  }

  public void accept(@NotNull YakshaVisitor visitor) {
    visitor.visitFncall(this);
  }

  @Override
  public void accept(@NotNull PsiElementVisitor visitor) {
    if (visitor instanceof YakshaVisitor) accept((YakshaVisitor)visitor);
    else super.accept(visitor);
  }

  @Override
  @Nullable
  public YakshaArguments getArguments() {
    return findChildByClass(YakshaArguments.class);
  }

  @Override
  @Nullable
  public YakshaExp getExp() {
    return findChildByClass(YakshaExp.class);
  }

  @Override
  @NotNull
  public YakshaIdentifierExp getIdentifierExp() {
    return findNotNullChildByClass(YakshaIdentifierExp.class);
  }

}
