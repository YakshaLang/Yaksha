// This is a generated file. Not intended for manual editing.
package org.intellij.sdk.language.psi;

import com.intellij.psi.tree.IElementType;
import com.intellij.psi.PsiElement;
import com.intellij.lang.ASTNode;
import org.intellij.sdk.language.psi.impl.*;

public interface YakshaTypes {

  IElementType ANNOTATION = new YakshaElementType("ANNOTATION");
  IElementType ANNOTATION_ARG = new YakshaElementType("ANNOTATION_ARG");
  IElementType ARGUMENTS = new YakshaElementType("ARGUMENTS");
  IElementType ASSIGNMENT_STATEMENT = new YakshaElementType("ASSIGNMENT_STATEMENT");
  IElementType ASSIGNMENT_STATEMENT_WO_INDENT = new YakshaElementType("ASSIGNMENT_STATEMENT_WO_INDENT");
  IElementType BITWISE = new YakshaElementType("BITWISE");
  IElementType BREAK_STATEMENT = new YakshaElementType("BREAK_STATEMENT");
  IElementType CCODE_STATEMENT = new YakshaElementType("CCODE_STATEMENT");
  IElementType CCODE_STATEMENT_WO_INDENT = new YakshaElementType("CCODE_STATEMENT_WO_INDENT");
  IElementType CLASS_BITS = new YakshaElementType("CLASS_BITS");
  IElementType CLASS_BLOCK = new YakshaElementType("CLASS_BLOCK");
  IElementType CLASS_FIELD = new YakshaElementType("CLASS_FIELD");
  IElementType CLASS_FIELD_WO_INDENT = new YakshaElementType("CLASS_FIELD_WO_INDENT");
  IElementType CLASS_STATEMENT = new YakshaElementType("CLASS_STATEMENT");
  IElementType COMPARISON = new YakshaElementType("COMPARISON");
  IElementType CONST_STATEMENT = new YakshaElementType("CONST_STATEMENT");
  IElementType CONTINUE_STATEMENT = new YakshaElementType("CONTINUE_STATEMENT");
  IElementType DATA_TYPE = new YakshaElementType("DATA_TYPE");
  IElementType DATA_TYPE_ARGS = new YakshaElementType("DATA_TYPE_ARGS");
  IElementType DATA_TYPE_ARG_BITS = new YakshaElementType("DATA_TYPE_ARG_BITS");
  IElementType DATA_TYPE_BIT = new YakshaElementType("DATA_TYPE_BIT");
  IElementType DATA_TYPE_IDENTIFIER = new YakshaElementType("DATA_TYPE_IDENTIFIER");
  IElementType DEFER_STATEMENT = new YakshaElementType("DEFER_STATEMENT");
  IElementType DEFER_STATEMENT_WO_INDENT = new YakshaElementType("DEFER_STATEMENT_WO_INDENT");
  IElementType DEF_BITS = new YakshaElementType("DEF_BITS");
  IElementType DEF_BLOCK = new YakshaElementType("DEF_BLOCK");
  IElementType DEF_PARAM = new YakshaElementType("DEF_PARAM");
  IElementType DEF_PARAMS = new YakshaElementType("DEF_PARAMS");
  IElementType DEF_STATEMENT = new YakshaElementType("DEF_STATEMENT");
  IElementType DEL_STATEMENT = new YakshaElementType("DEL_STATEMENT");
  IElementType DEL_STATEMENT_WO_INDENT = new YakshaElementType("DEL_STATEMENT_WO_INDENT");
  IElementType ELIF_STATEMENT = new YakshaElementType("ELIF_STATEMENT");
  IElementType ELSE_STATEMENT = new YakshaElementType("ELSE_STATEMENT");
  IElementType EMPTY_LINE = new YakshaElementType("EMPTY_LINE");
  IElementType EXP = new YakshaElementType("EXP");
  IElementType EXPR_STATEMENT = new YakshaElementType("EXPR_STATEMENT");
  IElementType EXPR_STATEMENT_WO_INDENT = new YakshaElementType("EXPR_STATEMENT_WO_INDENT");
  IElementType FACTOR = new YakshaElementType("FACTOR");
  IElementType FNCALL = new YakshaElementType("FNCALL");
  IElementType FOREACH_STATEMENT = new YakshaElementType("FOREACH_STATEMENT");
  IElementType FORENDLESS_STATEMENT = new YakshaElementType("FORENDLESS_STATEMENT");
  IElementType IF_STATEMENT = new YakshaElementType("IF_STATEMENT");
  IElementType IMPORT_STATEMENT = new YakshaElementType("IMPORT_STATEMENT");
  IElementType LET_STATEMENT = new YakshaElementType("LET_STATEMENT");
  IElementType LITERAL = new YakshaElementType("LITERAL");
  IElementType LOGIC_AND = new YakshaElementType("LOGIC_AND");
  IElementType LOGIC_OR = new YakshaElementType("LOGIC_OR");
  IElementType OUTER_STATEMENT = new YakshaElementType("OUTER_STATEMENT");
  IElementType PAREN_EXP = new YakshaElementType("PAREN_EXP");
  IElementType PASS_STATEMENT = new YakshaElementType("PASS_STATEMENT");
  IElementType PASS_STATEMENT_WO_INDENT = new YakshaElementType("PASS_STATEMENT_WO_INDENT");
  IElementType PRIMARY = new YakshaElementType("PRIMARY");
  IElementType RETURN_STATEMENT = new YakshaElementType("RETURN_STATEMENT");
  IElementType RETURN_STATEMENT_WO_INDENT = new YakshaElementType("RETURN_STATEMENT_WO_INDENT");
  IElementType RUNTIMEFEATURE_STATEMENT = new YakshaElementType("RUNTIMEFEATURE_STATEMENT");
  IElementType SINGLE_LINE_CLASS_BITS = new YakshaElementType("SINGLE_LINE_CLASS_BITS");
  IElementType SINGLE_LINE_DEF_BITS = new YakshaElementType("SINGLE_LINE_DEF_BITS");
  IElementType TERM = new YakshaElementType("TERM");
  IElementType UNARY = new YakshaElementType("UNARY");
  IElementType WHILE_STATEMENT = new YakshaElementType("WHILE_STATEMENT");

