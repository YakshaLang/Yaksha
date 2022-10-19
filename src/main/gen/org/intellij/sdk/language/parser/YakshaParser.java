// This is a generated file. Not intended for manual editing.
package org.intellij.sdk.language.parser;

import com.intellij.lang.PsiBuilder;
import com.intellij.lang.PsiBuilder.Marker;
import static org.intellij.sdk.language.psi.YakshaTypes.*;
import static com.intellij.lang.parser.GeneratedParserUtilBase.*;
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
  // I exp S? (OPERATOR_EQ | OPERATOR_PLUS_EQ | OPERATOR_MINUS_EQ | OPERATOR_MUL_EQ | OPERATOR_DIV_EQ | OPERATOR_REMAINDER_EQ | OPERATOR_SHL_EQ | OPERATOR_SHR_EQ | OPERATOR_B_AND_EQ | OPERATOR_B_OR_EQ | OPERATOR_B_XOR_EQ)  S? exp S? NL
  public static boolean assignment_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "assignment_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, I);
    r = r && exp(b, l + 1);
    r = r && assignment_statement_2(b, l + 1);
    r = r && assignment_statement_3(b, l + 1);
    r = r && assignment_statement_4(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && assignment_statement_6(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, ASSIGNMENT_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean assignment_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "assignment_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // OPERATOR_EQ | OPERATOR_PLUS_EQ | OPERATOR_MINUS_EQ | OPERATOR_MUL_EQ | OPERATOR_DIV_EQ | OPERATOR_REMAINDER_EQ | OPERATOR_SHL_EQ | OPERATOR_SHR_EQ | OPERATOR_B_AND_EQ | OPERATOR_B_OR_EQ | OPERATOR_B_XOR_EQ
  private static boolean assignment_statement_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "assignment_statement_3")) return false;
    boolean r;
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
    return r;
  }

  // S?
  private static boolean assignment_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "assignment_statement_4")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean assignment_statement_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "assignment_statement_6")) return false;
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
  // I KW_CCODE S? STRING S? NL
  public static boolean ccode_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "ccode_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_CCODE);
    r = r && ccode_statement_2(b, l + 1);
    r = r && consumeToken(b, STRING);
    r = r && ccode_statement_4(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, CCODE_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean ccode_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "ccode_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean ccode_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "ccode_statement_4")) return false;
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
  // I IDENTIFIER S? OPERATOR_COLON S? data_type S? NL
  public static boolean class_field(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_field")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, IDENTIFIER);
    r = r && class_field_2(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && class_field_4(b, l + 1);
    r = r && data_type(b, l + 1);
    r = r && class_field_6(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, CLASS_FIELD, r);
    return r;
  }

  // S?
  private static boolean class_field_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_field_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean class_field_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_field_4")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean class_field_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_field_6")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // KW_CLASS S IDENTIFIER S? OPERATOR_COLON S? NL class_bits+
  public static boolean class_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_statement")) return false;
    if (!nextTokenIs(b, KW_CLASS)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, KW_CLASS, S, IDENTIFIER);
    r = r && class_statement_3(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && class_statement_5(b, l + 1);
    r = r && consumeToken(b, NL);
    r = r && class_statement_7(b, l + 1);
    exit_section_(b, m, CLASS_STATEMENT, r);
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

  // class_bits+
  private static boolean class_statement_7(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "class_statement_7")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = class_bits(b, l + 1);
    while (r) {
      int c = current_position_(b);
      if (!class_bits(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "class_statement_7", c)) break;
    }
    exit_section_(b, m, null, r);
    return r;
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
  // IDENTIFIER S? OPERATOR_COLON S? data_type S? OPERATOR_EQ S? literal S? NL
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
    r = r && literal(b, l + 1);
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
  // data_type_identifier | PRIMITIVE_DATA_TYPE | KW_NONE
  public static boolean data_type_bit(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "data_type_bit")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, DATA_TYPE_BIT, "<data type bit>");
    r = data_type_identifier(b, l + 1);
    if (!r) r = consumeToken(b, PRIMITIVE_DATA_TYPE);
    if (!r) r = consumeToken(b, KW_NONE);
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
  // pass_statement | ccode_statement | if_statement | elif_statement | else_statement | while_statement | del_statement | defer_statement | return_statement | expr_statement | assignment_statement | let_statement | empty_line | continue_statement | break_statement | COMMENT
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
    if (!r) r = del_statement(b, l + 1);
    if (!r) r = defer_statement(b, l + 1);
    if (!r) r = return_statement(b, l + 1);
    if (!r) r = expr_statement(b, l + 1);
    if (!r) r = assignment_statement(b, l + 1);
    if (!r) r = let_statement(b, l + 1);
    if (!r) r = empty_line(b, l + 1);
    if (!r) r = continue_statement(b, l + 1);
    if (!r) r = break_statement(b, l + 1);
    if (!r) r = consumeToken(b, COMMENT);
    exit_section_(b, l, m, r, false, null);
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
  // KW_DEF S IDENTIFIER S? OPERATOR_OPEN_P S? def_params? S? OPERATOR_CLOSE_P S? OPERATOR_ARROW S? data_type S? OPERATOR_COLON NL def_bits+
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
    r = r && consumeTokens(b, 0, OPERATOR_COLON, NL);
    r = r && def_statement_16(b, l + 1);
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

  // def_bits+
  private static boolean def_statement_16(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "def_statement_16")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = def_bits(b, l + 1);
    while (r) {
      int c = current_position_(b);
      if (!def_bits(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "def_statement_16", c)) break;
    }
    exit_section_(b, m, null, r);
    return r;
  }

  /* ********************************************************** */
  // I KW_DEFER S? KW_DEL? S? exp NL
  public static boolean defer_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "defer_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_DEFER);
    r = r && defer_statement_2(b, l + 1);
    r = r && defer_statement_3(b, l + 1);
    r = r && defer_statement_4(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, DEFER_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean defer_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "defer_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // KW_DEL?
  private static boolean defer_statement_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "defer_statement_3")) return false;
    consumeToken(b, KW_DEL);
    return true;
  }

  // S?
  private static boolean defer_statement_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "defer_statement_4")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I KW_DEL  S? exp NL
  public static boolean del_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "del_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_DEL);
    r = r && del_statement_2(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, DEL_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean del_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "del_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // I KW_ELIF S? exp S? OPERATOR_COLON S? NL def_bits+
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
    r = r && consumeToken(b, NL);
    r = r && elif_statement_8(b, l + 1);
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

  // def_bits+
  private static boolean elif_statement_8(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "elif_statement_8")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = def_bits(b, l + 1);
    while (r) {
      int c = current_position_(b);
      if (!def_bits(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "elif_statement_8", c)) break;
    }
    exit_section_(b, m, null, r);
    return r;
  }

  /* ********************************************************** */
  // I KW_ELSE S? OPERATOR_COLON S? NL def_bits+
  public static boolean else_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "else_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_ELSE);
    r = r && else_statement_2(b, l + 1);
    r = r && consumeToken(b, OPERATOR_COLON);
    r = r && else_statement_4(b, l + 1);
    r = r && consumeToken(b, NL);
    r = r && else_statement_6(b, l + 1);
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

  // def_bits+
  private static boolean else_statement_6(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "else_statement_6")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = def_bits(b, l + 1);
    while (r) {
      int c = current_position_(b);
      if (!def_bits(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "else_statement_6", c)) break;
    }
    exit_section_(b, m, null, r);
    return r;
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
  // I exp S? NL
  public static boolean expr_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "expr_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, I);
    r = r && exp(b, l + 1);
    r = r && expr_statement_2(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, EXPR_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean expr_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "expr_statement_2")) return false;
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
  // identifier_exp (S? OPERATOR_OPEN_P S? arguments? S? OPERATOR_CLOSE_P | S? OPERATOR_OPEN_SQB S? exp S? OPERATOR_CLOSE_SQB )
  public static boolean fncall(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall")) return false;
    if (!nextTokenIs(b, IDENTIFIER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = identifier_exp(b, l + 1);
    r = r && fncall_1(b, l + 1);
    exit_section_(b, m, FNCALL, r);
    return r;
  }

  // S? OPERATOR_OPEN_P S? arguments? S? OPERATOR_CLOSE_P | S? OPERATOR_OPEN_SQB S? exp S? OPERATOR_CLOSE_SQB
  private static boolean fncall_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = fncall_1_0(b, l + 1);
    if (!r) r = fncall_1_1(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S? OPERATOR_OPEN_P S? arguments? S? OPERATOR_CLOSE_P
  private static boolean fncall_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = fncall_1_0_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_OPEN_P);
    r = r && fncall_1_0_2(b, l + 1);
    r = r && fncall_1_0_3(b, l + 1);
    r = r && fncall_1_0_4(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CLOSE_P);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean fncall_1_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean fncall_1_0_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // arguments?
  private static boolean fncall_1_0_3(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_3")) return false;
    arguments(b, l + 1);
    return true;
  }

  // S?
  private static boolean fncall_1_0_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_0_4")) return false;
    consumeToken(b, S);
    return true;
  }

  // S? OPERATOR_OPEN_SQB S? exp S? OPERATOR_CLOSE_SQB
  private static boolean fncall_1_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_1")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = fncall_1_1_0(b, l + 1);
    r = r && consumeToken(b, OPERATOR_OPEN_SQB);
    r = r && fncall_1_1_2(b, l + 1);
    r = r && exp(b, l + 1);
    r = r && fncall_1_1_4(b, l + 1);
    r = r && consumeToken(b, OPERATOR_CLOSE_SQB);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean fncall_1_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_1_0")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean fncall_1_1_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_1_2")) return false;
    consumeToken(b, S);
    return true;
  }

  // S?
  private static boolean fncall_1_1_4(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "fncall_1_1_4")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // IDENTIFIER (OPERATOR_DOT IDENTIFIER)*
  public static boolean identifier_exp(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "identifier_exp")) return false;
    if (!nextTokenIs(b, IDENTIFIER)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeToken(b, IDENTIFIER);
    r = r && identifier_exp_1(b, l + 1);
    exit_section_(b, m, IDENTIFIER_EXP, r);
    return r;
  }

  // (OPERATOR_DOT IDENTIFIER)*
  private static boolean identifier_exp_1(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "identifier_exp_1")) return false;
    while (true) {
      int c = current_position_(b);
      if (!identifier_exp_1_0(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "identifier_exp_1", c)) break;
    }
    return true;
  }

  // OPERATOR_DOT IDENTIFIER
  private static boolean identifier_exp_1_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "identifier_exp_1_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, OPERATOR_DOT, IDENTIFIER);
    exit_section_(b, m, null, r);
    return r;
  }

  /* ********************************************************** */
  // I KW_IF S? exp S? OPERATOR_COLON S? NL def_bits+
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
    r = r && consumeToken(b, NL);
    r = r && if_statement_8(b, l + 1);
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

  // def_bits+
  private static boolean if_statement_8(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "if_statement_8")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = def_bits(b, l + 1);
    while (r) {
      int c = current_position_(b);
      if (!def_bits(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "if_statement_8", c)) break;
    }
    exit_section_(b, m, null, r);
    return r;
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
  // runtimefeature_statement | import_statement | const_statement | annotation* class_statement | annotation* def_statement
  public static boolean outer_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "outer_statement")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, OUTER_STATEMENT, "<outer statement>");
    r = runtimefeature_statement(b, l + 1);
    if (!r) r = import_statement(b, l + 1);
    if (!r) r = const_statement(b, l + 1);
    if (!r) r = outer_statement_3(b, l + 1);
    if (!r) r = outer_statement_4(b, l + 1);
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
  // I KW_PASS S? NL
  public static boolean pass_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "pass_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_PASS);
    r = r && pass_statement_2(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, PASS_STATEMENT, r);
    return r;
  }

  // S?
  private static boolean pass_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "pass_statement_2")) return false;
    consumeToken(b, S);
    return true;
  }

  /* ********************************************************** */
  // KW_TRUE | KW_FALSE | KW_NONE | NUMBER | STRING | identifier_exp | paren_exp
  public static boolean primary(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "primary")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, PRIMARY, "<primary>");
    r = consumeToken(b, KW_TRUE);
    if (!r) r = consumeToken(b, KW_FALSE);
    if (!r) r = consumeToken(b, KW_NONE);
    if (!r) r = consumeToken(b, NUMBER);
    if (!r) r = consumeToken(b, STRING);
    if (!r) r = identifier_exp(b, l + 1);
    if (!r) r = paren_exp(b, l + 1);
    exit_section_(b, l, m, r, false, null);
    return r;
  }

  /* ********************************************************** */
  // I KW_RETURN (S? exp)? NL
  public static boolean return_statement(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "return_statement")) return false;
    if (!nextTokenIs(b, I)) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = consumeTokens(b, 0, I, KW_RETURN);
    r = r && return_statement_2(b, l + 1);
    r = r && consumeToken(b, NL);
    exit_section_(b, m, RETURN_STATEMENT, r);
    return r;
  }

  // (S? exp)?
  private static boolean return_statement_2(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "return_statement_2")) return false;
    return_statement_2_0(b, l + 1);
    return true;
  }

  // S? exp
  private static boolean return_statement_2_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "return_statement_2_0")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = return_statement_2_0_0(b, l + 1);
    r = r && exp(b, l + 1);
    exit_section_(b, m, null, r);
    return r;
  }

  // S?
  private static boolean return_statement_2_0_0(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "return_statement_2_0_0")) return false;
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
  // (OPERATOR_B_NOT | OPERATOR_MINUS | OPERATOR_NOT) S? exp | fncall | primary
  public static boolean unary(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "unary")) return false;
    boolean r;
    Marker m = enter_section_(b, l, _NONE_, UNARY, "<unary>");
    r = unary_0(b, l + 1);
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
  // I KW_WHILE S? exp S? OPERATOR_COLON S? NL def_bits+
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
    r = r && consumeToken(b, NL);
    r = r && while_statement_8(b, l + 1);
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

  // def_bits+
  private static boolean while_statement_8(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "while_statement_8")) return false;
    boolean r;
    Marker m = enter_section_(b);
    r = def_bits(b, l + 1);
    while (r) {
      int c = current_position_(b);
      if (!def_bits(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "while_statement_8", c)) break;
    }
    exit_section_(b, m, null, r);
    return r;
  }

  /* ********************************************************** */
  // item_*
  static boolean yakshaFile(PsiBuilder b, int l) {
    if (!recursion_guard_(b, l, "yakshaFile")) return false;
    while (true) {
      int c = current_position_(b);
      if (!item_(b, l + 1)) break;
      if (!empty_element_parsed_guard_(b, "yakshaFile", c)) break;
    }
    return true;
  }

}
