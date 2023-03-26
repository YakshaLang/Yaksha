package org.intellij.sdk.language.tw;

import com.intellij.openapi.wm.ToolWindow;
import org.intellij.sdk.language.YakshaIcons;
import org.intellij.sdk.language.yaksha_docs.YakshaDocs;

import javax.swing.*;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeCellRenderer;
import javax.swing.tree.DefaultTreeModel;
import java.awt.*;

public class YakshaToolWindow {

    private JPanel myToolWindowContent;
    private JTree documentationTree;

    public YakshaToolWindow(ToolWindow toolWindow) {
        final DefaultMutableTreeNode root = new DefaultMutableTreeNode("Root");
        final DefaultTreeModel treeModel = new DefaultTreeModel(root);
        YakshaDocs.INSTANCE.fillTo(root);
        final DefaultTreeCellRenderer renderer = new DefaultTreeCellRenderer() {
            @Override
            public Component getTreeCellRendererComponent(JTree tree, Object value, boolean sel, boolean expanded, boolean leaf, int row, boolean hasFocus) {
                super.getTreeCellRendererComponent(tree, value, sel, expanded, leaf, row, hasFocus);
                final DefaultMutableTreeNode currentNode = (DefaultMutableTreeNode) value;
                if (currentNode.getUserObject() instanceof YakshaDocs.DocWithIcon) {
                    setIcon(((YakshaDocs.DocWithIcon)currentNode.getUserObject()).icon);
                } else if (tree.getModel().getRoot().equals(currentNode)) {
                    setIcon(YakshaIcons.FILE);
                } else if (currentNode.getChildCount() > 0) {
                    setIcon(YakshaIcons.FILE);
                } else {
                    setIcon(YakshaIcons.BUILT_IN);
                }
                return this;
            }
        };
        documentationTree.setModel(treeModel);
        documentationTree.setCellRenderer(renderer);
        documentationTree.setShowsRootHandles(true);
        documentationTree.setRootVisible(false);
    }

    public JPanel getContent() {
        return myToolWindowContent;
    }

}
