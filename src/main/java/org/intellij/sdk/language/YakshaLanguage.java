package org.intellij.sdk.language;

import com.intellij.lang.Language;

public class YakshaLanguage extends Language {

    public static final YakshaLanguage INSTANCE = new YakshaLanguage();

    private YakshaLanguage() {
        super("Yaksha");
    }
}