  IElementType COMMENT = new YakshaTokenType("COMMENT");
  IElementType I = new YakshaTokenType("I");
  IElementType IDENTIFIER = new YakshaTokenType("IDENTIFIER");
  IElementType KW_AS = new YakshaTokenType("KW_AS");
  IElementType KW_BREAK = new YakshaTokenType("KW_BREAK");
  IElementType KW_CCODE = new YakshaTokenType("KW_CCODE");
  IElementType KW_CLASS = new YakshaTokenType("KW_CLASS");
  IElementType KW_CONTINUE = new YakshaTokenType("KW_CONTINUE");
  IElementType KW_DEF = new YakshaTokenType("KW_DEF");
  IElementType KW_DEFER = new YakshaTokenType("KW_DEFER");
  IElementType KW_DEL = new YakshaTokenType("KW_DEL");
  IElementType KW_ELIF = new YakshaTokenType("KW_ELIF");
  IElementType KW_ELSE = new YakshaTokenType("KW_ELSE");
  IElementType KW_FALSE = new YakshaTokenType("KW_FALSE");
  IElementType KW_FOR = new YakshaTokenType("KW_FOR");
  IElementType KW_IF = new YakshaTokenType("KW_IF");
  IElementType KW_IMPORT = new YakshaTokenType("KW_IMPORT");
  IElementType KW_IN = new YakshaTokenType("KW_IN");
  IElementType KW_NONE = new YakshaTokenType("KW_NONE");
  IElementType KW_PASS = new YakshaTokenType("KW_PASS");
  IElementType KW_RETURN = new YakshaTokenType("KW_RETURN");
  IElementType KW_RUNTIMEFEATURE = new YakshaTokenType("KW_RUNTIMEFEATURE");
  IElementType KW_TRUE = new YakshaTokenType("KW_TRUE");
  IElementType KW_WHILE = new YakshaTokenType("KW_WHILE");
  IElementType NL = new YakshaTokenType("NL");
  IElementType NUMBER = new YakshaTokenType("NUMBER");
  IElementType OPERATOR_AND = new YakshaTokenType("OPERATOR_AND");
  IElementType OPERATOR_ARROW = new YakshaTokenType("OPERATOR_ARROW");
  IElementType OPERATOR_AT = new YakshaTokenType("OPERATOR_AT");
  IElementType OPERATOR_B_AND = new YakshaTokenType("OPERATOR_B_AND");
  IElementType OPERATOR_B_AND_EQ = new YakshaTokenType("OPERATOR_B_AND_EQ");
  IElementType OPERATOR_B_NOT = new YakshaTokenType("OPERATOR_B_NOT");
  IElementType OPERATOR_B_OR = new YakshaTokenType("OPERATOR_B_OR");
  IElementType OPERATOR_B_OR_EQ = new YakshaTokenType("OPERATOR_B_OR_EQ");
  IElementType OPERATOR_B_XOR = new YakshaTokenType("OPERATOR_B_XOR");
  IElementType OPERATOR_B_XOR_EQ = new YakshaTokenType("OPERATOR_B_XOR_EQ");
  IElementType OPERATOR_CLOSE_P = new YakshaTokenType("OPERATOR_CLOSE_P");
  IElementType OPERATOR_CLOSE_SQB = new YakshaTokenType("OPERATOR_CLOSE_SQB");
  IElementType OPERATOR_COLON = new YakshaTokenType("OPERATOR_COLON");
  IElementType OPERATOR_COMMA = new YakshaTokenType("OPERATOR_COMMA");
  IElementType OPERATOR_COMPARISON = new YakshaTokenType("OPERATOR_COMPARISON");
  IElementType OPERATOR_DIV = new YakshaTokenType("OPERATOR_DIV");
  IElementType OPERATOR_DIV_EQ = new YakshaTokenType("OPERATOR_DIV_EQ");
  IElementType OPERATOR_DOT = new YakshaTokenType("OPERATOR_DOT");
  IElementType OPERATOR_EQ = new YakshaTokenType("OPERATOR_EQ");
  IElementType OPERATOR_MINUS = new YakshaTokenType("OPERATOR_MINUS");
  IElementType OPERATOR_MINUS_EQ = new YakshaTokenType("OPERATOR_MINUS_EQ");
  IElementType OPERATOR_MUL = new YakshaTokenType("OPERATOR_MUL");
  IElementType OPERATOR_MUL_EQ = new YakshaTokenType("OPERATOR_MUL_EQ");
  IElementType OPERATOR_NOT = new YakshaTokenType("OPERATOR_NOT");
  IElementType OPERATOR_OPEN_P = new YakshaTokenType("OPERATOR_OPEN_P");
  IElementType OPERATOR_OPEN_SQB = new YakshaTokenType("OPERATOR_OPEN_SQB");
  IElementType OPERATOR_OR = new YakshaTokenType("OPERATOR_OR");
  IElementType OPERATOR_PLUS = new YakshaTokenType("OPERATOR_PLUS");
  IElementType OPERATOR_PLUS_EQ = new YakshaTokenType("OPERATOR_PLUS_EQ");
  IElementType OPERATOR_REMAINDER = new YakshaTokenType("OPERATOR_REMAINDER");
  IElementType OPERATOR_REMAINDER_EQ = new YakshaTokenType("OPERATOR_REMAINDER_EQ");
  IElementType OPERATOR_SHL = new YakshaTokenType("OPERATOR_SHL");
  IElementType OPERATOR_SHL_EQ = new YakshaTokenType("OPERATOR_SHL_EQ");
  IElementType OPERATOR_SHR = new YakshaTokenType("OPERATOR_SHR");
  IElementType OPERATOR_SHR_EQ = new YakshaTokenType("OPERATOR_SHR_EQ");
  IElementType PRIMITIVE_DATA_TYPE = new YakshaTokenType("PRIMITIVE_DATA_TYPE");
  IElementType S = new YakshaTokenType("S");
  IElementType STRING = new YakshaTokenType("STRING");

