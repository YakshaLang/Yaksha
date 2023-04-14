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

public class YakshaSingleLineDefBitsImpl extends ASTWrapperPsiElement implements YakshaSingleLineDefBits {

  public YakshaSingleLineDefBitsImpl(@NotNull ASTNode node) {
    super(node);
  }

  public void accept(@NotNull YakshaVisitor visitor) {
    visitor.visitSingleLineDefBits(this);
  }

  @Override
  public void accept(@NotNull PsiElementVisitor visitor) {
    if (visitor instanceof YakshaVisitor) accept((YakshaVisitor)visitor);
    else super.accept(visitor);
  }

  @Override
  @Nullable
  public YakshaAssignmentStatementWoIndent getAssignmentStatementWoIndent() {
    return findChildByClass(YakshaAssignmentStatementWoIndent.class);
  }

  @Override
  @Nullable
  public YakshaCcodeStatementWoIndent getCcodeStatementWoIndent() {
    return findChildByClass(YakshaCcodeStatementWoIndent.class);
  }

  @Override
  @Nullable
  public YakshaDeferStatementWoIndent getDeferStatementWoIndent() {
    return findChildByClass(YakshaDeferStatementWoIndent.class);
  }

  @Override
  @Nullable
  public YakshaDelStatementWoIndent getDelStatementWoIndent() {
    return findChildByClass(YakshaDelStatementWoIndent.class);
  }

  @Override
  @Nullable
  public YakshaExprStatementWoIndent getExprStatementWoIndent() {
    return findChildByClass(YakshaExprStatementWoIndent.class);
  }

  @Override
  @Nullable
  public YakshaPassStatementWoIndent getPassStatementWoIndent() {
    return findChildByClass(YakshaPassStatementWoIndent.class);
  }

  @Override
  @Nullable
  public YakshaReturnStatementWoIndent getReturnStatementWoIndent() {
    return findChildByClass(YakshaReturnStatementWoIndent.class);
  }

}
