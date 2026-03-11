package org.intellij.sdk.language;

import com.google.common.collect.ImmutableList;
import com.intellij.codeInsight.completion.*;
import com.intellij.codeInsight.lookup.LookupElementBuilder;
import com.intellij.lang.ASTNode;
import com.intellij.openapi.project.Project;
import com.intellij.openapi.vfs.VirtualFile;
import com.intellij.patterns.PlatformPatterns;
import com.intellij.psi.PsiElement;
import com.intellij.psi.PsiFile;
import com.intellij.psi.PsiManager;
import com.intellij.psi.search.FileTypeIndex;
import com.intellij.psi.search.GlobalSearchScope;
import com.intellij.util.ProcessingContext;
import org.intellij.sdk.language.psi.*;
import org.intellij.sdk.language.yaksha_docs.YakshaDocs;
import org.jetbrains.annotations.NotNull;

import java.util.*;

public class YakshaCompletionContributor extends CompletionContributor {
    private static final List<String> IMPORTS = ImmutableList.<String>builder()
            .add("import libs.argparse")
            .add("import libs.strings.array as sarr")
            .add("import libs.strings.array")
            .add("import libs.strings")
            .add("import libs.fileformats.toml")
            .add("import libs.fileformats.ini")
            .add("import libs.console")
            .add("import libs.io")
            .add("import libs.os.path")
            .add("import libs.os.path as ospath")
            .add("import libs.os")
            .add("import libs.mpc")
            .add("import libs.numbers")
            .add("import libs.numbers as num")
            .add("import libs.numbers as n")
            .add("import libs.perlin")
            .add("import libs.random")
            .add("import libs.strings.buffer as sbuf")
            .add("import libs.strings.buffer")
            .add("import libs.strings.utf8")
            .add("import libs.thread")
            .add("import libs.timespec")
            .add("import libs")
            .add("import libs.c")
            .add("import raylib as rl")
            .add("import raylib")
            .add("import raylib.gl")
            .add("import raylib.gui")
            .add("import raylib.math")
            .add("import raylib.utils")
            .add("import w4")
            .build();
    private static final Set<String> PRIMITIVES = new HashSet<>(java.util.Arrays.asList(
            "int", "i8", "i16", "i32", "i64", "u8", "u16", "u32", "u64",
            "float", "f32", "f64", "bool", "str", "sr", "None",
            "Array", "FixedArr", "Tuple", "Ptr", "Function", "In", "Out",
            "Const", "SMEntry", "MEntry"
    ));

