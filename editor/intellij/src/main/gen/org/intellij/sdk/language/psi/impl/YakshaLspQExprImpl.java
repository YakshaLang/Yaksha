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

public class YakshaLspQExprImpl extends ASTWrapperPsiElement implements YakshaLspQExpr {

  public YakshaLspQExprImpl(@NotNull ASTNode node) {
    super(node);
  }

  public void accept(@NotNull YakshaVisitor visitor) {
    visitor.visitLspQExpr(this);
  }

  @Override
  public void accept(@NotNull PsiElementVisitor visitor) {
    if (visitor instanceof YakshaVisitor) accept((YakshaVisitor)visitor);
    else super.accept(visitor);
  }

  @Override
  @NotNull
  public List<YakshaAnyWs> getAnyWsList() {
    return PsiTreeUtil.getChildrenOfTypeAsList(this, YakshaAnyWs.class);
  }

  @Override
  @NotNull
  public List<YakshaLspExpr> getLspExprList() {
    return PsiTreeUtil.getChildrenOfTypeAsList(this, YakshaLspExpr.class);
  }

}
