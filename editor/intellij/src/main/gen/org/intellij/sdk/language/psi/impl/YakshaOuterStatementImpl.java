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

public class YakshaOuterStatementImpl extends ASTWrapperPsiElement implements YakshaOuterStatement {

  public YakshaOuterStatementImpl(@NotNull ASTNode node) {
    super(node);
  }

  public void accept(@NotNull YakshaVisitor visitor) {
    visitor.visitOuterStatement(this);
  }

  @Override
  public void accept(@NotNull PsiElementVisitor visitor) {
    if (visitor instanceof YakshaVisitor) accept((YakshaVisitor)visitor);
    else super.accept(visitor);
  }

  @Override
  @NotNull
  public List<YakshaAnnotation> getAnnotationList() {
    return PsiTreeUtil.getChildrenOfTypeAsList(this, YakshaAnnotation.class);
  }

  @Override
  @Nullable
  public YakshaClassStatement getClassStatement() {
    return findChildByClass(YakshaClassStatement.class);
  }

  @Override
  @Nullable
  public YakshaConstStatement getConstStatement() {
    return findChildByClass(YakshaConstStatement.class);
  }

  @Override
  @Nullable
  public YakshaDefStatement getDefStatement() {
    return findChildByClass(YakshaDefStatement.class);
  }

  @Override
  @Nullable
  public YakshaImportStatement getImportStatement() {
    return findChildByClass(YakshaImportStatement.class);
  }

  @Override
  @Nullable
  public YakshaMacroDeclarationStatement getMacroDeclarationStatement() {
    return findChildByClass(YakshaMacroDeclarationStatement.class);
  }

  @Override
  @Nullable
  public YakshaRuntimefeatureStatement getRuntimefeatureStatement() {
    return findChildByClass(YakshaRuntimefeatureStatement.class);
  }

}
