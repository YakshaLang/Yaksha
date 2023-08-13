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

public class YakshaDefBitsImpl extends ASTWrapperPsiElement implements YakshaDefBits {

  public YakshaDefBitsImpl(@NotNull ASTNode node) {
    super(node);
  }

  public void accept(@NotNull YakshaVisitor visitor) {
    visitor.visitDefBits(this);
  }

  @Override
  public void accept(@NotNull PsiElementVisitor visitor) {
    if (visitor instanceof YakshaVisitor) accept((YakshaVisitor)visitor);
    else super.accept(visitor);
  }

  @Override
  @Nullable
  public YakshaAssignmentStatement getAssignmentStatement() {
    return findChildByClass(YakshaAssignmentStatement.class);
  }

  @Override
  @Nullable
  public YakshaBreakStatement getBreakStatement() {
    return findChildByClass(YakshaBreakStatement.class);
  }

  @Override
  @Nullable
  public YakshaCcodeStatement getCcodeStatement() {
    return findChildByClass(YakshaCcodeStatement.class);
  }

  @Override
  @Nullable
  public YakshaContinueStatement getContinueStatement() {
    return findChildByClass(YakshaContinueStatement.class);
  }

  @Override
  @Nullable
  public YakshaDeferStatement getDeferStatement() {
    return findChildByClass(YakshaDeferStatement.class);
  }

  @Override
  @Nullable
  public YakshaDelStatement getDelStatement() {
    return findChildByClass(YakshaDelStatement.class);
  }

  @Override
  @Nullable
  public YakshaDslInnerBlock getDslInnerBlock() {
    return findChildByClass(YakshaDslInnerBlock.class);
  }

  @Override
  @Nullable
  public YakshaElifStatement getElifStatement() {
    return findChildByClass(YakshaElifStatement.class);
  }

  @Override
  @Nullable
  public YakshaElseStatement getElseStatement() {
    return findChildByClass(YakshaElseStatement.class);
  }

  @Override
  @Nullable
  public YakshaEmptyLine getEmptyLine() {
    return findChildByClass(YakshaEmptyLine.class);
  }

  @Override
  @Nullable
  public YakshaExprStatement getExprStatement() {
    return findChildByClass(YakshaExprStatement.class);
  }

  @Override
  @Nullable
  public YakshaForeachStatement getForeachStatement() {
    return findChildByClass(YakshaForeachStatement.class);
  }

  @Override
  @Nullable
  public YakshaForendlessStatement getForendlessStatement() {
    return findChildByClass(YakshaForendlessStatement.class);
  }

  @Override
  @Nullable
  public YakshaIfStatement getIfStatement() {
    return findChildByClass(YakshaIfStatement.class);
  }

  @Override
  @Nullable
  public YakshaLetStatement getLetStatement() {
    return findChildByClass(YakshaLetStatement.class);
  }

  @Override
  @Nullable
  public YakshaPassStatement getPassStatement() {
    return findChildByClass(YakshaPassStatement.class);
  }

  @Override
  @Nullable
  public YakshaReturnStatement getReturnStatement() {
    return findChildByClass(YakshaReturnStatement.class);
  }

  @Override
  @Nullable
  public YakshaWhileStatement getWhileStatement() {
    return findChildByClass(YakshaWhileStatement.class);
  }

}
