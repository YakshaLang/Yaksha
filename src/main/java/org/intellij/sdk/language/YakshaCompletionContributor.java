package org.intellij.sdk.language;

import com.google.common.collect.ImmutableList;
import com.intellij.codeInsight.completion.CompletionContributor;
import com.intellij.codeInsight.completion.CompletionParameters;
import com.intellij.codeInsight.completion.CompletionProvider;
import com.intellij.codeInsight.completion.CompletionResultSet;
import com.intellij.codeInsight.completion.CompletionType;
import com.intellij.codeInsight.lookup.LookupElementBuilder;
import com.intellij.patterns.PlatformPatterns;
import com.intellij.util.ProcessingContext;
import org.intellij.sdk.language.psi.YakshaImportStatement;
import org.intellij.sdk.language.yaksha_docs.YakshaDocs;
import org.jetbrains.annotations.NotNull;

import java.util.List;
import java.util.Map;

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
            .add("import libs.number")
            .add("import libs.number as num")
            .add("import libs.number as n")
            .add("import libs.perlin")
            .add("import libs.random")
            .add("import libs.strings.buffer as sbuf")
            .add("import libs.strings.buffer")
            .add("import libs")
            .add("import libs.c")
            .add("import raylib as rl")
            .add("import raylib")
            .add("import raylib.gl")
            .add("import raylib.gui")
            .add("import raylib.math")
            .add("import raylib.utils")
            .build();


    public YakshaCompletionContributor() {
        extend(CompletionType.BASIC, PlatformPatterns.psiElement(),
                new CompletionProvider<>() {
                    public void addCompletions(@NotNull CompletionParameters parameters,
                                               @NotNull ProcessingContext context,
                                               @NotNull CompletionResultSet resultSet) {
                        boolean filled = false;
                        /*
                         * Provide from docs.json
                         */
                        try {
                            if (parameters.getPosition().getPrevSibling().getPrevSibling().getPrevSibling() == null &&
                                    parameters.getPosition().getPrevSibling().toString().equals("PsiElement(YakshaTokenType.OPERATOR_DOT)")) {
                                // 1) Find what is my identifier
                                final String ident = parameters.getPosition().getPrevSibling().getPrevSibling().getText();
                                // 2) Find all my imports, match with identifier
                                YakshaImportStatement whichImport = null;
                                List<YakshaImportStatement> imps = ExtractUtils.getChildrenOfTypeAsList(parameters.getOriginalFile(), YakshaImportStatement.class);
                                for (YakshaImportStatement i : imps) {
                                    if (ident.equals(i.getName())) {
                                        // Found the import
                                        whichImport = i;
                                        break;
                                    }
                                }
                                // 2) Based on my import match with Loader.INSTANCE.doc fill it now
                                if (whichImport != null) {
                                    filled = YakshaDocs.INSTANCE.fillTo(resultSet, whichImport.getImportPath());
                                }

                            }
                        } catch (Exception ignored) {
                        }

                        if (filled) {
                            return;
                        }
                        /*
                         * Provide standard lib imports
                         */

                        // Imports
                        try {
                            if (parameters.getPosition().getPrevSibling() == null ||
                                    String.valueOf(parameters.getPosition().getPrevSibling().getFirstChild()).equals("YakshaImportStatementImpl(IMPORT_STATEMENT)")) {
                                for (final String imp : IMPORTS) {
                                    resultSet.addElement(
                                            LookupElementBuilder.create(imp).withIcon(YakshaIcons.IMPORT)
                                    );
                                }
                            }
                        } catch (Exception ignored) {
                        }


                        /*
                         * Provide keywords
                         */
                        resultSet.addElement(LookupElementBuilder.create("import").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("as").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("def").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("class").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("ccode").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("if").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("else").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("while").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("break").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("continue").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("del").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("defer").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("return").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("pass").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("True").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("False").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("None").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("and").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("not").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("or").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("@native").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("@nativedefine").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("@nativemacro").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("@varargs").withIcon(YakshaIcons.KEYWORD));
                        resultSet.addElement(LookupElementBuilder.create("@dotaccess").withIcon(YakshaIcons.KEYWORD));

                        resultSet.addElement(LookupElementBuilder.create("Array").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("SMEntry").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("MEntry").withIcon(YakshaIcons.DATA_TYPE));
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
                        resultSet.addElement(LookupElementBuilder.create("float").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("bool").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("f32").withIcon(YakshaIcons.DATA_TYPE));
                        resultSet.addElement(LookupElementBuilder.create("f64").withIcon(YakshaIcons.DATA_TYPE));

                        for (Map.Entry<String, String> e : YakshaDocs.BUILTIN_FUNCTIONS.entrySet()) {
                            resultSet.addElement(LookupElementBuilder.create(e.getKey())
                                    .withIcon(YakshaIcons.BUILT_IN).withTypeText(e.getValue()));
                        }
                    }
                });
    }
}