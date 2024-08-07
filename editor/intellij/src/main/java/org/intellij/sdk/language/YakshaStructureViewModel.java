package org.intellij.sdk.language;

import com.intellij.ide.structureView.StructureViewModel;
import com.intellij.ide.structureView.StructureViewModelBase;
import com.intellij.ide.structureView.StructureViewTreeElement;
import com.intellij.ide.util.treeView.smartTree.Sorter;
import com.intellij.openapi.editor.Editor;
import com.intellij.psi.PsiFile;
import org.intellij.sdk.language.psi.*;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

public class YakshaStructureViewModel extends StructureViewModelBase implements
        StructureViewModel.ElementInfoProvider {

    public YakshaStructureViewModel(@Nullable Editor editor, PsiFile psiFile) {
        super(psiFile, editor, new YakshaStructureViewElement(psiFile));
    }

    @NotNull
    public Sorter @NotNull [] getSorters() {
        return new Sorter[]{Sorter.ALPHA_SORTER};
    }


    @Override
    public boolean isAlwaysShowsPlus(StructureViewTreeElement element) {
        return false;
    }

    @Override
    public boolean isAlwaysLeaf(StructureViewTreeElement element) {
        return element.getValue() instanceof YakshaClassField
                || element.getValue() instanceof YakshaDefStatement
                || element.getValue() instanceof YakshaConstStatement
                || element.getValue() instanceof YakshaImportStatement
                || element.getValue() instanceof YakshaEnumField
                || element.getValue() instanceof  YakshaDeclStatement
                ;
    }

    @Override
    protected Class<?> @NotNull [] getSuitableClasses() {
        return new Class[]{YakshaClassStatement.class, YakshaDefStatement.class, YakshaConstStatement.class, YakshaImportStatement.class, YakshaClassField.class,
                YakshaEnumStatement.class, YakshaDeclStatement.class, YakshaEnumField.class};
    }
}