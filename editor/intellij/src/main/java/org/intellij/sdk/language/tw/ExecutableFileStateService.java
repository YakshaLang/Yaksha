package org.intellij.sdk.language.tw;

import com.intellij.openapi.components.PersistentStateComponent;
import com.intellij.openapi.components.Service;
import com.intellij.openapi.components.State;
import com.intellij.openapi.components.Storage;
import com.intellij.openapi.project.Project;
import org.jetbrains.annotations.NotNull;
import org.jetbrains.annotations.Nullable;

@State(
        name = "ExecutableFileStateService",
        storages = @Storage("ExecutableFileStateService.xml")
)
@Service
public final class ExecutableFileStateService implements PersistentStateComponent<ExecutableFileState> {

    private ExecutableFileState state = new ExecutableFileState();

    @Nullable
    @Override
    public ExecutableFileState getState() {
        return state;
    }

    @Override
    public void loadState(@NotNull ExecutableFileState state) {
        this.state = state;
    }

    public static ExecutableFileStateService getInstance(Project project) {
        return project.getService(ExecutableFileStateService.class);
    }
}
