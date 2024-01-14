// This is a generated file. Not intended for manual editing.
package org.intellij.sdk.language.parser;

import com.intellij.lang.PsiBuilder;
import com.intellij.lang.PsiBuilder.Marker;
import static org.intellij.sdk.language.psi.YakshaTypes.*;
import static org.intellij.sdk.language.parser.YakshaParserUtil.*;
import com.intellij.psi.tree.IElementType;
import com.intellij.lang.ASTNode;
import com.intellij.psi.tree.TokenSet;
import com.intellij.lang.PsiParser;
import com.intellij.lang.LightPsiParser;

@SuppressWarnings({"SimplifiableIfStatement", "UnusedAssignment"})
public class YakshaParser implements PsiParser, LightPsiParser {

  public ASTNode parse(IElementType t, PsiBuilder b) {
    parseLight(t, b);
    return b.getTreeBuilt();
  }

  public void parseLight(IElementType t, PsiBuilder b) {
    boolean r;
    b = adapt_builder_(t, b, this, null);
    Marker m = enter_section_(b, 0, _COLLAPSE_, null);
    r = parse_root_(t, b);
    exit_section_(b, 0, m, t, r, true, TRUE_CONDITION);
  }

  protected boolean parse_root_(IElementType t, PsiBuilder b) {
    return parse_root_(t, b, 0);
  }

  static boolean parse_root_(IElementType t, PsiBuilder b, int l) {
    return yakshaFile(b, l + 1);
  }

