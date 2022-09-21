package org.intellij.sdk.language;

import com.intellij.lexer.FlexLexer;
import com.intellij.psi.tree.IElementType;
import org.intellij.sdk.language.psi.YakshaTokenType;
import org.intellij.sdk.language.psi.YakshaTypes;
import com.intellij.psi.TokenType;

%%

%class YakshaLexer
%implements FlexLexer
%unicode
%function advance
%type IElementType


/* main character classes */
LineTerminator = \r|\n|\r\n
InputCharacter = [^\r\n]

WhiteSpace = {LineTerminator} | [ \t\f]+
Space = [ \t]+
Indentation = ([ ][ ][ ][ ])+
/* comments */
Comment = {Space}* "#" {InputCharacter}* {LineTerminator}?

/* identifiers */
Identifier = [a-zA-Z][a-zA-Z0-9_]*

/* integer literals */
DecIntegerLiteral = 0 | [1-9][0-9]*
DecLongLiteral    = {DecIntegerLiteral} [lL]

HexIntegerLiteral = 0 [xX] 0* {HexDigit} {1,8}
HexLongLiteral    = 0 [xX] 0* {HexDigit} {1,16} [lL]
HexDigit          = [0-9a-fA-F]

OctIntegerLiteral = 0+ [1-3]? {OctDigit} {1,15}
OctLongLiteral    = 0+ 1? {OctDigit} {1,21} [lL]
OctDigit          = [0-7]

/* floating point literals */
FloatLiteral  = ({FLit1}|{FLit2}|{FLit3}) {Exponent}? [fF]
DoubleLiteral = ({FLit1}|{FLit2}|{FLit3}) {Exponent}?

FLit1    = [0-9]+ \. [0-9]*
FLit2    = \. [0-9]+
FLit3    = [0-9]+
Exponent = [eE] [+-]? [0-9]+



// Based on https://upsource.jetbrains.com/idea-ce/file/idea-ce-ea97e292e04f0e52b3310454ab7f29e039bbfb4f/python/python-psi-impl/src/com/jetbrains/python/lexer/Python.flex
SINGLE_QUOTED_STRING=({QUOTED_LITERAL} | {DOUBLE_QUOTED_LITERAL})
TRIPLE_QUOTED_STRING=({TRIPLE_QUOTED_LITERAL}|{TRIPLE_APOS_LITERAL})

