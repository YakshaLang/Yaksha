#include <string.h>
static const char *YK__EMPTY_STRING_BSTR = "";
#define YK__BSTR_CONSIDER_LEN(t)                                               \
  do {                                                                         \
    size_t cmp = t;                                                            \
    if (cmp == 0) return lhs_l > rhs_l ? 1 : (lhs_l < rhs_l ? -1 : 0);         \
    return (int32_t) cmp;                                                      \
  } while (0)
struct yk__bstr yk__bstr_s(const char *s, size_t length) {
  if (s == NULL) {
    return ((struct yk__bstr){.data.s = YK__EMPTY_STRING_BSTR,
                              .l = 0,
                              .t = yk__bstr_static});
  }
  return ((struct yk__bstr){.data.s = s, .l = length, .t = yk__bstr_static});
}
struct yk__bstr yk__bstr_c(const char *s, size_t length) {
  if (s == NULL) {
    return ((struct yk__bstr){.data.s = YK__EMPTY_STRING_BSTR,
                              .l = 0,
                              .t = yk__bstr_static});
  }
  return (
      (struct yk__bstr){.data.c = (char *) s, .l = length, .t = yk__bstr_cstr});
}
struct yk__bstr yk__bstr_h(yk__sds h) {
  if (h == NULL) {
    return ((struct yk__bstr){.data.s = YK__EMPTY_STRING_BSTR,
                              .l = 0,
                              .t = yk__bstr_static});
  }
  return (
      (struct yk__bstr){.data.h = h, .l = yk__sdslen(h), .t = yk__bstr_str});
}
void yk__bstr_free_underlying(struct yk__bstr b) {
  if (b.t == yk__bstr_str) { yk__sdsfree(b.data.h); }
  if (b.t == yk__bstr_cstr) { free(b.data.c); }
  // static storage does not need deletion
}
yk__sds yk__bstr_copy_to_sds(struct yk__bstr b) {
  if (b.t == yk__bstr_str) { return yk__sdsdup(b.data.h); }
  if (b.t == yk__bstr_cstr) { return yk__sdsnew(b.data.c); }
  return yk__sdsnewlen(b.data.s, b.l);
}
size_t yk__bstr_len(struct yk__bstr b) {
  if (b.t == yk__bstr_str) { return yk__sdslen(b.data.h); }
  if (b.t == yk__bstr_cstr) { return strlen(b.data.c); }
  return b.l;
}
const char *yk__bstr_get_reference(struct yk__bstr b) {
  const char *lhs_s;
  if (b.t == yk__bstr_str) {
    lhs_s = b.data.h;
  } else if (b.t == yk__bstr_static) {
    lhs_s = b.data.s;
  } else {
    lhs_s = b.data.c;
  }
  return lhs_s;
}
yk__sds yk__append_sds_bstr(yk__sds lhs, struct yk__bstr rhs) {
  return yk__sdscatlen(lhs, yk__bstr_get_reference(rhs), yk__bstr_len(rhs));
}
yk__sds yk__append_sds_sds(yk__sds lhs, yk__sds rhs) {
  return yk__sdscatsds(lhs, rhs);
}
yk__sds yk__append_sds_lit(yk__sds lhs, const char *rhs, size_t rhs_len) {
  return yk__sdscatlen(lhs, rhs, rhs_len);
}
yk__sds yk__concat_sds_bstr(yk__sds lhs, struct yk__bstr rhs) {
  yk__sds copy = yk__sdsdup(lhs);
  if (copy == NULL) { return NULL; }
  return yk__sdscatlen(copy, yk__bstr_get_reference(rhs), yk__bstr_len(rhs));
}
yk__sds yk__concat_sds_sds(yk__sds lhs, yk__sds rhs) {
  yk__sds copy = yk__sdsdup(lhs);
  if (copy == NULL) { return NULL; }
  return yk__sdscatsds(copy, rhs);
}
yk__sds yk__concat_sds_lit(yk__sds lhs, const char *rhs, size_t rhs_len) {
  yk__sds copy = yk__sdsdup(lhs);
  if (copy == NULL) { return NULL; }
  return yk__sdscatlen(copy, rhs, rhs_len);
}
yk__sds yk__concat_bstr_bstr(struct yk__bstr lhs, struct yk__bstr rhs) {
  yk__sds lhs_new =
      yk__sdsnewlen(yk__bstr_get_reference(lhs), yk__bstr_len(lhs));
  if (lhs_new == NULL) { return NULL; }
  return yk__sdscatlen(lhs_new, yk__bstr_get_reference(rhs), yk__bstr_len(rhs));
}
yk__sds yk__concat_bstr_sds(struct yk__bstr lhs, yk__sds rhs) {
  yk__sds lhs_new =
      yk__sdsnewlen(yk__bstr_get_reference(lhs), yk__bstr_len(lhs));
  if (lhs_new == NULL) { return NULL; }
  return yk__sdscatsds(lhs_new, rhs);
}
yk__sds yk__concat_bstr_lit(struct yk__bstr lhs, const char *rhs,
                            size_t rhs_len) {
  yk__sds lhs_new =
      yk__sdsnewlen(yk__bstr_get_reference(lhs), yk__bstr_len(lhs));
  if (lhs_new == NULL) { return NULL; }
  return yk__sdscatlen(lhs_new, rhs, rhs_len);
}
yk__sds yk__concat_lit_bstr(const char *lhs, size_t lhs_len,
                            struct yk__bstr rhs) {
  yk__sds lhs_new = yk__sdsnewlen(lhs, lhs_len);
  if (lhs_new == NULL) { return NULL; }
  return yk__sdscatlen(lhs_new, yk__bstr_get_reference(rhs), yk__bstr_len(rhs));
}
yk__sds yk__concat_lit_sds(const char *lhs, size_t lhs_len, yk__sds rhs) {
  yk__sds lhs_new = yk__sdsnewlen(lhs, lhs_len);
  if (lhs_new == NULL) { return NULL; }
  return yk__sdscatsds(lhs_new, rhs);
}
yk__sds yk__concat_lit_lit(const char *lhs, size_t lhs_len, const char *rhs,
                           size_t rhs_len) {
  yk__sds lhs_new = yk__sdsnewlen(lhs, lhs_len);
  if (lhs_new == NULL) { return NULL; }
  return yk__sdscatlen(lhs_new, rhs, rhs_len);
}
int32_t yk__cmp_sds_bstr(yk__sds lhs, struct yk__bstr rhs) {
  size_t lhs_l = yk__sdslen(lhs);
  size_t rhs_l = yk__bstr_len(rhs);
  size_t size_min = lhs_l < rhs_l ? lhs_l : rhs_l;
  const char *lhs_s = lhs;
  const char *rhs_s = yk__bstr_get_reference(rhs);
  if (lhs_s == rhs_s && lhs_l == rhs_l) { return 0; }
  YK__BSTR_CONSIDER_LEN(memcmp(lhs_s, rhs_s, size_min));
}
int32_t yk__cmp_sds_sds(yk__sds lhs, yk__sds rhs) {
  if (lhs == rhs) { return 0; }
  return yk__sdscmp(lhs, rhs);
}
int32_t yk__cmp_sds_lit(yk__sds lhs, const char *rhs, size_t rhs_len) {
  if (lhs == rhs) { return 0; }
  size_t lhs_l = yk__sdslen(lhs);
  size_t rhs_l = rhs_len;
  size_t size_min = lhs_l < rhs_l ? lhs_l : rhs_l;
  const char *lhs_s = lhs;
  const char *rhs_s = rhs;
  if (lhs_s == rhs_s && lhs_l == rhs_l) { return 0; }
  YK__BSTR_CONSIDER_LEN(memcmp(lhs_s, rhs_s, size_min));
}
int32_t yk__cmp_bstr_bstr(struct yk__bstr lhs, struct yk__bstr rhs) {
  size_t lhs_l = yk__bstr_len(lhs);
  size_t rhs_l = yk__bstr_len(rhs);
  size_t size_min = lhs_l < rhs_l ? lhs_l : rhs_l;
  const char *lhs_s = yk__bstr_get_reference(lhs);
  const char *rhs_s = yk__bstr_get_reference(rhs);
  if (lhs_s == rhs_s && lhs_l == rhs_l) { return 0; }
  YK__BSTR_CONSIDER_LEN(memcmp(lhs_s, rhs_s, size_min));
}
int32_t yk__cmp_bstr_sds(struct yk__bstr lhs, yk__sds rhs) {
  size_t lhs_l = yk__bstr_len(lhs);
  size_t rhs_l = yk__sdslen(rhs);
  size_t size_min = lhs_l < rhs_l ? lhs_l : rhs_l;
  const char *lhs_s = yk__bstr_get_reference(lhs);
  const char *rhs_s = rhs;
  if (lhs_s == rhs_s && lhs_l == rhs_l) { return 0; }
  YK__BSTR_CONSIDER_LEN(memcmp(lhs_s, rhs_s, size_min));
}
int32_t yk__cmp_bstr_lit(struct yk__bstr lhs, const char *rhs, size_t rhs_len) {
  size_t lhs_l = yk__bstr_len(lhs);
  size_t rhs_l = rhs_len;
  size_t size_min = lhs_l < rhs_l ? lhs_l : rhs_l;
  const char *lhs_s = yk__bstr_get_reference(lhs);
  const char *rhs_s = rhs;
  if (lhs_s == rhs_s && lhs_l == rhs_l) { return 0; }
  YK__BSTR_CONSIDER_LEN(memcmp(lhs_s, rhs_s, size_min));
}
int32_t yk__cmp_lit_bstr(const char *lhs, size_t lhs_len, struct yk__bstr rhs) {
  size_t lhs_l = lhs_len;
  size_t rhs_l = yk__bstr_len(rhs);
  size_t size_min = lhs_l < rhs_l ? lhs_l : rhs_l;
  const char *lhs_s = lhs;
  const char *rhs_s = yk__bstr_get_reference(rhs);
  if (lhs_s == rhs_s && lhs_l == rhs_l) { return 0; }
  YK__BSTR_CONSIDER_LEN(memcmp(lhs_s, rhs_s, size_min));
}
int32_t yk__cmp_lit_sds(const char *lhs, size_t lhs_len, yk__sds rhs) {
  size_t lhs_l = lhs_len;
  size_t rhs_l = yk__sdslen(rhs);
  size_t size_min = lhs_l < rhs_l ? lhs_l : rhs_l;
  const char *lhs_s = lhs;
  const char *rhs_s = rhs;
  if (lhs_s == rhs_s && lhs_l == rhs_l) { return 0; }
  YK__BSTR_CONSIDER_LEN(memcmp(lhs_s, rhs_s, size_min));
}
int32_t yk__cmp_lit_lit(const char *lhs, size_t lhs_len, const char *rhs,
                        size_t rhs_len) {
  if (lhs == rhs && lhs_len == rhs_len) { return 0; }
  size_t lhs_l = lhs_len;
  size_t rhs_l = rhs_len;
  size_t size_min = lhs_l < rhs_l ? lhs_l : rhs_l;
  const char *lhs_s = lhs;
  const char *rhs_s = rhs;
  YK__BSTR_CONSIDER_LEN(memcmp(lhs_s, rhs_s, size_min));
}