  /* ********************************************************** */
  // IDENTIFIER | STRING | NUMBER | OPERATOR_COMPARISON | OPERATOR_AT | OPERATOR_COLON | OPERATOR_DOT | OPERATOR_COMMA | OPERATOR_EQ | OPERATOR_PLUS_EQ | OPERATOR_MINUS_EQ | OPERATOR_MUL_EQ | OPERATOR_DIV_EQ | OPERATOR_REMAINDER_EQ | OPERATOR_SHL_EQ | OPERATOR_SHR_EQ | OPERATOR_B_AND_EQ | OPERATOR_B_OR_EQ | OPERATOR_B_XOR_EQ | OPERATOR_NOT | OPERATOR_B_NOT | OPERATOR_OR | OPERATOR_AND | OPERATOR_ARROW | OPERATOR_PLUS | OPERATOR_MINUS | OPERATOR_MUL | OPERATOR_DIV | OPERATOR_REMAINDER | OPERATOR_SHL | OPERATOR_SHR | OPERATOR_B_AND | OPERATOR_B_OR | OPERATOR_B_XOR | PRIMITIVE_DATA_TYPE | KW_AS | KW_BREAK | KW_CLASS | KW_STRUCT | KW_CCODE | KW_CONTINUE | KW_DEF | KW_DEL | KW_DEFER | KW_ELSE | KW_IF | KW_ELIF | KW_IMPORT | KW_PASS | KW_RETURN | KW_WHILE | KW_TRUE | KW_FALSE | KW_NONE | KW_RUNTIMEFEATURE | KW_FOR | KW_IN | KW_MACROS
  public static boolean all_allowed_symbols(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "all_allowed_symbols")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, ALL_ALLOWED_SYMBOLS, "<all allowed symbols>");
    r = consumeToken(b, IDENTIFIER);
    if (!r) r = consumeToken(b, STRING);
    if (!r) r = consumeToken(b, NUMBER);
    if (!r) r = consumeToken(b, OPERATOR_COMPARISON);
    if (!r) r = consumeToken(b, OPERATOR_AT);
    if (!r) r = consumeToken(b, OPERATOR_COLON);
    if (!r) r = consumeToken(b, OPERATOR_DOT);
    if (!r) r = consumeToken(b, OPERATOR_COMMA);
    if (!r) r = consumeToken(b, OPERATOR_EQ);
    if (!r) r = consumeToken(b, OPERATOR_PLUS_EQ);
    if (!r) r = consumeToken(b, OPERATOR_MINUS_EQ);
    if (!r) r = consumeToken(b, OPERATOR_MUL_EQ);
    if (!r) r = consumeToken(b, OPERATOR_DIV_EQ);
    if (!r) r = consumeToken(b, OPERATOR_REMAINDER_EQ);
    if (!r) r = consumeToken(b, OPERATOR_SHL_EQ);
    if (!r) r = consumeToken(b, OPERATOR_SHR_EQ);
    if (!r) r = consumeToken(b, OPERATOR_B_AND_EQ);
    if (!r) r = consumeToken(b, OPERATOR_B_OR_EQ);
    if (!r) r = consumeToken(b, OPERATOR_B_XOR_EQ);
    if (!r) r = consumeToken(b, OPERATOR_NOT);
    if (!r) r = consumeToken(b, OPERATOR_B_NOT);
    if (!r) r = consumeToken(b, OPERATOR_OR);
    if (!r) r = consumeToken(b, OPERATOR_AND);
    if (!r) r = consumeToken(b, OPERATOR_ARROW);
    if (!r) r = consumeToken(b, OPERATOR_PLUS);
    if (!r) r = consumeToken(b, OPERATOR_MINUS);
    if (!r) r = consumeToken(b, OPERATOR_MUL);
    if (!r) r = consumeToken(b, OPERATOR_DIV);
    if (!r) r = consumeToken(b, OPERATOR_REMAINDER);
    if (!r) r = consumeToken(b, OPERATOR_SHL);
    if (!r) r = consumeToken(b, OPERATOR_SHR);
    if (!r) r = consumeToken(b, OPERATOR_B_AND);
    if (!r) r = consumeToken(b, OPERATOR_B_OR);
    if (!r) r = consumeToken(b, OPERATOR_B_XOR);
    if (!r) r = consumeToken(b, PRIMITIVE_DATA_TYPE);
    if (!r) r = consumeToken(b, KW_AS);
    if (!r) r = consumeToken(b, KW_BREAK);
    if (!r) r = consumeToken(b, KW_CLASS);
    if (!r) r = consumeToken(b, KW_STRUCT);
    if (!r) r = consumeToken(b, KW_CCODE);
    if (!r) r = consumeToken(b, KW_CONTINUE);
    if (!r) r = consumeToken(b, KW_DEF);
    if (!r) r = consumeToken(b, KW_DEL);
    if (!r) r = consumeToken(b, KW_DEFER);
    if (!r) r = consumeToken(b, KW_ELSE);
    if (!r) r = consumeToken(b, KW_IF);
    if (!r) r = consumeToken(b, KW_ELIF);
    if (!r) r = consumeToken(b, KW_IMPORT);
    if (!r) r = consumeToken(b, KW_PASS);
    if (!r) r = consumeToken(b, KW_RETURN);
    if (!r) r = consumeToken(b, KW_WHILE);
    if (!r) r = consumeToken(b, KW_TRUE);
    if (!r) r = consumeToken(b, KW_FALSE);
    if (!r) r = consumeToken(b, KW_NONE);
    if (!r) r = consumeToken(b, KW_RUNTIMEFEATURE);
    if (!r) r = consumeToken(b, KW_FOR);
    if (!r) r = consumeToken(b, KW_IN);
    if (!r) r = consumeToken(b, KW_MACROS);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  /* ********************************************************** */
  // OPERATOR_AT IDENTIFIER annotation_arg? S? NL
  public static boolean annotation(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "annotation")) return false;
    if (!nextTokenIs(b, OPERATOR_AT)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, OPERATOR_AT, IDENTIFIER);
    r = r && annotation_2(b, l + 1);
    r = r && annotation_3(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, ANNOTATION, r);
    return r;
  }

  // annotation_arg?
  private static boolean annotation_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "annotation_2")) return false;
    annotation_arg(b, l + 1);
    return true;
  }

  // S?
  private static boolean annotation_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "annotation_3")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // S? OPERATOR_OPEN_P S? STRING S? OPERATOR_CLOSE_P
  public static boolean annotation_arg(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "annotation_arg")) return false;
    if (!nextTokenIs(b, "<annotation arg>", OPERATOR_OPEN_P, S)) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, ANNOTATION_ARG, "<annotation arg>");
    r = annotation_arg_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_OPEN_P);
    r = r && annotation_arg_2(b, l + 1);
    r = r && consumeToken(b, STRING);
    r = r && annotation_arg_4(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CLOSE_P);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // S?
  private static boolean annotation_arg_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "annotation_arg_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean annotation_arg_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "annotation_arg_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean annotation_arg_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "annotation_arg_4")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // (I | S | NL)+
  public static boolean any_ws(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "any_ws")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, ANY_WS, "<any ws>");
    r = any_ws_0(b, l + 1);
    while (r) {
      int c = current_position_(b);
      if (!any_ws_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "any_ws", c)) break;
    }
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // I | S | NL
  private static boolean any_ws_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "any_ws_0")) return false;
    boolean r;
    r = consumeToken(b, I);
    if (!r) r = consumeToken(b, S);
    if (!r) r = consumeToken(b, NL);
    return r;
  }

  /* ********************************************************** */
  // exp (S? OPERATOR_COMMA S? exp)*
  public static boolean arguments(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "arguments")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, ARGUMENTS, "<arguments>");
    r = exp(b, l + 1);
    r = r && arguments_1(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // (S? OPERATOR_COMMA S? exp)*
  private static boolean arguments_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "arguments_1")) return false;
    while (true) {
      int c = current_position_(b);
      if (!arguments_1_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "arguments_1", c)) break;
    }
    return true;
  }

  // S? OPERATOR_COMMA S? exp
  private static boolean arguments_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "arguments_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = arguments_1_0_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COMMA);
    r = r && arguments_1_0_2(b, l + 1);
    r = r && exp(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean arguments_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "arguments_1_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean arguments_1_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "arguments_1_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // OPERATOR_EQ | OPERATOR_PLUS_EQ | OPERATOR_MINUS_EQ | OPERATOR_MUL_EQ | OPERATOR_DIV_EQ |
  //                                        OPERATOR_REMAINDER_EQ | OPERATOR_SHL_EQ | OPERATOR_SHR_EQ | OPERATOR_B_AND_EQ | OPERATOR_B_OR_EQ | OPERATOR_B_XOR_EQ
  public static boolean assignment_oper(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "assignment_oper")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, ASSIGNMENT_OPER, "<assignment oper>");
    r = consumeToken(b, OPERATOR_EQ);
    if (!r) r = consumeToken(b, OPERATOR_PLUS_EQ);
    if (!r) r = consumeToken(b, OPERATOR_MINUS_EQ);
    if (!r) r = consumeToken(b, OPERATOR_MUL_EQ);
    if (!r) r = consumeToken(b, OPERATOR_DIV_EQ);
    if (!r) r = consumeToken(b, OPERATOR_REMAINDER_EQ);
    if (!r) r = consumeToken(b, OPERATOR_SHL_EQ);
    if (!r) r = consumeToken(b, OPERATOR_SHR_EQ);
    if (!r) r = consumeToken(b, OPERATOR_B_AND_EQ);
    if (!r) r = consumeToken(b, OPERATOR_B_OR_EQ);
    if (!r) r = consumeToken(b, OPERATOR_B_XOR_EQ);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  /* ********************************************************** */
  // I assignment_statement_wo_indent
  public static boolean assignment_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "assignment_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, I);
    r = r && assignment_statement_wo_indent(b, l + 1);
    exit_section_(b, m, ASSIGNMENT_STATEMENT, r);
    return r;
  }

  /* ********************************************************** */
  // exp S? assignment_oper S? exp S? NL
  public static boolean assignment_statement_wo_indent(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "assignment_statement_wo_indent")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, ASSIGNMENT_STATEMENT_WO_INDENT, "<assignment statement wo indent>");
    r = exp(b, l + 1);
    r = r && assignment_statement_wo_indent_1(b, l + 1);
    r = r && assignment_oper(b, l + 1);
    r = r && assignment_statement_wo_indent_3(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && assignment_statement_wo_indent_5(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // S?
  private static boolean assignment_statement_wo_indent_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "assignment_statement_wo_indent_1")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean assignment_statement_wo_indent_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "assignment_statement_wo_indent_3")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean assignment_statement_wo_indent_5(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "assignment_statement_wo_indent_5")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // term (S? (OPERATOR_B_OR | OPERATOR_B_AND | OPERATOR_B_XOR | OPERATOR_SHL | OPERATOR_SHR ) S? term)* | term
  public static boolean bitwise(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "bitwise")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, BITWISE, "<bitwise>");
    r = bitwise_0(b, l + 1);
    if (!r) r = term(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // term (S? (OPERATOR_B_OR | OPERATOR_B_AND | OPERATOR_B_XOR | OPERATOR_SHL | OPERATOR_SHR ) S? term)*
  private static boolean bitwise_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "bitwise_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = term(b, l + 1);
    r = r && bitwise_0_1(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // (S? (OPERATOR_B_OR | OPERATOR_B_AND | OPERATOR_B_XOR | OPERATOR_SHL | OPERATOR_SHR ) S? term)*
  private static boolean bitwise_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "bitwise_0_1")) return false;
    while (true) {
      int c = current_position_(b);
      if (!bitwise_0_1_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "bitwise_0_1", c)) break;
    }
    return true;
  }

  // S? (OPERATOR_B_OR | OPERATOR_B_AND | OPERATOR_B_XOR | OPERATOR_SHL | OPERATOR_SHR ) S? term
  private static boolean bitwise_0_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "bitwise_0_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = bitwise_0_1_0_0(b, l + 1);
    r = r && bitwise_0_1_0_1(b, l + 1);
    r = r && bitwise_0_1_0_2(b, l + 1);
    r = r && term(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean bitwise_0_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "bitwise_0_1_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // OPERATOR_B_OR | OPERATOR_B_AND | OPERATOR_B_XOR | OPERATOR_SHL | OPERATOR_SHR
  private static boolean bitwise_0_1_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "bitwise_0_1_0_1")) return false;
    boolean r;
    r = consumeToken(b, OPERATOR_B_OR);
    if (!r) r = consumeToken(b, OPERATOR_B_AND);
    if (!r) r = consumeToken(b, OPERATOR_B_XOR);
    if (!r) r = consumeToken(b, OPERATOR_SHL);
    if (!r) r = consumeToken(b, OPERATOR_SHR);
    return r;
  }

  // S?
  private static boolean bitwise_0_1_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "bitwise_0_1_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I KW_BREAK S? NL
  public static boolean break_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "break_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_BREAK);
    r = r && break_statement_2(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, BREAK_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean break_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "break_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I ccode_statement_wo_indent
  public static boolean ccode_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "ccode_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, I);
    r = r && ccode_statement_wo_indent(b, l + 1);
    exit_section_(b, m, CCODE_STATEMENT, r);
    return r;
  }

  /* ********************************************************** */
  // KW_CCODE S? STRING S? NL
  public static boolean ccode_statement_wo_indent(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "ccode_statement_wo_indent")) return false;
    if (!nextTokenIs(b, KW_CCODE)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, KW_CCODE);
    r = r && ccode_statement_wo_indent_1(b, l + 1);
    r = r && consumeToken(b, STRING);
    r = r && ccode_statement_wo_indent_3(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, CCODE_STATEMENT_WO_INDENT, r);
    return r;
  }

  // S?
  private static boolean ccode_statement_wo_indent_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "ccode_statement_wo_indent_1")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean ccode_statement_wo_indent_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "ccode_statement_wo_indent_3")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // exp assignment_oper exp | exp
  public static boolean cfor_expr(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_expr")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, CFOR_EXPR, "<cfor expr>");
    r = cfor_expr_0(b, l + 1);
    if (!r) r = exp(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // exp assignment_oper exp
  private static boolean cfor_expr_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_expr_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = exp(b, l + 1);
    r = r && assignment_oper(b, l + 1);
    r = r && exp(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  /* ********************************************************** */
  // I KW_FOR S? OPERATOR_OPEN_P S? cfor_expr? S? OPERATOR_SEMICOLON S? exp? S? OPERATOR_SEMICOLON S? cfor_expr? S? OPERATOR_CLOSE_P S? OPERATOR_COLON S? def_block
  public static boolean cfor_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_FOR);
    r = r && cfor_statement_2(b, l + 1);
    r = r && consumeToken(b, OPERATOR_OPEN_P);
    r = r && cfor_statement_4(b, l + 1);
    r = r && cfor_statement_5(b, l + 1);
    r = r && cfor_statement_6(b, l + 1);
    r = r && consumeToken(b, OPERATOR_SEMICOLON);
    r = r && cfor_statement_8(b, l + 1);
    r = r && cfor_statement_9(b, l + 1);
    r = r && cfor_statement_10(b, l + 1);
    r = r && consumeToken(b, OPERATOR_SEMICOLON);
    r = r && cfor_statement_12(b, l + 1);
    r = r && cfor_statement_13(b, l + 1);
    r = r && cfor_statement_14(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CLOSE_P);
    r = r && cfor_statement_16(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && cfor_statement_18(b, l + 1);
    r = r && def_block(b, l + 1);
    exit_section_(b, m, CFOR_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean cfor_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean cfor_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement_4")) return false;
    consumeToken(b, S);
    return true;
  }

  // cfor_expr?
  private static boolean cfor_statement_5(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement_5")) return false;
    cfor_expr(b, l + 1);
    return true;
  }

  // S?
  private static boolean cfor_statement_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement_6")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean cfor_statement_8(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement_8")) return false;
    consumeToken(b, S);
    return true;
  }

  // exp?
  private static boolean cfor_statement_9(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement_9")) return false;
    exp(b, l + 1);
    return true;
  }

  // S?
  private static boolean cfor_statement_10(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement_10")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean cfor_statement_12(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement_12")) return false;
    consumeToken(b, S);
    return true;
  }

  // cfor_expr?
  private static boolean cfor_statement_13(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement_13")) return false;
    cfor_expr(b, l + 1);
    return true;
  }

  // S?
  private static boolean cfor_statement_14(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement_14")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean cfor_statement_16(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement_16")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean cfor_statement_18(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "cfor_statement_18")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // pass_statement | COMMENT | empty_line | class_field
  public static boolean class_bits(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_bits")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, CLASS_BITS, "<class bits>");
    r = pass_statement(b, l + 1);
    if (!r) r = consumeToken(b, COMMENT);
    if (!r) r = empty_line(b, l + 1);
    if (!r) r = class_field(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  /* ********************************************************** */
  // single_line_class_bits | NL class_bits+
  public static boolean class_block(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_block")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, CLASS_BLOCK, "<class block>");
    r = single_line_class_bits(b, l + 1);
    if (!r) r = class_block_1(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // NL class_bits+
  private static boolean class_block_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_block_1")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, NL);
    r = r && class_block_1_1(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // class_bits+
  private static boolean class_block_1_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_block_1_1")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = class_bits(b, l + 1);
    while (r) {
      int c = current_position_(b);
      if (!class_bits(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "class_block_1_1", c)) break;
    }
    exit_section_(b, m, null, r);
    return r;
  }

  /* ********************************************************** */
  // I class_field_wo_indent
  public static boolean class_field(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_field")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, I);
    r = r && class_field_wo_indent(b, l + 1);
    exit_section_(b, m, CLASS_FIELD, r);
    return r;
  }

  /* ********************************************************** */
  // IDENTIFIER S? OPERATOR_COLON S? data_type S? NL
  public static boolean class_field_wo_indent(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_field_wo_indent")) return false;
    if (!nextTokenIs(b, IDENTIFIER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, IDENTIFIER);
    r = r && class_field_wo_indent_1(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && class_field_wo_indent_3(b, l + 1);
    r = r && data_type(b, l + 1);
    r = r && class_field_wo_indent_5(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, CLASS_FIELD_WO_INDENT, r);
    return r;
  }

  // S?
  private static boolean class_field_wo_indent_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_field_wo_indent_1")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean class_field_wo_indent_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_field_wo_indent_3")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean class_field_wo_indent_5(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_field_wo_indent_5")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // (KW_CLASS | KW_STRUCT) S IDENTIFIER S? OPERATOR_COLON S? class_block
  public static boolean class_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_statement")) return false;
    if (!nextTokenIs(b, "<class statement>", KW_CLASS, KW_STRUCT)) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, CLASS_STATEMENT, "<class statement>");
    r = class_statement_0(b, l + 1);
    r = r && consumeTokens(b, 0, S, IDENTIFIER);
    r = r && class_statement_3(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && class_statement_5(b, l + 1);
    r = r && class_block(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // KW_CLASS | KW_STRUCT
  private static boolean class_statement_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_statement_0")) return false;
    boolean r;
    r = consumeToken(b, KW_CLASS);
    if (!r) r = consumeToken(b, KW_STRUCT);
    return r;
  }

  // S?
  private static boolean class_statement_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_statement_3")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean class_statement_5(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_statement_5")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // bitwise (S? OPERATOR_COMPARISON S? bitwise)* | bitwise
  public static boolean comparison(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "comparison")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, COMPARISON, "<comparison>");
    r = comparison_0(b, l + 1);
    if (!r) r = bitwise(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // bitwise (S? OPERATOR_COMPARISON S? bitwise)*
  private static boolean comparison_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "comparison_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = bitwise(b, l + 1);
    r = r && comparison_0_1(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // (S? OPERATOR_COMPARISON S? bitwise)*
  private static boolean comparison_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "comparison_0_1")) return false;
    while (true) {
      int c = current_position_(b);
      if (!comparison_0_1_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "comparison_0_1", c)) break;
    }
    return true;
  }

  // S? OPERATOR_COMPARISON S? bitwise
  private static boolean comparison_0_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "comparison_0_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = comparison_0_1_0_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COMPARISON);
    r = r && comparison_0_1_0_2(b, l + 1);
    r = r && bitwise(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean comparison_0_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "comparison_0_1_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean comparison_0_1_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "comparison_0_1_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // IDENTIFIER S? OPERATOR_COLON S? data_type S? OPERATOR_EQ S? (KW_CCODE? S? STRING| literal) S? NL
  public static boolean const_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "const_statement")) return false;
    if (!nextTokenIs(b, IDENTIFIER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, IDENTIFIER);
    r = r && const_statement_1(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && const_statement_3(b, l + 1);
    r = r && data_type(b, l + 1);
    r = r && const_statement_5(b, l + 1);
    r = r && consumeToken(b, OPERATOR_EQ);
    r = r && const_statement_7(b, l + 1);
    r = r && const_statement_8(b, l + 1);
    r = r && const_statement_9(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, CONST_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean const_statement_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "const_statement_1")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean const_statement_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "const_statement_3")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean const_statement_5(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "const_statement_5")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean const_statement_7(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "const_statement_7")) return false;
    consumeToken(b, S);
    return true;
  }

  // KW_CCODE? S? STRING| literal
  private static boolean const_statement_8(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "const_statement_8")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = const_statement_8_0(b, l + 1);
    if (!r) r = literal(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // KW_CCODE? S? STRING
  private static boolean const_statement_8_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "const_statement_8_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = const_statement_8_0_0(b, l + 1);
    r = r && const_statement_8_0_1(b, l + 1);
    r = r && consumeToken(b, STRING);
    exit_section_(b, m, null, r);
    return r;
  }

  // KW_CCODE?
  private static boolean const_statement_8_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "const_statement_8_0_0")) return false;
    consumeToken(b, KW_CCODE);
    return true;
  }

  // S?
  private static boolean const_statement_8_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "const_statement_8_0_1")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean const_statement_9(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "const_statement_9")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I KW_CONTINUE S? NL
  public static boolean continue_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "continue_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_CONTINUE);
    r = r && continue_statement_2(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, CONTINUE_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean continue_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "continue_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // data_type_bit data_type_args | data_type_bit
  public static boolean data_type(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, DATA_TYPE, "<data type>");
    r = data_type_0(b, l + 1);
    if (!r) r = data_type_bit(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // data_type_bit data_type_args
  private static boolean data_type_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = data_type_bit(b, l + 1);
    r = r && data_type_args(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  /* ********************************************************** */
  // data_type (S? OPERATOR_COMMA S? data_type)*
  public static boolean data_type_arg_bits(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_arg_bits")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, DATA_TYPE_ARG_BITS, "<data type arg bits>");
    r = data_type(b, l + 1);
    r = r && data_type_arg_bits_1(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // (S? OPERATOR_COMMA S? data_type)*
  private static boolean data_type_arg_bits_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_arg_bits_1")) return false;
    while (true) {
      int c = current_position_(b);
      if (!data_type_arg_bits_1_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "data_type_arg_bits_1", c)) break;
    }
    return true;
  }

  // S? OPERATOR_COMMA S? data_type
  private static boolean data_type_arg_bits_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_arg_bits_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = data_type_arg_bits_1_0_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COMMA);
    r = r && data_type_arg_bits_1_0_2(b, l + 1);
    r = r && data_type(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean data_type_arg_bits_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_arg_bits_1_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean data_type_arg_bits_1_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_arg_bits_1_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // S? OPERATOR_OPEN_SQB S? data_type_arg_bits S? OPERATOR_CLOSE_SQB S?
  public static boolean data_type_args(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_args")) return false;
    if (!nextTokenIs(b, "<data type args>", OPERATOR_OPEN_SQB, S)) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, DATA_TYPE_ARGS, "<data type args>");
    r = data_type_args_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_OPEN_SQB);
    r = r && data_type_args_2(b, l + 1);
    r = r && data_type_arg_bits(b, l + 1);
    r = r && data_type_args_4(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CLOSE_SQB);
    r = r && data_type_args_6(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // S?
  private static boolean data_type_args_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_args_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean data_type_args_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_args_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean data_type_args_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_args_4")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean data_type_args_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_args_6")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // data_type_identifier | PRIMITIVE_DATA_TYPE | KW_NONE | NUMBER
  public static boolean data_type_bit(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_bit")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, DATA_TYPE_BIT, "<data type bit>");
    r = data_type_identifier(b, l + 1);
    if (!r) r = consumeToken(b, PRIMITIVE_DATA_TYPE);
    if (!r) r = consumeToken(b, KW_NONE);
    if (!r) r = consumeToken(b, NUMBER);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  /* ********************************************************** */
  // IDENTIFIER (OPERATOR_DOT IDENTIFIER)?
  public static boolean data_type_identifier(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_identifier")) return false;
    if (!nextTokenIs(b, IDENTIFIER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, IDENTIFIER);
    r = r && data_type_identifier_1(b, l + 1);
    exit_section_(b, m, DATA_TYPE_IDENTIFIER, r);
    return r;
  }

  // (OPERATOR_DOT IDENTIFIER)?
  private static boolean data_type_identifier_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_identifier_1")) return false;
    data_type_identifier_1_0(b, l + 1);
    return true;
  }

  // OPERATOR_DOT IDENTIFIER
  private static boolean data_type_identifier_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_identifier_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, OPERATOR_DOT, IDENTIFIER);
    exit_section_(b, m, null, r);
    return r;
  }

  /* ********************************************************** */
  // pass_statement | ccode_statement | if_statement | elif_statement | else_statement | while_statement | foreach_statement
  //   | forendless_statement | cfor_statement | del_statement | defer_statement | return_statement | expr_statement | assignment_statement
  //   | let_statement | empty_line | continue_statement | break_statement | dsl_inner_block | COMMENT
  public static boolean def_bits(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_bits")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, DEF_BITS, "<def bits>");
    r = pass_statement(b, l + 1);
    if (!r) r = ccode_statement(b, l + 1);
    if (!r) r = if_statement(b, l + 1);
    if (!r) r = elif_statement(b, l + 1);
    if (!r) r = else_statement(b, l + 1);
    if (!r) r = while_statement(b, l + 1);
    if (!r) r = foreach_statement(b, l + 1);
    if (!r) r = forendless_statement(b, l + 1);
    if (!r) r = cfor_statement(b, l + 1);
    if (!r) r = del_statement(b, l + 1);
    if (!r) r = defer_statement(b, l + 1);
    if (!r) r = return_statement(b, l + 1);
    if (!r) r = expr_statement(b, l + 1);
    if (!r) r = assignment_statement(b, l + 1);
    if (!r) r = let_statement(b, l + 1);
    if (!r) r = empty_line(b, l + 1);
    if (!r) r = continue_statement(b, l + 1);
    if (!r) r = break_statement(b, l + 1);
    if (!r) r = dsl_inner_block(b, l + 1);
    if (!r) r = consumeToken(b, COMMENT);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  /* ********************************************************** */
  // single_line_def_bits | NL def_bits+
  public static boolean def_block(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_block")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, DEF_BLOCK, "<def block>");
    r = single_line_def_bits(b, l + 1);
    if (!r) r = def_block_1(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // NL def_bits+
  private static boolean def_block_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_block_1")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, NL);
    r = r && def_block_1_1(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // def_bits+
  private static boolean def_block_1_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_block_1_1")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = def_bits(b, l + 1);
    while (r) {
      int c = current_position_(b);
      if (!def_bits(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "def_block_1_1", c)) break;
    }
    exit_section_(b, m, null, r);
    return r;
  }

  /* ********************************************************** */
  // IDENTIFIER S? OPERATOR_COLON S? data_type
  public static boolean def_param(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_param")) return false;
    if (!nextTokenIs(b, IDENTIFIER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, IDENTIFIER);
    r = r && def_param_1(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && def_param_3(b, l + 1);
    r = r && data_type(b, l + 1);
    exit_section_(b, m, DEF_PARAM, r);
    return r;
  }

  // S?
  private static boolean def_param_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_param_1")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean def_param_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_param_3")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // def_param (S? OPERATOR_COMMA S? def_param)*
  public static boolean def_params(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_params")) return false;
    if (!nextTokenIs(b, IDENTIFIER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = def_param(b, l + 1);
    r = r && def_params_1(b, l + 1);
    exit_section_(b, m, DEF_PARAMS, r);
    return r;
  }

  // (S? OPERATOR_COMMA S? def_param)*
  private static boolean def_params_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_params_1")) return false;
    while (true) {
      int c = current_position_(b);
      if (!def_params_1_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "def_params_1", c)) break;
    }
    return true;
  }

  // S? OPERATOR_COMMA S? def_param
  private static boolean def_params_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_params_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = def_params_1_0_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COMMA);
    r = r && def_params_1_0_2(b, l + 1);
    r = r && def_param(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean def_params_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_params_1_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean def_params_1_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_params_1_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // KW_DEF S IDENTIFIER S? OPERATOR_OPEN_P S? def_params? S? OPERATOR_CLOSE_P S? OPERATOR_ARROW S? data_type S? OPERATOR_COLON S? def_block
  public static boolean def_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_statement")) return false;
    if (!nextTokenIs(b, KW_DEF)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, KW_DEF, S, IDENTIFIER);
    r = r && def_statement_3(b, l + 1);
    r = r && consumeToken(b, OPERATOR_OPEN_P);
    r = r && def_statement_5(b, l + 1);
    r = r && def_statement_6(b, l + 1);
    r = r && def_statement_7(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CLOSE_P);
    r = r && def_statement_9(b, l + 1);
    r = r && consumeToken(b, OPERATOR_ARROW);
    r = r && def_statement_11(b, l + 1);
    r = r && data_type(b, l + 1);
    r = r && def_statement_13(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && def_statement_15(b, l + 1);
    r = r && def_block(b, l + 1);
    exit_section_(b, m, DEF_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean def_statement_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_statement_3")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean def_statement_5(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_statement_5")) return false;
    consumeToken(b, S);
    return true;
  }

  // def_params?
  private static boolean def_statement_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_statement_6")) return false;
    def_params(b, l + 1);
    return true;
  }

  // S?
  private static boolean def_statement_7(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_statement_7")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean def_statement_9(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_statement_9")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean def_statement_11(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_statement_11")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean def_statement_13(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_statement_13")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean def_statement_15(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_statement_15")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I defer_statement_wo_indent
  public static boolean defer_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "defer_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, I);
    r = r && defer_statement_wo_indent(b, l + 1);
    exit_section_(b, m, DEFER_STATEMENT, r);
    return r;
  }

  /* ********************************************************** */
  // KW_DEFER S? KW_DEL? S? exp NL
  public static boolean defer_statement_wo_indent(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "defer_statement_wo_indent")) return false;
    if (!nextTokenIs(b, KW_DEFER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, KW_DEFER);
    r = r && defer_statement_wo_indent_1(b, l + 1);
    r = r && defer_statement_wo_indent_2(b, l + 1);
    r = r && defer_statement_wo_indent_3(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, DEFER_STATEMENT_WO_INDENT, r);
    return r;
  }

  // S?
  private static boolean defer_statement_wo_indent_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "defer_statement_wo_indent_1")) return false;
    consumeToken(b, S);
    return true;
  }

  // KW_DEL?
  private static boolean defer_statement_wo_indent_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "defer_statement_wo_indent_2")) return false;
    consumeToken(b, KW_DEL);
    return true;
  }

  // S?
  private static boolean defer_statement_wo_indent_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "defer_statement_wo_indent_3")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I del_statement_wo_indent
  public static boolean del_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "del_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, I);
    r = r && del_statement_wo_indent(b, l + 1);
    exit_section_(b, m, DEL_STATEMENT, r);
    return r;
  }

  /* ********************************************************** */
  // KW_DEL S? exp NL
  public static boolean del_statement_wo_indent(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "del_statement_wo_indent")) return false;
    if (!nextTokenIs(b, KW_DEL)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, KW_DEL);
    r = r && del_statement_wo_indent_1(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, DEL_STATEMENT_WO_INDENT, r);
    return r;
  }

  // S?
  private static boolean del_statement_wo_indent_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "del_statement_wo_indent_1")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I IDENTIFIER (OPERATOR_DOT IDENTIFIER)? OPERATOR_NOT_SYMBOL S? OPERATOR_CURLY_OPEN S? lisp_body? S? OPERATOR_CURLY_CLOSE S? OPERATOR_COLON? S? def_block
  public static boolean dsl_inner_block(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_inner_block")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, IDENTIFIER);
    r = r && dsl_inner_block_2(b, l + 1);
    r = r && consumeToken(b, OPERATOR_NOT_SYMBOL);
    r = r && dsl_inner_block_4(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CURLY_OPEN);
    r = r && dsl_inner_block_6(b, l + 1);
    r = r && dsl_inner_block_7(b, l + 1);
    r = r && dsl_inner_block_8(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CURLY_CLOSE);
    r = r && dsl_inner_block_10(b, l + 1);
    r = r && dsl_inner_block_11(b, l + 1);
    r = r && dsl_inner_block_12(b, l + 1);
    r = r && def_block(b, l + 1);
    exit_section_(b, m, DSL_INNER_BLOCK, r);
    return r;
  }

  // (OPERATOR_DOT IDENTIFIER)?
  private static boolean dsl_inner_block_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_inner_block_2")) return false;
    dsl_inner_block_2_0(b, l + 1);
    return true;
  }

  // OPERATOR_DOT IDENTIFIER
  private static boolean dsl_inner_block_2_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_inner_block_2_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, OPERATOR_DOT, IDENTIFIER);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean dsl_inner_block_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_inner_block_4")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean dsl_inner_block_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_inner_block_6")) return false;
    consumeToken(b, S);
    return true;
  }

  // lisp_body?
  private static boolean dsl_inner_block_7(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_inner_block_7")) return false;
    lisp_body(b, l + 1);
    return true;
  }

  // S?
  private static boolean dsl_inner_block_8(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_inner_block_8")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean dsl_inner_block_10(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_inner_block_10")) return false;
    consumeToken(b, S);
    return true;
  }

  // OPERATOR_COLON?
  private static boolean dsl_inner_block_11(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_inner_block_11")) return false;
    consumeToken(b, OPERATOR_COLON);
    return true;
  }

  // S?
  private static boolean dsl_inner_block_12(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_inner_block_12")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // IDENTIFIER (OPERATOR_DOT IDENTIFIER)? OPERATOR_NOT_SYMBOL S? OPERATOR_CURLY_OPEN S? lisp_body? S? OPERATOR_CURLY_CLOSE S? OPERATOR_COLON? S? def_block
  public static boolean dsl_outer_block(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_outer_block")) return false;
    if (!nextTokenIs(b, IDENTIFIER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, IDENTIFIER);
    r = r && dsl_outer_block_1(b, l + 1);
    r = r && consumeToken(b, OPERATOR_NOT_SYMBOL);
    r = r && dsl_outer_block_3(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CURLY_OPEN);
    r = r && dsl_outer_block_5(b, l + 1);
    r = r && dsl_outer_block_6(b, l + 1);
    r = r && dsl_outer_block_7(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CURLY_CLOSE);
    r = r && dsl_outer_block_9(b, l + 1);
    r = r && dsl_outer_block_10(b, l + 1);
    r = r && dsl_outer_block_11(b, l + 1);
    r = r && def_block(b, l + 1);
    exit_section_(b, m, DSL_OUTER_BLOCK, r);
    return r;
  }

  // (OPERATOR_DOT IDENTIFIER)?
  private static boolean dsl_outer_block_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_outer_block_1")) return false;
    dsl_outer_block_1_0(b, l + 1);
    return true;
  }

  // OPERATOR_DOT IDENTIFIER
  private static boolean dsl_outer_block_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_outer_block_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, OPERATOR_DOT, IDENTIFIER);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean dsl_outer_block_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_outer_block_3")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean dsl_outer_block_5(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_outer_block_5")) return false;
    consumeToken(b, S);
    return true;
  }

  // lisp_body?
  private static boolean dsl_outer_block_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_outer_block_6")) return false;
    lisp_body(b, l + 1);
    return true;
  }

  // S?
  private static boolean dsl_outer_block_7(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_outer_block_7")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean dsl_outer_block_9(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_outer_block_9")) return false;
    consumeToken(b, S);
    return true;
  }

  // OPERATOR_COLON?
  private static boolean dsl_outer_block_10(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_outer_block_10")) return false;
    consumeToken(b, OPERATOR_COLON);
    return true;
  }

  // S?
  private static boolean dsl_outer_block_11(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "dsl_outer_block_11")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I KW_ELIF S? exp S? OPERATOR_COLON S? def_block
  public static boolean elif_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "elif_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_ELIF);
    r = r && elif_statement_2(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && elif_statement_4(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && elif_statement_6(b, l + 1);
    r = r && def_block(b, l + 1);
    exit_section_(b, m, ELIF_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean elif_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "elif_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean elif_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "elif_statement_4")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean elif_statement_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "elif_statement_6")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I KW_ELSE S? OPERATOR_COLON S? def_block
  public static boolean else_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "else_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_ELSE);
    r = r && else_statement_2(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && else_statement_4(b, l + 1);
    r = r && def_block(b, l + 1);
    exit_section_(b, m, ELSE_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean else_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "else_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean else_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "else_statement_4")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // S? NL
  public static boolean empty_line(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "empty_line")) return false;
    if (!nextTokenIs(b, "<empty line>", NL, S)) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, EMPTY_LINE, "<empty line>");
    r = empty_line_0(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // S?
  private static boolean empty_line_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "empty_line_0")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // S? logic_or S?
  public static boolean exp(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "exp")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, EXP, "<exp>");
    r = exp_0(b, l + 1);
    r = r && logic_or(b, l + 1);
    r = r && exp_2(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // S?
  private static boolean exp_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "exp_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean exp_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "exp_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I expr_statement_wo_indent
  public static boolean expr_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "expr_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, I);
    r = r && expr_statement_wo_indent(b, l + 1);
    exit_section_(b, m, EXPR_STATEMENT, r);
    return r;
  }

  /* ********************************************************** */
  // exp S? NL
  public static boolean expr_statement_wo_indent(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "expr_statement_wo_indent")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, EXPR_STATEMENT_WO_INDENT, "<expr statement wo indent>");
    r = exp(b, l + 1);
    r = r && expr_statement_wo_indent_1(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // S?
  private static boolean expr_statement_wo_indent_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "expr_statement_wo_indent_1")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // unary (S? (OPERATOR_MUL | OPERATOR_DIV | OPERATOR_REMAINDER) S? unary)* | unary
  public static boolean factor(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "factor")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, FACTOR, "<factor>");
    r = factor_0(b, l + 1);
    if (!r) r = unary(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // unary (S? (OPERATOR_MUL | OPERATOR_DIV | OPERATOR_REMAINDER) S? unary)*
  private static boolean factor_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "factor_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = unary(b, l + 1);
    r = r && factor_0_1(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // (S? (OPERATOR_MUL | OPERATOR_DIV | OPERATOR_REMAINDER) S? unary)*
  private static boolean factor_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "factor_0_1")) return false;
    while (true) {
      int c = current_position_(b);
      if (!factor_0_1_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "factor_0_1", c)) break;
    }
    return true;
  }

  // S? (OPERATOR_MUL | OPERATOR_DIV | OPERATOR_REMAINDER) S? unary
  private static boolean factor_0_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "factor_0_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = factor_0_1_0_0(b, l + 1);
    r = r && factor_0_1_0_1(b, l + 1);
    r = r && factor_0_1_0_2(b, l + 1);
    r = r && unary(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean factor_0_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "factor_0_1_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // OPERATOR_MUL | OPERATOR_DIV | OPERATOR_REMAINDER
  private static boolean factor_0_1_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "factor_0_1_0_1")) return false;
    boolean r;
    r = consumeToken(b, OPERATOR_MUL);
    if (!r) r = consumeToken(b, OPERATOR_DIV);
    if (!r) r = consumeToken(b, OPERATOR_REMAINDER);
    return r;
  }

  // S?
  private static boolean factor_0_1_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "factor_0_1_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // IDENTIFIER (S? OPERATOR_OPEN_P S? arguments? S? OPERATOR_CLOSE_P | S? OPERATOR_OPEN_SQB S? exp S? OPERATOR_CLOSE_SQB | S? OPERATOR_CURLY_OPEN S? struct_arguments OPERATOR_CURLY_CLOSE | OPERATOR_DOT IDENTIFIER )*
  public static boolean fncall(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall")) return false;
    if (!nextTokenIs(b, IDENTIFIER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, IDENTIFIER);
    r = r && fncall_1(b, l + 1);
    exit_section_(b, m, FNCALL, r);
    return r;
  }

  // (S? OPERATOR_OPEN_P S? arguments? S? OPERATOR_CLOSE_P | S? OPERATOR_OPEN_SQB S? exp S? OPERATOR_CLOSE_SQB | S? OPERATOR_CURLY_OPEN S? struct_arguments OPERATOR_CURLY_CLOSE | OPERATOR_DOT IDENTIFIER )*
  private static boolean fncall_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1")) return false;
    while (true) {
      int c = current_position_(b);
      if (!fncall_1_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "fncall_1", c)) break;
    }
    return true;
  }

  // S? OPERATOR_OPEN_P S? arguments? S? OPERATOR_CLOSE_P | S? OPERATOR_OPEN_SQB S? exp S? OPERATOR_CLOSE_SQB | S? OPERATOR_CURLY_OPEN S? struct_arguments OPERATOR_CURLY_CLOSE | OPERATOR_DOT IDENTIFIER
  private static boolean fncall_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = fncall_1_0_0(b, l + 1);
    if (!r) r = fncall_1_0_1(b, l + 1);
    if (!r) r = fncall_1_0_2(b, l + 1);
    if (!r) r = parseTokens(b, 0, OPERATOR_DOT, IDENTIFIER);
    exit_section_(b, m, null, r);
    return r;
  }

  // S? OPERATOR_OPEN_P S? arguments? S? OPERATOR_CLOSE_P
  private static boolean fncall_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = fncall_1_0_0_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_OPEN_P);
    r = r && fncall_1_0_0_2(b, l + 1);
    r = r && fncall_1_0_0_3(b, l + 1);
    r = r && fncall_1_0_0_4(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CLOSE_P);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean fncall_1_0_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean fncall_1_0_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // arguments?
  private static boolean fncall_1_0_0_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_0_3")) return false;
    arguments(b, l + 1);
    return true;
  }

  // S?
  private static boolean fncall_1_0_0_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_0_4")) return false;
    consumeToken(b, S);
    return true;
  }

  // S? OPERATOR_OPEN_SQB S? exp S? OPERATOR_CLOSE_SQB
  private static boolean fncall_1_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_1")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = fncall_1_0_1_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_OPEN_SQB);
    r = r && fncall_1_0_1_2(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && fncall_1_0_1_4(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CLOSE_SQB);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean fncall_1_0_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_1_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean fncall_1_0_1_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_1_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean fncall_1_0_1_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_1_4")) return false;
    consumeToken(b, S);
    return true;
  }

  // S? OPERATOR_CURLY_OPEN S? struct_arguments OPERATOR_CURLY_CLOSE
  private static boolean fncall_1_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_2")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = fncall_1_0_2_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CURLY_OPEN);
    r = r && fncall_1_0_2_2(b, l + 1);
    r = r && struct_arguments(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CURLY_CLOSE);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean fncall_1_0_2_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_2_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean fncall_1_0_2_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_2_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I KW_FOR S? IDENTIFIER (S? OPERATOR_COLON S? data_type)? S? KW_IN S? exp S? OPERATOR_COLON S? def_block
  public static boolean foreach_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "foreach_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_FOR);
    r = r && foreach_statement_2(b, l + 1);
    r = r && consumeToken(b, IDENTIFIER);
    r = r && foreach_statement_4(b, l + 1);
    r = r && foreach_statement_5(b, l + 1);
    r = r && consumeToken(b, KW_IN);
    r = r && foreach_statement_7(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && foreach_statement_9(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && foreach_statement_11(b, l + 1);
    r = r && def_block(b, l + 1);
    exit_section_(b, m, FOREACH_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean foreach_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "foreach_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // (S? OPERATOR_COLON S? data_type)?
  private static boolean foreach_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "foreach_statement_4")) return false;
    foreach_statement_4_0(b, l + 1);
    return true;
  }

  // S? OPERATOR_COLON S? data_type
  private static boolean foreach_statement_4_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "foreach_statement_4_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = foreach_statement_4_0_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && foreach_statement_4_0_2(b, l + 1);
    r = r && data_type(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean foreach_statement_4_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "foreach_statement_4_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean foreach_statement_4_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "foreach_statement_4_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean foreach_statement_5(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "foreach_statement_5")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean foreach_statement_7(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "foreach_statement_7")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean foreach_statement_9(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "foreach_statement_9")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean foreach_statement_11(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "foreach_statement_11")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I KW_FOR S? OPERATOR_COLON S? def_block
  public static boolean forendless_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "forendless_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_FOR);
    r = r && forendless_statement_2(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && forendless_statement_4(b, l + 1);
    r = r && def_block(b, l + 1);
    exit_section_(b, m, FORENDLESS_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean forendless_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "forendless_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean forendless_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "forendless_statement_4")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I KW_IF S? exp S? OPERATOR_COLON S? def_block
  public static boolean if_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "if_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_IF);
    r = r && if_statement_2(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && if_statement_4(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && if_statement_6(b, l + 1);
    r = r && def_block(b, l + 1);
    exit_section_(b, m, IF_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean if_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "if_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean if_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "if_statement_4")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean if_statement_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "if_statement_6")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // KW_IMPORT S IDENTIFIER (OPERATOR_DOT IDENTIFIER)* (S KW_AS S IDENTIFIER)? S? NL
  public static boolean import_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "import_statement")) return false;
    if (!nextTokenIs(b, KW_IMPORT)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, KW_IMPORT, S, IDENTIFIER);
    r = r && import_statement_3(b, l + 1);
    r = r && import_statement_4(b, l + 1);
    r = r && import_statement_5(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, IMPORT_STATEMENT, r);
    return r;
  }

  // (OPERATOR_DOT IDENTIFIER)*
  private static boolean import_statement_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "import_statement_3")) return false;
    while (true) {
      int c = current_position_(b);
      if (!import_statement_3_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "import_statement_3", c)) break;
    }
    return true;
  }

  // OPERATOR_DOT IDENTIFIER
  private static boolean import_statement_3_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "import_statement_3_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, OPERATOR_DOT, IDENTIFIER);
    exit_section_(b, m, null, r);
    return r;
  }

  // (S KW_AS S IDENTIFIER)?
  private static boolean import_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "import_statement_4")) return false;
    import_statement_4_0(b, l + 1);
    return true;
  }

  // S KW_AS S IDENTIFIER
  private static boolean import_statement_4_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "import_statement_4_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, S, KW_AS, S, IDENTIFIER);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean import_statement_5(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "import_statement_5")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // outer_statement | COMMENT | empty_line
  static boolean item_(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "item_")) return false;
    boolean r;
    r = outer_statement(b, l + 1);
    if (!r) r = consumeToken(b, COMMENT);
    if (!r) r = empty_line(b, l + 1);
    return r;
  }

  /* ********************************************************** */
  // I IDENTIFIER S? OPERATOR_COLON S? data_type S? (OPERATOR_EQ S? exp S?)? NL
  public static boolean let_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "let_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, IDENTIFIER);
    r = r && let_statement_2(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && let_statement_4(b, l + 1);
    r = r && data_type(b, l + 1);
    r = r && let_statement_6(b, l + 1);
    r = r && let_statement_7(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, LET_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean let_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "let_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean let_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "let_statement_4")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean let_statement_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "let_statement_6")) return false;
    consumeToken(b, S);
    return true;
  }

  // (OPERATOR_EQ S? exp S?)?
  private static boolean let_statement_7(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "let_statement_7")) return false;
    let_statement_7_0(b, l + 1);
    return true;
  }

  // OPERATOR_EQ S? exp S?
  private static boolean let_statement_7_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "let_statement_7_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, OPERATOR_EQ);
    r = r && let_statement_7_0_1(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && let_statement_7_0_3(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean let_statement_7_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "let_statement_7_0_1")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean let_statement_7_0_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "let_statement_7_0_3")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // (lsp_expr | any_ws)+
  public static boolean lisp_body(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lisp_body")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, LISP_BODY, "<lisp body>");
    r = lisp_body_0(b, l + 1);
    while (r) {
      int c = current_position_(b);
      if (!lisp_body_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "lisp_body", c)) break;
    }
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // lsp_expr | any_ws
  private static boolean lisp_body_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lisp_body_0")) return false;
    boolean r;
    r = lsp_expr(b, l + 1);
    if (!r) r = any_ws(b, l + 1);
    return r;
  }

  /* ********************************************************** */
  // NUMBER | KW_TRUE | KW_FALSE
  public static boolean literal(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "literal")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, LITERAL, "<literal>");
    r = consumeToken(b, NUMBER);
    if (!r) r = consumeToken(b, KW_TRUE);
    if (!r) r = consumeToken(b, KW_FALSE);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  /* ********************************************************** */
  // comparison (S? OPERATOR_AND S? comparison)* | comparison
  public static boolean logic_and(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "logic_and")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, LOGIC_AND, "<logic and>");
    r = logic_and_0(b, l + 1);
    if (!r) r = comparison(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // comparison (S? OPERATOR_AND S? comparison)*
  private static boolean logic_and_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "logic_and_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = comparison(b, l + 1);
    r = r && logic_and_0_1(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // (S? OPERATOR_AND S? comparison)*
  private static boolean logic_and_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "logic_and_0_1")) return false;
    while (true) {
      int c = current_position_(b);
      if (!logic_and_0_1_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "logic_and_0_1", c)) break;
    }
    return true;
  }

  // S? OPERATOR_AND S? comparison
  private static boolean logic_and_0_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "logic_and_0_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = logic_and_0_1_0_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_AND);
    r = r && logic_and_0_1_0_2(b, l + 1);
    r = r && comparison(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean logic_and_0_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "logic_and_0_1_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean logic_and_0_1_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "logic_and_0_1_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // logic_and (S? OPERATOR_OR S? logic_and)* | logic_and
  public static boolean logic_or(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "logic_or")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, LOGIC_OR, "<logic or>");
    r = logic_or_0(b, l + 1);
    if (!r) r = logic_and(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // logic_and (S? OPERATOR_OR S? logic_and)*
  private static boolean logic_or_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "logic_or_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = logic_and(b, l + 1);
    r = r && logic_or_0_1(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // (S? OPERATOR_OR S? logic_and)*
  private static boolean logic_or_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "logic_or_0_1")) return false;
    while (true) {
      int c = current_position_(b);
      if (!logic_or_0_1_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "logic_or_0_1", c)) break;
    }
    return true;
  }

  // S? OPERATOR_OR S? logic_and
  private static boolean logic_or_0_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "logic_or_0_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = logic_or_0_1_0_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_OR);
    r = r && logic_or_0_1_0_2(b, l + 1);
    r = r && logic_and(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean logic_or_0_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "logic_or_0_1_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean logic_or_0_1_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "logic_or_0_1_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // all_allowed_symbols | lsp_s_expr | lsp_q_expr
  public static boolean lsp_expr(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_expr")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, LSP_EXPR, "<lsp expr>");
    r = all_allowed_symbols(b, l + 1);
    if (!r) r = lsp_s_expr(b, l + 1);
    if (!r) r = lsp_q_expr(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  /* ********************************************************** */
  // OPERATOR_CURLY_OPEN any_ws? OPERATOR_CURLY_CLOSE | OPERATOR_CURLY_OPEN any_ws? lsp_expr (any_ws? lsp_expr)* any_ws? OPERATOR_CURLY_CLOSE
  public static boolean lsp_q_expr(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_q_expr")) return false;
    if (!nextTokenIs(b, OPERATOR_CURLY_OPEN)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = lsp_q_expr_0(b, l + 1);
    if (!r) r = lsp_q_expr_1(b, l + 1);
    exit_section_(b, m, LSP_Q_EXPR, r);
    return r;
  }

  // OPERATOR_CURLY_OPEN any_ws? OPERATOR_CURLY_CLOSE
  private static boolean lsp_q_expr_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_q_expr_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, OPERATOR_CURLY_OPEN);
    r = r && lsp_q_expr_0_1(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CURLY_CLOSE);
    exit_section_(b, m, null, r);
    return r;
  }

  // any_ws?
  private static boolean lsp_q_expr_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_q_expr_0_1")) return false;
    any_ws(b, l + 1);
    return true;
  }

  // OPERATOR_CURLY_OPEN any_ws? lsp_expr (any_ws? lsp_expr)* any_ws? OPERATOR_CURLY_CLOSE
  private static boolean lsp_q_expr_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_q_expr_1")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, OPERATOR_CURLY_OPEN);
    r = r && lsp_q_expr_1_1(b, l + 1);
    r = r && lsp_expr(b, l + 1);
    r = r && lsp_q_expr_1_3(b, l + 1);
    r = r && lsp_q_expr_1_4(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CURLY_CLOSE);
    exit_section_(b, m, null, r);
    return r;
  }

  // any_ws?
  private static boolean lsp_q_expr_1_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_q_expr_1_1")) return false;
    any_ws(b, l + 1);
    return true;
  }

  // (any_ws? lsp_expr)*
  private static boolean lsp_q_expr_1_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_q_expr_1_3")) return false;
    while (true) {
      int c = current_position_(b);
      if (!lsp_q_expr_1_3_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "lsp_q_expr_1_3", c)) break;
    }
    return true;
  }

  // any_ws? lsp_expr
  private static boolean lsp_q_expr_1_3_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_q_expr_1_3_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = lsp_q_expr_1_3_0_0(b, l + 1);
    r = r && lsp_expr(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // any_ws?
  private static boolean lsp_q_expr_1_3_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_q_expr_1_3_0_0")) return false;
    any_ws(b, l + 1);
    return true;
  }

  // any_ws?
  private static boolean lsp_q_expr_1_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_q_expr_1_4")) return false;
    any_ws(b, l + 1);
    return true;
  }

  /* ********************************************************** */
  // OPERATOR_OPEN_P any_ws? OPERATOR_CLOSE_P |  OPERATOR_OPEN_P any_ws? lsp_expr (any_ws? lsp_expr)* any_ws? OPERATOR_CLOSE_P
  public static boolean lsp_s_expr(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_s_expr")) return false;
    if (!nextTokenIs(b, OPERATOR_OPEN_P)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = lsp_s_expr_0(b, l + 1);
    if (!r) r = lsp_s_expr_1(b, l + 1);
    exit_section_(b, m, LSP_S_EXPR, r);
    return r;
  }

  // OPERATOR_OPEN_P any_ws? OPERATOR_CLOSE_P
  private static boolean lsp_s_expr_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_s_expr_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, OPERATOR_OPEN_P);
    r = r && lsp_s_expr_0_1(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CLOSE_P);
    exit_section_(b, m, null, r);
    return r;
  }

  // any_ws?
  private static boolean lsp_s_expr_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_s_expr_0_1")) return false;
    any_ws(b, l + 1);
    return true;
  }

  // OPERATOR_OPEN_P any_ws? lsp_expr (any_ws? lsp_expr)* any_ws? OPERATOR_CLOSE_P
  private static boolean lsp_s_expr_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_s_expr_1")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, OPERATOR_OPEN_P);
    r = r && lsp_s_expr_1_1(b, l + 1);
    r = r && lsp_expr(b, l + 1);
    r = r && lsp_s_expr_1_3(b, l + 1);
    r = r && lsp_s_expr_1_4(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CLOSE_P);
    exit_section_(b, m, null, r);
    return r;
  }

  // any_ws?
  private static boolean lsp_s_expr_1_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_s_expr_1_1")) return false;
    any_ws(b, l + 1);
    return true;
  }

  // (any_ws? lsp_expr)*
  private static boolean lsp_s_expr_1_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_s_expr_1_3")) return false;
    while (true) {
      int c = current_position_(b);
      if (!lsp_s_expr_1_3_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "lsp_s_expr_1_3", c)) break;
    }
    return true;
  }

  // any_ws? lsp_expr
  private static boolean lsp_s_expr_1_3_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_s_expr_1_3_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = lsp_s_expr_1_3_0_0(b, l + 1);
    r = r && lsp_expr(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // any_ws?
  private static boolean lsp_s_expr_1_3_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_s_expr_1_3_0_0")) return false;
    any_ws(b, l + 1);
    return true;
  }

  // any_ws?
  private static boolean lsp_s_expr_1_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "lsp_s_expr_1_4")) return false;
    any_ws(b, l + 1);
    return true;
  }

  /* ********************************************************** */
  // IDENTIFIER (OPERATOR_DOT IDENTIFIER)? OPERATOR_NOT_SYMBOL S? (OPERATOR_OPEN_P S? arguments? S? OPERATOR_CLOSE_P | OPERATOR_CURLY_OPEN S? lisp_body? S? OPERATOR_CURLY_CLOSE)
  public static boolean macro_call(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call")) return false;
    if (!nextTokenIs(b, IDENTIFIER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, IDENTIFIER);
    r = r && macro_call_1(b, l + 1);
    r = r && consumeToken(b, OPERATOR_NOT_SYMBOL);
    r = r && macro_call_3(b, l + 1);
    r = r && macro_call_4(b, l + 1);
    exit_section_(b, m, MACRO_CALL, r);
    return r;
  }

  // (OPERATOR_DOT IDENTIFIER)?
  private static boolean macro_call_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call_1")) return false;
    macro_call_1_0(b, l + 1);
    return true;
  }

  // OPERATOR_DOT IDENTIFIER
  private static boolean macro_call_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, OPERATOR_DOT, IDENTIFIER);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean macro_call_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call_3")) return false;
    consumeToken(b, S);
    return true;
  }

  // OPERATOR_OPEN_P S? arguments? S? OPERATOR_CLOSE_P | OPERATOR_CURLY_OPEN S? lisp_body? S? OPERATOR_CURLY_CLOSE
  private static boolean macro_call_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call_4")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = macro_call_4_0(b, l + 1);
    if (!r) r = macro_call_4_1(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // OPERATOR_OPEN_P S? arguments? S? OPERATOR_CLOSE_P
  private static boolean macro_call_4_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call_4_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, OPERATOR_OPEN_P);
    r = r && macro_call_4_0_1(b, l + 1);
    r = r && macro_call_4_0_2(b, l + 1);
    r = r && macro_call_4_0_3(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CLOSE_P);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean macro_call_4_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call_4_0_1")) return false;
    consumeToken(b, S);
    return true;
  }

  // arguments?
  private static boolean macro_call_4_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call_4_0_2")) return false;
    arguments(b, l + 1);
    return true;
  }

  // S?
  private static boolean macro_call_4_0_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call_4_0_3")) return false;
    consumeToken(b, S);
    return true;
  }

  // OPERATOR_CURLY_OPEN S? lisp_body? S? OPERATOR_CURLY_CLOSE
  private static boolean macro_call_4_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call_4_1")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, OPERATOR_CURLY_OPEN);
    r = r && macro_call_4_1_1(b, l + 1);
    r = r && macro_call_4_1_2(b, l + 1);
    r = r && macro_call_4_1_3(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CURLY_CLOSE);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean macro_call_4_1_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call_4_1_1")) return false;
    consumeToken(b, S);
    return true;
  }

  // lisp_body?
  private static boolean macro_call_4_1_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call_4_1_2")) return false;
    lisp_body(b, l + 1);
    return true;
  }

  // S?
  private static boolean macro_call_4_1_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_call_4_1_3")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // KW_MACROS OPERATOR_NOT_SYMBOL any_ws? OPERATOR_CURLY_OPEN any_ws? lisp_body any_ws? OPERATOR_CURLY_CLOSE NL
  public static boolean macro_declaration_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_declaration_statement")) return false;
    if (!nextTokenIs(b, KW_MACROS)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, KW_MACROS, OPERATOR_NOT_SYMBOL);
    r = r && macro_declaration_statement_2(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CURLY_OPEN);
    r = r && macro_declaration_statement_4(b, l + 1);
    r = r && lisp_body(b, l + 1);
    r = r && macro_declaration_statement_6(b, l + 1);
    r = r && consumeTokens(b, 0, OPERATOR_CURLY_CLOSE, NL);
    exit_section_(b, m, MACRO_DECLARATION_STATEMENT, r);
    return r;
  }

  // any_ws?
  private static boolean macro_declaration_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_declaration_statement_2")) return false;
    any_ws(b, l + 1);
    return true;
  }

  // any_ws?
  private static boolean macro_declaration_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_declaration_statement_4")) return false;
    any_ws(b, l + 1);
    return true;
  }

  // any_ws?
  private static boolean macro_declaration_statement_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "macro_declaration_statement_6")) return false;
    any_ws(b, l + 1);
    return true;
  }

  /* ********************************************************** */
  // runtimefeature_statement | import_statement | const_statement | annotation* class_statement | annotation* def_statement | macro_declaration_statement | dsl_outer_block
  public static boolean outer_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "outer_statement")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, OUTER_STATEMENT, "<outer statement>");
    r = runtimefeature_statement(b, l + 1);
    if (!r) r = import_statement(b, l + 1);
    if (!r) r = const_statement(b, l + 1);
    if (!r) r = outer_statement_3(b, l + 1);
    if (!r) r = outer_statement_4(b, l + 1);
    if (!r) r = macro_declaration_statement(b, l + 1);
    if (!r) r = dsl_outer_block(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // annotation* class_statement
  private static boolean outer_statement_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "outer_statement_3")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = outer_statement_3_0(b, l + 1);
    r = r && class_statement(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // annotation*
  private static boolean outer_statement_3_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "outer_statement_3_0")) return false;
    while (true) {
      int c = current_position_(b);
      if (!annotation(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "outer_statement_3_0", c)) break;
    }
    return true;
  }

  // annotation* def_statement
  private static boolean outer_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "outer_statement_4")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = outer_statement_4_0(b, l + 1);
    r = r && def_statement(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // annotation*
  private static boolean outer_statement_4_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "outer_statement_4_0")) return false;
    while (true) {
      int c = current_position_(b);
      if (!annotation(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "outer_statement_4_0", c)) break;
    }
    return true;
  }

  /* ********************************************************** */
  // OPERATOR_OPEN_P S? exp S? OPERATOR_CLOSE_P
  public static boolean paren_exp(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "paren_exp")) return false;
    if (!nextTokenIs(b, OPERATOR_OPEN_P)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, OPERATOR_OPEN_P);
    r = r && paren_exp_1(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && paren_exp_3(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CLOSE_P);
    exit_section_(b, m, PAREN_EXP, r);
    return r;
  }

  // S?
  private static boolean paren_exp_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "paren_exp_1")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean paren_exp_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "paren_exp_3")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I pass_statement_wo_indent
  public static boolean pass_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "pass_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, I);
    r = r && pass_statement_wo_indent(b, l + 1);
    exit_section_(b, m, PASS_STATEMENT, r);
    return r;
  }

  /* ********************************************************** */
  // KW_PASS S? NL
  public static boolean pass_statement_wo_indent(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "pass_statement_wo_indent")) return false;
    if (!nextTokenIs(b, KW_PASS)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, KW_PASS);
    r = r && pass_statement_wo_indent_1(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, PASS_STATEMENT_WO_INDENT, r);
    return r;
  }

  // S?
  private static boolean pass_statement_wo_indent_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "pass_statement_wo_indent_1")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // KW_TRUE | KW_FALSE | KW_NONE | NUMBER | STRING | IDENTIFIER | paren_exp
  public static boolean primary(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "primary")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, PRIMARY, "<primary>");
    r = consumeToken(b, KW_TRUE);
    if (!r) r = consumeToken(b, KW_FALSE);
    if (!r) r = consumeToken(b, KW_NONE);
    if (!r) r = consumeToken(b, NUMBER);
    if (!r) r = consumeToken(b, STRING);
    if (!r) r = consumeToken(b, IDENTIFIER);
    if (!r) r = paren_exp(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  /* ********************************************************** */
  // I return_statement_wo_indent
  public static boolean return_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "return_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, I);
    r = r && return_statement_wo_indent(b, l + 1);
    exit_section_(b, m, RETURN_STATEMENT, r);
    return r;
  }

  /* ********************************************************** */
  // KW_RETURN (S? exp)? NL
  public static boolean return_statement_wo_indent(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "return_statement_wo_indent")) return false;
    if (!nextTokenIs(b, KW_RETURN)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, KW_RETURN);
    r = r && return_statement_wo_indent_1(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, RETURN_STATEMENT_WO_INDENT, r);
    return r;
  }

  // (S? exp)?
  private static boolean return_statement_wo_indent_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "return_statement_wo_indent_1")) return false;
    return_statement_wo_indent_1_0(b, l + 1);
    return true;
  }

  // S? exp
  private static boolean return_statement_wo_indent_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "return_statement_wo_indent_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = return_statement_wo_indent_1_0_0(b, l + 1);
    r = r && exp(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean return_statement_wo_indent_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "return_statement_wo_indent_1_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // KW_RUNTIMEFEATURE S STRING S? NL
  public static boolean runtimefeature_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "runtimefeature_statement")) return false;
    if (!nextTokenIs(b, KW_RUNTIMEFEATURE)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, KW_RUNTIMEFEATURE, S, STRING);
    r = r && runtimefeature_statement_3(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, RUNTIMEFEATURE_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean runtimefeature_statement_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "runtimefeature_statement_3")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // pass_statement_wo_indent | class_field_wo_indent
  public static boolean single_line_class_bits(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "single_line_class_bits")) return false;
    if (!nextTokenIs(b, "<single line class bits>", IDENTIFIER, KW_PASS)) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, SINGLE_LINE_CLASS_BITS, "<single line class bits>");
    r = pass_statement_wo_indent(b, l + 1);
    if (!r) r = class_field_wo_indent(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  /* ********************************************************** */
  // pass_statement_wo_indent | ccode_statement_wo_indent | del_statement_wo_indent
  //   | defer_statement_wo_indent | return_statement_wo_indent | expr_statement_wo_indent | assignment_statement_wo_indent
  public static boolean single_line_def_bits(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "single_line_def_bits")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, SINGLE_LINE_DEF_BITS, "<single line def bits>");
    r = pass_statement_wo_indent(b, l + 1);
    if (!r) r = ccode_statement_wo_indent(b, l + 1);
    if (!r) r = del_statement_wo_indent(b, l + 1);
    if (!r) r = defer_statement_wo_indent(b, l + 1);
    if (!r) r = return_statement_wo_indent(b, l + 1);
    if (!r) r = expr_statement_wo_indent(b, l + 1);
    if (!r) r = assignment_statement_wo_indent(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  /* ********************************************************** */
  // IDENTIFIER S? OPERATOR_COLON S? exp
  public static boolean struct_arg(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "struct_arg")) return false;
    if (!nextTokenIs(b, IDENTIFIER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, IDENTIFIER);
    r = r && struct_arg_1(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && struct_arg_3(b, l + 1);
    r = r && exp(b, l + 1);
    exit_section_(b, m, STRUCT_ARG, r);
    return r;
  }

  // S?
  private static boolean struct_arg_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "struct_arg_1")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean struct_arg_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "struct_arg_3")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // struct_arg (S? OPERATOR_COMMA S? struct_arg)*
  public static boolean struct_arguments(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "struct_arguments")) return false;
    if (!nextTokenIs(b, IDENTIFIER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = struct_arg(b, l + 1);
    r = r && struct_arguments_1(b, l + 1);
    exit_section_(b, m, STRUCT_ARGUMENTS, r);
    return r;
  }

  // (S? OPERATOR_COMMA S? struct_arg)*
  private static boolean struct_arguments_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "struct_arguments_1")) return false;
    while (true) {
      int c = current_position_(b);
      if (!struct_arguments_1_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "struct_arguments_1", c)) break;
    }
    return true;
  }

  // S? OPERATOR_COMMA S? struct_arg
  private static boolean struct_arguments_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "struct_arguments_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = struct_arguments_1_0_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COMMA);
    r = r && struct_arguments_1_0_2(b, l + 1);
    r = r && struct_arg(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean struct_arguments_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "struct_arguments_1_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean struct_arguments_1_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "struct_arguments_1_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // factor (S? (OPERATOR_MINUS | OPERATOR_PLUS) S? factor)* | factor
  public static boolean term(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "term")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, TERM, "<term>");
    r = term_0(b, l + 1);
    if (!r) r = factor(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // factor (S? (OPERATOR_MINUS | OPERATOR_PLUS) S? factor)*
  private static boolean term_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "term_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = factor(b, l + 1);
    r = r && term_0_1(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // (S? (OPERATOR_MINUS | OPERATOR_PLUS) S? factor)*
  private static boolean term_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "term_0_1")) return false;
    while (true) {
      int c = current_position_(b);
      if (!term_0_1_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "term_0_1", c)) break;
    }
    return true;
  }

  // S? (OPERATOR_MINUS | OPERATOR_PLUS) S? factor
  private static boolean term_0_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "term_0_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = term_0_1_0_0(b, l + 1);
    r = r && term_0_1_0_1(b, l + 1);
    r = r && term_0_1_0_2(b, l + 1);
    r = r && factor(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean term_0_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "term_0_1_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // OPERATOR_MINUS | OPERATOR_PLUS
  private static boolean term_0_1_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "term_0_1_0_1")) return false;
    boolean r;
    r = consumeToken(b, OPERATOR_MINUS);
    if (!r) r = consumeToken(b, OPERATOR_PLUS);
    return r;
  }

  // S?
  private static boolean term_0_1_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "term_0_1_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // !('@' | 'class'  | 'struct' | 'def' | 'import' | 'runtimefeature' | 'macros')
  static boolean top_level_recover(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "top_level_recover")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NOT_);
    r = !top_level_recover_0(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // '@' | 'class'  | 'struct' | 'def' | 'import' | 'runtimefeature' | 'macros'
  private static boolean top_level_recover_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "top_level_recover_0")) return false;
    boolean r;
    r = consumeToken(b, "@");
    if (!r) r = consumeToken(b, "class");
    if (!r) r = consumeToken(b, "struct");
    if (!r) r = consumeToken(b, "def");
    if (!r) r = consumeToken(b, "import");
    if (!r) r = consumeToken(b, "runtimefeature");
    if (!r) r = consumeToken(b, "macros");
    return r;
  }

  /* ********************************************************** */
  // (OPERATOR_B_NOT | OPERATOR_MINUS | OPERATOR_NOT) S? exp | macro_call | fncall | primary
  public static boolean unary(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "unary")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, UNARY, "<unary>");
    r = unary_0(b, l + 1);
    if (!r) r = macro_call(b, l + 1);
    if (!r) r = fncall(b, l + 1);
    if (!r) r = primary(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  // (OPERATOR_B_NOT | OPERATOR_MINUS | OPERATOR_NOT) S? exp
  private static boolean unary_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "unary_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = unary_0_0(b, l + 1);
    r = r && unary_0_1(b, l + 1);
    r = r && exp(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // OPERATOR_B_NOT | OPERATOR_MINUS | OPERATOR_NOT
  private static boolean unary_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "unary_0_0")) return false;
    boolean r;
    r = consumeToken(b, OPERATOR_B_NOT);
    if (!r) r = consumeToken(b, OPERATOR_MINUS);
    if (!r) r = consumeToken(b, OPERATOR_NOT);
    return r;
  }

  // S?
  private static boolean unary_0_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "unary_0_1")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I KW_WHILE S? exp S? OPERATOR_COLON S? def_block
  public static boolean while_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "while_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_WHILE);
    r = r && while_statement_2(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && while_statement_4(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && while_statement_6(b, l + 1);
    r = r && def_block(b, l + 1);
    exit_section_(b, m, WHILE_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean while_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "while_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean while_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "while_statement_4")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean while_statement_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "while_statement_6")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // item_*
  static boolean yakshaFile(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "yakshaFile")) return false;
    Marker m = enter_section_(b, l, _NONE_, null, "<import, def, class>");
    while (true) {
      int c = current_position_(b);
      if (!item_(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "yakshaFile", c)) break;
    }
    exit_section_(b, l, m, true, false, YakshaParser::top_level_recover);
    return true;
  }

}
