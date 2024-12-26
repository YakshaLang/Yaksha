package org.intellij.sdk.language.tw;

import com.intellij.openapi.ui.Messages;
import com.intellij.openapi.wm.ToolWindow;
import org.intellij.sdk.language.YakshaIcons;
import org.intellij.sdk.language.yaksha_docs.YakshaDocs;
import org.jetbrains.annotations.NotNull;

import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeCellRenderer;
import javax.swing.tree.DefaultTreeModel;
import java.awt.*;
import java.io.File;
import java.util.Locale;
import java.util.concurrent.*;

public class YakshaToolWindow {
    public static String YAKSHA_EXE_PATH = "";
    private JPanel myToolWindowContent;
    private JTree documentationTree;
    private JTextField filterText;
    private JButton setYakshaCompilerPathButton;

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

    public YakshaToolWindow(ToolWindow toolWindow, ExecutableFileStateService service) {
        final var state = service.getState();
        if (state != null) {
            final var path = state.getExecutableFilePath();
            if (path != null && !path.isBlank()) {
                YAKSHA_EXE_PATH = path; // Set current path when the tool window is opened
            }
        }
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

        setYakshaCompilerPathButton.addActionListener(e -> onSelectFileButtonClicked(service));
    }

    private void onSelectFileButtonClicked(ExecutableFileStateService service) {
        final var fileChooser = getExePicker();
        int returnValue = fileChooser.showOpenDialog(myToolWindowContent);
        if (returnValue == JFileChooser.APPROVE_OPTION) {
            File selectedFile = fileChooser.getSelectedFile();
            String filePath = selectedFile.getAbsolutePath();
            assert service.getState() != null;
            service.getState().setExecutableFilePath(filePath);
            YAKSHA_EXE_PATH = filePath;
            Messages.showMessageDialog("Set compiler path: " + filePath, "Information", Messages.getInformationIcon());
        }
    }

    private static @NotNull JFileChooser getExePicker() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setDialogTitle("Select Executable File");
        fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
        fileChooser.setFileFilter(new javax.swing.filechooser.FileFilter() {
            @Override
            public boolean accept(File f) {
                return f.isDirectory() || (f.isFile() && f.canExecute() && f.getName().toLowerCase(Locale.ROOT).startsWith("yaksha"));
            }

            @Override
            public String getDescription() {
                return "Yaksha executable";
            }
        });
        return fileChooser;
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
