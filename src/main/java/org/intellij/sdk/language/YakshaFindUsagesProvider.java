package org.intellij.sdk.language;

import com.intellij.json.JsonBundle;
import com.intellij.lang.HelpID;
import com.intellij.lang.cacheBuilder.DefaultWordsScanner;
import com.intellij.lang.cacheBuilder.WordsScanner;
import com.intellij.lang.findUsages.FindUsagesProvider;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiNamedElement;
import com.intellij.psi.tree.TokenSet;
import org.intellij.sdk.language.psi.YakshaClassStatement;
import org.intellij.sdk.language.psi.YakshaDefStatement;
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
        System.out.println("Can find usages for -> " + psiElement);
        return psiElement instanceof PsiNamedElement;
    }

    @Nullable
    @Override
    public String getHelpId(@NotNull PsiElement psiElement) {
        return HelpID.FIND_OTHER_USAGES;
    }

    @NotNull
    @Override
    public String getType(@NotNull PsiElement element) {
        if (element instanceof YakshaDefStatement) {
            return "Yaksha def";
        }
        if (element instanceof YakshaClassStatement) {
            return "Yaksha class";
        }
        if (element instanceof YakshaFncall) {
            return "Yaksha function call / create class";
        }
        return "";
    }

    @NotNull
    @Override
    public String getDescriptiveName(@NotNull PsiElement element) {
        final String name = element instanceof PsiNamedElement ? ((PsiNamedElement)element).getName() : null;
        return name != null ? name : JsonBundle.message("unnamed.desc");
    }

    @NotNull
    @Override
    public String getNodeText(@NotNull PsiElement element, boolean useFullName) {
        return getDescriptiveName(element);

    }

}