    public YakshaCompletionContributor() {
        extend(CompletionType.BASIC, PlatformPatterns.psiElement(),
                new CompletionProvider<>() {
                    public void addCompletions(@NotNull CompletionParameters parameters,
                                               @NotNull ProcessingContext context,
                                               @NotNull CompletionResultSet resultSet) {
                        PsiElement pos = parameters.getPosition();
                        boolean insideDef = isInsideDef(pos);
                        boolean insideMacro = isInsideMacroBlock(pos);
                        Set<String> seen = new HashSet<>();

                        boolean filled = false;
                        try {
                            if (pos.getPrevSibling() != null &&
                                    pos.getPrevSibling().toString().equals("PsiElement(YakshaTokenType.OPERATOR_DOT)") &&
                                    pos.getPrevSibling().getPrevSibling() != null) {
                                final String ident = pos.getPrevSibling().getPrevSibling().getText();
                                YakshaImportStatement whichImport = null;
                                for (YakshaImportStatement i : ExtractUtils.getChildrenOfTypeAsList(parameters.getOriginalFile(), YakshaImportStatement.class)) {
                                    if (ident.equals(i.getName())) {
                                        whichImport = i;
                                        break;
                                    }
                                }
                                if (whichImport != null) {
                                    filled = YakshaDocs.INSTANCE.fillTo(resultSet, whichImport.getImportPath());
                                    if (!filled)
                                        filled = fillFromLocalFile(parameters, resultSet, whichImport.getImportPath());
                                }
                                if (!filled && insideDef) {
                                    String[] parts = ident.split("\\.");
                                    List<String> chain = new ArrayList<>();
                                    for (String p : parts) {
                                        if (!p.isBlank()) chain.add(p);
                                    }
                                    if (!chain.isEmpty()) {
                                        YakshaDefStatement encDef = findEnclosingDef(pos);
                                        String resolvedType = resolveChainType(chain, encDef,
                                                parameters.getOriginalFile(), parameters.getOriginalFile().getProject());
                                        if (resolvedType != null) {
                                            VirtualFile vf = parameters.getOriginalFile().getVirtualFile();
                                            String filePath = vf != null ? vf.getPath() : null;
                                            filled = fillClassMembers(resolvedType,
                                                    parameters.getOriginalFile().getProject(),
                                                    filePath, resultSet, seen);
                                        }
                                    }
                                }
                            }
                        } catch (Exception ignored) {
                        }
                        if (filled) return;

                        /* ── Aliased import completions: alias.symbol for every import ── */
                        if (!insideMacro) {
                            try {
                                List<YakshaImportStatement> imps = ExtractUtils.getChildrenOfTypeAsList(
                                        parameters.getOriginalFile(), YakshaImportStatement.class);
                                for (YakshaImportStatement imp : imps) {
                                    String alias = imp.getName();
                                    String importPath = imp.getImportPath();
                                    if (alias == null || importPath == null) continue;
                                    boolean libFilled = YakshaDocs.INSTANCE.fillToWithAlias(resultSet, alias, importPath);
                                    if (!libFilled) {
                                        fillFromLocalFileWithAlias(parameters, resultSet, alias, importPath);
                                    }
                                }
                            } catch (Exception ignored) {
                            }
                        }

                        if (insideMacro) {
                            for (String e : YakshaDocs.LISP_BUILTIN_NAMES) {
                                resultSet.addElement(LookupElementBuilder.create(e)
                                        .withBoldness(true).withIcon(YakshaIcons.MACRO));
                            }
                            return; // no Yaksha keywords/types in lisp blocks
                        }

                        if (!insideDef) {
                            // Import suggestions
                            try {
                                if (pos.getPrevSibling() == null ||
                                        String.valueOf(pos.getPrevSibling().getFirstChild()).equals("YakshaImportStatementImpl(IMPORT_STATEMENT)")) {
                                    for (final String imp : IMPORTS) {
                                        resultSet.addElement(LookupElementBuilder.create(imp).withIcon(YakshaIcons.IMPORT));
                                    }
                                    addLocalFileImports(parameters, resultSet);
                                }
                            } catch (Exception ignored) {
                            }

                            resultSet.addElement(LookupElementBuilder.create("import").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("as").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("def").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("class").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("struct").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("enum").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("runtimefeature").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("@native").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("@nativedefine").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("@nativemacro").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("@varargs").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("@onstack").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("@template").withIcon(YakshaIcons.KEYWORD));

                            // Complex types (mainly for const/field declarations at top level)
                            resultSet.addElement(LookupElementBuilder.create("Array").withIcon(YakshaIcons.DATA_TYPE));
                            resultSet.addElement(LookupElementBuilder.create("FixedArr").withIcon(YakshaIcons.DATA_TYPE));
                            resultSet.addElement(LookupElementBuilder.create("Tuple").withIcon(YakshaIcons.DATA_TYPE));
                            resultSet.addElement(LookupElementBuilder.create("SMEntry").withIcon(YakshaIcons.DATA_TYPE));
                            resultSet.addElement(LookupElementBuilder.create("MEntry").withIcon(YakshaIcons.DATA_TYPE));
                            resultSet.addElement(LookupElementBuilder.create("Function").withIcon(YakshaIcons.DATA_TYPE));
                            resultSet.addElement(LookupElementBuilder.create("In").withIcon(YakshaIcons.DATA_TYPE));
                            resultSet.addElement(LookupElementBuilder.create("Out").withIcon(YakshaIcons.DATA_TYPE));
                            resultSet.addElement(LookupElementBuilder.create("Const").withIcon(YakshaIcons.DATA_TYPE));
                            resultSet.addElement(LookupElementBuilder.create("Ptr").withIcon(YakshaIcons.DATA_TYPE));
                        }

                        if (insideDef) {
                            // Control flow
                            resultSet.addElement(LookupElementBuilder.create("if").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("elif").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("else").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("while").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("for").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("break").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("continue").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("del").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("defer").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("return").withIcon(YakshaIcons.KEYWORD));
                            resultSet.addElement(LookupElementBuilder.create("ccode").withIcon(YakshaIcons.KEYWORD));

                            // Local variables and parameters
                            try {
                                YakshaDefStatement enclosingDef = findEnclosingDef(pos);
                                if (enclosingDef != null) {
                                    YakshaDefParams defParams = enclosingDef.getDefParams();
                                    if (defParams != null && defParams.getDefParamList() != null) {
                                        for (YakshaDefParam param : defParams.getDefParamList()) {
                                            ASTNode nameNode = param.getNode().findChildByType(YakshaTypes.IDENTIFIER);
                                            if (nameNode != null && !nameNode.getText().isEmpty()) {
                                                addUnique(resultSet, seen, LookupElementBuilder.create(nameNode.getText())
                                                        .withIcon(YakshaIcons.KEYWORD).withTypeText("param"));
                                            }
                                        }
                                    }
                                    collectLocalVars(resultSet, seen, enclosingDef);
                                }
                            } catch (Exception ignored) {
                            }
                        }

                        for (Map.Entry<String, YakshaDocs.BuiltinDoc> e : YakshaDocs.BUILTIN_FUNCTIONS.entrySet()) {
                            resultSet.addElement(LookupElementBuilder.create(e.getKey())
                                    .withIcon(YakshaIcons.BUILT_IN).withTypeText(e.getValue().typeText()));
                        }

                        resultSet.addElement(LookupElementBuilder.create("pass").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("True").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("False").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("None").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("and").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("not").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("or").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("in").withIcon(YakshaIcons.KEYWORD));

                        resultSet.addElement(LookupElementBuilder.create("int").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("i8").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("i16").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("i32").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("i64").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("u8").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("u16").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("u32").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("u64").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("str").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("sr").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("float").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("bool").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("f32").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("f64").withIcon(YakshaIcons.DATA_TYPE));

                        try {
                            PsiFile file = parameters.getOriginalFile();
                            for (YakshaDefStatement def : ExtractUtils.getChildrenOfTypeAsList(file, YakshaDefStatement.class)) {
                                if (def.getName() != null && !def.getName().isEmpty()) {
                                    addUnique(resultSet, seen, LookupElementBuilder.create(def.getName())
                                            .withIcon(YakshaIcons.DEF).withTypeText(file.getName()));
                                }
                            }
                            for (YakshaClassStatement cls : ExtractUtils.getChildrenOfTypeAsList(file, YakshaClassStatement.class)) {
                                if (cls.getName() != null && !cls.getName().isEmpty()) {
                                    addUnique(resultSet, seen, LookupElementBuilder.create(cls.getName())
                                            .withIcon(YakshaIcons.CLASS).withTypeText(file.getName()));
                                }
                            }
                            for (YakshaEnumStatement en : ExtractUtils.getChildrenOfTypeAsList(file, YakshaEnumStatement.class)) {
                                if (en.getName() != null && !en.getName().isEmpty()) {
                                    addUnique(resultSet, seen, LookupElementBuilder.create(en.getName())
                                            .withIcon(YakshaIcons.ENUM).withTypeText(file.getName()));
                                }
                            }
                            for (YakshaConstStatement con : ExtractUtils.getChildrenOfTypeAsList(file, YakshaConstStatement.class)) {
                                if (con.getName() != null && !con.getName().isEmpty()) {
                                    addUnique(resultSet, seen, LookupElementBuilder.create(con.getName())
                                            .withIcon(YakshaIcons.CONSTANT).withTypeText(file.getName()));
                                }
                            }
                        } catch (Exception ignored) {
                        }
                    }
                });
    }

