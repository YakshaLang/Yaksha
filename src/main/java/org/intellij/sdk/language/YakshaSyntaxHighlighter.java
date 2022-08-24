package org.intellij.sdk.language;

import com.google.common.collect.ImmutableSet;
import com.intellij.lexer.Lexer;
import com.intellij.openapi.editor.DefaultLanguageHighlighterColors;
import com.intellij.openapi.editor.HighlighterColors;
import com.intellij.openapi.editor.colors.TextAttributesKey;
import com.intellij.openapi.fileTypes.SyntaxHighlighterBase;
import com.intellij.psi.TokenType;
import com.intellij.psi.tree.IElementType;
import org.intellij.sdk.language.psi.YakshaTypes;
import org.jetbrains.annotations.NotNull;

import java.util.Set;

import static com.intellij.openapi.editor.colors.TextAttributesKey.createTextAttributesKey;

public class YakshaSyntaxHighlighter extends SyntaxHighlighterBase {

    public static final TextAttributesKey SIGN =
            createTextAttributesKey("YAKSHA_SIGN", DefaultLanguageHighlighterColors.OPERATION_SIGN);
    public static final TextAttributesKey KEYWORD =
            createTextAttributesKey("YAKSHA_KEYWORD", DefaultLanguageHighlighterColors.KEYWORD);
    public static final TextAttributesKey STRING =
            createTextAttributesKey("YAKSHA_STRING", DefaultLanguageHighlighterColors.STRING);

    public static final TextAttributesKey NUMBER =
            createTextAttributesKey("YAKSHA_NUMBER", DefaultLanguageHighlighterColors.NUMBER);

    public static final TextAttributesKey COMMENT =
            createTextAttributesKey("YAKSHA_COMMENT", DefaultLanguageHighlighterColors.LINE_COMMENT);
    public static final TextAttributesKey DATA_TYPE =
            createTextAttributesKey("YAKSHA_DATA_TYPE", DefaultLanguageHighlighterColors.METADATA);

    public static final TextAttributesKey BAD_CHARACTER =
            createTextAttributesKey("YAKSHA_BAD_CHARACTER", HighlighterColors.BAD_CHARACTER);

    private static final TextAttributesKey[] BAD_CHAR_KEYS = new TextAttributesKey[]{BAD_CHARACTER};
    private static final TextAttributesKey[] SIGN_KEYS = new TextAttributesKey[]{SIGN};
    private static final TextAttributesKey[] KEYWORD_KEYS = new TextAttributesKey[]{KEYWORD};
    private static final TextAttributesKey[] STRING_KEYS = new TextAttributesKey[]{STRING};
    private static final TextAttributesKey[] NUMBER_KEYS = new TextAttributesKey[]{NUMBER};
    private static final TextAttributesKey[] COMMENT_KEYS = new TextAttributesKey[]{COMMENT};
    private static final TextAttributesKey[] DATA_KEYS = new TextAttributesKey[]{DATA_TYPE};
    private static final TextAttributesKey[] EMPTY_KEYS = new TextAttributesKey[0];

    private static final Set<IElementType> YK_OPERATORS = ImmutableSet.<IElementType>builder()
            .add(YakshaTypes.OPERATOR_OPEN_P)
            .add(YakshaTypes.OPERATOR_CLOSE_P)
            .add(YakshaTypes.OPERATOR_OPEN_SQB)
            .add(YakshaTypes.OPERATOR_CLOSE_SQB)
            .add(YakshaTypes.OPERATOR_ARROW)
            .add(YakshaTypes.OPERATOR_PLUS)
            .add(YakshaTypes.OPERATOR_MINUS)
            .add(YakshaTypes.OPERATOR_MUL)
            .add(YakshaTypes.OPERATOR_DIV)
            .add(YakshaTypes.OPERATOR_COMPARISON)
            .add(YakshaTypes.OPERATOR_AT)
            .add(YakshaTypes.OPERATOR_COLON)
            .add(YakshaTypes.OPERATOR_DOT)
            .add(YakshaTypes.OPERATOR_COMMA)
            .add(YakshaTypes.OPERATOR_EQ)
            .add(YakshaTypes.OPERATOR_NOT)
            .add(YakshaTypes.OPERATOR_OR)
            .add(YakshaTypes.OPERATOR_AND)
            .build();

    private static final Set<IElementType> YK_KW = ImmutableSet.<IElementType>builder()
            .add(YakshaTypes.KW_AS)
            .add(YakshaTypes.KW_BREAK)
            .add(YakshaTypes.KW_CLASS)
            .add(YakshaTypes.KW_CCODE)
            .add(YakshaTypes.KW_CONTINUE)
            .add(YakshaTypes.KW_DEF)
            .add(YakshaTypes.KW_DEL)
            .add(YakshaTypes.KW_DEFER)
            .add(YakshaTypes.KW_ELSE)
            .add(YakshaTypes.KW_IF)
            .add(YakshaTypes.KW_IMPORT)
            .add(YakshaTypes.KW_PASS)
            .add(YakshaTypes.KW_RETURN)
            .add(YakshaTypes.KW_WHILE)
            .add(YakshaTypes.KW_TRUE)
            .add(YakshaTypes.KW_FALSE)
            .add(YakshaTypes.KW_NONE)
            .build();

    @NotNull
    @Override
    public Lexer getHighlightingLexer() {
        return new YakshaLexerAdapter();
    }

    @Override
    public TextAttributesKey @NotNull [] getTokenHighlights(IElementType tokenType) {
        if (YK_OPERATORS.contains(tokenType)) {
            return SIGN_KEYS;
        }
        if (YK_KW.contains(tokenType)) {
            return KEYWORD_KEYS;
        }
        if (tokenType.equals(YakshaTypes.NUMBER)) {
            return NUMBER_KEYS;
        }
        if (tokenType.equals(YakshaTypes.STRING)) {
            return STRING_KEYS;
        }
        if (tokenType.equals(YakshaTypes.COMMENT)) {
            return COMMENT_KEYS;
        }
        if (tokenType.equals(TokenType.BAD_CHARACTER)) {
            return BAD_CHAR_KEYS;
        }
        if (tokenType.equals(YakshaTypes.PRIMITIVE_DATA_TYPE)) {
            return DATA_KEYS;
        }
        return EMPTY_KEYS;
    }

}