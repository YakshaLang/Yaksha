package org.intellij.sdk.language.yaksha_docs;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;
import com.intellij.codeInsight.completion.CompletionResultSet;
import com.intellij.codeInsight.lookup.LookupElementBuilder;
import org.intellij.sdk.language.YakshaIcons;

import java.io.IOException;
import java.io.InputStreamReader;
import java.io.Reader;
import java.lang.reflect.Type;
import java.util.*;

public class Loader {
    private static final Type TYPE_OF_HASHMAP = new TypeToken<Map<String, Doc>>() {
    }.getType();
    private static final Gson GSON = new GsonBuilder().create();

    public final Map<String, Doc> doc;

    public static final Loader INSTANCE = new Loader();

    public Loader() {
        Map<String, Doc> doc;
        try (Reader reader = new InputStreamReader(Objects.requireNonNull(this.getClass().getResourceAsStream("/apidocs/docs.json")))) {
            doc = GSON.fromJson(reader, TYPE_OF_HASHMAP);
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
        for (GlobalConstant c: documentation.global_consts) {
            resultSet.addElement(LookupElementBuilder.create(c.name)
                    .withIcon(YakshaIcons.CONSTANT)
                    .withTypeText(c.getTypeText())
                    .withPresentableText(c.getRepr())
            );
        }
        for (Fn f: documentation.functions) {
            resultSet.addElement(LookupElementBuilder.create(f.name)
                    .withIcon(YakshaIcons.DEF)
                    .withTypeText(f.getTypeText())
                    .withPresentableText(f.getRepr())
            );
        }

        for (Cls cl: documentation.classes) {
            resultSet.addElement(LookupElementBuilder.create(cl.name)
                    .withIcon(YakshaIcons.CLASS)
                    .withTypeText(cl.getTypeText())
                    .withPresentableText(cl.getRepr())
            );
        }
        return true;
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
    }


}