    private static boolean isInsideDef(PsiElement element) {
        return findEnclosingDef(element) != null;
    }

    private static boolean isInsideMacroBlock(PsiElement element) {
        PsiElement cur = element != null ? element.getParent() : null;
        while (cur != null && !(cur instanceof PsiFile)) {
            if (cur instanceof YakshaMacroDeclarationStatement) return true;
            if (cur instanceof YakshaLispBody) return true;
            cur = cur.getParent();
        }
        return false;
    }

    private static YakshaDefStatement findEnclosingDef(PsiElement element) {
        PsiElement cur = element != null ? element.getParent() : null;
        while (cur != null && !(cur instanceof PsiFile)) {
            if (cur instanceof YakshaDefStatement) return (YakshaDefStatement) cur;
            cur = cur.getParent();
        }
        return null;
    }

    private static void collectLocalVars(CompletionResultSet resultSet, Set<String> seen, PsiElement parent) {
        for (PsiElement child = parent.getFirstChild(); child != null; child = child.getNextSibling()) {
            if (child instanceof YakshaLetStatement) {
                ASTNode nameNode = child.getNode().findChildByType(YakshaTypes.IDENTIFIER);
                if (nameNode != null && !nameNode.getText().isEmpty()) {
                    addUnique(resultSet, seen, LookupElementBuilder.create(nameNode.getText())
                            .withIcon(YakshaIcons.KEYWORD).withTypeText("var"));
                }
            } else if (child instanceof YakshaForeachStatement) {
                ASTNode nameNode = child.getNode().findChildByType(YakshaTypes.IDENTIFIER);
                if (nameNode != null && !nameNode.getText().isEmpty()) {
                    addUnique(resultSet, seen, LookupElementBuilder.create(nameNode.getText())
                            .withIcon(YakshaIcons.KEYWORD).withTypeText("var"));
                }
            }
            if (!(child instanceof YakshaDefStatement)) {
                collectLocalVars(resultSet, seen, child);
            }
        }
    }

