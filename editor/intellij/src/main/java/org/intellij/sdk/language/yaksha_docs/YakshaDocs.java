package org.intellij.sdk.language.yaksha_docs;

import com.google.common.collect.ImmutableMap;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;
import com.intellij.codeInsight.completion.CompletionResultSet;
import com.intellij.codeInsight.lookup.LookupElementBuilder;
import org.intellij.sdk.language.DocBuilder;
import org.intellij.sdk.language.YakshaIcons;

import javax.swing.*;
import javax.swing.tree.DefaultMutableTreeNode;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.lang.reflect.Type;
import java.util.*;

public class YakshaDocs {
    public static final Map<String, BuiltinDoc> BUILTIN_FUNCTIONS = ImmutableMap.<String, BuiltinDoc>builder()
            .put("print", BuiltinDoc.b("print(primitive) -> None", "Print without a new line"))
            .put("println", BuiltinDoc.b("println(primitive) -> None", "Print + new line"))
            .put("len", BuiltinDoc.b("len(Array[T]) -> int", "Get length of arrays,maps"))
            .put("arrput", BuiltinDoc.b("arrput(Array[T], T) -> None", "Put item to an array"))
            .put("arrpop", BuiltinDoc.b("arrpop(Array[T]) -> T", "Remove last item from an array and return it"))
            .put("arrnew", BuiltinDoc.b("arrnew(\"T\", int) -> Array[T]", "Create a new array of given size. (Uninitialized elements)"))
            .put("arrsetcap", BuiltinDoc.b("arrsetcap(Array[T], int) -> None", "Set array capacity / grow memory. Does not affect length."))
            .put("arrsetlen", BuiltinDoc.b("arrsetlen(Array[T], int) -> None", "Set array length. Each element will be an uninitialized element."))
            .put("array", BuiltinDoc.b("array(\"T\", T...) -> Array[T]", "Create a new array from given elements"))
            .put("getref", BuiltinDoc.b("getref(T) -> Ptr[T]", "Get a pointer to given object"))
            .put("unref", BuiltinDoc.b("unref(Ptr[T]) -> T", "Dereference a pointer"))
            .put("charat", BuiltinDoc.b("charat(str, int) -> int", "Get a character at a specific location in string"))
            .put("shnew", BuiltinDoc.b("shnew(Array[SMEntry[T]]) -> None", "Initialize Array[SMEntry[T]] object"))
            .put("shput", BuiltinDoc.b("shput(Array[SMEntry[T]], str, T) -> None", "Put item to a Array[SMEntry[T]]"))
            .put("shget", BuiltinDoc.b("shget(Array[SMEntry[T]], str) -> T", "Get item from a Array[SMEntry[T]]"))
            .put("shgeti", BuiltinDoc.b("shgeti(Array[SMEntry[T]], str) -> int", "Get item index from a Array[SMEntry[T]] (-1 if not found)"))
            .put("hmnew", BuiltinDoc.b("hmnew(Array[MEntry[K,T]]) -> None", "Initialize Array[MEntry[K,T]] object"))
            .put("hmput", BuiltinDoc.b("hmput(Array[MEntry[K,T]], K, T) -> None", "Put item to a Array[MEntry[K,T]]"))
            .put("hmget", BuiltinDoc.b("hmget(Array[MEntry[K,T]], K) -> T", "Get item from a Array[MEntry[K,T]]"))
            .put("hmgeti", BuiltinDoc.b("hmgeti(Array[MEntry[K,T]], K) -> int", "Get item index from a Array[MEntry[K,T]] (-1 if not found)"))
            .put("cast", BuiltinDoc.b("cast(\"T\", X) -> T", "Data type casting builtin"))
            .put("qsort", BuiltinDoc.b("qsort(Array[T],Function[In[Const[AnyPtrToConst],Const[AnyPtrToConst]],Out[int]]) -> bool", "Sort an array, returns True if successful"))
            .put("iif", BuiltinDoc.b("iif(bool, T, T) -> T", "Ternary functionality"))
            .put("foreach", BuiltinDoc.b("foreach(Array[T],Function[In[T,V],Out[bool]],V) -> bool", "For each element in array execute given function"))
            .put("countif", BuiltinDoc.b("countif(Array[T],Function[In[T,V],Out[bool]],V) -> int", "For each element in array count if function returns true"))
            .put("filter", BuiltinDoc.b("filter(Array[T],Function[In[T,V],Out[bool]],V) -> Array[T]", "Create a new array with filtered elements based on return value of given function"))
            .put("map", BuiltinDoc.b("map(Array[T],Function[In[T,V],Out[K]],V) -> Array[K]", "Create a new array with result of given function"))
            .put("binarydata", BuiltinDoc.b("binarydata(\"data\") -> Const[Ptr[Const[u8]]]", "Create constant binary data (must pass in a string literal).\nReturns Const[Ptr[Const[u8]]] that does not need to be deleted."))
            .build();
    public static final Set<String> BUILTIN_FUNCTION_NAMES = BUILTIN_FUNCTIONS.keySet();
    public static final Set<String> LISP_BUILTIN_NAMES = Set.of("YK_TOKEN_KEYWORD_RUNTIMEFEATURE", "YK_TOKEN_KEYWORD_RETURN",
            "YK_TOKEN_KEYWORD_OR", "YK_TOKEN_KEYWORD_NOT", "YK_TOKEN_KEYWORD_MACROS", "YK_TOKEN_KEYWORD_IMPORT", "YK_TOKEN_KEYWORD_IF",
            "YK_TOKEN_KEYWORD_ELSE", "YK_TOKEN_KEYWORD_ELIF", "YK_TOKEN_KEYWORD_DEL", "YK_TOKEN_KEYWORD_DEFER", "YK_TOKEN_KEYWORD_CLASS",
            "YK_TOKEN_KEYWORD_CCODE", "YK_TOKEN_KEYWORD_BREAK", "YK_TOKEN_KEYWORD_AS", "YK_TOKEN_KEYWORD_AND", "YK_TOKEN_XOR_EQ", "YK_TOKEN_UINTEGER_OCT_16",
            "YK_TOKEN_UINTEGER_HEX_8", "YK_TOKEN_UINTEGER_HEX_64", "YK_TOKEN_UINTEGER_DECIMAL_64", "YK_TOKEN_UINTEGER_DECIMAL_16",
            "YK_TOKEN_UINTEGER_DECIMAL", "YK_TOKEN_UINTEGER_BIN_8", "YK_TOKEN_UINTEGER_BIN_64", "YK_TOKEN_TILDE",
            "YK_TOKEN_THREE_QUOTE_STRING", "YK_TOKEN_SQUARE_BRACKET_CLOSE", "YK_TOKEN_SHR", "YK_TOKEN_SHL_EQ", "YK_TOKEN_POWER",
            "YK_TOKEN_PAREN_CLOSE", "YK_TOKEN_OR_EQ", "YK_TOKEN_NOT_SYMBOL", "YK_TOKEN_SHR_EQ", "YK_TOKEN_NAME", "YK_TOKEN_LESS_EQ",
            "YK_TOKEN_LESS", "YK_TOKEN_INT_DIV_EQ", "YK_TOKEN_INTEGER_OCT_8", "YK_TOKEN_INTEGER_OCT", "yk_create_token", "YK_TOKEN_SUB_EQ",
            "YK_TOKEN_INTEGER_HEX_8", "YK_TOKEN_INTEGER_HEX_64", "time", "random", "to_int", "YK_KEY_WHAT", "is_callable", "YK_TOKEN_UINTEGER_OCT",
            "YK_TOKEN_UINTEGER_BIN_16", "is_list", "input", "io_read_file", "print", "YK_TOKEN_KEYWORD_STRUCT", "/", "YK_TOKEN_SHL", "newline",
            "YK_TOKEN_UINTEGER_DECIMAL_8", "to_string", "io_write_file", "defun", "pop", "bitwise_or", "is_truthy", "not", "=", "YK_TOKEN_MUL_EQ",
            "set", "len", "YK_TOKEN_UINTEGER_BIN", "YK_TOKEN_SUB", "YK_TOKEN_EQ_EQ", "is_nil", "cons", "or", "filter", "for", "noop", "YK_TOKEN_INTEGER_DECIMAL",
            "YK_TOKEN_KEYWORD_WHILE", "head", "while", "try", "modulo", "YK_TOKEN_PLUS_EQ", "tail", "YK_TOKEN_BA_INDENT", "YK_TOKEN_KEYWORD_FOR",
            "-", "list", "YK_TOKEN_MOD", "<", "==", ">=", "is_string", "reduce", "n____original_println", "+", "push", "yk_register",
            "true", "range", "YK_TOKEN_INTEGER_DECIMAL_16", "yk_is_token", "YK_TOKEN_KEYWORD_TRY", "YK_TOKEN_OR", "YK_TOKEN_INTEGER_HEX_16",
            "yk_get_type", "YK_TOKEN_XOR", ">", "YK_TOKEN_KEYWORD_TRUE", "YK_TYPE_EXPR", "YK_TOKEN_STRING",
            "YK_TOKEN_INTEGER_OCT_64", "YK_TYPE_STMT", "<=", "YK_TOKEN_NOT_EQ", "and", "YK_TOKEN_UINTEGER_HEX_16",
            "YK_TOKEN_EQ", "YK_TOKEN_FLOAT_NUMBER", "YK_TOKEN_PAREN_OPEN", "println", "YK_TOKEN_MOD_EQ", "define",
            "if", "map", "do", "is_int", "YK_TOKEN_KEYWORD_CONTINUE", "YK_TOKEN_KEYWORD_NONE", "quote",
            "eval", "YK_TOKEN_DIV_EQ", "ykt_integer_decimal", "YK_TOKEN_KEYWORD_IN", "insert", "*", "remove", "map_keys",
            "def", "map_get", "YK_TOKEN_KEYWORD_FROM", "map_remove", "bitwise_xor", "bitwise_and", "bitwise_not", "YK_TOKEN_COMMA",
            "YK_TOKEN_INTEGER_HEX", "bitwise_left_shift", "YK_TOKEN_COLON", "index", "YK_TOKEN_KEYWORD_DEF", "map_set",
            "YK_TOKEN_UINTEGER_OCT_64", "map_values", "YK_TOKEN_INT_DIV", "YK_TOKEN_INTEGER_OCT_16", "this",
            "YK_TOKEN_UINTEGER_HEX", "parent", "YK_TOKEN_INTEGER_BIN_16", "YK_TOKEN_SQUARE_BRACKET_OPEN", "repr",
            "YK_TOKEN_POWER_EQ", "cond", "ghost", "raise_error", "n____original_print", "YK_PRELUDE_INCLUDED",
            "disable_print", "false", "enable_print", "YK_TOKEN_KEYWORD_FALSE", "YK_OBJECT_TYPE", "YK_TOKEN_PLUS",
            "nil", "YK_TYPE_TOKEN", "YK_TOKEN_KEYWORD_PASS", "yk_what", "yk_is_expr", "parse", "yk_is_stmt",
            "YK_TOKEN_MUL", "YK_TOKEN_CURLY_BRACKET_OPEN", "YK_TOKEN_AND", "YK_TOKEN_AND_EQ", "lambda", "YK_TOKEN_INTEGER_DECIMAL_64",
            "bitwise_right_shift", "YK_TOKEN_ARROW", "YK_TOKEN_KEYWORD_ASSERT", "YK_TOKEN_AT", "YK_TOKEN_INTEGER_DECIMAL_8", "YK_TOKEN_BA_DEDENT",
            "YK_TOKEN_INTEGER_BIN_64", "YK_TOKEN_CURLY_BRACKET_CLOSE", "try_catch", "YK_TOKEN_DIV", "scope", "YK_TOKEN_DOT",
            "YK_TOKEN_DOUBLE_NUMBER", "YK_TOKEN_ELLIPSIS", "YK_TOKEN_GREAT", "YK_TOKEN_UINTEGER_OCT_8", "!=",
            "YK_TOKEN_GREAT_EQ", "YK_TOKEN_INTEGER_BIN", "map_has", "YK_TOKEN_INTEGER_BIN_8");

