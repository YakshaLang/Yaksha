package org.intellij.sdk.language;

import com.intellij.openapi.project.Project;
import com.intellij.openapi.vfs.VirtualFile;
import com.intellij.psi.PsiManager;
import com.intellij.psi.search.FileTypeIndex;
import com.intellij.psi.search.GlobalSearchScope;
import com.intellij.psi.util.PsiTreeUtil;
import org.intellij.sdk.language.psi.YakshaClassStatement;
import org.intellij.sdk.language.psi.YakshaConstStatement;
import org.intellij.sdk.language.psi.YakshaDefStatement;
import org.intellij.sdk.language.psi.YakshaFile;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

public class YakshaUtil {

    public static List<YakshaClassStatement> findClasses(Project project, String key) {
        List<YakshaClassStatement> result = new ArrayList<>();
        Collection<VirtualFile> virtualFiles = FileTypeIndex.getFiles(YakaFileType.INSTANCE, GlobalSearchScope.allScope(project));
        for (VirtualFile virtualFile : virtualFiles) {
            YakshaFile yakaFile = (YakshaFile) PsiManager.getInstance(project).findFile(virtualFile);
            if (yakaFile != null) {
                YakshaClassStatement[] statements = ExtractUtils.getChildrenOfType(yakaFile, YakshaClassStatement.class);
                if (statements != null) {
                    for (YakshaClassStatement statement : statements) {
                        if (key.equals(statement.getName())) {
                            result.add(statement);
                        }
                    }
                }
            }
        }
        return result;
    }

    public static List<YakshaClassStatement> findClasses(Project project) {
        List<YakshaClassStatement> result = new ArrayList<>();
        Collection<VirtualFile> virtualFiles = FileTypeIndex.getFiles(YakaFileType.INSTANCE, GlobalSearchScope.allScope(project));
        for (VirtualFile virtualFile : virtualFiles) {
            YakshaFile yakaFile = (YakshaFile) PsiManager.getInstance(project).findFile(virtualFile);
            if (yakaFile != null) {
                YakshaClassStatement[] statements = ExtractUtils.getChildrenOfType(yakaFile, YakshaClassStatement.class);
                if (statements != null) {
                    Collections.addAll(result, statements);
                }
            }
        }
        return result;
    }

    public static List<YakshaDefStatement> findDefs(Project project, String key) {
        List<YakshaDefStatement> result = new ArrayList<>();
        Collection<VirtualFile> virtualFiles = FileTypeIndex.getFiles(YakaFileType.INSTANCE, GlobalSearchScope.allScope(project));
        for (VirtualFile virtualFile : virtualFiles) {
            YakshaFile yakaFile = (YakshaFile) PsiManager.getInstance(project).findFile(virtualFile);
            if (yakaFile != null) {
                YakshaDefStatement[] statements = ExtractUtils.getChildrenOfType(yakaFile, YakshaDefStatement.class);
                if (statements != null) {
                    for (YakshaDefStatement statement : statements) {
                        if (key.equals(statement.getName())) {
                            result.add(statement);
                        }
                    }
                }
            }
        }
        return result;
    }

    public static List<YakshaDefStatement> findDefs(Project project) {
        List<YakshaDefStatement> result = new ArrayList<>();
        Collection<VirtualFile> virtualFiles = FileTypeIndex.getFiles(YakaFileType.INSTANCE, GlobalSearchScope.allScope(project));
        for (VirtualFile virtualFile : virtualFiles) {
            YakshaFile yakaFile = (YakshaFile) PsiManager.getInstance(project).findFile(virtualFile);
            if (yakaFile != null) {
                YakshaDefStatement[] statements = ExtractUtils.getChildrenOfType(yakaFile, YakshaDefStatement.class);
                if (statements != null) {
                    Collections.addAll(result, statements);
                }
            }
        }
        return result;
    }


    public static List<YakshaConstStatement> findConsts(Project project, String key) {
        List<YakshaConstStatement> result = new ArrayList<>();
        Collection<VirtualFile> virtualFiles = FileTypeIndex.getFiles(YakaFileType.INSTANCE, GlobalSearchScope.allScope(project));
        for (VirtualFile virtualFile : virtualFiles) {
            YakshaFile yakaFile = (YakshaFile) PsiManager.getInstance(project).findFile(virtualFile);
            if (yakaFile != null) {
                YakshaConstStatement[] statements = ExtractUtils.getChildrenOfType(yakaFile, YakshaConstStatement.class);
                if (statements != null) {
                    for (YakshaConstStatement statement : statements) {
                        if (key.equals(statement.getName())) {
                            result.add(statement);
                        }
                    }
                }
            }
        }
        return result;
    }

    public static List<YakshaConstStatement> findConsts(Project project) {
        List<YakshaConstStatement> result = new ArrayList<>();
        Collection<VirtualFile> virtualFiles = FileTypeIndex.getFiles(YakaFileType.INSTANCE, GlobalSearchScope.allScope(project));
        for (VirtualFile virtualFile : virtualFiles) {
            YakshaFile yakaFile = (YakshaFile) PsiManager.getInstance(project).findFile(virtualFile);
            if (yakaFile != null) {
                YakshaConstStatement[] statements = ExtractUtils.getChildrenOfType(yakaFile, YakshaConstStatement.class);
                if (statements != null) {
                    Collections.addAll(result, statements);
                }
            }
        }
        return result;
    }

//    public static @NotNull String findDocumentationComment(SimpleProperty property) {
//        List<String> result = new LinkedList<>();
//        PsiElement element = property.getPrevSibling();
//        while (element instanceof PsiComment || element instanceof PsiWhiteSpace) {
//            if (element instanceof PsiComment) {
//                String commentText = element.getText().replaceFirst("[!# ]+", "");
//                result.add(commentText);
//            }
//            element = element.getPrevSibling();
//        }
//        return StringUtil.join(Lists.reverse(result),"\n ");
//    }
}
