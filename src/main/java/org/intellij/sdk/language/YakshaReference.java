package org.intellij.sdk.language;


import com.intellij.codeInsight.lookup.LookupElement;
import com.intellij.codeInsight.lookup.LookupElementBuilder;
import com.intellij.openapi.project.Project;
import com.intellij.openapi.util.TextRange;
import com.intellij.psi.*;
import org.intellij.sdk.language.psi.YakshaClassStatement;
import org.intellij.sdk.language.psi.YakshaDefStatement;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.ArrayList;
import java.util.List;

public class YakshaReference extends PsiReferenceBase<PsiElement> implements PsiPolyVariantReference {

  private final String key;

  public YakshaReference(@NotNull PsiElement element, TextRange textRange) {
    super(element, textRange);
    key = element.getText().substring(textRange.getStartOffset(), textRange.getEndOffset());
  }

  @Override
  public ResolveResult @NotNull [] multiResolve(boolean incompleteCode) {
    Project project = myElement.getProject();
    final List<YakshaDefStatement> properties = YakshaUtil.findDefs(project, key);
    List<ResolveResult> results = new ArrayList<>();
    for (YakshaDefStatement st : properties) {
      results.add(new PsiElementResolveResult(st));
    }
    return results.toArray(new ResolveResult[results.size()]);
  }

  @Nullable
  @Override
  public PsiElement resolve() {
    ResolveResult[] resolveResults = multiResolve(false);
    return resolveResults.length == 1 ? resolveResults[0].getElement() : null;
  }

  @Override
  public Object @NotNull [] getVariants() {
    Project project = myElement.getProject();
    List<LookupElement> variants = new ArrayList<>();

    // Functions
    List<YakshaDefStatement> defs = YakshaUtil.findDefs(project);
    for (final YakshaDefStatement st : defs) {
      if (st.getName() != null && st.getName().length() > 0) {
        variants.add(LookupElementBuilder
                .create(st).withIcon(YakshaIcons.D)
                .withTypeText(st.getContainingFile().getName())
        );
      }
    }

    // Classes
    List<YakshaClassStatement> classes = YakshaUtil.findClasses(project);
    for (final YakshaClassStatement st : classes) {
      if (st.getName() != null && st.getName().length() > 0) {
        variants.add(LookupElementBuilder
                .create(st).withIcon(YakshaIcons.C)
                .withTypeText(st.getContainingFile().getName())
        );
      }
    }


    return variants.toArray();
  }

}