    public static final YakshaDocs INSTANCE = new YakshaDocs();
    private final Map<String, Doc> doc;

    public YakshaDocs() {
        final Type typeOfHashmap = new TypeToken<Map<String, Doc>>() {
        }.getType();
        final Gson gson = new GsonBuilder().create();

        Map<String, Doc> doc;
        try (Reader reader = new InputStreamReader(Objects
                .requireNonNull(this.getClass().getResourceAsStream("/apidocs/docs.json")))) {
            doc = gson.fromJson(reader, typeOfHashmap);
        } catch (IOException e) {
            doc = new HashMap<>();
        }
        this.doc = doc;
    }

    public boolean fillTo(CompletionResultSet resultSet, String importPath) {
        Doc documentation = doc.get(importPath);
        if (documentation == null) {
            return false;
        }
        for (GlobalConstant c : documentation.global_consts) {
            resultSet.addElement(LookupElementBuilder.create(c.name)
                    .withIcon(YakshaIcons.CONSTANT)
                    .withTypeText(c.getTypeText())
                    .withPresentableText(c.getRepr())
            );
        }
        for (Fn f : documentation.functions) {
            resultSet.addElement(LookupElementBuilder.create(f.name)
                    .withIcon(YakshaIcons.DEF)
                    .withTypeText(f.getTypeText())
                    .withPresentableText(f.getRepr())
            );
        }

        for (Cls cl : documentation.classes) {
            resultSet.addElement(LookupElementBuilder.create(cl.name)
                    .withIcon(YakshaIcons.CLASS)
                    .withTypeText(cl.getTypeText())
                    .withPresentableText(cl.getRepr())
            );
        }
        return true;
    }