    private static String getBaseTypeName(YakshaDataType dt) {
        if (dt == null) return null;
        String text = dt.getDataTypeBit().getText();
        if (text == null || text.isBlank() || PRIMITIVES.contains(text)) return null;
        return text;
    }

    private static String resolveVarType(String varName, YakshaDefStatement enclosingDef) {
        if (enclosingDef == null || varName == null) return null;
        YakshaDefParams params = enclosingDef.getDefParams();
        if (params != null && params.getDefParamList() != null) {
            for (YakshaDefParam param : params.getDefParamList()) {
                ASTNode nameNode = param.getNode().findChildByType(YakshaTypes.IDENTIFIER);
                if (nameNode != null && varName.equals(nameNode.getText())) {
                    return getBaseTypeName(param.getDataType());
                }
            }
        }
        return resolveLetType(varName, enclosingDef);
    }

    private static String resolveLetType(String varName, PsiElement parent) {
        for (PsiElement child = parent.getFirstChild(); child != null; child = child.getNextSibling()) {
            if (child instanceof YakshaLetStatement) {
                ASTNode nameNode = child.getNode().findChildByType(YakshaTypes.IDENTIFIER);
                if (nameNode != null && varName.equals(nameNode.getText())) {
                    return getBaseTypeName(((YakshaLetStatement) child).getDataType());
                }
            }
            if (!(child instanceof YakshaDefStatement)) {
                String found = resolveLetType(varName, child);
                if (found != null) return found;
            }
        }
        return null;
    }

    private static String resolveChainType(List<String> chain, YakshaDefStatement enclosingDef,
                                           PsiFile file, com.intellij.openapi.project.Project project) {
        if (chain.isEmpty()) return null;
        String currentType = resolveVarType(chain.get(0), enclosingDef);
        if (currentType == null) return null;
        for (int i = 1; i < chain.size(); i++) {
            String fieldName = chain.get(i);
            String nextType = null;
            for (YakshaClassFieldWoIndent f : collectFieldsForType(currentType, project)) {
                if (fieldName.equals(f.getName())) {
                    nextType = getBaseTypeName(f.getDataType());
                    break;
                }
            }
            if (nextType == null) return null;
            currentType = nextType;
        }
        return currentType;
    }

    private static List<YakshaClassFieldWoIndent> collectFieldsForType(
            String typeName, com.intellij.openapi.project.Project project) {
        if (typeName == null) return Collections.emptyList();
        String simpleName = typeName.contains(".")
                ? typeName.substring(typeName.lastIndexOf('.') + 1)
                : typeName;
        List<YakshaClassStatement> classes = YakshaUtil.findClasses(project, simpleName);
        for (YakshaClassStatement cls : classes) {
            List<YakshaClassFieldWoIndent> fields = collectClassFields(cls);
            if (!fields.isEmpty()) return fields;
        }
        return Collections.emptyList();
    }

    private static List<YakshaClassFieldWoIndent> collectClassFields(YakshaClassStatement cls) {
        List<YakshaClassFieldWoIndent> result = new ArrayList<>();
        try {
            for (YakshaClassBits bits : cls.getClassBlock().getClassBitsList()) {
                if (bits.getClassField() != null) {
                    result.add(bits.getClassField().getClassFieldWoIndent());
                }
            }
            YakshaSingleLineClassBits slb = cls.getClassBlock().getSingleLineClassBits();
            if (slb != null && slb.getClassFieldWoIndent() != null) {
                result.add(slb.getClassFieldWoIndent());
            }
        } catch (Exception ignored) {
        }
        return result;
    }

