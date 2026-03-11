package org.intellij.sdk.language;

import com.intellij.openapi.project.Project;
import com.intellij.openapi.vfs.LocalFileSystem;
import com.intellij.openapi.vfs.VirtualFile;
import com.intellij.psi.PsiManager;
import com.intellij.psi.search.FileTypeIndex;
import com.intellij.psi.search.GlobalSearchScope;
import org.intellij.sdk.language.psi.*;
import org.intellij.sdk.language.tw.YakshaToolWindow;
import org.jetbrains.annotations.Nullable;

import java.nio.file.Paths;
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

    public static List<YakshaEnumStatement> findEnums(Project project) {
        List<YakshaEnumStatement> result = new ArrayList<>();
        Collection<VirtualFile> virtualFiles = FileTypeIndex.getFiles(YakaFileType.INSTANCE, GlobalSearchScope.allScope(project));
        for (VirtualFile virtualFile : virtualFiles) {
            YakshaFile yakaFile = (YakshaFile) PsiManager.getInstance(project).findFile(virtualFile);
            if (yakaFile != null) {
                YakshaEnumStatement[] statements = ExtractUtils.getChildrenOfType(yakaFile, YakshaEnumStatement.class);
                if (statements != null) {
                    Collections.addAll(result, statements);
                }
            }
        }
        return result;
    }

    public static List<YakshaEnumStatement> findEnums(Project project, String key) {
        List<YakshaEnumStatement> result = new ArrayList<>();
        Collection<VirtualFile> virtualFiles = FileTypeIndex.getFiles(YakaFileType.INSTANCE, GlobalSearchScope.allScope(project));
        for (VirtualFile virtualFile : virtualFiles) {
            YakshaFile yakaFile = (YakshaFile) PsiManager.getInstance(project).findFile(virtualFile);
            if (yakaFile != null) {
                YakshaEnumStatement[] statements = ExtractUtils.getChildrenOfType(yakaFile, YakshaEnumStatement.class);
                if (statements != null) {
                    for (YakshaEnumStatement statement : statements) {
                        if (key.equals(statement.getName())) {
                            result.add(statement);
                        }
                    }
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

    /**
     * Returns the root directory where yaksha standard library .yaka files live,
     * derived from the configured yaksha binary path (binary_dir/../libs).
     * Returns null if the binary path is not configured.
     */
    @Nullable
    public static java.nio.file.Path getLibsRoot() {
        String exe = YakshaToolWindow.YAKSHA_EXE_PATH;
        if (exe == null || exe.isBlank()) return null;
        try {
            java.nio.file.Path binDir = Paths.get(exe).getParent();
            if (binDir == null) return null;
            return binDir.resolve("../libs").normalize();
        } catch (Exception ignored) {
            return null;
        }
    }

    /**
     * Finds a .yaka file in the yaksha standard library directory for a dotted import path.
     * E.g. "libs.strings" -> <libs_root>/libs/strings.yaka
     */
    @Nullable
    public static VirtualFile findLibsFile(String importPath) {
        java.nio.file.Path libsRoot = getLibsRoot();
        if (libsRoot == null || importPath == null || importPath.isEmpty()) return null;
        try {
            java.nio.file.Path yakaPath = libsRoot.resolve(importPath.replace(".", "/") + ".yaka");
            return LocalFileSystem.getInstance().findFileByNioFile(yakaPath);
        } catch (Exception ignored) {
            return null;
        }
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