    public String generateDoc(String importPath, String name) {
        Doc documentation = doc.get(importPath);
        if (documentation == null) {
            return "";
        }
        // TODO hashmap this thing to make it faster
        for (GlobalConstant c : documentation.global_consts) {
            if (c.name.equals(name)) {
                return c.genDoc(importPath);
            }
        }
        for (Fn f : documentation.functions) {
            if (f.name.equals(name)) {
                return f.genDoc(importPath);
            }
        }

        for (Cls cl : documentation.classes) {
            if (cl.name.equals(name)) {
                return cl.genDoc(importPath);
            }
        }
        return "";
    }

    private static boolean keepOut(final String filter, final String haystack, final String haystack2) {
        if (filter == null || filter.isBlank()) {
            return false;
        }
        return !((!haystack.isBlank() && haystack.toLowerCase(Locale.ENGLISH).contains(filter))
                || (!haystack2.isBlank() && haystack2.toLowerCase(Locale.ENGLISH).contains(filter)));
    }

    public void fillTo(DefaultMutableTreeNode root, final String filter) {
        final String filterLowerCase = filter.toLowerCase(Locale.ENGLISH);
        DefaultMutableTreeNode builtins = new DefaultMutableTreeNode("builtins");
        BUILTIN_FUNCTIONS.forEach((k, v) -> {
            if (keepOut(filterLowerCase, v.typeDoc, v.comment)) {
                return;
            }
            DefaultMutableTreeNode node = new DefaultMutableTreeNode(DocWithIcon.dwi(v.typeDoc, YakshaIcons.BUILT_IN));
            addComments(v.comment, node);
            builtins.add(node);
        });
        if (builtins.getChildCount() > 0) {
            root.add(builtins);
        }
        doc.forEach((k, d) -> {
            DefaultMutableTreeNode lib = new DefaultMutableTreeNode(k);
            d.fill(lib, filterLowerCase);
            if (lib.getChildCount() > 0) {
                root.add(lib);
            }
        });
    }

