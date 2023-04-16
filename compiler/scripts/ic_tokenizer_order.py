# Given a list of tokens generate placeholder code for tokenization
# Note: This is not a generator script. This simply generates code so you can order things!
def main():
    items = ["...", ">>=", "<<=", "+=", "-=", "*=", "/=", "%=", "&=", "^=", "|=", ">>", "<<", "++", "--", "->", "&&",
             "||",
             "<=", ">=", "==", "!=", ";", "{", "<%", "}", "%>", ",", ":", "=", "(", ")", "[", "<:", "]", ":>", ".", "&",
             "!", "~", "-", "+", "*", "/", "%", "<", ">", "^", "|", "?", "/*", "//", "#", "##"]

    items = sorted(items, key=lambda h: (h[0], -len(h)))

    x = ""
    for i, item in enumerate(items):
        if i != 0:
            x += "else "
        if len(item) == 3:
            x += f"if (current == '{item[0]}' && next == '{item[1]}' && after_next == '{item[2]}') {{ emit_tok(" \
                 f" \"{item}\", ic_token_type::TK_UNKNOWN_TOKEN_DETECTED); skip_2(); }}"
        if len(item) == 2:
            x += f"if (current == '{item[0]}' && next == '{item[1]}') {{ emit_tok(\"{item}\", " \
                 f"ic_token_type" \
                 f"::TK_UNKNOWN_TOKEN_DETECTED); skip_1(); }}"
        if len(item) == 1:
            x += f"if (current == '{item[0]}') {{ emit_tok(\"{item}\", ic_token_type" \
                 f"::TK_UNKNOWN_TOKEN_DETECTED); }}"
        x += "\n"
    print(x)


if __name__ == "__main__":
    main()
