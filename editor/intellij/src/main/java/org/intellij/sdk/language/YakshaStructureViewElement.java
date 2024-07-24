package org.intellij.sdk.language;

import com.intellij.ide.projectView.PresentationData;
import com.intellij.ide.structureView.StructureViewTreeElement;
import com.intellij.ide.util.treeView.smartTree.SortableTreeElement;
import com.intellij.ide.util.treeView.smartTree.TreeElement;
import com.intellij.navigation.ItemPresentation;
import com.intellij.psi.NavigatablePsiElement;
import org.intellij.sdk.language.psi.*;
import org.intellij.sdk.language.psi.impl.*;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

import java.util.ArrayList;
import java.util.List;

public class YakshaStructureViewElement implements StructureViewTreeElement, SortableTreeElement {

    private final NavigatablePsiElement myElement;

    public YakshaStructureViewElement(NavigatablePsiElement element) {
        this.myElement = element;
    }

    @Override
    public Object getValue() {
        return myElement;
    }

    @Override
    public void navigate(boolean requestFocus) {
        myElement.navigate(requestFocus);
    }

    @Override
    public boolean canNavigate() {
        return myElement.canNavigate();
    }

    @Override
    public boolean canNavigateToSource() {
        return myElement.canNavigateToSource();
    }

    @NotNull
    @Override
    public String getAlphaSortKey() {
        String name = myElement.getName();
        return name != null ? name : "";
    }

    @NotNull
    @Override
    public ItemPresentation getPresentation() {
        ItemPresentation presentation = myElement.getPresentation();
        return presentation != null ? presentation : new PresentationData();
    }

    @Override
    public TreeElement @NotNull [] getChildren() {
        if (myElement instanceof YakshaFile) {
            List<TreeElement> treeElements = new ArrayList<>();

            List<YakshaImportStatement> imps = ExtractUtils.getChildrenOfTypeAsList(myElement, YakshaImportStatement.class);
            for (YakshaImportStatement im : imps) {
                treeElements.add(new YakshaStructureViewElement((YakshaImportStatementImpl) im));
            }

            List<YakshaConstStatement> consts = ExtractUtils.getChildrenOfTypeAsList(myElement, YakshaConstStatement.class);
            for (YakshaConstStatement cn : consts) {
                treeElements.add(new YakshaStructureViewElement((YakshaConstStatementImpl) cn));
            }

            List<YakshaClassStatement> classes = ExtractUtils.getChildrenOfTypeAsList(myElement, YakshaClassStatement.class);
            for (YakshaClassStatement cls : classes) {
                treeElements.add(new YakshaStructureViewElement((YakshaClassStatementImpl) cls));
            }

            List<YakshaDefStatement> defs = ExtractUtils.getChildrenOfTypeAsList(myElement, YakshaDefStatement.class);
            for (YakshaDefStatement def : defs) {
                treeElements.add(new YakshaStructureViewElement((YakshaDefStatementImpl) def));
            }

            List<YakshaEnumStatement> enums = ExtractUtils.getChildrenOfTypeAsList(myElement, YakshaEnumStatement.class);
            for (YakshaEnumStatement en : enums) {
                treeElements.add(new YakshaStructureViewElement((YakshaEnumStatementImpl) en));
            }

            List<YakshaDeclStatement> decls = ExtractUtils.getChildrenOfTypeAsList(myElement, YakshaDeclStatement.class);
            for (YakshaDeclStatement decl : decls) {
                treeElements.add(new YakshaStructureViewElement((YakshaDeclStatementImpl) decl));
            }

            return treeElements.toArray(new TreeElement[0]);
        }
        if (myElement instanceof YakshaClassStatement) {
            List<TreeElement> treeElements = new ArrayList<>();
            YakshaClassStatement st = (YakshaClassStatement) myElement;
            List<YakshaClassBits> bitList = st.getClassBlock().getClassBitsList();
            if (!(bitList == null || bitList.isEmpty())) {
                for (YakshaClassBits bit : bitList) {
                    final YakshaClassField field = bit.getClassField();
                    if (field != null) {
                        treeElements.add(new YakshaStructureViewElement((YakshaClassFieldImpl) field));
                    }
                }
            }
            @Nullable YakshaSingleLineClassBits possibleSingl = st.getClassBlock().getSingleLineClassBits();
            if (possibleSingl != null && possibleSingl.getClassFieldWoIndent() != null) {
                treeElements.add(new YakshaStructureViewElement((YakshaClassFieldWoIndentImpl) possibleSingl.getClassFieldWoIndent()));
            }
            return treeElements.toArray(new TreeElement[0]);
        }
        if (myElement instanceof YakshaEnumStatement) {
            List<TreeElement> treeElements = new ArrayList<>();
            YakshaEnumStatement st = (YakshaEnumStatement) myElement;
            List<YakshaEnumBits> bitList = st.getEnumBlock().getEnumBitsList();
            if (!(bitList == null || bitList.isEmpty())) {
                for (YakshaEnumBits bit : bitList) {
                    final YakshaEnumField field = bit.getEnumField();
                    if (field != null) {
                        treeElements.add(new YakshaStructureViewElement((YakshaEnumFieldImpl) field));
                    }
                }
            }
            return treeElements.toArray(new TreeElement[0]);
        }
        return EMPTY_ARRAY;
    }

}