QUOTED_LITERAL="'" ([^\\\'\r\n] | {ESCAPE_SEQUENCE} | (\\[\r\n]))* ("'"|\\)?
DOUBLE_QUOTED_LITERAL=\"([^\\\"\r\n]|{ESCAPE_SEQUENCE}|(\\[\r\n]))*?(\"|\\)?
ESCAPE_SEQUENCE=\\[^\r\n]

ANY_ESCAPE_SEQUENCE = \\[^]

THREE_QUO = (\"\"\")
ONE_TWO_QUO = (\"[^\\\"]) | (\"\\[^]) | (\"\"[^\\\"]) | (\"\"\\[^])
QUO_STRING_CHAR = [^\\\"] | {ANY_ESCAPE_SEQUENCE} | {ONE_TWO_QUO}
TRIPLE_QUOTED_LITERAL = {THREE_QUO} {QUO_STRING_CHAR}* {THREE_QUO}?

THREE_APOS = (\'\'\')
ONE_TWO_APOS = ('[^\\']) | ('\\[^]) | (''[^\\']) | (''\\[^])
APOS_STRING_CHAR = [^\\'] | {ANY_ESCAPE_SEQUENCE} | {ONE_TWO_APOS}
TRIPLE_APOS_LITERAL = {THREE_APOS} {APOS_STRING_CHAR}* {THREE_APOS}?

%%

<YYINITIAL> {

  /* keywords */
  "as"                           { return YakshaTypes.KW_AS; }
  "break"                        { return YakshaTypes.KW_BREAK; }
  "class"                        { return YakshaTypes.KW_CLASS; }
  "ccode"                        { return YakshaTypes.KW_CCODE; }
  "continue"                     { return YakshaTypes.KW_CONTINUE; }
  "def"                          { return YakshaTypes.KW_DEF; }
  "del"                          { return YakshaTypes.KW_DEL; }
  "defer"                        { return YakshaTypes.KW_DEFER; }
  "else"                         { return YakshaTypes.KW_ELSE; }
  "if"                           { return YakshaTypes.KW_IF; }
  "elif"                         { return YakshaTypes.KW_ELIF; }
  "import"                       { return YakshaTypes.KW_IMPORT; }
  "pass"                         { return YakshaTypes.KW_PASS; }
  "return"                       { return YakshaTypes.KW_RETURN; }
  "while"                        { return YakshaTypes.KW_WHILE; }
  "True"                         { return YakshaTypes.KW_TRUE; }
  "False"                        { return YakshaTypes.KW_FALSE; }
  "None"                         { return YakshaTypes.KW_NONE; }
  "runtimefeature"               { return YakshaTypes.KW_RUNTIMEFEATURE; }

"int" |
"i8" |
"i16" |
"i32" |
"i64" |
"u8" |
"u16" |
"u32" |
"u64" |
"str" |
"float" |
"bool" |
"f32" |
"f64" { return YakshaTypes.PRIMITIVE_DATA_TYPE; }

  /* operators */
  "("                            { return YakshaTypes.OPERATOR_OPEN_P; }
  ")"                            { return YakshaTypes.OPERATOR_CLOSE_P; }
  "["                            { return YakshaTypes.OPERATOR_OPEN_SQB; }
  "]"                            { return YakshaTypes.OPERATOR_CLOSE_SQB; }
  "->"                            { return YakshaTypes.OPERATOR_ARROW; }
  "+"                            { return YakshaTypes.OPERATOR_PLUS; }
  "-"                            { return YakshaTypes.OPERATOR_MINUS; }
  "*"                            { return YakshaTypes.OPERATOR_MUL; }
  "/"                            { return YakshaTypes.OPERATOR_DIV; }
  "%"                            { return YakshaTypes.OPERATOR_REMAINDER; }

  "<"                            |
  ">"                            |
  "<="                           |
  ">="                           |
  "=="                           |
  "!="                           { return YakshaTypes.OPERATOR_COMPARISON; }

  "@"                              { return YakshaTypes.OPERATOR_AT; }
  ":"                              { return YakshaTypes.OPERATOR_COLON; }
  "."                              { return YakshaTypes.OPERATOR_DOT; }
  ","                              { return YakshaTypes.OPERATOR_COMMA; }

  "="                              { return YakshaTypes.OPERATOR_EQ; }
  "not"                              { return YakshaTypes.OPERATOR_NOT; }
  "or"                              { return YakshaTypes.OPERATOR_OR; }
  "and"                              { return YakshaTypes.OPERATOR_AND; }

//
  /* numeric literals */

  {DecIntegerLiteral}            |
  {DecLongLiteral}               |

  {HexIntegerLiteral}            |
  {HexLongLiteral}               |

  {OctIntegerLiteral}            |
  {OctLongLiteral}               |

  {FloatLiteral}                 |
  {DoubleLiteral}                |
  {FloatLiteral}[jJ]             { return YakshaTypes.NUMBER; }

  /* Strings */
  {SINGLE_QUOTED_STRING}         { return YakshaTypes.STRING; }
  {TRIPLE_QUOTED_STRING}         { return YakshaTypes.STRING; }

  /* comments */
  {Comment}                      { return YakshaTypes.COMMENT; }

  /* whitespace */
  {Indentation}                  { return YakshaTypes.I; }
  {Space}                        { return YakshaTypes.S; }

  /* identifiers */
  {Identifier}                    { return YakshaTypes.IDENTIFIER; }
  {LineTerminator}                {return YakshaTypes.NL; }

}

/* error fallback */
[^]                                 { return TokenType.BAD_CHARACTER;  }



/*
 * Copyright 2022 Bhathiya Perera
 * Copied from https://github.com/nordfalk/jsyntaxpane/blob/master/jsyntaxpane/src/main/jflex/jsyntaxpane/lexers/python.flex
 * Then modified
 * Copyright 2008 Ayman Al-Sairafi ayman.alsairafi@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License
 *       at http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */