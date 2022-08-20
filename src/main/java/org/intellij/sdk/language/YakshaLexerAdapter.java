package org.intellij.sdk.language;

import com.intellij.lexer.FlexAdapter;

public class YakshaLexerAdapter extends FlexAdapter {

  public YakshaLexerAdapter() {
    super(new YakshaLexer(null));
  }

}