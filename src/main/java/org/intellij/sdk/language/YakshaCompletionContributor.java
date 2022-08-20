package org.intellij.sdk.language;

import com.google.common.collect.ImmutableList;
import com.intellij.codeInsight.completion.*;
import com.intellij.codeInsight.lookup.LookupElementBuilder;
import com.intellij.patterns.PlatformPatterns;
import com.intellij.util.ProcessingContext;
import org.jetbrains.annotations.NotNull;

import java.util.List;

public class YakshaCompletionContributor extends CompletionContributor {

    private static final List<String> IMPORTS = ImmutableList.<String>builder()
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
                        try {
                            if (String.valueOf(parameters.getPosition().getPrevSibling().getFirstChild()).equals("YakshaImportStatementImpl(IMPORT_STATEMENT)")) {
                                for (final String imp : IMPORTS) {
                                    resultSet.addElement(
                                            LookupElementBuilder.create(imp).withIcon(YakshaIcons.YK)
                                    );
                                }
                            }
                        } catch (NullPointerException ignored) {}
                    }
                }
        );
    }

}