    private static boolean fillClassMembers(String className,
                                            com.intellij.openapi.project.Project project,
                                            String filePath,
                                            CompletionResultSet resultSet,
                                            Set<String> seen) {
        boolean added = false;

        for (YakshaClassFieldWoIndent f : collectFieldsForType(className, project)) {
            String name = f.getName();
            if (name == null || name.isEmpty()) continue;
            String typeText = f.getDataType() != null ? f.getDataType().getText() : null;
            LookupElementBuilder elem = LookupElementBuilder.create(name).withIcon(YakshaIcons.KEYWORD);
            if (typeText != null) elem = elem.withTypeText(typeText);
            addUnique(resultSet, seen, elem);
            added = true;
        }

        if (!added && filePath != null) {
            Map<String, YakshaDocs.Doc> dumpData = YakshaService.findDumpDataForFile(filePath);
            for (YakshaDocs.Doc doc : dumpData.values()) {
                if (doc.classes == null) continue;
                for (YakshaDocs.Cls cls : doc.classes) {
                    if (!className.equals(cls.name) && !className.endsWith("." + cls.name)) continue;
                    if (cls.members == null) continue;
                    for (YakshaDocs.Param member : cls.members) {
                        if (member.name == null || member.name.isEmpty()) continue;
                        String typeText = member.datatype != null ? member.datatype.toString() : null;
                        LookupElementBuilder elem = LookupElementBuilder.create(member.name)
                                .withIcon(YakshaIcons.KEYWORD);
                        if (typeText != null) elem = elem.withTypeText(typeText);
                        addUnique(resultSet, seen, elem);
                        added = true;
                    }
                    if (added) break;
                }
                if (added) break;
            }
        }

        return added;
    }

    private static void addUnique(CompletionResultSet resultSet, Set<String> seen, LookupElementBuilder elem) {
        if (seen.add(elem.getLookupString())) {
            resultSet.addElement(elem);
        }
    }

    private void addLocalFileImports(@NotNull CompletionParameters parameters,
                                     @NotNull CompletionResultSet resultSet) {
        try {
            VirtualFile currentVF = parameters.getOriginalFile().getVirtualFile();
            if (currentVF == null) return;
            VirtualFile currentDir = currentVF.getParent();
            if (currentDir == null) return;
            String currentDirPath = currentDir.getPath();
            Project project = parameters.getOriginalFile().getProject();

            Collection<VirtualFile> allYakaFiles = FileTypeIndex.getFiles(
                    YakaFileType.INSTANCE, GlobalSearchScope.projectScope(project));
            for (VirtualFile yf : allYakaFiles) {
                if (yf.equals(currentVF)) continue;
                if (yf.getName().startsWith("_")) continue; // skip temp/internal files
                String path = yf.getPath();
                if (!path.startsWith(currentDirPath + "/")) continue;
                String relative = path.substring(currentDirPath.length() + 1);
                if (!relative.endsWith(".yaka")) continue;
                String importPath = relative.substring(0, relative.length() - 5).replace("/", ".");
                String alias = importPath.contains(".")
                        ? importPath.substring(importPath.lastIndexOf('.') + 1)
                        : importPath;
                resultSet.addElement(LookupElementBuilder.create("import " + importPath)
                        .withIcon(YakshaIcons.IMPORT));
                resultSet.addElement(LookupElementBuilder.create("import " + importPath + " as " + alias)
                        .withIcon(YakshaIcons.IMPORT));
            }
        } catch (Exception ignored) {
        }
    }

