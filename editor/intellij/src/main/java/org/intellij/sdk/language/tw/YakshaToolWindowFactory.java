package org.intellij.sdk.language.tw;

import com.intellij.openapi.project.Project;
import com.intellij.openapi.wm.ToolWindow;
import com.intellij.openapi.wm.ToolWindowFactory;
import com.intellij.ui.content.Content;
import com.intellij.ui.content.ContentFactory;
import org.jetbrains.annotations.NotNull;

public class YakshaToolWindowFactory implements ToolWindowFactory {
    public void createToolWindowContent(@NotNull Project project, @NotNull ToolWindow toolWindow) {
        ExecutableFileStateService service = ExecutableFileStateService.getInstance(project);
        YakshaToolWindow yakshaToolWindow = new YakshaToolWindow(toolWindow, service);
        ContentFactory contentFactory = ContentFactory.SERVICE.getInstance();
        Content content = contentFactory.createContent(yakshaToolWindow.getContent(), "", false);
        toolWindow.getContentManager().addContent(content);
    }
}