    private static void addComments(String allComments, DefaultMutableTreeNode node) {
        if (allComments.isBlank()) {
            return;
        }
        String[] comments = allComments.split("\\n");
        for (final String commentLine : comments) {
            node.add(new DefaultMutableTreeNode(DocWithIcon.dwi(commentLine, YakshaIcons.COMMENT)));
        }
    }

    public static class Doc {
        public List<Import> imports;
        public List<GlobalConstant> global_consts;
        public List<Fn> functions;
        public List<Cls> classes;

        public void fill(DefaultMutableTreeNode lib, String filterLowerCase) {
            global_consts.forEach(c -> {
                if (keepOut(filterLowerCase, c.getRepr(), c.getTypeText())) {
                    return;
                }
                DefaultMutableTreeNode node = new DefaultMutableTreeNode(DocWithIcon.dwi(c.getRepr(), YakshaIcons.CONSTANT));
                addComments(c.getTypeText(), node);
                lib.add(node);
            });
            classes.forEach(c -> {
                if (keepOut(filterLowerCase, c.name, c.getTypeText())) {
                    return;
                }
                DefaultMutableTreeNode node = new DefaultMutableTreeNode(DocWithIcon.dwi(c.name, YakshaIcons.CLASS));
                addComments(c.getTypeText(), node);
                for (Param p : c.members) {
                    node.add(new DefaultMutableTreeNode(DocWithIcon.dwi(p.toString(), YakshaIcons.SUB_SECTION)));
                }
                lib.add(node);
            });
            functions.forEach(c -> {
                if (keepOut(filterLowerCase, c.getRepr(), c.getTypeText())) {
                    return;
                }
                DefaultMutableTreeNode node = new DefaultMutableTreeNode(DocWithIcon.dwi(c.getRepr(), YakshaIcons.DEF));
                addComments(c.getTypeText(), node);
                lib.add(node);
            });
        }
    }

