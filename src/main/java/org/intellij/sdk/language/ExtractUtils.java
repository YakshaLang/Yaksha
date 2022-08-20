package org.intellij.sdk.language;

import com.intellij.psi.PsiElement;
import com.intellij.util.ArrayUtil;
import com.intellij.util.SmartList;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.Collections;
import java.util.List;

public class ExtractUtils {

    public static <T extends PsiElement> T @Nullable [] getChildrenOfType(@Nullable PsiElement element, @NotNull Class<T> aClass) {
        if (element == null) return null;
        List<T> result = getChildrenOfTypeAsList(element, aClass);
        return result.isEmpty() ? null : ArrayUtil.toObjectArray(result, aClass);
    }


    public static @NotNull <T extends PsiElement> List<T> getChildrenOfTypeAsList(@Nullable PsiElement element, @NotNull Class<? extends T> aClass) {
        List<T> result = null;
        if (element != null) {
            for (PsiElement child = element.getFirstChild(); child != null; child = child.getNextSibling()) {
                if (aClass.isInstance(child)) {
                    if (result == null) result = new SmartList<>();
                    result.add(aClass.cast(child));
                }
                for (PsiElement grandChild = child.getFirstChild(); grandChild != null; grandChild = grandChild.getNextSibling()) {
                    if (aClass.isInstance(grandChild)) {
                        if (result == null) result = new SmartList<>();
                        result.add(aClass.cast(grandChild));
                    }
                }
            }
        }
        return result != null ? result : Collections.emptyList();
    }
}