  class Factory {
    public static PsiElement createElement(ASTNode node) {
      IElementType type = node.getElementType();
      if (type == ANNOTATION) {
        return new YakshaAnnotationImpl(node);
      }
      else if (type == ANNOTATION_ARG) {
        return new YakshaAnnotationArgImpl(node);
      }
      else if (type == ARGUMENTS) {
        return new YakshaArgumentsImpl(node);
      }
      else if (type == ASSIGNMENT_STATEMENT) {
        return new YakshaAssignmentStatementImpl(node);
      }
      else if (type == ASSIGNMENT_STATEMENT_WO_INDENT) {
        return new YakshaAssignmentStatementWoIndentImpl(node);
      }
      else if (type == BITWISE) {
        return new YakshaBitwiseImpl(node);
      }
      else if (type == BREAK_STATEMENT) {
        return new YakshaBreakStatementImpl(node);
      }
      else if (type == CCODE_STATEMENT) {
        return new YakshaCcodeStatementImpl(node);
      }
      else if (type == CCODE_STATEMENT_WO_INDENT) {
        return new YakshaCcodeStatementWoIndentImpl(node);
      }
      else if (type == CLASS_BITS) {
        return new YakshaClassBitsImpl(node);
      }
      else if (type == CLASS_BLOCK) {
        return new YakshaClassBlockImpl(node);
      }
      else if (type == CLASS_FIELD) {
        return new YakshaClassFieldImpl(node);
      }
      else if (type == CLASS_FIELD_WO_INDENT) {
        return new YakshaClassFieldWoIndentImpl(node);
      }
      else if (type == CLASS_STATEMENT) {
        return new YakshaClassStatementImpl(node);
      }
      else if (type == COMPARISON) {
        return new YakshaComparisonImpl(node);
      }
      else if (type == CONST_STATEMENT) {
        return new YakshaConstStatementImpl(node);
      }
      else if (type == CONTINUE_STATEMENT) {
        return new YakshaContinueStatementImpl(node);
      }
      else if (type == DATA_TYPE) {
        return new YakshaDataTypeImpl(node);
      }
      else if (type == DATA_TYPE_ARGS) {
        return new YakshaDataTypeArgsImpl(node);
      }
      else if (type == DATA_TYPE_ARG_BITS) {
        return new YakshaDataTypeArgBitsImpl(node);
      }
      else if (type == DATA_TYPE_BIT) {
        return new YakshaDataTypeBitImpl(node);
      }
      else if (type == DATA_TYPE_IDENTIFIER) {
        return new YakshaDataTypeIdentifierImpl(node);
      }
      else if (type == DEFER_STATEMENT) {
        return new YakshaDeferStatementImpl(node);
      }
      else if (type == DEFER_STATEMENT_WO_INDENT) {
        return new YakshaDeferStatementWoIndentImpl(node);
      }
      else if (type == DEF_BITS) {
        return new YakshaDefBitsImpl(node);
      }
      else if (type == DEF_BLOCK) {
        return new YakshaDefBlockImpl(node);
      }
      else if (type == DEF_PARAM) {
        return new YakshaDefParamImpl(node);
      }
      else if (type == DEF_PARAMS) {
        return new YakshaDefParamsImpl(node);
      }
      else if (type == DEF_STATEMENT) {
        return new YakshaDefStatementImpl(node);
      }
      else if (type == DEL_STATEMENT) {
        return new YakshaDelStatementImpl(node);
      }
      else if (type == DEL_STATEMENT_WO_INDENT) {
        return new YakshaDelStatementWoIndentImpl(node);
      }
      else if (type == ELIF_STATEMENT) {
        return new YakshaElifStatementImpl(node);
      }
      else if (type == ELSE_STATEMENT) {
        return new YakshaElseStatementImpl(node);
      }
      else if (type == EMPTY_LINE) {
        return new YakshaEmptyLineImpl(node);
      }
      else if (type == EXP) {
        return new YakshaExpImpl(node);
      }
      else if (type == EXPR_STATEMENT) {
        return new YakshaExprStatementImpl(node);
      }
      else if (type == EXPR_STATEMENT_WO_INDENT) {
        return new YakshaExprStatementWoIndentImpl(node);
      }
      else if (type == FACTOR) {
        return new YakshaFactorImpl(node);
      }
      else if (type == FNCALL) {
        return new YakshaFncallImpl(node);
      }
      else if (type == FOREACH_STATEMENT) {
        return new YakshaForeachStatementImpl(node);
      }
      else if (type == FORENDLESS_STATEMENT) {
        return new YakshaForendlessStatementImpl(node);
      }
      else if (type == IF_STATEMENT) {
        return new YakshaIfStatementImpl(node);
      }
      else if (type == IMPORT_STATEMENT) {
        return new YakshaImportStatementImpl(node);
      }
      else if (type == LET_STATEMENT) {
        return new YakshaLetStatementImpl(node);
      }
      else if (type == LITERAL) {
        return new YakshaLiteralImpl(node);
      }
      else if (type == LOGIC_AND) {
        return new YakshaLogicAndImpl(node);
      }
      else if (type == LOGIC_OR) {
        return new YakshaLogicOrImpl(node);
      }
      else if (type == OUTER_STATEMENT) {
        return new YakshaOuterStatementImpl(node);
      }
      else if (type == PAREN_EXP) {
        return new YakshaParenExpImpl(node);
      }
      else if (type == PASS_STATEMENT) {
        return new YakshaPassStatementImpl(node);
      }
      else if (type == PASS_STATEMENT_WO_INDENT) {
        return new YakshaPassStatementWoIndentImpl(node);
      }
      else if (type == PRIMARY) {
        return new YakshaPrimaryImpl(node);
      }
      else if (type == RETURN_STATEMENT) {
        return new YakshaReturnStatementImpl(node);
      }
      else if (type == RETURN_STATEMENT_WO_INDENT) {
        return new YakshaReturnStatementWoIndentImpl(node);
      }
      else if (type == RUNTIMEFEATURE_STATEMENT) {
        return new YakshaRuntimefeatureStatementImpl(node);
      }
      else if (type == SINGLE_LINE_CLASS_BITS) {
        return new YakshaSingleLineClassBitsImpl(node);
      }
      else if (type == SINGLE_LINE_DEF_BITS) {
        return new YakshaSingleLineDefBitsImpl(node);
      }
      else if (type == TERM) {
        return new YakshaTermImpl(node);
      }
      else if (type == UNARY) {
        return new YakshaUnaryImpl(node);
      }
      else if (type == WHILE_STATEMENT) {
        return new YakshaWhileStatementImpl(node);
      }
      throw new AssertionError("Unknown element type: " + type);
    }
  }
}
