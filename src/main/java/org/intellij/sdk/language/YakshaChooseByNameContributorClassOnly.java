package org.intellij.sdk.language;

import com.intellij.navigation.ChooseByNameContributor;
import com.intellij.navigation.NavigationItem;
import com.intellij.openapi.project.Project;
import org.intellij.sdk.language.psi.YakshaClassStatement;
import org.intellij.sdk.language.psi.YakshaNamedElement;
import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.List;

public class YakshaChooseByNameContributorClassOnly implements ChooseByNameContributor {

    @Override
    public String @NotNull [] getNames(Project project, boolean includeNonProjectItems) {
        List<String> names = new ArrayList<>();
        List<YakshaClassStatement> classes = YakshaUtil.findClasses(project);
        for (YakshaClassStatement st : classes) {
            if (st.getName() != null && st.getName().length() > 0) {
                names.add(st.getName());
            }
        }
        return names.toArray(new String[names.size()]);
    }

    @Override
    public NavigationItem @NotNull [] getItemsByName(String name, String pattern, Project project, boolean includeNonProjectItems) {
        // TODO: include non project items
        List<YakshaNamedElement> navItems = new ArrayList<>();
        navItems.addAll(YakshaUtil.findClasses(project, name));
        return navItems.toArray(new NavigationItem[navItems.size()]);
    }

}