package org.intellij.sdk.language;

import com.intellij.lang.cacheBuilder.DefaultWordsScanner;
import com.intellij.lang.cacheBuilder.WordsScanner;
import com.intellij.lang.findUsages.FindUsagesProvider;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiNamedElement;
import com.intellij.psi.tree.TokenSet;
import org.intellij.sdk.language.psi.YakshaFncall;
import org.intellij.sdk.language.psi.YakshaTypes;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

public class YakshaFindUsagesProvider implements FindUsagesProvider {

  @Nullable
  @Override
  public WordsScanner getWordsScanner() {
    return new DefaultWordsScanner(new YakshaLexerAdapter(),
            TokenSet.create(YakshaTypes.IDENTIFIER),
            TokenSet.create(YakshaTypes.COMMENT),
            TokenSet.create(YakshaTypes.STRING, YakshaTypes.NUMBER),
            TokenSet.EMPTY);
  }

  @Override
  public boolean canFindUsagesFor(@NotNull PsiElement psiElement) {
    return psiElement instanceof PsiNamedElement;
  }

  @Nullable
  @Override
  public String getHelpId(@NotNull PsiElement psiElement) {
    return null;
  }

  @NotNull
  @Override
  public String getType(@NotNull PsiElement element) {
    if (element instanceof YakshaFncall) {
      return "function call";
    } else {
      return "";
    }
  }

  @NotNull
  @Override
  public String getDescriptiveName(@NotNull PsiElement element) {
    if (element instanceof YakshaFncall) {
      final String name = ((YakshaFncall) element).getDefOrClassName();
      return name == null ? "" : name;
    } else {
      return "";
    }
  }

  @NotNull
  @Override
  public String getNodeText(@NotNull PsiElement element, boolean useFullName) {
    if (element instanceof YakshaFncall) {
      final String name = ((YakshaFncall) element).getDefOrClassName();
      return name == null ? "" : name;
    } else {
      return "";
    }
  }

}