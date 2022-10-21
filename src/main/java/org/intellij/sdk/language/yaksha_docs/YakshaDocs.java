package org.intellij.sdk.language.yaksha_docs;

import com.google.common.collect.ImmutableMap;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;
import com.intellij.codeInsight.completion.CompletionResultSet;
import com.intellij.codeInsight.lookup.LookupElementBuilder;
import org.intellij.sdk.language.DocBuilder;
import org.intellij.sdk.language.YakshaIcons;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.lang.reflect.Type;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Set;
import java.util.StringJoiner;

public class YakshaDocs {
    public static final Map<String, String> BUILTIN_FUNCTIONS = ImmutableMap.<String, String>builder()
            .put("print", "Print without a new line")
            .put("println", "Print + new line")
            .put("len", "Get length of arrays,maps")
            .put("arrput", "Put item to an array")
            .put("arrpop", "Remove last item from an array and return it")
            .put("arrnew", "Create a new array of given size. (Uninitialized elements)")
            .put("array", "Create a new array from given elements")
            .put("getref", "Get a pointer to given object")
            .put("unref", "Dereference a pointer")
            .put("charat", "Get a character at a specific location in string")
            .put("shnew", "Initialize Array[SMEntry[T]] object")
            .put("shput", "Put item to a Array[SMEntry[T]]")
            .put("shget", "Get item from a Array[SMEntry[T]]")
            .put("shgeti", "Get item index from a Array[SMEntry[T]] (-1 if not found)")
            .put("hmnew", "Initialize Array[MEntry[T]] object")
            .put("hmput", "Put item to a Array[MEntry[T]]")
            .put("hmget", "Get item from a Array[MEntry[T]]")
            .put("hmgeti", "Get item index from a Array[MEntry[T]] (-1 if not found)")
            .put("cast", "Data type casting builtin")
            .put("qsort", "Sort an array, returns True if successful")
            .put("iif", "Ternary functionality")
            .put("foreach", "For each element in array execute given function")
            .put("countif", "For each element in array count if function returns true")
            .put("filter", "Create a new array with filtered elements based on return value of given function")
            .put("map", "Create a new array with result of given function")
            .put("binarydata", "Create constant binary data. Returns Const[Ptr[Const[u8]]] that does not need to be deleted.")
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

    public static class Doc {
        public List<Import> imports;
        public List<GlobalConstant> global_consts;
        public List<Fn> functions;
        public List<Cls> classes;
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


}
