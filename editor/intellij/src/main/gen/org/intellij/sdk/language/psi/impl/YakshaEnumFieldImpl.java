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
import com.intellij.navigation.ItemPresentation;

public class YakshaEnumFieldImpl extends ASTWrapperPsiElement implements YakshaEnumField {

  public YakshaEnumFieldImpl(@NotNull ASTNode node) {
    super(node);
  }

  public void accept(@NotNull YakshaVisitor visitor) {
    visitor.visitEnumField(this);
  }

  @Override
  public void accept(@NotNull PsiElementVisitor visitor) {
    if (visitor instanceof YakshaVisitor) accept((YakshaVisitor)visitor);
    else super.accept(visitor);
  }

  @Override
  @NotNull
  public YakshaEnumFieldWoIndent getEnumFieldWoIndent() {
    return findNotNullChildByClass(YakshaEnumFieldWoIndent.class);
  }

  @Override
  public String getName() {
    return YakshaPsiImplUtil.getName(this);
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
