// This is a generated file. Not intended for manual editing.
package org.intellij.sdk.language.psi.impl;

import java.util.List;
import org.jetbrains.annotations.*;
import com.intellij.lang.ASTNode;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiElementVisitor;
import com.intellij.psi.util.PsiTreeUtil;
import static org.intellij.sdk.language.psi.YakshaTypes.*;
import org.intellij.sdk.language.psi.*;
import com.intellij.navigation.ItemPresentation;

public class YakshaEnumStatementImpl extends YakshaNamedElementImpl implements YakshaEnumStatement {

  public YakshaEnumStatementImpl(@NotNull ASTNode node) {
    super(node);
  }

  public void accept(@NotNull YakshaVisitor visitor) {
    visitor.visitEnumStatement(this);
  }

  @Override
  public void accept(@NotNull PsiElementVisitor visitor) {
    if (visitor instanceof YakshaVisitor) accept((YakshaVisitor)visitor);
    else super.accept(visitor);
  }

  @Override
  @NotNull
  public YakshaEnumBlock getEnumBlock() {
    return findNotNullChildByClass(YakshaEnumBlock.class);
  }

  @Override
  public String getName() {
    return YakshaPsiImplUtil.getName(this);
  }

  @Override
  public PsiElement setName(String newName) {
    return YakshaPsiImplUtil.setName(this, newName);
  }

  @Override
  public PsiElement getNameIdentifier() {
    return YakshaPsiImplUtil.getNameIdentifier(this);
  }

  @Override
  public ItemPresentation getPresentation() {
    return YakshaPsiImplUtil.getPresentation(this);
  }

}