    public static class Import {
        public String alias;
        public List<String> path;
    }

    public static class GlobalConstant {
        public String name;
        public String comment;
        public Dt datatype;

        public String getRepr() {
            return name + ": " + datatype.toString();
        }

        public String getTypeText() {
            return comment;
        }

        public String genDoc(final String importPath) {
            DocBuilder b = new DocBuilder();
            b.title(importPath + "." + name);
            b.description(comment.replace("\n", "<br />"));
            b.keyValue("<b>Kind</b>", "Constant");
            b.keyValue("Data Type", datatype.toString());
            return b.build();
        }
    }

    public static class Fn {
        public String name;
        public String comment;
        public Dt return_type;
        public List<Param> parameters;
        public List<Ant> annotations;

        public String getRepr() {
            StringBuilder b = new StringBuilder();
            b.append(name).append("(");
            if (parameters != null && !parameters.isEmpty()) {
                final StringJoiner j = new StringJoiner(", ");
                parameters.forEach(e -> j.add(e.toString()));
                b.append(j);
            }
            b.append(") -> ").append(return_type.toString());
            return b.toString();
        }

        public String getTypeText() {
            return comment;
        }

        public String genDoc(final String importPath) {
            DocBuilder b = new DocBuilder();
            b.title(importPath + "." + name);
            b.description(comment.replace("\n", "<br />"));
            b.keyValue("<b>Kind</b>", "Function");
            if (parameters != null && !parameters.isEmpty()) {
                parameters.forEach(p -> b.typeKeyValue("Param", p.name, p.datatype.toString()));
            }
            b.keyValue("Return Type", return_type.toString());
            return b.build();
        }
    }

    public static class Dt {
        public String type;
        public String module;
        public List<Dt> arguments;

        @Override
        public String toString() {
            StringBuilder b = new StringBuilder();
            if (module != null && !module.isEmpty()) {
                b.append(module).append(".");
            }
            b.append(type);
            if (arguments != null && !arguments.isEmpty()) {
                b.append("[");
                final StringJoiner j = new StringJoiner(", ");
                arguments.forEach(e -> j.add(e.toString()));
                b.append(j);
                b.append("]");
            }
            return b.toString();
        }
    }

    public static class Ant {
        public String name;
        public String argument;
    }

    public static class Param {
        public String name;
        public Dt datatype;

        @Override
        public String toString() {
            return name + ": " + datatype;
        }
    }

    public static class Cls {
        public String name;
        public String comment;
        public List<Param> members;
        public List<Ant> annotations;

        public String getRepr() {
            StringBuilder b = new StringBuilder();
            b.append(name);
            if (members != null && !members.isEmpty()) {
                b.append(" { ");
                final StringJoiner j = new StringJoiner(", ");
                members.forEach(e -> j.add(e.toString()));
                b.append(j);
                b.append(" } ");
            }
            return b.toString();
        }

        public String getTypeText() {
            return comment;
        }

        public String genDoc(final String importPath) {
            DocBuilder b = new DocBuilder();
            b.title(importPath + "." + name);
            b.description(comment.replace("\n", "<br />"));
            b.keyValue("<b>Kind</b>", "Class");
            if (members != null && !members.isEmpty()) {
                members.forEach(p -> b.typeKeyValue("Member", p.name, p.datatype.toString()));
            }
            return b.build();
        }
    }

    public static class BuiltinDoc {
        public String typeDoc;
        public String comment;

        public static BuiltinDoc b(final String typeDoc, final String comment) {
            BuiltinDoc bd = new BuiltinDoc();
            bd.typeDoc = typeDoc;
            bd.comment = comment;
            return bd;
        }

        public String typeText() {
            return typeDoc;
        }
    }

    public static class DocWithIcon {
        public final String item;
        public final Icon icon;

        private DocWithIcon(String item, Icon icon) {
            this.item = item;
            this.icon = icon;
        }

        public static DocWithIcon dwi(String item, Icon icon) {
            return new DocWithIcon(item, icon);
        }

        @Override
        public String toString() {
            return item;
        }
    }

}
