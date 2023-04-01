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

    public void fillTo(DefaultMutableTreeNode root) {
        DefaultMutableTreeNode builtins = new DefaultMutableTreeNode("builtins");
        BUILTIN_FUNCTIONS.forEach((k, v) -> {
            DefaultMutableTreeNode node = new DefaultMutableTreeNode(DocWithIcon.dwi(v.typeDoc, YakshaIcons.BUILT_IN));
            addComments(v.comment, node);
            builtins.add(node);
        });
        root.add(builtins);
        doc.forEach((k, d) -> {
            DefaultMutableTreeNode lib = new DefaultMutableTreeNode(k);
            d.fill(lib);
            root.add(lib);
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

        public void fill(DefaultMutableTreeNode lib) {
            global_consts.forEach(c -> {
                DefaultMutableTreeNode node = new DefaultMutableTreeNode(DocWithIcon.dwi(c.getRepr(), YakshaIcons.CONSTANT));
                addComments(c.getTypeText(), node);
                lib.add(node);
            });
            classes.forEach(c -> {
                DefaultMutableTreeNode node = new DefaultMutableTreeNode(DocWithIcon.dwi(c.name, YakshaIcons.CLASS));
                addComments(c.getTypeText(), node);
                for (Param p : c.members) {
                    node.add(new DefaultMutableTreeNode(DocWithIcon.dwi(p.toString(), YakshaIcons.SUB_SECTION)));
                }
                lib.add(node);
            });
            functions.forEach(c -> {
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
