package org.intellij.sdk.language;

import com.intellij.lang.documentation.DocumentationMarkup;

import java.util.ArrayList;
import java.util.List;

public class DocBuilder {
    private final StringBuilder sb;
    private final List<KV> args = new ArrayList<>();
    private String title = "no title";
    private String description = "no desc";

    public DocBuilder() {
        sb = new StringBuilder();
    }

    public DocBuilder title(final String title) {
        this.title = title;
        return this;
    }

    public DocBuilder keyValue(final String k, final String v) {
        args.add(new KV(k, v));
        return this;
    }

    public DocBuilder typeKeyValue(final String type, final String k, final String v) {
        return keyValue("<span color='green'>" + type + "</span><b>:</b> <code>" + k + "</code>", "<code>" + v + "</code>");
    }

    public DocBuilder description(final String descriptionText) {
        this.description = descriptionText;
        return this;
    }

    public String build() {
        sb.setLength(0);
        addTitle(this.title);
        addDescription(this.description);
        if (!this.args.isEmpty()) {
            sb.append(DocumentationMarkup.SECTIONS_START);
            for (KV kv : args) {
                addKeyValueSection(kv.k, kv.v);
            }
            sb.append(DocumentationMarkup.SECTIONS_END);
        }
        return sb.toString();
    }

    private void addDescription(final String value) {
        sb.append(DocumentationMarkup.CONTENT_START);
        sb.append(value);
        sb.append(DocumentationMarkup.CONTENT_END);
    }

    private void addTitle(final String title) {
        sb.append(DocumentationMarkup.DEFINITION_START);
        sb.append(title);
        sb.append(DocumentationMarkup.DEFINITION_END);
    }

    private void addKeyValueSection(final String key, final String value) {
        sb.append(DocumentationMarkup.SECTION_HEADER_START);
        sb.append(key);
        sb.append(DocumentationMarkup.SECTION_SEPARATOR);
        sb.append("<p>");
        sb.append(value);
        sb.append(DocumentationMarkup.SECTION_END);
    }

    @Override
    public String toString() {
        return build();
    }

    public static class KV {
        public final String k;
        public final String v;

        public KV(final String k, final String v) {
            this.k = k;
            this.v = v;
        }
    }
}