    private boolean fillFromLocalFile(@NotNull CompletionParameters parameters,
                                      @NotNull CompletionResultSet resultSet,
                                      String importPath) {
        try {
            if (importPath == null || importPath.isEmpty()) return false;
            String filePath = importPath.replace(".", "/") + ".yaka";
            VirtualFile currentFile = parameters.getOriginalFile().getVirtualFile();
            if (currentFile == null) return false;
            VirtualFile currentDir = currentFile.getParent();
            if (currentDir == null) return false;
            VirtualFile targetFile = currentDir.findFileByRelativePath(filePath);
            if (targetFile == null) targetFile = YakshaUtil.findLibsFile(importPath);
            if (targetFile == null) return false;
            YakshaFile yakaFile = (YakshaFile) PsiManager.getInstance(parameters.getOriginalFile().getProject()).findFile(targetFile);
            if (yakaFile == null) return false;

            boolean added = false;
            List<YakshaDefStatement> defs = ExtractUtils.getChildrenOfTypeAsList(yakaFile, YakshaDefStatement.class);
            for (YakshaDefStatement def : defs) {
                if (def.getName() != null && !def.getName().isEmpty()) {
                    resultSet.addElement(LookupElementBuilder.create(def.getName())
                            .withIcon(YakshaIcons.DEF).withTypeText(targetFile.getName()));
                    added = true;
                }
            }
            List<YakshaClassStatement> classes = ExtractUtils.getChildrenOfTypeAsList(yakaFile, YakshaClassStatement.class);
            for (YakshaClassStatement cls : classes) {
                if (cls.getName() != null && !cls.getName().isEmpty()) {
                    resultSet.addElement(LookupElementBuilder.create(cls.getName())
                            .withIcon(YakshaIcons.CLASS).withTypeText(targetFile.getName()));
                    added = true;
                }
            }
            List<YakshaEnumStatement> enums = ExtractUtils.getChildrenOfTypeAsList(yakaFile, YakshaEnumStatement.class);
            for (YakshaEnumStatement en : enums) {
                if (en.getName() != null && !en.getName().isEmpty()) {
                    resultSet.addElement(LookupElementBuilder.create(en.getName())
                            .withIcon(YakshaIcons.ENUM).withTypeText(targetFile.getName()));
                    added = true;
                }
            }
            List<YakshaConstStatement> consts = ExtractUtils.getChildrenOfTypeAsList(yakaFile, YakshaConstStatement.class);
            for (YakshaConstStatement con : consts) {
                if (con.getName() != null && !con.getName().isEmpty()) {
                    resultSet.addElement(LookupElementBuilder.create(con.getName())
                            .withIcon(YakshaIcons.CONSTANT).withTypeText(targetFile.getName()));
                    added = true;
                }
            }
            return added;
        } catch (Exception ignored) {
            return false;
        }
    }

    private void fillFromLocalFileWithAlias(@NotNull CompletionParameters parameters,
                                            @NotNull CompletionResultSet resultSet,
                                            String alias,
                                            String importPath) {
        try {
            if (importPath == null || importPath.isEmpty()) return;
            String filePath = importPath.replace(".", "/") + ".yaka";
            VirtualFile currentFile = parameters.getOriginalFile().getVirtualFile();
            if (currentFile == null) return;
            VirtualFile currentDir = currentFile.getParent();
            if (currentDir == null) return;
            VirtualFile targetFile = currentDir.findFileByRelativePath(filePath);
            if (targetFile == null) targetFile = YakshaUtil.findLibsFile(importPath);
            if (targetFile == null) return;
            YakshaFile yakaFile = (YakshaFile) PsiManager.getInstance(parameters.getOriginalFile().getProject()).findFile(targetFile);
            if (yakaFile == null) return;

            String prefix = alias + ".";
            for (YakshaDefStatement def : ExtractUtils.getChildrenOfTypeAsList(yakaFile, YakshaDefStatement.class)) {
                if (def.getName() != null && !def.getName().isEmpty()) {
                    resultSet.addElement(LookupElementBuilder.create(prefix + def.getName())
                            .withIcon(YakshaIcons.DEF).withTypeText(targetFile.getName()));
                }
            }
            for (YakshaClassStatement cls : ExtractUtils.getChildrenOfTypeAsList(yakaFile, YakshaClassStatement.class)) {
                if (cls.getName() != null && !cls.getName().isEmpty()) {
                    resultSet.addElement(LookupElementBuilder.create(prefix + cls.getName())
                            .withIcon(YakshaIcons.CLASS).withTypeText(targetFile.getName()));
                }
            }
            for (YakshaEnumStatement en : ExtractUtils.getChildrenOfTypeAsList(yakaFile, YakshaEnumStatement.class)) {
                if (en.getName() != null && !en.getName().isEmpty()) {
                    resultSet.addElement(LookupElementBuilder.create(prefix + en.getName())
                            .withIcon(YakshaIcons.ENUM).withTypeText(targetFile.getName()));
                }
            }
            for (YakshaConstStatement con : ExtractUtils.getChildrenOfTypeAsList(yakaFile, YakshaConstStatement.class)) {
                if (con.getName() != null && !con.getName().isEmpty()) {
                    resultSet.addElement(LookupElementBuilder.create(prefix + con.getName())
                            .withIcon(YakshaIcons.CONSTANT).withTypeText(targetFile.getName()));
                }
            }
        } catch (Exception ignored) {
        }
    }
}