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

public class YakshaDeclStatementImpl extends ASTWrapperPsiElement implements YakshaDeclStatement {

  public YakshaDeclStatementImpl(@NotNull ASTNode node) {
    super(node);
  }

  public void accept(@NotNull YakshaVisitor visitor) {
    visitor.visitDeclStatement(this);
  }

  @Override
  public void accept(@NotNull PsiElementVisitor visitor) {
    if (visitor instanceof YakshaVisitor) accept((YakshaVisitor)visitor);
    else super.accept(visitor);
  }

  @Override
  @NotNull
  public List<YakshaAllAllowedSymbols> getAllAllowedSymbolsList() {
    return PsiTreeUtil.getChildrenOfTypeAsList(this, YakshaAllAllowedSymbols.class);
  }

}
