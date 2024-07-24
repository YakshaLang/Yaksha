(native_def readfile ( fname:str) (block (c "size_t ln;\n    int err;\n    char *out = yk__bhalib_read_file(nn__fname, &ln, &err);\n    yk__sdsfree(nn__fname); // clean up filename as it will be copied\n    if (err == 0) { return yk__sdsnewlen(out, ln); }\n    return yk__sdsempty()")))
(native_def is_empty_str ( s:str) (block (c "bool x = yk__sdslen(nn__s) == 0;\n    yk__sdsfree(nn__s);\n    return x")))
(native_macro_def min_int ( a:i32 b:i32) (block (c "((nn__a < nn__b) \? nn__a : nn__b)")))
(native_macro_def max_int ( a:i32 b:i32) (block (nop)))
(native_def leakme ( a:str b:str) (block (nop)))
(def main () (block (expression (call print "// ----->>> this is my code <<<<------\n")) (let a:str (call readfile "test.c")) (if (expr (call is_empty_str a)) then (block (expression (call print "test.c is empty or not found"))) else (block (expression (call print a)))) (return 0)))

