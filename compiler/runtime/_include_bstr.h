struct yk__bstr { // Yaksha Base String
  union data {
    yk__sds h;    // reference to a heap allocated string, this string has some extra magic few bytes before this pointer
    const char *s;// reference to a statically allocated string
    char *c;      // reference to c.CStr that is heap allocated.
  } data;
  size_t l;
  // TODO Array[u8], Ptr[u8] support
  enum yk__bstr_type { yk__bstr_str, yk__bstr_static, yk__bstr_cstr } t;
};
struct yk__bstr yk__bstr_s(const char *s, size_t length);
struct yk__bstr yk__bstr_c(const char *s, size_t length);
struct yk__bstr yk__bstr_h(yk__sds h);
void yk__bstr_free_underlying(struct yk__bstr b);
yk__sds yk__bstr_copy_to_sds(struct yk__bstr b);

int32_t yk__cmp_sds_bstr(yk__sds lhs, struct yk__bstr rhs);
int32_t yk__cmp_sds_sds(yk__sds lhs, yk__sds rhs);
int32_t yk__cmp_sds_lit(yk__sds lhs, const char* rhs, size_t rhs_len);
int32_t yk__cmp_bstr_bstr(struct yk__bstr lhs, struct yk__bstr rhs);
int32_t yk__cmp_bstr_sds(struct yk__bstr lhs, yk__sds rhs);
int32_t yk__cmp_bstr_lit(struct yk__bstr lhs, const char* rhs, size_t rhs_len);
int32_t yk__cmp_lit_bstr(const char* lhs, size_t lhs_len, struct yk__bstr rhs);
int32_t yk__cmp_lit_sds(const char* lhs, size_t lhs_len, yk__sds rhs);
int32_t yk__cmp_lit_lit(const char* lhs, size_t lhs_len, const char* rhs, size_t rhs_len);

yk__sds yk__append_sds_bstr(yk__sds lhs, struct yk__bstr rhs);
yk__sds yk__append_sds_sds(yk__sds lhs, yk__sds rhs);
yk__sds yk__append_sds_lit(yk__sds lhs, const char* rhs, size_t rhs_len);

yk__sds yk__concat_sds_bstr(yk__sds lhs, struct yk__bstr rhs);
yk__sds yk__concat_sds_sds(yk__sds lhs, yk__sds rhs);
yk__sds yk__concat_sds_lit(yk__sds lhs, const char* rhs, size_t rhs_len);
yk__sds yk__concat_bstr_bstr(struct yk__bstr lhs, struct yk__bstr rhs);
yk__sds yk__concat_bstr_sds(struct yk__bstr lhs, yk__sds rhs);
yk__sds yk__concat_bstr_lit(struct yk__bstr lhs, const char* rhs, size_t rhs_len);
yk__sds yk__concat_lit_bstr(const char* lhs, size_t lhs_len, struct yk__bstr rhs);
yk__sds yk__concat_lit_sds(const char* lhs, size_t lhs_len, yk__sds rhs);
yk__sds yk__concat_lit_lit(const char* lhs, size_t lhs_len, const char* rhs, size_t rhs_len);

size_t yk__bstr_len(struct yk__bstr b);
const char* yk__bstr_get_reference(struct  yk__bstr b);
// TODO use c99 model to inline these at somepoint https://www.greenend.org.uk/rjk/tech/inline.html
//  Also see sds code, it also uses static inline, we can use that
