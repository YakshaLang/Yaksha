package org.intellij.sdk.language.tw;

import com.intellij.openapi.wm.ToolWindow;
import org.intellij.sdk.language.YakshaIcons;
import org.intellij.sdk.language.yaksha_docs.YakshaDocs;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeCellRenderer;
import javax.swing.tree.DefaultTreeModel;
import java.awt.*;
import java.util.concurrent.*;

public class YakshaToolWindow {

    private JPanel myToolWindowContent;
    private JTree documentationTree;
    private JTextField filterText;

    private final Debouncer debouncer = new Debouncer();

    public static class Debouncer {
        private final ScheduledExecutorService scheduler = Executors.newSingleThreadScheduledExecutor();
        private final ConcurrentHashMap<Object, Future<?>> delayedMap = new ConcurrentHashMap<>();

        /**
         * Debounces {@code callable} by {@code delay}, i.e., schedules it to be executed after {@code delay},
         * or cancels its execution if the method is called with the same key within the {@code delay} again.
         */
        public void debounce(final Object key, final Runnable runnable, long delay, TimeUnit unit) {
            final Future<?> prev = delayedMap.put(key, scheduler.schedule(() -> {
                try {
                    runnable.run();
                } finally {
                    delayedMap.remove(key);
                }
            }, delay, unit));
            if (prev != null) {
                prev.cancel(true);
            }
        }

        public void shutdown() {
            scheduler.shutdownNow();
        }
    }

    public YakshaToolWindow(ToolWindow toolWindow) {
        final DefaultTreeCellRenderer renderer = new DefaultTreeCellRenderer() {
            @Override
            public Component getTreeCellRendererComponent(JTree tree, Object value, boolean sel, boolean expanded, boolean leaf, int row, boolean hasFocus) {
                super.getTreeCellRendererComponent(tree, value, sel, expanded, leaf, row, hasFocus);
                final DefaultMutableTreeNode currentNode = (DefaultMutableTreeNode) value;
                if (currentNode.getUserObject() instanceof YakshaDocs.DocWithIcon) {
                    setIcon(((YakshaDocs.DocWithIcon) currentNode.getUserObject()).icon);
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
        documentationTree.setCellRenderer(renderer);
        documentationTree.setShowsRootHandles(true);
        documentationTree.setRootVisible(false);
        renderTree("");
        filterText.getDocument().addDocumentListener(new DocumentListener() {
            public void changedUpdate(DocumentEvent e) {
                handle();
            }

            public void removeUpdate(DocumentEvent e) {
                handle();
            }

            public void insertUpdate(DocumentEvent e) {
                handle();
            }

            public void handle() {
                renderTree(filterText.getText().strip());
            }
        });
    }

    private void renderTree(String filter) {
        debouncer.debounce(Void.class, () -> SwingUtilities.invokeLater(() -> {
            final DefaultMutableTreeNode root = new DefaultMutableTreeNode("Root");
            final DefaultTreeModel treeModel = new DefaultTreeModel(root);
            YakshaDocs.INSTANCE.fillTo(root, filter);
            documentationTree.setModel(null);
            documentationTree.setModel(treeModel);
        }), 50, TimeUnit.MILLISECONDS);

    }

    public JPanel getContent() {
        return myToolWindowContent;
    }

}
