
/*
Copyright (c) 2006-2014, Salvatore Sanfilippo <antirez at gmail dot com>

All rights reserved.

    Redistribution and use in source and binary forms, with or without
                modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.

        * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
                and/or other materials provided with the distribution.

           THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
               ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
        WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
            DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
                ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
    ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
            */
#ifndef YK__SDS_SINGLE_HEADER
#define YK__SDS_SINGLE_HEADER
#ifndef YK____SDS_H
#define YK____SDS_H
#if _MSC_VER && !__INTEL_COMPILER
#define __attribute__(X)
#define ssize_t intmax_t
#endif
#define YK__SDS_MAX_PREALLOC (1024 * 1024)
extern const char *YK__SDS_NOINIT;
#include <stdarg.h>
#include <stdint.h>
#include <sys/types.h>
typedef char *yk__sds;
/* Note: yk__sdshdr5 is never used, we just access the flags byte directly.
 * However is here to document the layout of type 5 SDS strings. */
struct __attribute__((__packed__)) yk__sdshdr5 {
  unsigned char flags; /* 3 lsb of type, and 5 msb of string length */
  char buf[];
};
struct __attribute__((__packed__)) yk__sdshdr8 {
  uint8_t len;         /* used */
  uint8_t alloc;       /* excluding the header and null terminator */
  unsigned char flags; /* 3 lsb of type, 5 unused bits */
  char buf[];
};
struct __attribute__((__packed__)) yk__sdshdr16 {
  uint16_t len;        /* used */
  uint16_t alloc;      /* excluding the header and null terminator */
  unsigned char flags; /* 3 lsb of type, 5 unused bits */
  char buf[];
};
struct __attribute__((__packed__)) yk__sdshdr32 {
  uint32_t len;        /* used */
  uint32_t alloc;      /* excluding the header and null terminator */
  unsigned char flags; /* 3 lsb of type, 5 unused bits */
  char buf[];
};
struct __attribute__((__packed__)) yk__sdshdr64 {
  uint64_t len;        /* used */
  uint64_t alloc;      /* excluding the header and null terminator */
  unsigned char flags; /* 3 lsb of type, 5 unused bits */
  char buf[];
};
#define YK__SDS_TYPE_5 0
#define YK__SDS_TYPE_8 1
#define YK__SDS_TYPE_16 2
#define YK__SDS_TYPE_32 3
#define YK__SDS_TYPE_64 4
#define YK__SDS_TYPE_MASK 7
#define YK__SDS_TYPE_BITS 3
#define YK__SDS_HDR_VAR(T, s)                                                  \
  struct yk__sdshdr##T *sh = (void *) ((s) - (sizeof(struct yk__sdshdr##T)));
#define YK__SDS_HDR(T, s)                                                      \
  ((struct yk__sdshdr##T *) ((s) - (sizeof(struct yk__sdshdr##T))))
#define YK__SDS_TYPE_5_LEN(f) ((f) >> YK__SDS_TYPE_BITS)
static inline size_t yk__sdslen(const yk__sds s) {
  unsigned char flags = s[-1];
  switch (flags & YK__SDS_TYPE_MASK) {
    case YK__SDS_TYPE_5:
      return YK__SDS_TYPE_5_LEN(flags);
    case YK__SDS_TYPE_8:
      return YK__SDS_HDR(8, s)->len;
    case YK__SDS_TYPE_16:
      return YK__SDS_HDR(16, s)->len;
    case YK__SDS_TYPE_32:
      return YK__SDS_HDR(32, s)->len;
    case YK__SDS_TYPE_64:
      return YK__SDS_HDR(64, s)->len;
  }
  return 0;
}
static inline size_t yk__sdsavail(const yk__sds s) {
  unsigned char flags = s[-1];
  switch (flags & YK__SDS_TYPE_MASK) {
    case YK__SDS_TYPE_5: {
      return 0;
    }
    case YK__SDS_TYPE_8: {
      YK__SDS_HDR_VAR(8, s);
      return sh->alloc - sh->len;
    }
    case YK__SDS_TYPE_16: {
      YK__SDS_HDR_VAR(16, s);
      return sh->alloc - sh->len;
    }
    case YK__SDS_TYPE_32: {
      YK__SDS_HDR_VAR(32, s);
      return sh->alloc - sh->len;
    }
    case YK__SDS_TYPE_64: {
      YK__SDS_HDR_VAR(64, s);
      return sh->alloc - sh->len;
    }
  }
  return 0;
}
static inline void yk__sdssetlen(yk__sds s, size_t newlen) {
  unsigned char flags = s[-1];
  switch (flags & YK__SDS_TYPE_MASK) {
    case YK__SDS_TYPE_5: {
      unsigned char *fp = ((unsigned char *) s) - 1;
      *fp = YK__SDS_TYPE_5 | (newlen << YK__SDS_TYPE_BITS);
    } break;
    case YK__SDS_TYPE_8:
      YK__SDS_HDR(8, s)->len = newlen;
      break;
    case YK__SDS_TYPE_16:
      YK__SDS_HDR(16, s)->len = newlen;
      break;
    case YK__SDS_TYPE_32:
      YK__SDS_HDR(32, s)->len = newlen;
      break;
    case YK__SDS_TYPE_64:
      YK__SDS_HDR(64, s)->len = newlen;
      break;
  }
}
static inline void yk__sdsinclen(yk__sds s, size_t inc) {
  unsigned char flags = s[-1];
  switch (flags & YK__SDS_TYPE_MASK) {
    case YK__SDS_TYPE_5: {
      unsigned char *fp = ((unsigned char *) s) - 1;
      unsigned char newlen = YK__SDS_TYPE_5_LEN(flags) + inc;
      *fp = YK__SDS_TYPE_5 | (newlen << YK__SDS_TYPE_BITS);
    } break;
    case YK__SDS_TYPE_8:
      YK__SDS_HDR(8, s)->len += inc;
      break;
    case YK__SDS_TYPE_16:
      YK__SDS_HDR(16, s)->len += inc;
      break;
    case YK__SDS_TYPE_32:
      YK__SDS_HDR(32, s)->len += inc;
      break;
    case YK__SDS_TYPE_64:
      YK__SDS_HDR(64, s)->len += inc;
      break;
  }
}
/* yk__sdsalloc() = yk__sdsavail() + yk__sdslen() */
static inline size_t yk__sdsalloc(const yk__sds s) {
  unsigned char flags = s[-1];
  switch (flags & YK__SDS_TYPE_MASK) {
    case YK__SDS_TYPE_5:
      return YK__SDS_TYPE_5_LEN(flags);
    case YK__SDS_TYPE_8:
      return YK__SDS_HDR(8, s)->alloc;
    case YK__SDS_TYPE_16:
      return YK__SDS_HDR(16, s)->alloc;
    case YK__SDS_TYPE_32:
      return YK__SDS_HDR(32, s)->alloc;
    case YK__SDS_TYPE_64:
      return YK__SDS_HDR(64, s)->alloc;
  }
  return 0;
}
static inline void yk__sdssetalloc(yk__sds s, size_t newlen) {
  unsigned char flags = s[-1];
  switch (flags & YK__SDS_TYPE_MASK) {
    case YK__SDS_TYPE_5:
      /* Nothing to do, this type has no total allocation info. */
      break;
    case YK__SDS_TYPE_8:
      YK__SDS_HDR(8, s)->alloc = newlen;
      break;
    case YK__SDS_TYPE_16:
      YK__SDS_HDR(16, s)->alloc = newlen;
      break;
    case YK__SDS_TYPE_32:
      YK__SDS_HDR(32, s)->alloc = newlen;
      break;
    case YK__SDS_TYPE_64:
      YK__SDS_HDR(64, s)->alloc = newlen;
      break;
  }
}
yk__sds yk__sdsnewlen(const void *init, size_t initlen);
yk__sds yk__sdsnew(const char *init);
yk__sds yk__sdsempty(void);
yk__sds yk__sdsdup(const yk__sds s);
void yk__sdsfree(yk__sds s);
yk__sds yk__sdsgrowzero(yk__sds s, size_t len);
yk__sds yk__sdscatlen(yk__sds s, const void *t, size_t len);
yk__sds yk__sdscat(yk__sds s, const char *t);
yk__sds yk__sdscatsds(yk__sds s, const yk__sds t);
yk__sds yk__sdscpylen(yk__sds s, const char *t, size_t len);
yk__sds yk__sdscpy(yk__sds s, const char *t);
yk__sds yk__sdscatvprintf(yk__sds s, const char *fmt, va_list ap);
#ifdef __GNUC__
yk__sds yk__sdscatprintf(yk__sds s, const char *fmt, ...)
    __attribute__((format(printf, 2, 3)));
#else
yk__sds yk__sdscatprintf(yk__sds s, const char *fmt, ...);
#endif
yk__sds yk__sdscatfmt(yk__sds s, char const *fmt, ...);
yk__sds yk__sdstrim(yk__sds s, const char *cset);
void yk__sdsrange(yk__sds s, ssize_t start, ssize_t end);
void yk__sdsupdatelen(yk__sds s);
void yk__sdsclear(yk__sds s);
int yk__sdscmp(const yk__sds s1, const yk__sds s2);
yk__sds *yk__sdssplitlen(const char *s, ssize_t len, const char *sep,
                         int seplen, int *count);
void yk__sdsfreesplitres(yk__sds *tokens, int count);
void yk__sdstolower(yk__sds s);
void yk__sdstoupper(yk__sds s);
yk__sds yk__sdsfromlonglong(long long value);
yk__sds yk__sdscatrepr(yk__sds s, const char *p, size_t len);
yk__sds *yk__sdssplitargs(const char *line, int *argc);
yk__sds yk__sdsmapchars(yk__sds s, const char *from, const char *to,
                        size_t setlen);
yk__sds yk__sdsjoin(char **argv, int argc, char *sep);
yk__sds yk__sdsjoinsds(yk__sds *argv, int argc, const char *sep, size_t seplen);
/* Low level functions exposed to the user API */
yk__sds yk__sdsMakeRoomFor(yk__sds s, size_t addlen);
void yk__sdsIncrLen(yk__sds s, ssize_t incr);
yk__sds yk__sdsRemoveFreeSpace(yk__sds s);
size_t yk__sdsAllocSize(yk__sds s);
void *yk__sdsAllocPtr(yk__sds s);
/* Export the allocator used by SDS to the program using SDS.
 * Sometimes the program SDS is linked to, may use a different set of
 * allocators, but may want to allocate or free things that SDS will
 * respectively free or allocate. */
void *yk__sds_malloc(size_t size);
void *yk__sds_realloc(void *ptr, size_t size);
void yk__sds_free(void *ptr);
#ifdef REDIS_TEST
int yk__sdsTest(int argc, char *argv[]);
#endif
#endif
#endif /* YK__SDS_SINGLE_HEADER */
#ifdef YK__SDS_IMPLEMENTATION
/* SDS allocator selection.
 *
 * This file is used in order to change the SDS allocator at compile time.
 * Just define the following defines to what you want to use. Also add
 * the include of your alternate allocator if needed (not needed in order
 * to use the default libc allocator). */
#define yk__s_malloc malloc
#define yk__s_realloc realloc
#define yk__s_free free
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const char *YK__SDS_NOINIT = "YK__SDS_NOINIT";
static inline int yk__sdsHdrSize(char type) {
  switch (type & YK__SDS_TYPE_MASK) {
    case YK__SDS_TYPE_5:
      return sizeof(struct yk__sdshdr5);
    case YK__SDS_TYPE_8:
      return sizeof(struct yk__sdshdr8);
    case YK__SDS_TYPE_16:
      return sizeof(struct yk__sdshdr16);
    case YK__SDS_TYPE_32:
      return sizeof(struct yk__sdshdr32);
    case YK__SDS_TYPE_64:
      return sizeof(struct yk__sdshdr64);
  }
  return 0;
}
static inline char yk__sdsReqType(size_t string_size) {
  if (string_size < 1 << 5) return YK__SDS_TYPE_5;
  if (string_size < 1 << 8) return YK__SDS_TYPE_8;
  if (string_size < 1 << 16) return YK__SDS_TYPE_16;
#if (LONG_MAX == LLONG_MAX)
  if (string_size < 1ll << 32) return YK__SDS_TYPE_32;
  return YK__SDS_TYPE_64;
#else
  return YK__SDS_TYPE_32;
#endif
}
/* Create a new yk__sds string with the content specified by the 'init' pointer
 * and 'initlen'.
 * If NULL is used for 'init' the string is initialized with zero bytes.
 * If YK__SDS_NOINIT is used, the buffer is left uninitialized;
 *
 * The string is always null-termined (all the yk__sds strings are, always) so
 * even if you create an yk__sds string with:
 *
 * mystring = yk__sdsnewlen("abc",3);
 *
 * You can print the string with printf() as there is an implicit \0 at the
 * end of the string. However the string is binary safe and can contain
 * \0 characters in the middle, as the length is stored in the yk__sds header. */
yk__sds yk__sdsnewlen(const void *init, size_t initlen) {
  void *sh;
  yk__sds s;
  char type = yk__sdsReqType(initlen);
  /* Empty strings are usually created in order to append. Use type 8
     * since type 5 is not good at this. */
  if (type == YK__SDS_TYPE_5 && initlen == 0) type = YK__SDS_TYPE_8;
  int hdrlen = yk__sdsHdrSize(type);
  unsigned char *fp; /* flags pointer. */
  sh = yk__s_malloc(hdrlen + initlen + 1);
  if (sh == NULL) return NULL;
  if (init == YK__SDS_NOINIT) init = NULL;
  else if (!init)
    memset(sh, 0, hdrlen + initlen + 1);
  s = (char *) sh + hdrlen;
  fp = ((unsigned char *) s) - 1;
  switch (type) {
    case YK__SDS_TYPE_5: {
      *fp = type | (initlen << YK__SDS_TYPE_BITS);
      break;
    }
    case YK__SDS_TYPE_8: {
      YK__SDS_HDR_VAR(8, s);
      sh->len = initlen;
      sh->alloc = initlen;
      *fp = type;
      break;
    }
    case YK__SDS_TYPE_16: {
      YK__SDS_HDR_VAR(16, s);
      sh->len = initlen;
      sh->alloc = initlen;
      *fp = type;
      break;
    }
    case YK__SDS_TYPE_32: {
      YK__SDS_HDR_VAR(32, s);
      sh->len = initlen;
      sh->alloc = initlen;
      *fp = type;
      break;
    }
    case YK__SDS_TYPE_64: {
      YK__SDS_HDR_VAR(64, s);
      sh->len = initlen;
      sh->alloc = initlen;
      *fp = type;
      break;
    }
  }
  if (initlen && init) memcpy(s, init, initlen);
  s[initlen] = '\0';
  return s;
}
/* Create an empty (zero length) yk__sds string. Even in this case the string
 * always has an implicit null term. */
yk__sds yk__sdsempty(void) { return yk__sdsnewlen("", 0); }
/* Create a new yk__sds string starting from a null terminated C string. */
yk__sds yk__sdsnew(const char *init) {
  size_t initlen = (init == NULL) ? 0 : strlen(init);
  return yk__sdsnewlen(init, initlen);
}
/* Duplicate an yk__sds string. */
yk__sds yk__sdsdup(const yk__sds s) { return yk__sdsnewlen(s, yk__sdslen(s)); }
/* Free an yk__sds string. No operation is performed if 's' is NULL. */
void yk__sdsfree(yk__sds s) {
  if (s == NULL) return;
  yk__s_free((char *) s - yk__sdsHdrSize(s[-1]));
}
/* Set the yk__sds string length to the length as obtained with strlen(), so
 * considering as content only up to the first null term character.
 *
 * This function is useful when the yk__sds string is hacked manually in some
 * way, like in the following example:
 *
 * s = yk__sdsnew("foobar");
 * s[2] = '\0';
 * yk__sdsupdatelen(s);
 * printf("%d\n", yk__sdslen(s));
 *
 * The output will be "2", but if we comment out the call to yk__sdsupdatelen()
 * the output will be "6" as the string was modified but the logical length
 * remains 6 bytes. */
void yk__sdsupdatelen(yk__sds s) {
  size_t reallen = strlen(s);
  yk__sdssetlen(s, reallen);
}
/* Modify an yk__sds string in-place to make it empty (zero length).
 * However all the existing buffer is not discarded but set as free space
 * so that next append operations will not require allocations up to the
 * number of bytes previously available. */
void yk__sdsclear(yk__sds s) {
  yk__sdssetlen(s, 0);
  s[0] = '\0';
}
/* Enlarge the free space at the end of the yk__sds string so that the caller
 * is sure that after calling this function can overwrite up to addlen
 * bytes after the end of the string, plus one more byte for nul term.
 *
 * Note: this does not change the *length* of the yk__sds string as returned
 * by yk__sdslen(), but only the free buffer space we have. */
yk__sds yk__sdsMakeRoomFor(yk__sds s, size_t addlen) {
  void *sh, *newsh;
  size_t avail = yk__sdsavail(s);
  size_t len, newlen;
  char type, oldtype = s[-1] & YK__SDS_TYPE_MASK;
  int hdrlen;
  /* Return ASAP if there is enough space left. */
  if (avail >= addlen) return s;
  len = yk__sdslen(s);
  sh = (char *) s - yk__sdsHdrSize(oldtype);
  newlen = (len + addlen);
  if (newlen < YK__SDS_MAX_PREALLOC) newlen *= 2;
  else
    newlen += YK__SDS_MAX_PREALLOC;
  type = yk__sdsReqType(newlen);
  /* Don't use type 5: the user is appending to the string and type 5 is
     * not able to remember empty space, so yk__sdsMakeRoomFor() must be called
     * at every appending operation. */
  if (type == YK__SDS_TYPE_5) type = YK__SDS_TYPE_8;
  hdrlen = yk__sdsHdrSize(type);
  if (oldtype == type) {
    newsh = yk__s_realloc(sh, hdrlen + newlen + 1);
    if (newsh == NULL) return NULL;
    s = (char *) newsh + hdrlen;
  } else {
    /* Since the header size changes, need to move the string forward,
         * and can't use realloc */
    newsh = yk__s_malloc(hdrlen + newlen + 1);
    if (newsh == NULL) return NULL;
    memcpy((char *) newsh + hdrlen, s, len + 1);
    yk__s_free(sh);
    s = (char *) newsh + hdrlen;
    s[-1] = type;
    yk__sdssetlen(s, len);
  }
  yk__sdssetalloc(s, newlen);
  return s;
}
/* Reallocate the yk__sds string so that it has no free space at the end. The
 * contained string remains not altered, but next concatenation operations
 * will require a reallocation.
 *
 * After the call, the passed yk__sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
yk__sds yk__sdsRemoveFreeSpace(yk__sds s) {
  void *sh, *newsh;
  char type, oldtype = s[-1] & YK__SDS_TYPE_MASK;
  int hdrlen, oldhdrlen = yk__sdsHdrSize(oldtype);
  size_t len = yk__sdslen(s);
  size_t avail = yk__sdsavail(s);
  sh = (char *) s - oldhdrlen;
  /* Return ASAP if there is no space left. */
  if (avail == 0) return s;
  /* Check what would be the minimum SDS header that is just good enough to
     * fit this string. */
  type = yk__sdsReqType(len);
  hdrlen = yk__sdsHdrSize(type);
  /* If the type is the same, or at least a large enough type is still
     * required, we just realloc(), letting the allocator to do the copy
     * only if really needed. Otherwise if the change is huge, we manually
     * reallocate the string to use the different header type. */
  if (oldtype == type || type > YK__SDS_TYPE_8) {
    newsh = yk__s_realloc(sh, oldhdrlen + len + 1);
    if (newsh == NULL) return NULL;
    s = (char *) newsh + oldhdrlen;
  } else {
    newsh = yk__s_malloc(hdrlen + len + 1);
    if (newsh == NULL) return NULL;
    memcpy((char *) newsh + hdrlen, s, len + 1);
    yk__s_free(sh);
    s = (char *) newsh + hdrlen;
    s[-1] = type;
    yk__sdssetlen(s, len);
  }
  yk__sdssetalloc(s, len);
  return s;
}
/* Return the total size of the allocation of the specified yk__sds string,
 * including:
 * 1) The yk__sds header before the pointer.
 * 2) The string.
 * 3) The free buffer at the end if any.
 * 4) The implicit null term.
 */
size_t yk__sdsAllocSize(yk__sds s) {
  size_t alloc = yk__sdsalloc(s);
  return yk__sdsHdrSize(s[-1]) + alloc + 1;
}
/* Return the pointer of the actual SDS allocation (normally SDS strings
 * are referenced by the start of the string buffer). */
void *yk__sdsAllocPtr(yk__sds s) {
  return (void *) (s - yk__sdsHdrSize(s[-1]));
}
/* Increment the yk__sds length and decrements the left free space at the
 * end of the string according to 'incr'. Also set the null term
 * in the new end of the string.
 *
 * This function is used in order to fix the string length after the
 * user calls yk__sdsMakeRoomFor(), writes something after the end of
 * the current string, and finally needs to set the new length.
 *
 * Note: it is possible to use a negative increment in order to
 * right-trim the string.
 *
 * Usage example:
 *
 * Using yk__sdsIncrLen() and yk__sdsMakeRoomFor() it is possible to mount the
 * following schema, to cat bytes coming from the kernel to the end of an
 * yk__sds string without copying into an intermediate buffer:
 *
 * oldlen = yk__sdslen(s);
 * s = yk__sdsMakeRoomFor(s, BUFFER_SIZE);
 * nread = read(fd, s+oldlen, BUFFER_SIZE);
 * ... check for nread <= 0 and handle it ...
 * yk__sdsIncrLen(s, nread);
 */
void yk__sdsIncrLen(yk__sds s, ssize_t incr) {
  unsigned char flags = s[-1];
  size_t len;
  switch (flags & YK__SDS_TYPE_MASK) {
    case YK__SDS_TYPE_5: {
      unsigned char *fp = ((unsigned char *) s) - 1;
      unsigned char oldlen = YK__SDS_TYPE_5_LEN(flags);
      assert((incr > 0 && oldlen + incr < 32) ||
             (incr < 0 && oldlen >= (unsigned int) (-incr)));
      *fp = YK__SDS_TYPE_5 | ((oldlen + incr) << YK__SDS_TYPE_BITS);
      len = oldlen + incr;
      break;
    }
    case YK__SDS_TYPE_8: {
      YK__SDS_HDR_VAR(8, s);
      assert((incr >= 0 && sh->alloc - sh->len >= incr) ||
             (incr < 0 && sh->len >= (unsigned int) (-incr)));
      len = (sh->len += incr);
      break;
    }
    case YK__SDS_TYPE_16: {
      YK__SDS_HDR_VAR(16, s);
      assert((incr >= 0 && sh->alloc - sh->len >= incr) ||
             (incr < 0 && sh->len >= (unsigned int) (-incr)));
      len = (sh->len += incr);
      break;
    }
    case YK__SDS_TYPE_32: {
      YK__SDS_HDR_VAR(32, s);
      assert((incr >= 0 && sh->alloc - sh->len >= (unsigned int) incr) ||
             (incr < 0 && sh->len >= (unsigned int) (-incr)));
      len = (sh->len += incr);
      break;
    }
    case YK__SDS_TYPE_64: {
      YK__SDS_HDR_VAR(64, s);
      assert((incr >= 0 && sh->alloc - sh->len >= (uint64_t) incr) ||
             (incr < 0 && sh->len >= (uint64_t) (-incr)));
      len = (sh->len += incr);
      break;
    }
    default:
      len = 0; /* Just to avoid compilation warnings. */
  }
  s[len] = '\0';
}
/* Grow the yk__sds to have the specified length. Bytes that were not part of
 * the original length of the yk__sds will be set to zero.
 *
 * if the specified length is smaller than the current length, no operation
 * is performed. */
yk__sds yk__sdsgrowzero(yk__sds s, size_t len) {
  size_t curlen = yk__sdslen(s);
  if (len <= curlen) return s;
  s = yk__sdsMakeRoomFor(s, len - curlen);
  if (s == NULL) return NULL;
  /* Make sure added region doesn't contain garbage */
  memset(s + curlen, 0, (len - curlen + 1)); /* also set trailing \0 byte */
  yk__sdssetlen(s, len);
  return s;
}
/* Append the specified binary-safe string pointed by 't' of 'len' bytes to the
 * end of the specified yk__sds string 's'.
 *
 * After the call, the passed yk__sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
yk__sds yk__sdscatlen(yk__sds s, const void *t, size_t len) {
  size_t curlen = yk__sdslen(s);
  s = yk__sdsMakeRoomFor(s, len);
  if (s == NULL) return NULL;
  memcpy(s + curlen, t, len);
  yk__sdssetlen(s, curlen + len);
  s[curlen + len] = '\0';
  return s;
}
/* Append the specified null termianted C string to the yk__sds string 's'.
 *
 * After the call, the passed yk__sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
yk__sds yk__sdscat(yk__sds s, const char *t) {
  return yk__sdscatlen(s, t, strlen(t));
}
/* Append the specified yk__sds 't' to the existing yk__sds 's'.
 *
 * After the call, the modified yk__sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
yk__sds yk__sdscatsds(yk__sds s, const yk__sds t) {
  return yk__sdscatlen(s, t, yk__sdslen(t));
}
/* Destructively modify the yk__sds string 's' to hold the specified binary
 * safe string pointed by 't' of length 'len' bytes. */
yk__sds yk__sdscpylen(yk__sds s, const char *t, size_t len) {
  if (yk__sdsalloc(s) < len) {
    s = yk__sdsMakeRoomFor(s, len - yk__sdslen(s));
    if (s == NULL) return NULL;
  }
  memcpy(s, t, len);
  s[len] = '\0';
  yk__sdssetlen(s, len);
  return s;
}
/* Like yk__sdscpylen() but 't' must be a null-termined string so that the length
 * of the string is obtained with strlen(). */
yk__sds yk__sdscpy(yk__sds s, const char *t) {
  return yk__sdscpylen(s, t, strlen(t));
}
/* Helper for sdscatlonglong() doing the actual number -> string
 * conversion. 's' must point to a string with room for at least
 * YK__SDS_LLSTR_SIZE bytes.
 *
 * The function returns the length of the null-terminated string
 * representation stored at 's'. */
#define YK__SDS_LLSTR_SIZE 21
int yk__sdsll2str(char *s, long long value) {
  char *p, aux;
  unsigned long long v;
  size_t l;
  /* Generate the string representation, this method produces
     * an reversed string. */
  v = (value < 0) ? -value : value;
  p = s;
  do {
    *p++ = '0' + (v % 10);
    v /= 10;
  } while (v);
  if (value < 0) *p++ = '-';
  /* Compute length and add null term. */
  l = p - s;
  *p = '\0';
  /* Reverse the string. */
  p--;
  while (s < p) {
    aux = *s;
    *s = *p;
    *p = aux;
    s++;
    p--;
  }
  return l;
}
/* Identical yk__sdsll2str(), but for unsigned long long type. */
int yk__sdsull2str(char *s, unsigned long long v) {
  char *p, aux;
  size_t l;
  /* Generate the string representation, this method produces
     * an reversed string. */
  p = s;
  do {
    *p++ = '0' + (v % 10);
    v /= 10;
  } while (v);
  /* Compute length and add null term. */
  l = p - s;
  *p = '\0';
  /* Reverse the string. */
  p--;
  while (s < p) {
    aux = *s;
    *s = *p;
    *p = aux;
    s++;
    p--;
  }
  return l;
}
/* Create an yk__sds string from a long long value. It is much faster than:
 *
 * yk__sdscatprintf(yk__sdsempty(),"%lld\n", value);
 */
yk__sds yk__sdsfromlonglong(long long value) {
  char buf[YK__SDS_LLSTR_SIZE];
  int len = yk__sdsll2str(buf, value);
  return yk__sdsnewlen(buf, len);
}
/* Like yk__sdscatprintf() but gets va_list instead of being variadic. */
yk__sds yk__sdscatvprintf(yk__sds s, const char *fmt, va_list ap) {
  va_list cpy;
  char staticbuf[1024], *buf = staticbuf, *t;
  size_t buflen = strlen(fmt) * 2;
  /* We try to start using a static buffer for speed.
     * If not possible we revert to heap allocation. */
  if (buflen > sizeof(staticbuf)) {
    buf = yk__s_malloc(buflen);
    if (buf == NULL) return NULL;
  } else {
    buflen = sizeof(staticbuf);
  }
  /* Try with buffers two times bigger every time we fail to
     * fit the string in the current buffer size. */
  while (1) {
    buf[buflen - 2] = '\0';
    va_copy(cpy, ap);
    vsnprintf(buf, buflen, fmt, cpy);
    va_end(cpy);
    if (buf[buflen - 2] != '\0') {
      if (buf != staticbuf) yk__s_free(buf);
      buflen *= 2;
      buf = yk__s_malloc(buflen);
      if (buf == NULL) return NULL;
      continue;
    }
    break;
  }
  /* Finally concat the obtained string to the SDS string and return it. */
  t = yk__sdscat(s, buf);
  if (buf != staticbuf) yk__s_free(buf);
  return t;
}
/* Append to the yk__sds string 's' a string obtained using printf-alike format
 * specifier.
 *
 * After the call, the modified yk__sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call.
 *
 * Example:
 *
 * s = yk__sdsnew("Sum is: ");
 * s = yk__sdscatprintf(s,"%d+%d = %d",a,b,a+b).
 *
 * Often you need to create a string from scratch with the printf-alike
 * format. When this is the need, just use yk__sdsempty() as the target string:
 *
 * s = yk__sdscatprintf(yk__sdsempty(), "... your format ...", args);
 */
yk__sds yk__sdscatprintf(yk__sds s, const char *fmt, ...) {
  va_list ap;
  char *t;
  va_start(ap, fmt);
  t = yk__sdscatvprintf(s, fmt, ap);
  va_end(ap);
  return t;
}
/* This function is similar to yk__sdscatprintf, but much faster as it does
 * not rely on sprintf() family functions implemented by the libc that
 * are often very slow. Moreover directly handling the yk__sds string as
 * new data is concatenated provides a performance improvement.
 *
 * However this function only handles an incompatible subset of printf-alike
 * format specifiers:
 *
 * %s - C String
 * %S - SDS string
 * %i - signed int
 * %I - 64 bit signed integer (long long, int64_t)
 * %u - unsigned int
 * %U - 64 bit unsigned integer (unsigned long long, uint64_t)
 * %% - Verbatim "%" character.
 */
yk__sds yk__sdscatfmt(yk__sds s, char const *fmt, ...) {
  size_t initlen = yk__sdslen(s);
  const char *f = fmt;
  long i;
  va_list ap;
  /* To avoid continuous reallocations, let's start with a buffer that
     * can hold at least two times the format string itself. It's not the
     * best heuristic but seems to work in practice. */
  s = yk__sdsMakeRoomFor(s, initlen + strlen(fmt) * 2);
  va_start(ap, fmt);
  f = fmt;     /* Next format specifier byte to process. */
  i = initlen; /* Position of the next byte to write to dest str. */
  while (*f) {
    char next, *str;
    size_t l;
    long long num;
    unsigned long long unum;
    /* Make sure there is always space for at least 1 char. */
    if (yk__sdsavail(s) == 0) { s = yk__sdsMakeRoomFor(s, 1); }
    switch (*f) {
      case '%':
        next = *(f + 1);
        f++;
        switch (next) {
          case 's':
          case 'S':
            str = va_arg(ap, char *);
            l = (next == 's') ? strlen(str) : yk__sdslen(str);
            if (yk__sdsavail(s) < l) { s = yk__sdsMakeRoomFor(s, l); }
            memcpy(s + i, str, l);
            yk__sdsinclen(s, l);
            i += l;
            break;
          case 'i':
          case 'I':
            if (next == 'i') num = va_arg(ap, int);
            else
              num = va_arg(ap, long long);
            {
              char buf[YK__SDS_LLSTR_SIZE];
              l = yk__sdsll2str(buf, num);
              if (yk__sdsavail(s) < l) { s = yk__sdsMakeRoomFor(s, l); }
              memcpy(s + i, buf, l);
              yk__sdsinclen(s, l);
              i += l;
            }
            break;
          case 'u':
          case 'U':
            if (next == 'u') unum = va_arg(ap, unsigned int);
            else
              unum = va_arg(ap, unsigned long long);
            {
              char buf[YK__SDS_LLSTR_SIZE];
              l = yk__sdsull2str(buf, unum);
              if (yk__sdsavail(s) < l) { s = yk__sdsMakeRoomFor(s, l); }
              memcpy(s + i, buf, l);
              yk__sdsinclen(s, l);
              i += l;
            }
            break;
          default: /* Handle %% and generally %<unknown>. */
            s[i++] = next;
            yk__sdsinclen(s, 1);
            break;
        }
        break;
      default:
        s[i++] = *f;
        yk__sdsinclen(s, 1);
        break;
    }
    f++;
  }
  va_end(ap);
  /* Add null-term */
  s[i] = '\0';
  return s;
}
/* Remove the part of the string from left and from right composed just of
 * contiguous characters found in 'cset', that is a null terminted C string.
 *
 * After the call, the modified yk__sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call.
 *
 * Example:
 *
 * s = yk__sdsnew("AA...AA.a.aa.aHelloWorld     :::");
 * s = yk__sdstrim(s,"Aa. :");
 * printf("%s\n", s);
 *
 * Output will be just "HelloWorld".
 */
yk__sds yk__sdstrim(yk__sds s, const char *cset) {
  char *start, *end, *sp, *ep;
  size_t len;
  sp = start = s;
  ep = end = s + yk__sdslen(s) - 1;
  while (sp <= end && strchr(cset, *sp)) sp++;
  while (ep > sp && strchr(cset, *ep)) ep--;
  len = (sp > ep) ? 0 : ((ep - sp) + 1);
  if (s != sp) memmove(s, sp, len);
  s[len] = '\0';
  yk__sdssetlen(s, len);
  return s;
}
/* Turn the string into a smaller (or equal) string containing only the
 * substring specified by the 'start' and 'end' indexes.
 *
 * start and end can be negative, where -1 means the last character of the
 * string, -2 the penultimate character, and so forth.
 *
 * The interval is inclusive, so the start and end characters will be part
 * of the resulting string.
 *
 * The string is modified in-place.
 *
 * Example:
 *
 * s = yk__sdsnew("Hello World");
 * yk__sdsrange(s,1,-1); => "ello World"
 */
void yk__sdsrange(yk__sds s, ssize_t start, ssize_t end) {
  size_t newlen, len = yk__sdslen(s);
  if (len == 0) return;
  if (start < 0) {
    start = len + start;
    if (start < 0) start = 0;
  }
  if (end < 0) {
    end = len + end;
    if (end < 0) end = 0;
  }
  newlen = (start > end) ? 0 : (end - start) + 1;
  if (newlen != 0) {
    if (start >= (ssize_t) len) {
      newlen = 0;
    } else if (end >= (ssize_t) len) {
      end = len - 1;
      newlen = (start > end) ? 0 : (end - start) + 1;
    }
  } else {
    start = 0;
  }
  if (start && newlen) memmove(s, s + start, newlen);
  s[newlen] = 0;
  yk__sdssetlen(s, newlen);
}
/* Apply tolower() to every character of the yk__sds string 's'. */
void yk__sdstolower(yk__sds s) {
  size_t len = yk__sdslen(s), j;
  for (j = 0; j < len; j++) s[j] = tolower(s[j]);
}
/* Apply toupper() to every character of the yk__sds string 's'. */
void yk__sdstoupper(yk__sds s) {
  size_t len = yk__sdslen(s), j;
  for (j = 0; j < len; j++) s[j] = toupper(s[j]);
}
/* Compare two yk__sds strings s1 and s2 with memcmp().
 *
 * Return value:
 *
 *     positive if s1 > s2.
 *     negative if s1 < s2.
 *     0 if s1 and s2 are exactly the same binary string.
 *
 * If two strings share exactly the same prefix, but one of the two has
 * additional characters, the longer string is considered to be greater than
 * the smaller one. */
int yk__sdscmp(const yk__sds s1, const yk__sds s2) {
  size_t l1, l2, minlen;
  int cmp;
  l1 = yk__sdslen(s1);
  l2 = yk__sdslen(s2);
  minlen = (l1 < l2) ? l1 : l2;
  cmp = memcmp(s1, s2, minlen);
  if (cmp == 0) return l1 > l2 ? 1 : (l1 < l2 ? -1 : 0);
  return cmp;
}
/* Split 's' with separator in 'sep'. An array
 * of yk__sds strings is returned. *count will be set
 * by reference to the number of tokens returned.
 *
 * On out of memory, zero length string, zero length
 * separator, NULL is returned.
 *
 * Note that 'sep' is able to split a string using
 * a multi-character separator. For example
 * sdssplit("foo_-_bar","_-_"); will return two
 * elements "foo" and "bar".
 *
 * This version of the function is binary-safe but
 * requires length arguments. sdssplit() is just the
 * same function but for zero-terminated strings.
 */
yk__sds *yk__sdssplitlen(const char *s, ssize_t len, const char *sep,
                         int seplen, int *count) {
  int elements = 0, slots = 5;
  long start = 0, j;
  yk__sds *tokens;
  if (seplen < 1 || len < 0) return NULL;
  tokens = yk__s_malloc(sizeof(yk__sds) * slots);
  if (tokens == NULL) return NULL;
  if (len == 0) {
    *count = 0;
    return tokens;
  }
  for (j = 0; j < (len - (seplen - 1)); j++) {
    /* make sure there is room for the next element and the final one */
    if (slots < elements + 2) {
      yk__sds *newtokens;
      slots *= 2;
      newtokens = yk__s_realloc(tokens, sizeof(yk__sds) * slots);
      if (newtokens == NULL) goto cleanup;
      tokens = newtokens;
    }
    /* search the separator */
    if ((seplen == 1 && *(s + j) == sep[0]) ||
        (memcmp(s + j, sep, seplen) == 0)) {
      tokens[elements] = yk__sdsnewlen(s + start, j - start);
      if (tokens[elements] == NULL) goto cleanup;
      elements++;
      start = j + seplen;
      j = j + seplen - 1; /* skip the separator */
    }
  }
  /* Add the final element. We are sure there is room in the tokens array. */
  tokens[elements] = yk__sdsnewlen(s + start, len - start);
  if (tokens[elements] == NULL) goto cleanup;
  elements++;
  *count = elements;
  return tokens;
cleanup : {
  int i;
  for (i = 0; i < elements; i++) yk__sdsfree(tokens[i]);
  yk__s_free(tokens);
  *count = 0;
  return NULL;
}
}
/* Free the result returned by yk__sdssplitlen(), or do nothing if 'tokens' is NULL. */
void yk__sdsfreesplitres(yk__sds *tokens, int count) {
  if (!tokens) return;
  while (count--) yk__sdsfree(tokens[count]);
  yk__s_free(tokens);
}
/* Append to the yk__sds string "s" an escaped string representation where
 * all the non-printable characters (tested with isprint()) are turned into
 * escapes in the form "\n\r\a...." or "\x<hex-number>".
 *
 * After the call, the modified yk__sds string is no longer valid and all the
 * references must be substituted with the new pointer returned by the call. */
yk__sds yk__sdscatrepr(yk__sds s, const char *p, size_t len) {
  s = yk__sdscatlen(s, "\"", 1);
  while (len--) {
    switch (*p) {
      case '\\':
      case '"':
        s = yk__sdscatprintf(s, "\\%c", *p);
        break;
      case '\n':
        s = yk__sdscatlen(s, "\\n", 2);
        break;
      case '\r':
        s = yk__sdscatlen(s, "\\r", 2);
        break;
      case '\t':
        s = yk__sdscatlen(s, "\\t", 2);
        break;
      case '\a':
        s = yk__sdscatlen(s, "\\a", 2);
        break;
      case '\b':
        s = yk__sdscatlen(s, "\\b", 2);
        break;
      default:
        if (isprint(*p)) s = yk__sdscatprintf(s, "%c", *p);
        else
          s = yk__sdscatprintf(s, "\\x%02x", (unsigned char) *p);
        break;
    }
    p++;
  }
  return yk__sdscatlen(s, "\"", 1);
}
/* Helper function for yk__sdssplitargs() that returns non zero if 'c'
 * is a valid hex digit. */
int is_hex_digit(char c) {
  return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') ||
         (c >= 'A' && c <= 'F');
}
/* Helper function for yk__sdssplitargs() that converts a hex digit into an
 * integer from 0 to 15 */
int hex_digit_to_int(char c) {
  switch (c) {
    case '0':
      return 0;
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;
    case 'a':
    case 'A':
      return 10;
    case 'b':
    case 'B':
      return 11;
    case 'c':
    case 'C':
      return 12;
    case 'd':
    case 'D':
      return 13;
    case 'e':
    case 'E':
      return 14;
    case 'f':
    case 'F':
      return 15;
    default:
      return 0;
  }
}
/* Split a line into arguments, where every argument can be in the
 * following programming-language REPL-alike form:
 *
 * foo bar "newline are supported\n" and "\xff\x00otherstuff"
 *
 * The number of arguments is stored into *argc, and an array
 * of yk__sds is returned.
 *
 * The caller should free the resulting array of yk__sds strings with
 * yk__sdsfreesplitres().
 *
 * Note that yk__sdscatrepr() is able to convert back a string into
 * a quoted string in the same format yk__sdssplitargs() is able to parse.
 *
 * The function returns the allocated tokens on success, even when the
 * input string is empty, or NULL if the input contains unbalanced
 * quotes or closed quotes followed by non space characters
 * as in: "foo"bar or "foo'
 */
yk__sds *yk__sdssplitargs(const char *line, int *argc) {
  const char *p = line;
  char *current = NULL;
  char **vector = NULL;
  *argc = 0;
  while (1) {
    /* skip blanks */
    while (*p && isspace(*p)) p++;
    if (*p) {
      /* get a token */
      int inq = 0;  /* set to 1 if we are in "quotes" */
      int insq = 0; /* set to 1 if we are in 'single quotes' */
      int done = 0;
      if (current == NULL) current = yk__sdsempty();
      while (!done) {
        if (inq) {
          if (*p == '\\' && *(p + 1) == 'x' && is_hex_digit(*(p + 2)) &&
              is_hex_digit(*(p + 3))) {
            unsigned char byte;
            byte =
                (hex_digit_to_int(*(p + 2)) * 16) + hex_digit_to_int(*(p + 3));
            current = yk__sdscatlen(current, (char *) &byte, 1);
            p += 3;
          } else if (*p == '\\' && *(p + 1)) {
            char c;
            p++;
            switch (*p) {
              case 'n':
                c = '\n';
                break;
              case 'r':
                c = '\r';
                break;
              case 't':
                c = '\t';
                break;
              case 'b':
                c = '\b';
                break;
              case 'a':
                c = '\a';
                break;
              default:
                c = *p;
                break;
            }
            current = yk__sdscatlen(current, &c, 1);
          } else if (*p == '"') {
            /* closing quote must be followed by a space or
                         * nothing at all. */
            if (*(p + 1) && !isspace(*(p + 1))) goto err;
            done = 1;
          } else if (!*p) {
            /* unterminated quotes */
            goto err;
          } else {
            current = yk__sdscatlen(current, p, 1);
          }
        } else if (insq) {
          if (*p == '\\' && *(p + 1) == '\'') {
            p++;
            current = yk__sdscatlen(current, "'", 1);
          } else if (*p == '\'') {
            /* closing quote must be followed by a space or
                         * nothing at all. */
            if (*(p + 1) && !isspace(*(p + 1))) goto err;
            done = 1;
          } else if (!*p) {
            /* unterminated quotes */
            goto err;
          } else {
            current = yk__sdscatlen(current, p, 1);
          }
        } else {
          switch (*p) {
            case ' ':
            case '\n':
            case '\r':
            case '\t':
            case '\0':
              done = 1;
              break;
            case '"':
              inq = 1;
              break;
            case '\'':
              insq = 1;
              break;
            default:
              current = yk__sdscatlen(current, p, 1);
              break;
          }
        }
        if (*p) p++;
      }
      /* add the token to the vector */
      vector = yk__s_realloc(vector, ((*argc) + 1) * sizeof(char *));
      vector[*argc] = current;
      (*argc)++;
      current = NULL;
    } else {
      /* Even on empty input string return something not NULL. */
      if (vector == NULL) vector = yk__s_malloc(sizeof(void *));
      return vector;
    }
  }
err:
  while ((*argc)--) yk__sdsfree(vector[*argc]);
  yk__s_free(vector);
  if (current) yk__sdsfree(current);
  *argc = 0;
  return NULL;
}
/* Modify the string substituting all the occurrences of the set of
 * characters specified in the 'from' string to the corresponding character
 * in the 'to' array.
 *
 * For instance: yk__sdsmapchars(mystring, "ho", "01", 2)
 * will have the effect of turning the string "hello" into "0ell1".
 *
 * The function returns the yk__sds string pointer, that is always the same
 * as the input pointer since no resize is needed. */
yk__sds yk__sdsmapchars(yk__sds s, const char *from, const char *to,
                        size_t setlen) {
  size_t j, i, l = yk__sdslen(s);
  for (j = 0; j < l; j++) {
    for (i = 0; i < setlen; i++) {
      if (s[j] == from[i]) {
        s[j] = to[i];
        break;
      }
    }
  }
  return s;
}
/* Join an array of C strings using the specified separator (also a C string).
 * Returns the result as an yk__sds string. */
yk__sds yk__sdsjoin(char **argv, int argc, char *sep) {
  yk__sds join = yk__sdsempty();
  int j;
  for (j = 0; j < argc; j++) {
    join = yk__sdscat(join, argv[j]);
    if (j != argc - 1) join = yk__sdscat(join, sep);
  }
  return join;
}
/* Like yk__sdsjoin, but joins an array of SDS strings. */
yk__sds yk__sdsjoinsds(yk__sds *argv, int argc, const char *sep,
                       size_t seplen) {
  yk__sds join = yk__sdsempty();
  int j;
  for (j = 0; j < argc; j++) {
    join = yk__sdscatsds(join, argv[j]);
    if (j != argc - 1) join = yk__sdscatlen(join, sep, seplen);
  }
  return join;
}
/* Wrappers to the allocators used by SDS. Note that SDS will actually
 * just use the macros defined into sdsalloc.h in order to avoid to pay
 * the overhead of function calls. Here we define these wrappers only for
 * the programs SDS is linked to, if they want to touch the SDS internals
 * even if they use a different allocator. */
void *yk__sds_malloc(size_t size) { return yk__s_malloc(size); }
void *yk__sds_realloc(void *ptr, size_t size) {
  return yk__s_realloc(ptr, size);
}
void yk__sds_free(void *ptr) { yk__s_free(ptr); }
#if defined(YK__SDS_TEST_MAIN)
#include "limits.h"
#include "testhelp.h"
#include <stdio.h>
#define UNUSED(x) (void) (x)
int yk__sdsTest(void) {
  {
    yk__sds x = yk__sdsnew("foo"), y;
    test_cond("Create a string and obtain the length",
              yk__sdslen(x) == 3 && memcmp(x, "foo\0", 4) == 0) yk__sdsfree(x);
    x = yk__sdsnewlen("foo", 2);
    test_cond("Create a string with specified length",
              yk__sdslen(x) == 2 && memcmp(x, "fo\0", 3) == 0) x =
        yk__sdscat(x, "bar");
    test_cond("Strings concatenation",
              yk__sdslen(x) == 5 && memcmp(x, "fobar\0", 6) == 0);
    x = yk__sdscpy(x, "a");
    test_cond("yk__sdscpy() against an originally longer string",
              yk__sdslen(x) == 1 && memcmp(x, "a\0", 2) == 0) x =
        yk__sdscpy(x, "xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk");
    test_cond("yk__sdscpy() against an originally shorter string",
              yk__sdslen(x) == 33 &&
                  memcmp(x, "xyzxxxxxxxxxxyyyyyyyyyykkkkkkkkkk\0", 33) == 0)
        yk__sdsfree(x);
    x = yk__sdscatprintf(yk__sdsempty(), "%d", 123);
    test_cond("yk__sdscatprintf() seems working in the base case",
              yk__sdslen(x) == 3 && memcmp(x, "123\0", 4) == 0) yk__sdsfree(x);
    x = yk__sdsnew("--");
    x = yk__sdscatfmt(x, "Hello %s World %I,%I--", "Hi!", LLONG_MIN, LLONG_MAX);
    test_cond("yk__sdscatfmt() seems working in the base case",
              yk__sdslen(x) == 60 &&
                  memcmp(x,
                         "--Hello Hi! World -9223372036854775808,"
                         "9223372036854775807--",
                         60) == 0) printf("[%s]\n", x);
    yk__sdsfree(x);
    x = yk__sdsnew("--");
    x = yk__sdscatfmt(x, "%u,%U--", UINT_MAX, ULLONG_MAX);
    test_cond("yk__sdscatfmt() seems working with unsigned numbers",
              yk__sdslen(x) == 35 &&
                  memcmp(x, "--4294967295,18446744073709551615--", 35) == 0)
        yk__sdsfree(x);
    x = yk__sdsnew(" x ");
    yk__sdstrim(x, " x");
    test_cond("yk__sdstrim() works when all chars match", yk__sdslen(x) == 0)
        yk__sdsfree(x);
    x = yk__sdsnew(" x ");
    yk__sdstrim(x, " ");
    test_cond("yk__sdstrim() works when a single char remains",
              yk__sdslen(x) == 1 && x[0] == 'x') yk__sdsfree(x);
    x = yk__sdsnew("xxciaoyyy");
    yk__sdstrim(x, "xy");
    test_cond("yk__sdstrim() correctly trims characters",
              yk__sdslen(x) == 4 && memcmp(x, "ciao\0", 5) == 0) y =
        yk__sdsdup(x);
    yk__sdsrange(y, 1, 1);
    test_cond("yk__sdsrange(...,1,1)",
              yk__sdslen(y) == 1 && memcmp(y, "i\0", 2) == 0) yk__sdsfree(y);
    y = yk__sdsdup(x);
    yk__sdsrange(y, 1, -1);
    test_cond("yk__sdsrange(...,1,-1)",
              yk__sdslen(y) == 3 && memcmp(y, "iao\0", 4) == 0) yk__sdsfree(y);
    y = yk__sdsdup(x);
    yk__sdsrange(y, -2, -1);
    test_cond("yk__sdsrange(...,-2,-1)",
              yk__sdslen(y) == 2 && memcmp(y, "ao\0", 3) == 0) yk__sdsfree(y);
    y = yk__sdsdup(x);
    yk__sdsrange(y, 2, 1);
    test_cond("yk__sdsrange(...,2,1)",
              yk__sdslen(y) == 0 && memcmp(y, "\0", 1) == 0) yk__sdsfree(y);
    y = yk__sdsdup(x);
    yk__sdsrange(y, 1, 100);
    test_cond("yk__sdsrange(...,1,100)",
              yk__sdslen(y) == 3 && memcmp(y, "iao\0", 4) == 0) yk__sdsfree(y);
    y = yk__sdsdup(x);
    yk__sdsrange(y, 100, 100);
    test_cond("yk__sdsrange(...,100,100)",
              yk__sdslen(y) == 0 && memcmp(y, "\0", 1) == 0) yk__sdsfree(y);
    yk__sdsfree(x);
    x = yk__sdsnew("foo");
    y = yk__sdsnew("foa");
    test_cond("yk__sdscmp(foo,foa)", yk__sdscmp(x, y) > 0) yk__sdsfree(y);
    yk__sdsfree(x);
    x = yk__sdsnew("bar");
    y = yk__sdsnew("bar");
    test_cond("yk__sdscmp(bar,bar)", yk__sdscmp(x, y) == 0) yk__sdsfree(y);
    yk__sdsfree(x);
    x = yk__sdsnew("aar");
    y = yk__sdsnew("bar");
    test_cond("yk__sdscmp(bar,bar)", yk__sdscmp(x, y) < 0) yk__sdsfree(y);
    yk__sdsfree(x);
    x = yk__sdsnewlen("\a\n\0foo\r", 7);
    y = yk__sdscatrepr(yk__sdsempty(), x, yk__sdslen(x));
    test_cond("yk__sdscatrepr(...data...)",
              memcmp(y, "\"\\a\\n\\x00foo\\r\"", 15) == 0) {
      unsigned int oldfree;
      char *p;
      int step = 10, j, i;
      yk__sdsfree(x);
      yk__sdsfree(y);
      x = yk__sdsnew("0");
      test_cond("yk__sdsnew() free/len buffers",
                yk__sdslen(x) == 1 && yk__sdsavail(x) == 0);
      /* Run the test a few times in order to hit the first two
             * SDS header types. */
      for (i = 0; i < 10; i++) {
        int oldlen = yk__sdslen(x);
        x = yk__sdsMakeRoomFor(x, step);
        int type = x[-1] & YK__SDS_TYPE_MASK;
        test_cond("yk__sdsMakeRoomFor() len", yk__sdslen(x) == oldlen);
        if (type != YK__SDS_TYPE_5) {
          test_cond("yk__sdsMakeRoomFor() free", yk__sdsavail(x) >= step);
          oldfree = yk__sdsavail(x);
        }
        p = x + oldlen;
        for (j = 0; j < step; j++) { p[j] = 'A' + j; }
        yk__sdsIncrLen(x, step);
      }
      test_cond("yk__sdsMakeRoomFor() content",
                memcmp("0ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCD"
                       "EFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJ",
                       x, 101) == 0);
      test_cond("yk__sdsMakeRoomFor() final length", yk__sdslen(x) == 101);
      yk__sdsfree(x);
    }
  }
  test_report() return 0;
}
#endif
#ifdef YK__SDS_TEST_MAIN
int main(void) { return yk__sdsTest(); }
#endif
#endif /* YK__SDS_IMPLEMENTATION */
/*
*/
/* yk__stb_ds.h - v0.67 - public domain data structures - Sean Barrett 2019

   This is a single-header-file library that provides easy-to-use
   dynamic arrays and hash tables for C (also works in C++).

   For a gentle introduction:
      http://nothings.org/stb_ds

   To use this library, do this in *one* C or C++ file:
      #define YK__STB_DS_IMPLEMENTATION
      #include "yk__stb_ds.h"

TABLE OF CONTENTS

  Table of Contents
  Compile-time options
  License
  Documentation
  Notes
  Notes - Dynamic arrays
  Notes - Hash maps
  Credits

COMPILE-TIME OPTIONS

  #define YK__STBDS_NO_SHORT_NAMES

     This flag needs to be set globally.

     By default stb_ds exposes shorter function names that are not qualified
     with the "stbds_" prefix. If these names conflict with the names in your
     code, define this flag.

  #define YK__STBDS_SIPHASH_2_4

     This flag only needs to be set in the file containing #define YK__STB_DS_IMPLEMENTATION.

     By default yk__stb_ds.h hashes using a weaker variant of SipHash and a custom hash for
     4- and 8-byte keys. On 64-bit platforms, you can define the above flag to force
     yk__stb_ds.h to use specification-compliant SipHash-2-4 for all keys. Doing so makes
     hash table insertion about 20% slower on 4- and 8-byte keys, 5% slower on
     64-byte keys, and 10% slower on 256-byte keys on my test computer.

  #define YK__STBDS_REALLOC(context,ptr,size) better_realloc
  #define YK__STBDS_FREE(context,ptr)         better_free

     These defines only need to be set in the file containing #define YK__STB_DS_IMPLEMENTATION.

     By default stb_ds uses stdlib realloc() and free() for memory management. You can
     substitute your own functions instead by defining these symbols. You must either
     define both, or neither. Note that at the moment, 'context' will always be NULL.
     @TODO add an yk__array/hash initialization function that takes a memory context pointer.

  #define YK__STBDS_UNIT_TESTS

     Defines a function yk__stbds_unit_tests() that checks the functioning of the data structures.

  Note that on older versions of gcc (e.g. 5.x.x) you may need to build with '-std=c++0x'
     (or equivalentally '-std=c++11') when using anonymous structures as seen on the web
     page or in YK__STBDS_UNIT_TESTS.

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

DOCUMENTATION

  Dynamic Arrays

    Non-function interface:

      Declare an empty dynamic yk__array of type T
        T* foo = NULL;

      Access the i'th item of a dynamic yk__array 'foo' of type T, T* foo:
        foo[i]

    Functions (actually macros)

      yk__arrfree:
        void yk__arrfree(T*);
          Frees the yk__array.

      yk__arrlen:
        ptrdiff_t yk__arrlen(T*);
          Returns the number of elements in the yk__array.

      yk__arrlenu:
        size_t yk__arrlenu(T*);
          Returns the number of elements in the yk__array as an unsigned type.

      yk__arrpop:
        T yk__arrpop(T* a)
          Removes the final element of the yk__array and returns it.

      yk__arrput:
        T yk__arrput(T* a, T b);
          Appends the item b to the end of yk__array a. Returns b.

      yk__arrins:
        T yk__arrins(T* a, int p, T b);
          Inserts the item b into the middle of yk__array a, into a[p],
          moving the rest of the yk__array over. Returns b.

      yk__arrinsn:
        void yk__arrinsn(T* a, int p, int n);
          Inserts n uninitialized items into yk__array a starting at a[p],
          moving the rest of the yk__array over.

      yk__arraddnptr:
        T* yk__arraddnptr(T* a, int n)
          Appends n uninitialized items onto yk__array at the end.
          Returns a pointer to the first uninitialized item added.

      yk__arraddnindex:
        size_t yk__arraddnindex(T* a, int n)
          Appends n uninitialized items onto yk__array at the end.
          Returns the index of the first uninitialized item added.

      yk__arrdel:
        void yk__arrdel(T* a, int p);
          Deletes the element at a[p], moving the rest of the yk__array over.

      yk__arrdeln:
        void yk__arrdeln(T* a, int p, int n);
          Deletes n elements starting at a[p], moving the rest of the yk__array over.

      yk__arrdelswap:
        void yk__arrdelswap(T* a, int p);
          Deletes the element at a[p], replacing it with the element from
          the end of the yk__array. O(1) performance.

      yk__arrsetlen:
        void yk__arrsetlen(T* a, int n);
          Changes the length of the yk__array to n. Allocates uninitialized
          slots at the end if necessary.

      yk__arrsetcap:
        size_t yk__arrsetcap(T* a, int n);
          Sets the length of allocated storage to at least n. It will not
          change the length of the yk__array.

      yk__arrcap:
        size_t yk__arrcap(T* a);
          Returns the number of total elements the yk__array can contain without
          needing to be reallocated.

  Hash maps & String hash maps

    Given T is a structure type: struct { TK key; TV value; }. Note that some
    functions do not require TV value and can have other fields. For string
    hash maps, TK must be 'char *'.

    Special interface:

      yk__stbds_rand_seed:
        void yk__stbds_rand_seed(size_t seed);
          For security against adversarially chosen data, you should seed the
          library with a strong random number. Or at least seed it with time().

      yk__stbds_hash_string:
        size_t yk__stbds_hash_string(char *str, size_t seed);
          Returns a hash value for a string.

      yk__stbds_hash_bytes:
        size_t yk__stbds_hash_bytes(void *p, size_t len, size_t seed);
          These functions hash an arbitrary number of bytes. The function
          uses a custom hash for 4- and 8-byte data, and a weakened version
          of SipHash for everything else. On 64-bit platforms you can get
          specification-compliant SipHash-2-4 on all data by defining
          YK__STBDS_SIPHASH_2_4, at a significant cost in speed.

    Non-function interface:

      Declare an empty hash map of type T
        T* foo = NULL;

      Access the i'th entry in a hash table T* foo:
        foo[i]

    Function interface (actually macros):

      yk__hmfree
      yk__shfree
        void yk__hmfree(T*);
        void yk__shfree(T*);
          Frees the hashmap and sets the pointer to NULL.

      yk__hmlen
      yk__shlen
        ptrdiff_t yk__hmlen(T*)
        ptrdiff_t yk__shlen(T*)
          Returns the number of elements in the hashmap.

      yk__hmlenu
      yk__shlenu
        size_t yk__hmlenu(T*)
        size_t yk__shlenu(T*)
          Returns the number of elements in the hashmap.

      yk__hmgeti
      yk__shgeti
      yk__hmgeti_ts
        ptrdiff_t yk__hmgeti(T*, TK key)
        ptrdiff_t yk__shgeti(T*, char* key)
        ptrdiff_t yk__hmgeti_ts(T*, TK key, ptrdiff_t tempvar)
          Returns the index in the hashmap which has the key 'key', or -1
          if the key is not present.

      yk__hmget
      yk__hmget_ts
      yk__shget
        TV yk__hmget(T*, TK key)
        TV yk__shget(T*, char* key)
        TV yk__hmget_ts(T*, TK key, ptrdiff_t tempvar)
          Returns the value corresponding to 'key' in the hashmap.
          The structure must have a 'value' field

      yk__hmgets
      yk__shgets
        T yk__hmgets(T*, TK key)
        T yk__shgets(T*, char* key)
          Returns the structure corresponding to 'key' in the hashmap.

      yk__hmgetp
      yk__shgetp
      yk__hmgetp_ts
      yk__hmgetp_null
      yk__shgetp_null
        T* yk__hmgetp(T*, TK key)
        T* yk__shgetp(T*, char* key)
        T* yk__hmgetp_ts(T*, TK key, ptrdiff_t tempvar)
        T* yk__hmgetp_null(T*, TK key)
        T* yk__shgetp_null(T*, char *key)
          Returns a pointer to the structure corresponding to 'key' in
          the hashmap. Functions ending in "_null" return NULL if the key
          is not present in the hashmap; the others return a pointer to a
          structure holding the default value (but not the searched-for key).

      yk__hmdefault
      yk__shdefault
        TV yk__hmdefault(T*, TV value)
        TV yk__shdefault(T*, TV value)
          Sets the default value for the hashmap, the value which will be
          returned by yk__hmget/yk__shget if the key is not present.

      yk__hmdefaults
      yk__shdefaults
        TV yk__hmdefaults(T*, T item)
        TV yk__shdefaults(T*, T item)
          Sets the default struct for the hashmap, the contents which will be
          returned by yk__hmgets/yk__shgets if the key is not present.

      yk__hmput
      yk__shput
        TV yk__hmput(T*, TK key, TV value)
        TV yk__shput(T*, char* key, TV value)
          Inserts a <key,value> pair into the hashmap. If the key is already
          present in the hashmap, updates its value.

      yk__hmputs
      yk__shputs
        T yk__hmputs(T*, T item)
        T yk__shputs(T*, T item)
          Inserts a struct with T.key into the hashmap. If the struct is already
          present in the hashmap, updates it.

      yk__hmdel
      yk__shdel
        int yk__hmdel(T*, TK key)
        int yk__shdel(T*, char* key)
          If 'key' is in the hashmap, deletes its entry and returns 1.
          Otherwise returns 0.

    Function interface (actually macros) for strings only:

      yk__sh_new_strdup
        void yk__sh_new_strdup(T*);
          Overwrites the existing pointer with a newly allocated
          string hashmap which will automatically allocate and free
          each string key using realloc/free

      yk__sh_new_arena
        void yk__sh_new_arena(T*);
          Overwrites the existing pointer with a newly allocated
          string hashmap which will automatically allocate each string
          key to a string arena. Every string key ever used by this
          hash table remains in the arena until the arena is freed.
          Additionally, any key which is deleted and reinserted will
          be allocated multiple times in the string arena.

NOTES

  * These data structures are realloc'd when they grow, and the macro
    "functions" write to the provided pointer. This means: (a) the pointer
    must be an lvalue, and (b) the pointer to the data structure is not
    stable, and you must maintain it the same as you would a realloc'd
    pointer. For example, if you pass a pointer to a dynamic yk__array to a
    function which updates it, the function must return back the new
    pointer to the caller. This is the price of trying to do this in C.

  * The following are the only functions that are thread-safe on a single data
    structure, i.e. can be run in multiple threads simultaneously on the same
    data structure
        yk__hmlen        yk__shlen
        yk__hmlenu       yk__shlenu
        yk__hmget_ts     shget_ts
        yk__hmgeti_ts    shgeti_ts
        hmgets_ts    shgets_ts

  * You iterate over the contents of a dynamic yk__array and a hashmap in exactly
    the same way, using yk__arrlen/yk__hmlen/yk__shlen:

      for (i=0; i < yk__arrlen(foo); ++i)
         ... foo[i] ...

  * All operations except yk__arrins/yk__arrdel are O(1) amortized, but individual
    operations can be slow, so these data structures may not be suitable
    for real time use. Dynamic arrays double in capacity as needed, so
    elements are copied an average of once. Hash tables double/halve
    their size as needed, with appropriate hysteresis to maintain O(1)
    performance.

NOTES - DYNAMIC ARRAY

  * If you know how long a dynamic yk__array is going to be in advance, you can avoid
    extra memory allocations by using yk__arrsetlen to allocate it to that length in
    advance and use foo[n] while filling it out, or yk__arrsetcap to allocate the memory
    for that length and use yk__arrput/yk__arrpush as normal.

  * Unlike some other versions of the dynamic yk__array, this version should
    be safe to use with strict-aliasing optimizations.

NOTES - HASH MAP

  * For compilers other than GCC and clang (e.g. Visual Studio), for yk__hmput/yk__hmget/yk__hmdel
    and variants, the key must be an lvalue (so the macro can take the address of it).
    Extensions are used that eliminate this requirement if you're using C99 and later
    in GCC or clang, or if you're using C++ in GCC. But note that this can make your
    code less portable.

  * To test for presence of a key in a hashmap, just do 'yk__hmgeti(foo,key) >= 0'.

  * The iteration order of your data in the hashmap is determined solely by the
    order of insertions and deletions. In particular, if you never delete, new
    keys are always added at the end of the yk__array. This will be consistent
    across all platforms and versions of the library. However, you should not
    attempt to serialize the internal hash table, as the hash is not consistent
    between different platforms, and may change with future versions of the library.

  * Use yk__sh_new_arena() for string hashmaps that you never delete from. Initialize
    with NULL if you're managing the memory for your strings, or your strings are
    never freed (at least until the hashmap is freed). Otherwise, use yk__sh_new_strdup().
    @TODO: make an arena variant that garbage collects the strings with a trivial
    copy collector into a new arena whenever the table shrinks / rebuilds. Since
    current arena recommendation is to only use arena if it never deletes, then
    this can just replace current arena implementation.

  * If adversarial input is a serious concern and you're on a 64-bit platform,
    enable YK__STBDS_SIPHASH_2_4 (see the 'Compile-time options' section), and pass
    a strong random number to yk__stbds_rand_seed.

  * The default value for the hash table is stored in foo[-1], so if you
    use code like 'yk__hmget(T,k)->value = 5' you can accidentally overwrite
    the value stored by yk__hmdefault if 'k' is not present.

CREDITS

  Sean Barrett -- library, idea for dynamic yk__array API/implementation
  Per Vognsen  -- idea for hash table API/implementation
  Rafael Sachetto -- yk__arrpop()
  github:HeroicKatora -- yk__arraddn() reworking

  Bugfixes:
    Andy Durdin
    Shane Liesegang
    Vinh Truong
    Andreas Molzer
    github:hashitaku
    github:srdjanstipic
    Macoy Madson
    Andreas Vennstrom
    Tobias Mansfield-Williams
*/
#ifdef YK__STBDS_UNIT_TESTS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef YK__INCLUDE_STB_DS_H
#define YK__INCLUDE_STB_DS_H
#include <stddef.h>
#include <string.h>
#ifndef YK__STBDS_NO_SHORT_NAMES
#define yk__arrlen yk__stbds_arrlen
#define yk__arrlenu yk__stbds_arrlenu
#define yk__arrput yk__stbds_arrput
#define yk__arrpush yk__stbds_arrput
#define yk__arrpop yk__stbds_arrpop
#define yk__arrfree yk__stbds_arrfree
#define yk__arraddn                                                            \
  yk__stbds_arraddn// deprecated, use one of the following instead:
#define yk__arraddnptr yk__stbds_arraddnptr
#define yk__arraddnindex yk__stbds_arraddnindex
#define yk__arrsetlen yk__stbds_arrsetlen
#define yk__arrlast yk__stbds_arrlast
#define yk__arrins yk__stbds_arrins
#define yk__arrinsn yk__stbds_arrinsn
#define yk__arrdel yk__stbds_arrdel
#define yk__arrdeln yk__stbds_arrdeln
#define yk__arrdelswap yk__stbds_arrdelswap
#define yk__arrcap yk__stbds_arrcap
#define yk__arrsetcap yk__stbds_arrsetcap
#define yk__hmput yk__stbds_hmput
#define yk__hmputs yk__stbds_hmputs
#define yk__hmget yk__stbds_hmget
#define yk__hmget_ts yk__stbds_hmget_ts
#define yk__hmgets yk__stbds_hmgets
#define yk__hmgetp yk__stbds_hmgetp
#define yk__hmgetp_ts yk__stbds_hmgetp_ts
#define yk__hmgetp_null yk__stbds_hmgetp_null
#define yk__hmgeti yk__stbds_hmgeti
#define yk__hmgeti_ts yk__stbds_hmgeti_ts
#define yk__hmdel yk__stbds_hmdel
#define yk__hmlen yk__stbds_hmlen
#define yk__hmlenu yk__stbds_hmlenu
#define yk__hmfree yk__stbds_hmfree
#define yk__hmdefault yk__stbds_hmdefault
#define yk__hmdefaults yk__stbds_hmdefaults
#define yk__shput yk__stbds_shput
#define yk__shputi yk__stbds_shputi
#define yk__shputs yk__stbds_shputs
#define yk__shget yk__stbds_shget
#define yk__shgeti yk__stbds_shgeti
#define yk__shgets yk__stbds_shgets
#define yk__shgetp yk__stbds_shgetp
#define yk__shgetp_null yk__stbds_shgetp_null
#define yk__shdel yk__stbds_shdel
#define yk__shlen yk__stbds_shlen
#define yk__shlenu yk__stbds_shlenu
#define yk__shfree yk__stbds_shfree
#define yk__shdefault yk__stbds_shdefault
#define yk__shdefaults yk__stbds_shdefaults
#define yk__sh_new_arena yk__stbds_sh_new_arena
#define yk__sh_new_strdup yk__stbds_sh_new_strdup
#define stralloc yk__stbds_stralloc
#define strreset yk__stbds_strreset
#endif
#if defined(YK__STBDS_REALLOC) && !defined(YK__STBDS_FREE) ||                  \
    !defined(YK__STBDS_REALLOC) && defined(YK__STBDS_FREE)
#error "You must define both YK__STBDS_REALLOC and YK__STBDS_FREE, or neither."
#endif
#if !defined(YK__STBDS_REALLOC) && !defined(YK__STBDS_FREE)
#include <stdlib.h>
#define YK__STBDS_REALLOC(c, p, s) realloc(p, s)
#define YK__STBDS_FREE(c, p) free(p)
#endif
#ifdef _MSC_VER
#define YK__STBDS_NOTUSED(v) (void) (v)
#else
#define YK__STBDS_NOTUSED(v) (void) sizeof(v)
#endif
#ifdef __cplusplus
extern "C" {
#endif
// for security against attackers, seed the library with a random number, at least time() but stronger is better
extern void yk__stbds_rand_seed(size_t seed);
// these are the hash functions used internally if you want to test them or use them for other purposes
extern size_t yk__stbds_hash_bytes(void *p, size_t len, size_t seed);
extern size_t yk__stbds_hash_string(yk__sds str, size_t seed);
// this is a simple string arena allocator, initialize with e.g. 'yk__stbds_string_arena my_arena={0}'.
typedef struct yk__stbds_string_arena yk__stbds_string_arena;
extern char *yk__stbds_stralloc(yk__stbds_string_arena *a, char *str);
extern void yk__stbds_strreset(yk__stbds_string_arena *a);
// have to #define YK__STBDS_UNIT_TESTS to call this
extern void yk__stbds_unit_tests(void);
///////////////
//
// Everything below here is implementation details
//
extern void *yk__stbds_arrgrowf(void *a, size_t elemsize, size_t addlen,
                                size_t min_cap);
extern void yk__stbds_arrfreef(void *a);
extern void yk__stbds_hmfree_func(void *p, size_t elemsize);
extern void *yk__stbds_hmget_key(void *a, size_t elemsize, void *key,
                                 size_t keysize, int mode);
extern void *yk__stbds_hmget_key_ts(void *a, size_t elemsize, void *key,
                                    size_t keysize, ptrdiff_t *temp, int mode);
extern void *yk__stbds_hmput_default(void *a, size_t elemsize);
extern void *yk__stbds_hmput_key(void *a, size_t elemsize, void *key,
                                 size_t keysize, int mode);
extern void *yk__stbds_hmdel_key(void *a, size_t elemsize, void *key,
                                 size_t keysize, size_t keyoffset, int mode);
extern void *yk__stbds_shmode_func(size_t elemsize, int mode);
#ifdef __cplusplus
}
#endif
#if defined(__GNUC__) || defined(__clang__)
#define YK__STBDS_HAS_TYPEOF
#ifdef __cplusplus
//#define YK__STBDS_HAS_LITERAL_ARRAY  // this is currently broken for clang
#endif
#endif
#if !defined(__cplusplus)
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#define YK__STBDS_HAS_LITERAL_ARRAY
#endif
#endif
// this macro takes the address of the argument, but on gcc/clang can accept rvalues
#if defined(YK__STBDS_HAS_LITERAL_ARRAY) && defined(YK__STBDS_HAS_TYPEOF)
#if __clang__
#define YK__STBDS_ADDRESSOF(typevar, value)                                    \
  ((__typeof__(typevar)[1]){                                                   \
      value})// literal yk__array decays to pointer to value
#else
#define YK__STBDS_ADDRESSOF(typevar, value)                                    \
  ((typeof(typevar)[1]){value})// literal yk__array decays to pointer to value
#endif
#else
#define YK__STBDS_ADDRESSOF(typevar, value) &(value)
#endif
#define YK__STBDS_OFFSETOF(var, field) ((char *) &(var)->field - (char *) (var))
#define yk__stbds_header(t) ((yk__stbds_array_header *) (t) -1)
#define yk__stbds_temp(t) yk__stbds_header(t)->temp
#define yk__stbds_temp_key(t) (*(char **) yk__stbds_header(t)->hash_table)
#define yk__stbds_arrsetcap(a, n) (yk__stbds_arrgrow(a, 0, n))
#define yk__stbds_arrsetlen(a, n)                                              \
  ((yk__stbds_arrcap(a) < (size_t) (n)                                         \
    ? yk__stbds_arrsetcap((a), (size_t) (n)),                                  \
    0 : 0),                                                                    \
   (a) ? yk__stbds_header(a)->length = (size_t) (n) : 0)
#define yk__stbds_arrcap(a) ((a) ? yk__stbds_header(a)->capacity : 0)
#define yk__stbds_arrlen(a) ((a) ? (ptrdiff_t) yk__stbds_header(a)->length : 0)
#define yk__stbds_arrlenu(a) ((a) ? yk__stbds_header(a)->length : 0)
#define yk__stbds_arrput(a, v)                                                 \
  (yk__stbds_arrmaybegrow(a, 1), (a)[yk__stbds_header(a)->length++] = (v))
#define yk__stbds_arrpush yk__stbds_arrput// synonym
#define yk__stbds_arrpop(a)                                                    \
  (yk__stbds_header(a)->length--, (a)[yk__stbds_header(a)->length])
#define yk__stbds_arraddn(a, n)                                                \
  ((void) (yk__stbds_arraddnindex(                                             \
      a, n)))// deprecated, use one of the following instead:
#define yk__stbds_arraddnptr(a, n)                                             \
  (yk__stbds_arrmaybegrow(a, n),                                               \
   (n) ? (yk__stbds_header(a)->length += (n),                                  \
          &(a)[yk__stbds_header(a)->length - (n)])                             \
       : (a))
#define yk__stbds_arraddnindex(a, n)                                           \
  (yk__stbds_arrmaybegrow(a, n), (n) ? (yk__stbds_header(a)->length += (n),    \
                                        yk__stbds_header(a)->length - (n))     \
                                     : yk__stbds_arrlen(a))
#define yk__stbds_arraddnoff yk__stbds_arraddnindex
#define yk__stbds_arrlast(a) ((a)[yk__stbds_header(a)->length - 1])
#define yk__stbds_arrfree(a)                                                   \
  ((void) ((a) ? YK__STBDS_FREE(NULL, yk__stbds_header(a)) : (void) 0),        \
   (a) = NULL)
#define yk__stbds_arrdel(a, i) yk__stbds_arrdeln(a, i, 1)
#define yk__stbds_arrdeln(a, i, n)                                             \
  (memmove(&(a)[i], &(a)[(i) + (n)],                                           \
           sizeof *(a) * (yk__stbds_header(a)->length - (n) - (i))),           \
   yk__stbds_header(a)->length -= (n))
#define yk__stbds_arrdelswap(a, i)                                             \
  ((a)[i] = yk__stbds_arrlast(a), yk__stbds_header(a)->length -= 1)
#define yk__stbds_arrinsn(a, i, n)                                             \
  (yk__stbds_arraddn((a), (n)),                                                \
   memmove(&(a)[(i) + (n)], &(a)[i],                                           \
           sizeof *(a) * (yk__stbds_header(a)->length - (n) - (i))))
#define yk__stbds_arrins(a, i, v) (yk__stbds_arrinsn((a), (i), 1), (a)[i] = (v))
#define yk__stbds_arrmaybegrow(a, n)                                           \
  ((!(a) || yk__stbds_header(a)->length + (n) > yk__stbds_header(a)->capacity) \
       ? (yk__stbds_arrgrow(a, n, 0), 0)                                       \
       : 0)
#define yk__stbds_arrgrow(a, b, c)                                             \
  ((a) = yk__stbds_arrgrowf_wrapper((a), sizeof *(a), (b), (c)))
#define yk__stbds_hmput(t, k, v)                                               \
  ((t) = yk__stbds_hmput_key_wrapper(                                          \
       (t), sizeof *(t), (void *) YK__STBDS_ADDRESSOF((t)->key, (k)),          \
       sizeof(t)->key, 0),                                                     \
   (t)[yk__stbds_temp((t) -1)].key = (k),                                      \
   (t)[yk__stbds_temp((t) -1)].value = (v))
#define yk__stbds_hmputs(t, s)                                                 \
  ((t) = yk__stbds_hmput_key_wrapper((t), sizeof *(t), &(s).key,               \
                                     sizeof(s).key, YK__STBDS_HM_BINARY),      \
   (t)[yk__stbds_temp((t) -1)] = (s))
#define yk__stbds_hmgeti(t, k)                                                 \
  ((t) = yk__stbds_hmget_key_wrapper(                                          \
       (t), sizeof *(t), (void *) YK__STBDS_ADDRESSOF((t)->key, (k)),          \
       sizeof(t)->key, YK__STBDS_HM_BINARY),                                   \
   yk__stbds_temp((t) -1))
#define yk__stbds_hmgeti_ts(t, k, temp)                                        \
  ((t) = yk__stbds_hmget_key_ts_wrapper(                                       \
       (t), sizeof *(t), (void *) YK__STBDS_ADDRESSOF((t)->key, (k)),          \
       sizeof(t)->key, &(temp), YK__STBDS_HM_BINARY),                          \
   (temp))
#define yk__stbds_hmgetp(t, k)                                                 \
  ((void) yk__stbds_hmgeti(t, k), &(t)[yk__stbds_temp((t) -1)])
#define yk__stbds_hmgetp_ts(t, k, temp)                                        \
  ((void) yk__stbds_hmgeti_ts(t, k, temp), &(t)[temp])
#define yk__stbds_hmdel(t, k)                                                  \
  (((t) = yk__stbds_hmdel_key_wrapper(                                         \
        (t), sizeof *(t), (void *) YK__STBDS_ADDRESSOF((t)->key, (k)),         \
        sizeof(t)->key, YK__STBDS_OFFSETOF((t), key), YK__STBDS_HM_BINARY)),   \
   (t) ? yk__stbds_temp((t) -1) : 0)
#define yk__stbds_hmdefault(t, v)                                              \
  ((t) = yk__stbds_hmput_default_wrapper((t), sizeof *(t)), (t)[-1].value = (v))
#define yk__stbds_hmdefaults(t, s)                                             \
  ((t) = yk__stbds_hmput_default_wrapper((t), sizeof *(t)), (t)[-1] = (s))
#define yk__stbds_hmfree(p)                                                    \
  ((void) ((p) != NULL ? yk__stbds_hmfree_func((p) -1, sizeof *(p)), 0 : 0),   \
   (p) = NULL)
#define yk__stbds_hmgets(t, k) (*yk__stbds_hmgetp(t, k))
#define yk__stbds_hmget(t, k) (yk__stbds_hmgetp(t, k)->value)
#define yk__stbds_hmget_ts(t, k, temp) (yk__stbds_hmgetp_ts(t, k, temp)->value)
#define yk__stbds_hmlen(t)                                                     \
  ((t) ? (ptrdiff_t) yk__stbds_header((t) -1)->length - 1 : 0)
#define yk__stbds_hmlenu(t) ((t) ? yk__stbds_header((t) -1)->length - 1 : 0)
#define yk__stbds_hmgetp_null(t, k)                                            \
  (yk__stbds_hmgeti(t, k) == -1 ? NULL : &(t)[yk__stbds_temp((t) -1)])
#define yk__stbds_shput(t, k, v)                                               \
  ((t) = yk__stbds_hmput_key_wrapper((t), sizeof *(t), (void *) (k),           \
                                     sizeof(t)->key, YK__STBDS_HM_STRING),     \
   (t)[yk__stbds_temp((t) -1)].value = (v))
#define yk__stbds_shputi(t, k, v)                                              \
  ((t) = yk__stbds_hmput_key_wrapper((t), sizeof *(t), (void *) (k),           \
                                     sizeof(t)->key, YK__STBDS_HM_STRING),     \
   (t)[yk__stbds_temp((t) -1)].value = (v), yk__stbds_temp((t) -1))
#define yk__stbds_shputs(t, s)                                                 \
  ((t) = yk__stbds_hmput_key_wrapper((t), sizeof *(t), (void *) (s).key,       \
                                     sizeof(s).key, YK__STBDS_HM_STRING),      \
   (t)[yk__stbds_temp((t) -1)] = (s),                                          \
   (t)[yk__stbds_temp((t) -1)].key = yk__stbds_temp_key((                      \
       t) -1))// above line overwrites whole structure, so must rewrite key here if it was allocated internally
#define yk__stbds_pshput(t, p)                                                 \
  ((t) = yk__stbds_hmput_key_wrapper((t), sizeof *(t), (void *) (p)->key,      \
                                     sizeof(p)->key,                           \
                                     YK__STBDS_HM_PTR_TO_STRING),              \
   (t)[yk__stbds_temp((t) -1)] = (p))
#define yk__stbds_shgeti(t, k)                                                 \
  ((t) = yk__stbds_hmget_key_wrapper((t), sizeof *(t), (void *) (k),           \
                                     sizeof(t)->key, YK__STBDS_HM_STRING),     \
   yk__stbds_temp((t) -1))
#define yk__stbds_pshgeti(t, k)                                                \
  ((t) = yk__stbds_hmget_key_wrapper((t), sizeof *(t), (void *) (k),           \
                                     sizeof(*(t))->key,                        \
                                     YK__STBDS_HM_PTR_TO_STRING),              \
   yk__stbds_temp((t) -1))
#define yk__stbds_shgetp(t, k)                                                 \
  ((void) yk__stbds_shgeti(t, k), &(t)[yk__stbds_temp((t) -1)])
#define yk__stbds_pshget(t, k)                                                 \
  ((void) yk__stbds_pshgeti(t, k), (t)[yk__stbds_temp((t) -1)])
#define yk__stbds_shdel(t, k)                                                  \
  (((t) = yk__stbds_hmdel_key_wrapper(                                         \
        (t), sizeof *(t), (void *) (k), sizeof(t)->key,                        \
        YK__STBDS_OFFSETOF((t), key), YK__STBDS_HM_STRING)),                   \
   (t) ? yk__stbds_temp((t) -1) : 0)
#define yk__stbds_pshdel(t, k)                                                 \
  (((t) = yk__stbds_hmdel_key_wrapper(                                         \
        (t), sizeof *(t), (void *) (k), sizeof(*(t))->key,                     \
        YK__STBDS_OFFSETOF(*(t), key), YK__STBDS_HM_PTR_TO_STRING)),           \
   (t) ? yk__stbds_temp((t) -1) : 0)
#define yk__stbds_sh_new_arena(t)                                              \
  ((t) = yk__stbds_shmode_func_wrapper(t, sizeof *(t), YK__STBDS_SH_ARENA))
#define yk__stbds_sh_new_strdup(t)                                             \
  ((t) = yk__stbds_shmode_func_wrapper(t, sizeof *(t), YK__STBDS_SH_STRDUP))
#define yk__stbds_shdefault(t, v) yk__stbds_hmdefault(t, v)
#define yk__stbds_shdefaults(t, s) yk__stbds_hmdefaults(t, s)
#define yk__stbds_shfree yk__stbds_hmfree
#define yk__stbds_shlenu yk__stbds_hmlenu
#define yk__stbds_shgets(t, k) (*yk__stbds_shgetp(t, k))
#define yk__stbds_shget(t, k) (yk__stbds_shgetp(t, k)->value)
#define yk__stbds_shgetp_null(t, k)                                            \
  (yk__stbds_shgeti(t, k) == -1 ? NULL : &(t)[yk__stbds_temp((t) -1)])
#define yk__stbds_shlen yk__stbds_hmlen
typedef struct {
  size_t length;
  size_t capacity;
  void *hash_table;
  ptrdiff_t temp;
} yk__stbds_array_header;
typedef struct yk__stbds_string_block {
  struct yk__stbds_string_block *next;
  char storage[8];
} yk__stbds_string_block;
struct yk__stbds_string_arena {
  yk__stbds_string_block *storage;
  size_t remaining;
  unsigned char block;
  unsigned char mode;// this isn't used by the string arena itself
};
#define YK__STBDS_HM_BINARY 0
#define YK__STBDS_HM_STRING 1
enum {
  YK__STBDS_SH_NONE,
  YK__STBDS_SH_DEFAULT,
  YK__STBDS_SH_STRDUP,
  YK__STBDS_SH_ARENA
};
#ifdef __cplusplus
// in C we use implicit assignment from these void*-returning functions to T*.
// in C++ these templates make the same code work
template<class T>
static T *yk__stbds_arrgrowf_wrapper(T *a, size_t elemsize, size_t addlen,
                                     size_t min_cap) {
  return (T *) yk__stbds_arrgrowf((void *) a, elemsize, addlen, min_cap);
}
template<class T>
static T *yk__stbds_hmget_key_wrapper(T *a, size_t elemsize, void *key,
                                      size_t keysize, int mode) {
  return (T *) yk__stbds_hmget_key((void *) a, elemsize, key, keysize, mode);
}
template<class T>
static T *yk__stbds_hmget_key_ts_wrapper(T *a, size_t elemsize, void *key,
                                         size_t keysize, ptrdiff_t *temp,
                                         int mode) {
  return (T *) yk__stbds_hmget_key_ts((void *) a, elemsize, key, keysize, temp,
                                      mode);
}
template<class T>
static T *yk__stbds_hmput_default_wrapper(T *a, size_t elemsize) {
  return (T *) yk__stbds_hmput_default((void *) a, elemsize);
}
template<class T>
static T *yk__stbds_hmput_key_wrapper(T *a, size_t elemsize, void *key,
                                      size_t keysize, int mode) {
  return (T *) yk__stbds_hmput_key((void *) a, elemsize, key, keysize, mode);
}
template<class T>
static T *yk__stbds_hmdel_key_wrapper(T *a, size_t elemsize, void *key,
                                      size_t keysize, size_t keyoffset,
                                      int mode) {
  return (T *) yk__stbds_hmdel_key((void *) a, elemsize, key, keysize,
                                   keyoffset, mode);
}
template<class T>
static T *yk__stbds_shmode_func_wrapper(T *, size_t elemsize, int mode) {
  return (T *) yk__stbds_shmode_func(elemsize, mode);
}
#else
#define yk__stbds_arrgrowf_wrapper yk__stbds_arrgrowf
#define yk__stbds_hmget_key_wrapper yk__stbds_hmget_key
#define yk__stbds_hmget_key_ts_wrapper yk__stbds_hmget_key_ts
#define yk__stbds_hmput_default_wrapper yk__stbds_hmput_default
#define yk__stbds_hmput_key_wrapper yk__stbds_hmput_key
#define yk__stbds_hmdel_key_wrapper yk__stbds_hmdel_key
#define yk__stbds_shmode_func_wrapper(t, e, m) yk__stbds_shmode_func(e, m)
#endif
#endif// YK__INCLUDE_STB_DS_H
//////////////////////////////////////////////////////////////////////////////
//
//   IMPLEMENTATION
//
#ifdef YK__STB_DS_IMPLEMENTATION
#include <assert.h>
#include <string.h>
#ifndef YK__STBDS_ASSERT
#define YK__STBDS_ASSERT_WAS_UNDEFINED
#define YK__STBDS_ASSERT(x) ((void) 0)
#endif
#ifdef YK__STBDS_STATISTICS
#define YK__STBDS_STATS(x) x
size_t yk__stbds_array_grow;
size_t yk__stbds_hash_grow;
size_t yk__stbds_hash_shrink;
size_t yk__stbds_hash_rebuild;
size_t yk__stbds_hash_probes;
size_t yk__stbds_hash_alloc;
size_t yk__stbds_rehash_probes;
size_t yk__stbds_rehash_items;
#else
#define YK__STBDS_STATS(x)
#endif
//
// stbds_arr implementation
//
//int *prev_allocs[65536];
//int num_prev;
void *yk__stbds_arrgrowf(void *a, size_t elemsize, size_t addlen,
                         size_t min_cap) {
  yk__stbds_array_header temp = {0};// force debugging
  void *b;
  size_t min_len = yk__stbds_arrlen(a) + addlen;
  (void) sizeof(temp);
  // compute the minimum capacity needed
  if (min_len > min_cap) min_cap = min_len;
  if (min_cap <= yk__stbds_arrcap(a)) return a;
  // increase needed capacity to guarantee O(1) amortized
  if (min_cap < 2 * yk__stbds_arrcap(a)) min_cap = 2 * yk__stbds_arrcap(a);
  else if (min_cap < 4)
    min_cap = 4;
  //if (num_prev < 65536) if (a) prev_allocs[num_prev++] = (int *) ((char *) a+1);
  //if (num_prev == 2201)
  //  num_prev = num_prev;
  b = YK__STBDS_REALLOC(NULL, (a) ? yk__stbds_header(a) : 0,
                        elemsize * min_cap + sizeof(yk__stbds_array_header));
  //if (num_prev < 65536) prev_allocs[num_prev++] = (int *) (char *) b;
  b = (char *) b + sizeof(yk__stbds_array_header);
  if (a == NULL) {
    yk__stbds_header(b)->length = 0;
    yk__stbds_header(b)->hash_table = 0;
    yk__stbds_header(b)->temp = 0;
  } else {
    YK__STBDS_STATS(++yk__stbds_array_grow);
  }
  yk__stbds_header(b)->capacity = min_cap;
  return b;
}
void yk__stbds_arrfreef(void *a) { YK__STBDS_FREE(NULL, yk__stbds_header(a)); }
//
// stbds_hm hash table implementation
//
#ifdef YK__STBDS_INTERNAL_SMALL_BUCKET
#define YK__STBDS_BUCKET_LENGTH 4
#else
#define YK__STBDS_BUCKET_LENGTH 8
#endif
#define YK__STBDS_BUCKET_SHIFT (YK__STBDS_BUCKET_LENGTH == 8 ? 3 : 2)
#define YK__STBDS_BUCKET_MASK (YK__STBDS_BUCKET_LENGTH - 1)
#define YK__STBDS_CACHE_LINE_SIZE 64
#define YK__STBDS_ALIGN_FWD(n, a) (((n) + (a) -1) & ~((a) -1))
typedef struct {
  size_t hash[YK__STBDS_BUCKET_LENGTH];
  ptrdiff_t index[YK__STBDS_BUCKET_LENGTH];
} yk__stbds_hash_bucket;// in 32-bit, this is one 64-byte cache line; in 64-bit, each yk__array is one 64-byte cache line
typedef struct {
  char *temp_key;// this MUST be the first field of the hash table
  size_t slot_count;
  size_t used_count;
  size_t used_count_threshold;
  size_t used_count_shrink_threshold;
  size_t tombstone_count;
  size_t tombstone_count_threshold;
  size_t seed;
  size_t slot_count_log2;
  yk__stbds_string_arena string;
  yk__stbds_hash_bucket *
      storage;// not a separate allocation, just 64-byte aligned storage after this struct
} yk__stbds_hash_index;
#define YK__STBDS_INDEX_EMPTY -1
#define YK__STBDS_INDEX_DELETED -2
#define YK__STBDS_INDEX_IN_USE(x) ((x) >= 0)
#define YK__STBDS_HASH_EMPTY 0
#define YK__STBDS_HASH_DELETED 1
static size_t yk__stbds_hash_seed = 0x31415926;
void yk__stbds_rand_seed(size_t seed) { yk__stbds_hash_seed = seed; }
#define yk__stbds_load_32_or_64(var, temp, v32, v64_hi, v64_lo)                \
  temp = v64_lo ^ v32, temp <<= 16, temp <<= 16, temp >>= 16,                  \
  temp >>= 16,                              /* discard if 32-bit */            \
      var = v64_hi, var <<= 16, var <<= 16, /* discard if 32-bit */            \
      var ^= temp ^ v32
#define YK__STBDS_SIZE_T_BITS ((sizeof(size_t)) * 8)
static size_t yk__stbds_probe_position(size_t hash, size_t slot_count,
                                       size_t slot_log2) {
  size_t pos;
  YK__STBDS_NOTUSED(slot_log2);
  pos = hash & (slot_count - 1);
#ifdef YK__STBDS_INTERNAL_BUCKET_START
  pos &= ~YK__STBDS_BUCKET_MASK;
#endif
  return pos;
}
static size_t yk__stbds_log2(size_t slot_count) {
  size_t n = 0;
  while (slot_count > 1) {
    slot_count >>= 1;
    ++n;
  }
  return n;
}
static yk__stbds_hash_index *
yk__stbds_make_hash_index(size_t slot_count, yk__stbds_hash_index *ot) {
  yk__stbds_hash_index *t;
  t = (yk__stbds_hash_index *) YK__STBDS_REALLOC(
      NULL, 0,
      (slot_count >> YK__STBDS_BUCKET_SHIFT) * sizeof(yk__stbds_hash_bucket) +
          sizeof(yk__stbds_hash_index) + YK__STBDS_CACHE_LINE_SIZE - 1);
  t->storage = (yk__stbds_hash_bucket *) YK__STBDS_ALIGN_FWD(
      (size_t) (t + 1), YK__STBDS_CACHE_LINE_SIZE);
  t->slot_count = slot_count;
  t->slot_count_log2 = yk__stbds_log2(slot_count);
  t->tombstone_count = 0;
  t->used_count = 0;
#if 0  // A1
  t->used_count_threshold        = slot_count*12/16; // if 12/16th of table is occupied, grow
  t->tombstone_count_threshold   = slot_count* 2/16; // if tombstones are 2/16th of table, rebuild
  t->used_count_shrink_threshold = slot_count* 4/16; // if table is only 4/16th full, shrink
#elif 1// A2
  //t->used_count_threshold        = slot_count*12/16; // if 12/16th of table is occupied, grow
  //t->tombstone_count_threshold   = slot_count* 3/16; // if tombstones are 3/16th of table, rebuild
  //t->used_count_shrink_threshold = slot_count* 4/16; // if table is only 4/16th full, shrink
  // compute without overflowing
  t->used_count_threshold = slot_count - (slot_count >> 2);
  t->tombstone_count_threshold = (slot_count >> 3) + (slot_count >> 4);
  t->used_count_shrink_threshold = slot_count >> 2;
#elif 0// B1
  t->used_count_threshold =
      slot_count * 13 / 16;// if 13/16th of table is occupied, grow
  t->tombstone_count_threshold =
      slot_count * 2 / 16;// if tombstones are 2/16th of table, rebuild
  t->used_count_shrink_threshold =
      slot_count * 5 / 16;// if table is only 5/16th full, shrink
#else  // C1
  t->used_count_threshold =
      slot_count * 14 / 16;// if 14/16th of table is occupied, grow
  t->tombstone_count_threshold =
      slot_count * 2 / 16;// if tombstones are 2/16th of table, rebuild
  t->used_count_shrink_threshold =
      slot_count * 6 / 16;// if table is only 6/16th full, shrink
#endif
  // Following statistics were measured on a Core i7-6700 @ 4.00Ghz, compiled with clang 7.0.1 -O2
  // Note that the larger tables have high variance as they were run fewer times
  //     A1            A2          B1           C1
  //    0.10ms :     0.10ms :     0.10ms :     0.11ms :      2,000 inserts creating 2K table
  //    0.96ms :     0.95ms :     0.97ms :     1.04ms :     20,000 inserts creating 20K table
  //   14.48ms :    14.46ms :    10.63ms :    11.00ms :    200,000 inserts creating 200K table
  //  195.74ms :   196.35ms :   203.69ms :   214.92ms :  2,000,000 inserts creating 2M table
  // 2193.88ms :  2209.22ms :  2285.54ms :  2437.17ms : 20,000,000 inserts creating 20M table
  //   65.27ms :    53.77ms :    65.33ms :    65.47ms : 500,000 inserts & deletes in 2K table
  //   72.78ms :    62.45ms :    71.95ms :    72.85ms : 500,000 inserts & deletes in 20K table
  //   89.47ms :    77.72ms :    96.49ms :    96.75ms : 500,000 inserts & deletes in 200K table
  //   97.58ms :    98.14ms :    97.18ms :    97.53ms : 500,000 inserts & deletes in 2M table
  //  118.61ms :   119.62ms :   120.16ms :   118.86ms : 500,000 inserts & deletes in 20M table
  //  192.11ms :   194.39ms :   196.38ms :   195.73ms : 500,000 inserts & deletes in 200M table
  if (slot_count <= YK__STBDS_BUCKET_LENGTH) t->used_count_shrink_threshold = 0;
  // to avoid infinite loop, we need to guarantee that at least one slot is empty and will terminate probes
  YK__STBDS_ASSERT(t->used_count_threshold + t->tombstone_count_threshold <
                   t->slot_count);
  YK__STBDS_STATS(++yk__stbds_hash_alloc);
  if (ot) {
    t->string = ot->string;
    // reuse old seed so we can reuse old hashes so below "copy out old data" doesn't do any hashing
    t->seed = ot->seed;
  } else {
    size_t a, b, temp;
    memset(&t->string, 0, sizeof(t->string));
    t->seed = yk__stbds_hash_seed;
    // LCG
    // in 32-bit, a =          2147001325   b =  715136305
    // in 64-bit, a = 2862933555777941757   b = 3037000493
    yk__stbds_load_32_or_64(a, temp, 2147001325, 0x27bb2ee6, 0x87b0b0fd);
    yk__stbds_load_32_or_64(b, temp, 715136305, 0, 0xb504f32d);
    yk__stbds_hash_seed = yk__stbds_hash_seed * a + b;
  }
  {
    size_t i, j;
    for (i = 0; i < slot_count >> YK__STBDS_BUCKET_SHIFT; ++i) {
      yk__stbds_hash_bucket *b = &t->storage[i];
      for (j = 0; j < YK__STBDS_BUCKET_LENGTH; ++j)
        b->hash[j] = YK__STBDS_HASH_EMPTY;
      for (j = 0; j < YK__STBDS_BUCKET_LENGTH; ++j)
        b->index[j] = YK__STBDS_INDEX_EMPTY;
    }
  }
  // copy out the old data, if any
  if (ot) {
    size_t i, j;
    t->used_count = ot->used_count;
    for (i = 0; i < ot->slot_count >> YK__STBDS_BUCKET_SHIFT; ++i) {
      yk__stbds_hash_bucket *ob = &ot->storage[i];
      for (j = 0; j < YK__STBDS_BUCKET_LENGTH; ++j) {
        if (YK__STBDS_INDEX_IN_USE(ob->index[j])) {
          size_t hash = ob->hash[j];
          size_t pos =
              yk__stbds_probe_position(hash, t->slot_count, t->slot_count_log2);
          size_t step = YK__STBDS_BUCKET_LENGTH;
          YK__STBDS_STATS(++yk__stbds_rehash_items);
          for (;;) {
            size_t limit, z;
            yk__stbds_hash_bucket *bucket;
            bucket = &t->storage[pos >> YK__STBDS_BUCKET_SHIFT];
            YK__STBDS_STATS(++yk__stbds_rehash_probes);
            for (z = pos & YK__STBDS_BUCKET_MASK; z < YK__STBDS_BUCKET_LENGTH;
                 ++z) {
              if (bucket->hash[z] == 0) {
                bucket->hash[z] = hash;
                bucket->index[z] = ob->index[j];
                goto done;
              }
            }
            limit = pos & YK__STBDS_BUCKET_MASK;
            for (z = 0; z < limit; ++z) {
              if (bucket->hash[z] == 0) {
                bucket->hash[z] = hash;
                bucket->index[z] = ob->index[j];
                goto done;
              }
            }
            pos += step;// quadratic probing
            step += YK__STBDS_BUCKET_LENGTH;
            pos &= (t->slot_count - 1);
          }
        }
      done:;
      }
    }
  }
  return t;
}
#define YK__STBDS_ROTATE_LEFT(val, n)                                          \
  (((val) << (n)) | ((val) >> (YK__STBDS_SIZE_T_BITS - (n))))
#define YK__STBDS_ROTATE_RIGHT(val, n)                                         \
  (((val) >> (n)) | ((val) << (YK__STBDS_SIZE_T_BITS - (n))))
size_t yk__stbds_hash_string(yk__sds str, size_t seed) {
  size_t hash = seed;
  size_t string_length = yk__sdslen(str);
  if (string_length > 0) {
    for (size_t i = 0; i < string_length; i++) {
      hash = YK__STBDS_ROTATE_LEFT(hash, 9) + (unsigned char) *str++;
    }
  }
  // Thomas Wang 64-to-32 bit mix function, hopefully also works in 32 bits
  hash ^= seed;
  hash = (~hash) + (hash << 18);
  hash ^= hash ^ YK__STBDS_ROTATE_RIGHT(hash, 31);
  hash = hash * 21;
  hash ^= hash ^ YK__STBDS_ROTATE_RIGHT(hash, 11);
  hash += (hash << 6);
  hash ^= YK__STBDS_ROTATE_RIGHT(hash, 22);
  return hash + seed;
}
#ifdef YK__STBDS_SIPHASH_2_4
#define YK__STBDS_SIPHASH_C_ROUNDS 2
#define YK__STBDS_SIPHASH_D_ROUNDS 4
typedef int YK__STBDS_SIPHASH_2_4_can_only_be_used_in_64_bit_builds
    [sizeof(size_t) == 8 ? 1 : -1];
#endif
#ifndef YK__STBDS_SIPHASH_C_ROUNDS
#define YK__STBDS_SIPHASH_C_ROUNDS 1
#endif
#ifndef YK__STBDS_SIPHASH_D_ROUNDS
#define YK__STBDS_SIPHASH_D_ROUNDS 1
#endif
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(                                                               \
    disable : 4127)// conditional expression is constant, for do..while(0) and sizeof()==
#endif
static size_t yk__stbds_siphash_bytes(void *p, size_t len, size_t seed) {
  unsigned char *d = (unsigned char *) p;
  size_t i, j;
  size_t v0, v1, v2, v3, data;
  // hash that works on 32- or 64-bit registers without knowing which we have
  // (computes different results on 32-bit and 64-bit platform)
  // derived from siphash, but on 32-bit platforms very different as it uses 4 32-bit state not 4 64-bit
  v0 = ((((size_t) 0x736f6d65 << 16) << 16) + 0x70736575) ^ seed;
  v1 = ((((size_t) 0x646f7261 << 16) << 16) + 0x6e646f6d) ^ ~seed;
  v2 = ((((size_t) 0x6c796765 << 16) << 16) + 0x6e657261) ^ seed;
  v3 = ((((size_t) 0x74656462 << 16) << 16) + 0x79746573) ^ ~seed;
#ifdef YK__STBDS_TEST_SIPHASH_2_4
  // hardcoded with key material in the siphash test vectors
  v0 ^= 0x0706050403020100ull ^ seed;
  v1 ^= 0x0f0e0d0c0b0a0908ull ^ ~seed;
  v2 ^= 0x0706050403020100ull ^ seed;
  v3 ^= 0x0f0e0d0c0b0a0908ull ^ ~seed;
#endif
#define YK__STBDS_SIPROUND()                                                   \
  do {                                                                         \
    v0 += v1;                                                                  \
    v1 = YK__STBDS_ROTATE_LEFT(v1, 13);                                        \
    v1 ^= v0;                                                                  \
    v0 = YK__STBDS_ROTATE_LEFT(v0, YK__STBDS_SIZE_T_BITS / 2);                 \
    v2 += v3;                                                                  \
    v3 = YK__STBDS_ROTATE_LEFT(v3, 16);                                        \
    v3 ^= v2;                                                                  \
    v2 += v1;                                                                  \
    v1 = YK__STBDS_ROTATE_LEFT(v1, 17);                                        \
    v1 ^= v2;                                                                  \
    v2 = YK__STBDS_ROTATE_LEFT(v2, YK__STBDS_SIZE_T_BITS / 2);                 \
    v0 += v3;                                                                  \
    v3 = YK__STBDS_ROTATE_LEFT(v3, 21);                                        \
    v3 ^= v0;                                                                  \
  } while (0)
  for (i = 0; i + sizeof(size_t) <= len;
       i += sizeof(size_t), d += sizeof(size_t)) {
    data = d[0] | (d[1] << 8) | (d[2] << 16) | (d[3] << 24);
    data |= (size_t) (d[4] | (d[5] << 8) | (d[6] << 16) | (d[7] << 24))
            << 16 << 16;// discarded if size_t == 4
    v3 ^= data;
    for (j = 0; j < YK__STBDS_SIPHASH_C_ROUNDS; ++j) YK__STBDS_SIPROUND();
    v0 ^= data;
  }
  data = len << (YK__STBDS_SIZE_T_BITS - 8);
  switch (len - i) {
    case 7:
      data |= ((size_t) d[6] << 24) << 24;// fall through
    case 6:
      data |= ((size_t) d[5] << 20) << 20;// fall through
    case 5:
      data |= ((size_t) d[4] << 16) << 16;// fall through
    case 4:
      data |= (d[3] << 24);// fall through
    case 3:
      data |= (d[2] << 16);// fall through
    case 2:
      data |= (d[1] << 8);// fall through
    case 1:
      data |= d[0];// fall through
    case 0:
      break;
  }
  v3 ^= data;
  for (j = 0; j < YK__STBDS_SIPHASH_C_ROUNDS; ++j) YK__STBDS_SIPROUND();
  v0 ^= data;
  v2 ^= 0xff;
  for (j = 0; j < YK__STBDS_SIPHASH_D_ROUNDS; ++j) YK__STBDS_SIPROUND();
#ifdef YK__STBDS_SIPHASH_2_4
  return v0 ^ v1 ^ v2 ^ v3;
#else
  return v1 ^ v2 ^
         v3;// slightly stronger since v0^v3 in above cancels out final round operation? I tweeted at the authors of SipHash about this but they didn't reply
#endif
}
size_t yk__stbds_hash_bytes(void *p, size_t len, size_t seed) {
#ifdef YK__STBDS_SIPHASH_2_4
  return yk__stbds_siphash_bytes(p, len, seed);
#else
  unsigned char *d = (unsigned char *) p;
  if (len == 4) {
    unsigned int hash = d[0] | (d[1] << 8) | (d[2] << 16) | (d[3] << 24);
#if 0
    // HASH32-A  Bob Jenkin's hash function w/o large constants
    hash ^= seed;
    hash -= (hash<<6);
    hash ^= (hash>>17);
    hash -= (hash<<9);
    hash ^= seed;
    hash ^= (hash<<4);
    hash -= (hash<<3);
    hash ^= (hash<<10);
    hash ^= (hash>>15);
#elif 1
    // HASH32-BB  Bob Jenkin's presumably-accidental version of Thomas Wang hash with rotates turned into shifts.
    // Note that converting these back to rotates makes it run a lot slower, presumably due to collisions, so I'm
    // not really sure what's going on.
    hash ^= seed;
    hash = (hash ^ 61) ^ (hash >> 16);
    hash = hash + (hash << 3);
    hash = hash ^ (hash >> 4);
    hash = hash * 0x27d4eb2d;
    hash ^= seed;
    hash = hash ^ (hash >> 15);
#else// HASH32-C   -  Murmur3
    hash ^= seed;
    hash *= 0xcc9e2d51;
    hash = (hash << 17) | (hash >> 15);
    hash *= 0x1b873593;
    hash ^= seed;
    hash = (hash << 19) | (hash >> 13);
    hash = hash * 5 + 0xe6546b64;
    hash ^= hash >> 16;
    hash *= 0x85ebca6b;
    hash ^= seed;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;
#endif
    // Following statistics were measured on a Core i7-6700 @ 4.00Ghz, compiled with clang 7.0.1 -O2
    // Note that the larger tables have high variance as they were run fewer times
    //  HASH32-A   //  HASH32-BB  //  HASH32-C
    //    0.10ms   //    0.10ms   //    0.10ms :      2,000 inserts creating 2K table
    //    0.96ms   //    0.95ms   //    0.99ms :     20,000 inserts creating 20K table
    //   14.69ms   //   14.43ms   //   14.97ms :    200,000 inserts creating 200K table
    //  199.99ms   //  195.36ms   //  202.05ms :  2,000,000 inserts creating 2M table
    // 2234.84ms   // 2187.74ms   // 2240.38ms : 20,000,000 inserts creating 20M table
    //   55.68ms   //   53.72ms   //   57.31ms : 500,000 inserts & deletes in 2K table
    //   63.43ms   //   61.99ms   //   65.73ms : 500,000 inserts & deletes in 20K table
    //   80.04ms   //   77.96ms   //   81.83ms : 500,000 inserts & deletes in 200K table
    //  100.42ms   //   97.40ms   //  102.39ms : 500,000 inserts & deletes in 2M table
    //  119.71ms   //  120.59ms   //  121.63ms : 500,000 inserts & deletes in 20M table
    //  185.28ms   //  195.15ms   //  187.74ms : 500,000 inserts & deletes in 200M table
    //   15.58ms   //   14.79ms   //   15.52ms : 200,000 inserts creating 200K table with varying key spacing
    return (((size_t) hash << 16 << 16) | hash) ^ seed;
  } else if (len == 8 && sizeof(size_t) == 8) {
    size_t hash = d[0] | (d[1] << 8) | (d[2] << 16) | (d[3] << 24);
    hash |= (size_t) (d[4] | (d[5] << 8) | (d[6] << 16) | (d[7] << 24))
            << 16 << 16;// avoid warning if size_t == 4
    hash ^= seed;
    hash = (~hash) + (hash << 21);
    hash ^= YK__STBDS_ROTATE_RIGHT(hash, 24);
    hash *= 265;
    hash ^= YK__STBDS_ROTATE_RIGHT(hash, 14);
    hash ^= seed;
    hash *= 21;
    hash ^= YK__STBDS_ROTATE_RIGHT(hash, 28);
    hash += (hash << 31);
    hash = (~hash) + (hash << 18);
    return hash;
  } else {
    return yk__stbds_siphash_bytes(p, len, seed);
  }
#endif
}
#ifdef _MSC_VER
#pragma warning(pop)
#endif
static int yk__stbds_is_key_equal(void *a, size_t elemsize, void *key,
                                  size_t keysize, size_t keyoffset, int mode,
                                  size_t i) {
  if (mode >= YK__STBDS_HM_STRING)
    return 0 == yk__sdscmp((char *) key,
                           *(char **) ((char *) a + elemsize * i + keyoffset));
  else
    return 0 == memcmp(key, (char *) a + elemsize * i + keyoffset, keysize);
}
#define YK__STBDS_HASH_TO_ARR(x, elemsize) ((char *) (x) - (elemsize))
#define YK__STBDS_ARR_TO_HASH(x, elemsize) ((char *) (x) + (elemsize))
#define yk__stbds_hash_table(a)                                                \
  ((yk__stbds_hash_index *) yk__stbds_header(a)->hash_table)
void yk__stbds_hmfree_func(void *a, size_t elemsize) {
  if (a == NULL) return;
  if (yk__stbds_hash_table(a) != NULL) {
    if (yk__stbds_hash_table(a)->string.mode == YK__STBDS_SH_STRDUP) {
      size_t i;
      // skip 0th element, which is default
      for (i = 1; i < yk__stbds_header(a)->length; ++i)
        yk__sdsfree(*(char **) ((char *) a + elemsize * i));
    }
    yk__stbds_strreset(&yk__stbds_hash_table(a)->string);
  }
  YK__STBDS_FREE(NULL, yk__stbds_header(a)->hash_table);
  YK__STBDS_FREE(NULL, yk__stbds_header(a));
}
static ptrdiff_t yk__stbds_hm_find_slot(void *a, size_t elemsize, void *key,
                                        size_t keysize, size_t keyoffset,
                                        int mode) {
  void *raw_a = YK__STBDS_HASH_TO_ARR(a, elemsize);
  yk__stbds_hash_index *table = yk__stbds_hash_table(raw_a);
  size_t hash = mode >= YK__STBDS_HM_STRING
                    ? yk__stbds_hash_string((char *) key, table->seed)
                    : yk__stbds_hash_bytes(key, keysize, table->seed);
  size_t step = YK__STBDS_BUCKET_LENGTH;
  size_t limit, i;
  size_t pos;
  yk__stbds_hash_bucket *bucket;
  if (hash < 2)
    hash +=
        2;// stored hash values are forbidden from being 0, so we can detect empty slots
  pos =
      yk__stbds_probe_position(hash, table->slot_count, table->slot_count_log2);
  for (;;) {
    YK__STBDS_STATS(++yk__stbds_hash_probes);
    bucket = &table->storage[pos >> YK__STBDS_BUCKET_SHIFT];
    // start searching from pos to end of bucket, this should help performance on small hash tables that fit in cache
    for (i = pos & YK__STBDS_BUCKET_MASK; i < YK__STBDS_BUCKET_LENGTH; ++i) {
      if (bucket->hash[i] == hash) {
        if (yk__stbds_is_key_equal(a, elemsize, key, keysize, keyoffset, mode,
                                   bucket->index[i])) {
          return (pos & ~YK__STBDS_BUCKET_MASK) + i;
        }
      } else if (bucket->hash[i] == YK__STBDS_HASH_EMPTY) {
        return -1;
      }
    }
    // search from beginning of bucket to pos
    limit = pos & YK__STBDS_BUCKET_MASK;
    for (i = 0; i < limit; ++i) {
      if (bucket->hash[i] == hash) {
        if (yk__stbds_is_key_equal(a, elemsize, key, keysize, keyoffset, mode,
                                   bucket->index[i])) {
          return (pos & ~YK__STBDS_BUCKET_MASK) + i;
        }
      } else if (bucket->hash[i] == YK__STBDS_HASH_EMPTY) {
        return -1;
      }
    }
    // quadratic probing
    pos += step;
    step += YK__STBDS_BUCKET_LENGTH;
    pos &= (table->slot_count - 1);
  }
  /* NOTREACHED */
}
void *yk__stbds_hmget_key_ts(void *a, size_t elemsize, void *key,
                             size_t keysize, ptrdiff_t *temp, int mode) {
  size_t keyoffset = 0;
  if (a == NULL) {
    // make it non-empty so we can return a temp
    a = yk__stbds_arrgrowf(0, elemsize, 0, 1);
    yk__stbds_header(a)->length += 1;
    memset(a, 0, elemsize);
    *temp = YK__STBDS_INDEX_EMPTY;
    // adjust a to point after the default element
    return YK__STBDS_ARR_TO_HASH(a, elemsize);
  } else {
    yk__stbds_hash_index *table;
    void *raw_a = YK__STBDS_HASH_TO_ARR(a, elemsize);
    // adjust a to point to the default element
    table = (yk__stbds_hash_index *) yk__stbds_header(raw_a)->hash_table;
    if (table == 0) {
      *temp = -1;
    } else {
      ptrdiff_t slot =
          yk__stbds_hm_find_slot(a, elemsize, key, keysize, keyoffset, mode);
      if (slot < 0) {
        *temp = YK__STBDS_INDEX_EMPTY;
      } else {
        yk__stbds_hash_bucket *b =
            &table->storage[slot >> YK__STBDS_BUCKET_SHIFT];
        *temp = b->index[slot & YK__STBDS_BUCKET_MASK];
      }
    }
    return a;
  }
}
void *yk__stbds_hmget_key(void *a, size_t elemsize, void *key, size_t keysize,
                          int mode) {
  ptrdiff_t temp;
  void *p = yk__stbds_hmget_key_ts(a, elemsize, key, keysize, &temp, mode);
  yk__stbds_temp(YK__STBDS_HASH_TO_ARR(p, elemsize)) = temp;
  return p;
}
void *yk__stbds_hmput_default(void *a, size_t elemsize) {
  // three cases:
  //   a is NULL <- allocate
  //   a has a hash table but no entries, because of shmode <- grow
  //   a has entries <- do nothing
  if (a == NULL ||
      yk__stbds_header(YK__STBDS_HASH_TO_ARR(a, elemsize))->length == 0) {
    a = yk__stbds_arrgrowf(a ? YK__STBDS_HASH_TO_ARR(a, elemsize) : NULL,
                           elemsize, 0, 1);
    yk__stbds_header(a)->length += 1;
    memset(a, 0, elemsize);
    a = YK__STBDS_ARR_TO_HASH(a, elemsize);
  }
  return a;
}
static char *yk__stbds_strdup(char *str);
void *yk__stbds_hmput_key(void *a, size_t elemsize, void *key, size_t keysize,
                          int mode) {
  size_t keyoffset = 0;
  void *raw_a;
  yk__stbds_hash_index *table;
  if (a == NULL) {
    a = yk__stbds_arrgrowf(0, elemsize, 0, 1);
    memset(a, 0, elemsize);
    yk__stbds_header(a)->length += 1;
    // adjust a to point AFTER the default element
    a = YK__STBDS_ARR_TO_HASH(a, elemsize);
  }
  // adjust a to point to the default element
  raw_a = a;
  a = YK__STBDS_HASH_TO_ARR(a, elemsize);
  table = (yk__stbds_hash_index *) yk__stbds_header(a)->hash_table;
  if (table == NULL || table->used_count >= table->used_count_threshold) {
    yk__stbds_hash_index *nt;
    size_t slot_count;
    slot_count =
        (table == NULL) ? YK__STBDS_BUCKET_LENGTH : table->slot_count * 2;
    nt = yk__stbds_make_hash_index(slot_count, table);
    if (table) YK__STBDS_FREE(NULL, table);
    else
      nt->string.mode = mode >= YK__STBDS_HM_STRING ? YK__STBDS_SH_DEFAULT : 0;
    yk__stbds_header(a)->hash_table = table = nt;
    YK__STBDS_STATS(++yk__stbds_hash_grow);
  }
  // we iterate hash table explicitly because we want to track if we saw a tombstone
  {
    size_t hash = mode >= YK__STBDS_HM_STRING
                      ? yk__stbds_hash_string((char *) key, table->seed)
                      : yk__stbds_hash_bytes(key, keysize, table->seed);
    size_t step = YK__STBDS_BUCKET_LENGTH;
    size_t pos;
    ptrdiff_t tombstone = -1;
    yk__stbds_hash_bucket *bucket;
    // stored hash values are forbidden from being 0, so we can detect empty slots to early out quickly
    if (hash < 2) hash += 2;
    pos = yk__stbds_probe_position(hash, table->slot_count,
                                   table->slot_count_log2);
    for (;;) {
      size_t limit, i;
      YK__STBDS_STATS(++yk__stbds_hash_probes);
      bucket = &table->storage[pos >> YK__STBDS_BUCKET_SHIFT];
      // start searching from pos to end of bucket
      for (i = pos & YK__STBDS_BUCKET_MASK; i < YK__STBDS_BUCKET_LENGTH; ++i) {
        if (bucket->hash[i] == hash) {
          if (yk__stbds_is_key_equal(raw_a, elemsize, key, keysize, keyoffset,
                                     mode, bucket->index[i])) {
            yk__stbds_temp(a) = bucket->index[i];
            if (mode >= YK__STBDS_HM_STRING)
              yk__stbds_temp_key(a) =
                  *(char **) ((char *) raw_a + elemsize * bucket->index[i] +
                              keyoffset);
            return YK__STBDS_ARR_TO_HASH(a, elemsize);
          }
        } else if (bucket->hash[i] == 0) {
          pos = (pos & ~YK__STBDS_BUCKET_MASK) + i;
          goto found_empty_slot;
        } else if (tombstone < 0) {
          if (bucket->index[i] == YK__STBDS_INDEX_DELETED)
            tombstone = (ptrdiff_t) ((pos & ~YK__STBDS_BUCKET_MASK) + i);
        }
      }
      // search from beginning of bucket to pos
      limit = pos & YK__STBDS_BUCKET_MASK;
      for (i = 0; i < limit; ++i) {
        if (bucket->hash[i] == hash) {
          if (yk__stbds_is_key_equal(raw_a, elemsize, key, keysize, keyoffset,
                                     mode, bucket->index[i])) {
            yk__stbds_temp(a) = bucket->index[i];
            return YK__STBDS_ARR_TO_HASH(a, elemsize);
          }
        } else if (bucket->hash[i] == 0) {
          pos = (pos & ~YK__STBDS_BUCKET_MASK) + i;
          goto found_empty_slot;
        } else if (tombstone < 0) {
          if (bucket->index[i] == YK__STBDS_INDEX_DELETED)
            tombstone = (ptrdiff_t) ((pos & ~YK__STBDS_BUCKET_MASK) + i);
        }
      }
      // quadratic probing
      pos += step;
      step += YK__STBDS_BUCKET_LENGTH;
      pos &= (table->slot_count - 1);
    }
  found_empty_slot:
    if (tombstone >= 0) {
      pos = tombstone;
      --table->tombstone_count;
    }
    ++table->used_count;
    {
      ptrdiff_t i = (ptrdiff_t) yk__stbds_arrlen(a);
      // we want to do yk__stbds_arraddn(1), but we can't use the macros since we don't have something of the right type
      if ((size_t) i + 1 > yk__stbds_arrcap(a))
        *(void **) &a = yk__stbds_arrgrowf(a, elemsize, 1, 0);
      raw_a = YK__STBDS_ARR_TO_HASH(a, elemsize);
      YK__STBDS_ASSERT((size_t) i + 1 <= yk__stbds_arrcap(a));
      yk__stbds_header(a)->length = i + 1;
      bucket = &table->storage[pos >> YK__STBDS_BUCKET_SHIFT];
      bucket->hash[pos & YK__STBDS_BUCKET_MASK] = hash;
      bucket->index[pos & YK__STBDS_BUCKET_MASK] = i - 1;
      yk__stbds_temp(a) = i - 1;
      switch (table->string.mode) {
        case YK__STBDS_SH_STRDUP:
          yk__stbds_temp_key(a) = *(char **) ((char *) a + elemsize * i) =
              yk__stbds_strdup((char *) key);
          break;
        case YK__STBDS_SH_ARENA:
          yk__stbds_temp_key(a) = *(char **) ((char *) a + elemsize * i) =
              yk__stbds_stralloc(&table->string, (char *) key);
          break;
        case YK__STBDS_SH_DEFAULT:
          yk__stbds_temp_key(a) = *(char **) ((char *) a + elemsize * i) =
              (char *) key;
          break;
        default:
          memcpy((char *) a + elemsize * i, key, keysize);
          break;
      }
    }
    return YK__STBDS_ARR_TO_HASH(a, elemsize);
  }
}
void *yk__stbds_shmode_func(size_t elemsize, int mode) {
  void *a = yk__stbds_arrgrowf(0, elemsize, 0, 1);
  yk__stbds_hash_index *h;
  memset(a, 0, elemsize);
  yk__stbds_header(a)->length = 1;
  yk__stbds_header(a)->hash_table = h =
      (yk__stbds_hash_index *) yk__stbds_make_hash_index(
          YK__STBDS_BUCKET_LENGTH, NULL);
  h->string.mode = (unsigned char) mode;
  return YK__STBDS_ARR_TO_HASH(a, elemsize);
}
void *yk__stbds_hmdel_key(void *a, size_t elemsize, void *key, size_t keysize,
                          size_t keyoffset, int mode) {
  if (a == NULL) {
    return 0;
  } else {
    yk__stbds_hash_index *table;
    void *raw_a = YK__STBDS_HASH_TO_ARR(a, elemsize);
    table = (yk__stbds_hash_index *) yk__stbds_header(raw_a)->hash_table;
    yk__stbds_temp(raw_a) = 0;
    if (table == 0) {
      return a;
    } else {
      ptrdiff_t slot;
      slot = yk__stbds_hm_find_slot(a, elemsize, key, keysize, keyoffset, mode);
      if (slot < 0) return a;
      else {
        yk__stbds_hash_bucket *b =
            &table->storage[slot >> YK__STBDS_BUCKET_SHIFT];
        int i = slot & YK__STBDS_BUCKET_MASK;
        ptrdiff_t old_index = b->index[i];
        ptrdiff_t final_index =
            (ptrdiff_t) yk__stbds_arrlen(raw_a) - 1 -
            1;// minus one for the raw_a vs a, and minus one for 'last'
        YK__STBDS_ASSERT(slot < (ptrdiff_t) table->slot_count);
        --table->used_count;
        ++table->tombstone_count;
        yk__stbds_temp(raw_a) = 1;
        YK__STBDS_ASSERT(table->used_count >= 0);
        //YK__STBDS_ASSERT(table->tombstone_count < table->slot_count/4);
        b->hash[i] = YK__STBDS_HASH_DELETED;
        b->index[i] = YK__STBDS_INDEX_DELETED;
        if (mode == YK__STBDS_HM_STRING &&
            table->string.mode == YK__STBDS_SH_STRDUP)
          yk__sdsfree(*(char **) ((char *) a + elemsize * old_index));
        // if indices are the same, memcpy is a no-op, but back-pointer-fixup will fail, so skip
        if (old_index != final_index) {
          // swap delete
          memmove((char *) a + elemsize * old_index,
                  (char *) a + elemsize * final_index, elemsize);
          // now find the slot for the last element
          if (mode == YK__STBDS_HM_STRING)
            slot = yk__stbds_hm_find_slot(
                a, elemsize,
                *(char **) ((char *) a + elemsize * old_index + keyoffset),
                keysize, keyoffset, mode);
          else
            slot = yk__stbds_hm_find_slot(
                a, elemsize, (char *) a + elemsize * old_index + keyoffset,
                keysize, keyoffset, mode);
          YK__STBDS_ASSERT(slot >= 0);
          b = &table->storage[slot >> YK__STBDS_BUCKET_SHIFT];
          i = slot & YK__STBDS_BUCKET_MASK;
          YK__STBDS_ASSERT(b->index[i] == final_index);
          b->index[i] = old_index;
        }
        yk__stbds_header(raw_a)->length -= 1;
        if (table->used_count < table->used_count_shrink_threshold &&
            table->slot_count > YK__STBDS_BUCKET_LENGTH) {
          yk__stbds_header(raw_a)->hash_table =
              yk__stbds_make_hash_index(table->slot_count >> 1, table);
          YK__STBDS_FREE(NULL, table);
          YK__STBDS_STATS(++yk__stbds_hash_shrink);
        } else if (table->tombstone_count > table->tombstone_count_threshold) {
          yk__stbds_header(raw_a)->hash_table =
              yk__stbds_make_hash_index(table->slot_count, table);
          YK__STBDS_FREE(NULL, table);
          YK__STBDS_STATS(++yk__stbds_hash_rebuild);
        }
        return a;
      }
    }
  }
  /* NOTREACHED */
}
static yk__sds yk__stbds_strdup(yk__sds str) { return yk__sdsdup(str); }
#ifndef YK__STBDS_STRING_ARENA_BLOCKSIZE_MIN
#define YK__STBDS_STRING_ARENA_BLOCKSIZE_MIN 512u
#endif
#ifndef YK__STBDS_STRING_ARENA_BLOCKSIZE_MAX
#define YK__STBDS_STRING_ARENA_BLOCKSIZE_MAX (1u << 20)
#endif
char *yk__stbds_stralloc(yk__stbds_string_arena *a, char *str) {
  char *p;
  size_t len = strlen(str) + 1;
  if (len > a->remaining) {
    // compute the next blocksize
    size_t blocksize = a->block;
    // size is 512, 512, 1024, 1024, 2048, 2048, 4096, 4096, etc., so that
    // there are log(SIZE) allocations to free when we destroy the table
    blocksize = (size_t) (YK__STBDS_STRING_ARENA_BLOCKSIZE_MIN)
                << (blocksize >> 1);
    // if size is under 1M, advance to next blocktype
    if (blocksize < (size_t) (YK__STBDS_STRING_ARENA_BLOCKSIZE_MAX)) ++a->block;
    if (len > blocksize) {
      // if string is larger than blocksize, then just allocate the full size.
      // note that we still advance string_block so block size will continue
      // increasing, so e.g. if somebody only calls this with 1000-long strings,
      // eventually the arena will start doubling and handling those as well
      yk__stbds_string_block *sb = (yk__stbds_string_block *) YK__STBDS_REALLOC(
          NULL, 0, sizeof(*sb) - 8 + len);
      memmove(sb->storage, str, len);
      if (a->storage) {
        // insert it after the first element, so that we don't waste the space there
        sb->next = a->storage->next;
        a->storage->next = sb;
      } else {
        sb->next = 0;
        a->storage = sb;
        a->remaining = 0;// this is redundant, but good for clarity
      }
      return sb->storage;
    } else {
      yk__stbds_string_block *sb = (yk__stbds_string_block *) YK__STBDS_REALLOC(
          NULL, 0, sizeof(*sb) - 8 + blocksize);
      sb->next = a->storage;
      a->storage = sb;
      a->remaining = blocksize;
    }
  }
  YK__STBDS_ASSERT(len <= a->remaining);
  p = a->storage->storage + a->remaining - len;
  a->remaining -= len;
  memmove(p, str, len);
  return p;
}
void yk__stbds_strreset(yk__stbds_string_arena *a) {
  yk__stbds_string_block *x, *y;
  x = a->storage;
  while (x) {
    y = x->next;
    YK__STBDS_FREE(NULL, x);
    x = y;
  }
  memset(a, 0, sizeof(*a));
}
#endif
//////////////////////////////////////////////////////////////////////////////
//
//   UNIT TESTS
//
#ifdef YK__STBDS_UNIT_TESTS
#include <stdio.h>
#ifdef YK__STBDS_ASSERT_WAS_UNDEFINED
#undef YK__STBDS_ASSERT
#endif
#ifndef YK__STBDS_ASSERT
#define YK__STBDS_ASSERT assert
#include <assert.h>
#endif
typedef struct {
  int key, b, c, d;
} yk__stbds_struct;
typedef struct {
  int key[2], b, c, d;
} yk__stbds_struct2;
static char buffer[256];
char *strkey(int n) {
#if defined(_WIN32) && defined(__STDC_WANT_SECURE_LIB__)
  sprintf_s(buffer, sizeof(buffer), "test_%d", n);
#else
  sprintf(buffer, "test_%d", n);
#endif
  return buffer;
}
void yk__stbds_unit_tests(void) {
#if defined(_MSC_VER) && _MSC_VER <= 1200 && defined(__cplusplus)
  // VC6 C++ doesn't like the template<> trick on unnamed structures, so do nothing!
  YK__STBDS_ASSERT(0);
#else
  const int testsize = 100000;
  const int testsize2 = testsize / 20;
  int *yk__arr = NULL;
  struct {
    int key;
    int value;
  } *intmap = NULL;
  struct {
    char *key;
    int value;
  } *strmap = NULL, s;
  struct {
    yk__stbds_struct key;
    int value;
  } *map = NULL;
  yk__stbds_struct *map2 = NULL;
  yk__stbds_struct2 *map3 = NULL;
  yk__stbds_string_arena sa = {0};
  int key3[2] = {1, 2};
  ptrdiff_t temp;
  int i, j;
  YK__STBDS_ASSERT(yk__arrlen(yk__arr) == 0);
  for (i = 0; i < 20000; i += 50) {
    for (j = 0; j < i; ++j) yk__arrpush(yk__arr, j);
    yk__arrfree(yk__arr);
  }
  for (i = 0; i < 4; ++i) {
    yk__arrpush(yk__arr, 1);
    yk__arrpush(yk__arr, 2);
    yk__arrpush(yk__arr, 3);
    yk__arrpush(yk__arr, 4);
    yk__arrdel(yk__arr, i);
    yk__arrfree(yk__arr);
    yk__arrpush(yk__arr, 1);
    yk__arrpush(yk__arr, 2);
    yk__arrpush(yk__arr, 3);
    yk__arrpush(yk__arr, 4);
    yk__arrdelswap(yk__arr, i);
    yk__arrfree(yk__arr);
  }
  for (i = 0; i < 5; ++i) {
    yk__arrpush(yk__arr, 1);
    yk__arrpush(yk__arr, 2);
    yk__arrpush(yk__arr, 3);
    yk__arrpush(yk__arr, 4);
    yk__stbds_arrins(yk__arr, i, 5);
    YK__STBDS_ASSERT(yk__arr[i] == 5);
    if (i < 4) YK__STBDS_ASSERT(yk__arr[4] == 4);
    yk__arrfree(yk__arr);
  }
  i = 1;
  YK__STBDS_ASSERT(yk__hmgeti(intmap, i) == -1);
  yk__hmdefault(intmap, -2);
  YK__STBDS_ASSERT(yk__hmgeti(intmap, i) == -1);
  YK__STBDS_ASSERT(yk__hmget(intmap, i) == -2);
  for (i = 0; i < testsize; i += 2) yk__hmput(intmap, i, i * 5);
  for (i = 0; i < testsize; i += 1) {
    if (i & 1) YK__STBDS_ASSERT(yk__hmget(intmap, i) == -2);
    else
      YK__STBDS_ASSERT(yk__hmget(intmap, i) == i * 5);
    if (i & 1) YK__STBDS_ASSERT(yk__hmget_ts(intmap, i, temp) == -2);
    else
      YK__STBDS_ASSERT(yk__hmget_ts(intmap, i, temp) == i * 5);
  }
  for (i = 0; i < testsize; i += 2) yk__hmput(intmap, i, i * 3);
  for (i = 0; i < testsize; i += 1)
    if (i & 1) YK__STBDS_ASSERT(yk__hmget(intmap, i) == -2);
    else
      YK__STBDS_ASSERT(yk__hmget(intmap, i) == i * 3);
  for (i = 2; i < testsize; i += 4)
    yk__hmdel(intmap, i);// delete half the entries
  for (i = 0; i < testsize; i += 1)
    if (i & 3) YK__STBDS_ASSERT(yk__hmget(intmap, i) == -2);
    else
      YK__STBDS_ASSERT(yk__hmget(intmap, i) == i * 3);
  for (i = 0; i < testsize; i += 1)
    yk__hmdel(intmap, i);// delete the rest of the entries
  for (i = 0; i < testsize; i += 1)
    YK__STBDS_ASSERT(yk__hmget(intmap, i) == -2);
  yk__hmfree(intmap);
  for (i = 0; i < testsize; i += 2) yk__hmput(intmap, i, i * 3);
  yk__hmfree(intmap);
#if defined(__clang__) || defined(__GNUC__)
#ifndef __cplusplus
  intmap = NULL;
  yk__hmput(intmap, 15, 7);
  yk__hmput(intmap, 11, 3);
  yk__hmput(intmap, 9, 5);
  YK__STBDS_ASSERT(yk__hmget(intmap, 9) == 5);
  YK__STBDS_ASSERT(yk__hmget(intmap, 11) == 3);
  YK__STBDS_ASSERT(yk__hmget(intmap, 15) == 7);
#endif
#endif
  for (i = 0; i < testsize; ++i) stralloc(&sa, strkey(i));
  strreset(&sa);
  {
    s.key = "a", s.value = 1;
    yk__shputs(strmap, s);
    YK__STBDS_ASSERT(*strmap[0].key == 'a');
    YK__STBDS_ASSERT(strmap[0].key == s.key);
    YK__STBDS_ASSERT(strmap[0].value == s.value);
    yk__shfree(strmap);
  }
  {
    s.key = "a", s.value = 1;
    yk__sh_new_strdup(strmap);
    yk__shputs(strmap, s);
    YK__STBDS_ASSERT(*strmap[0].key == 'a');
    YK__STBDS_ASSERT(strmap[0].key != s.key);
    YK__STBDS_ASSERT(strmap[0].value == s.value);
    yk__shfree(strmap);
  }
  {
    s.key = "a", s.value = 1;
    yk__sh_new_arena(strmap);
    yk__shputs(strmap, s);
    YK__STBDS_ASSERT(*strmap[0].key == 'a');
    YK__STBDS_ASSERT(strmap[0].key != s.key);
    YK__STBDS_ASSERT(strmap[0].value == s.value);
    yk__shfree(strmap);
  }
  for (j = 0; j < 2; ++j) {
    YK__STBDS_ASSERT(yk__shgeti(strmap, "foo") == -1);
    if (j == 0) yk__sh_new_strdup(strmap);
    else
      yk__sh_new_arena(strmap);
    YK__STBDS_ASSERT(yk__shgeti(strmap, "foo") == -1);
    yk__shdefault(strmap, -2);
    YK__STBDS_ASSERT(yk__shgeti(strmap, "foo") == -1);
    for (i = 0; i < testsize; i += 2) yk__shput(strmap, strkey(i), i * 3);
    for (i = 0; i < testsize; i += 1)
      if (i & 1) YK__STBDS_ASSERT(yk__shget(strmap, strkey(i)) == -2);
      else
        YK__STBDS_ASSERT(yk__shget(strmap, strkey(i)) == i * 3);
    for (i = 2; i < testsize; i += 4)
      yk__shdel(strmap, strkey(i));// delete half the entries
    for (i = 0; i < testsize; i += 1)
      if (i & 3) YK__STBDS_ASSERT(yk__shget(strmap, strkey(i)) == -2);
      else
        YK__STBDS_ASSERT(yk__shget(strmap, strkey(i)) == i * 3);
    for (i = 0; i < testsize; i += 1)
      yk__shdel(strmap, strkey(i));// delete the rest of the entries
    for (i = 0; i < testsize; i += 1)
      YK__STBDS_ASSERT(yk__shget(strmap, strkey(i)) == -2);
    yk__shfree(strmap);
  }
  {
    struct {
      char *key;
      char value;
    } *hash = NULL;
    char name[4] = "jen";
    yk__shput(hash, "bob", 'h');
    yk__shput(hash, "sally", 'e');
    yk__shput(hash, "fred", 'l');
    yk__shput(hash, "jen", 'x');
    yk__shput(hash, "doug", 'o');
    yk__shput(hash, name, 'l');
    yk__shfree(hash);
  }
  for (i = 0; i < testsize; i += 2) {
    yk__stbds_struct s = {i, i * 2, i * 3, i * 4};
    yk__hmput(map, s, i * 5);
  }
  for (i = 0; i < testsize; i += 1) {
    yk__stbds_struct s = {i, i * 2, i * 3, i * 4};
    yk__stbds_struct t = {i, i * 2, i * 3 + 1, i * 4};
    if (i & 1) YK__STBDS_ASSERT(yk__hmget(map, s) == 0);
    else
      YK__STBDS_ASSERT(yk__hmget(map, s) == i * 5);
    if (i & 1) YK__STBDS_ASSERT(yk__hmget_ts(map, s, temp) == 0);
    else
      YK__STBDS_ASSERT(yk__hmget_ts(map, s, temp) == i * 5);
    //YK__STBDS_ASSERT(yk__hmget(map, t.key) == 0);
  }
  for (i = 0; i < testsize; i += 2) {
    yk__stbds_struct s = {i, i * 2, i * 3, i * 4};
    yk__hmputs(map2, s);
  }
  yk__hmfree(map);
  for (i = 0; i < testsize; i += 1) {
    yk__stbds_struct s = {i, i * 2, i * 3, i * 4};
    yk__stbds_struct t = {i, i * 2, i * 3 + 1, i * 4};
    if (i & 1) YK__STBDS_ASSERT(yk__hmgets(map2, s.key).d == 0);
    else
      YK__STBDS_ASSERT(yk__hmgets(map2, s.key).d == i * 4);
    //YK__STBDS_ASSERT(yk__hmgetp(map2, t.key) == 0);
  }
  yk__hmfree(map2);
  for (i = 0; i < testsize; i += 2) {
    yk__stbds_struct2 s = {{i, i * 2}, i * 3, i * 4, i * 5};
    yk__hmputs(map3, s);
  }
  for (i = 0; i < testsize; i += 1) {
    yk__stbds_struct2 s = {{i, i * 2}, i * 3, i * 4, i * 5};
    yk__stbds_struct2 t = {{i, i * 2}, i * 3 + 1, i * 4, i * 5};
    if (i & 1) YK__STBDS_ASSERT(yk__hmgets(map3, s.key).d == 0);
    else
      YK__STBDS_ASSERT(yk__hmgets(map3, s.key).d == i * 5);
    //YK__STBDS_ASSERT(yk__hmgetp(map3, t.key) == 0);
  }
#endif
}
#endif
/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2019 Sean Barrett
Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
------------------------------------------------------------------------------
ALTERNATIVE B - Public Domain (www.unlicense.org)
This is free and unencumbered software released into the public domain.
Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
software, either in source code form or as a compiled binary, for any purpose,
commercial or non-commercial, and by any means.
In jurisdictions that recognize copyright laws, the author or authors of this
software dedicate any and all copyright interest in the software to the public
domain. We make this dedication for the benefit of the public at large and to
the detriment of our heirs and successors. We intend this dedication to be an
overt act of relinquishment in perpetuity of all present and future rights to
this software under copyright law.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
------------------------------------------------------------------------------
*/
/**
 * Bunch of utilities
 * Copyright (C) 2021-2022 Bhathiya Perera (JaDogg)
 */
#ifndef YK__BHALIB_SINGLE_HEADER
#define YK__BHALIB_SINGLE_HEADER
#include <stdio.h>
#include <stdlib.h>
// Default to malloc if not defined
#ifndef yk__bhalib_malloc
#define yk__bhalib_malloc malloc
#endif
// Default to free if not defined
#ifndef yk__bhalib_free
#define yk__bhalib_free free
#endif
/**
 * Could not open the file
 */
#define YK__BHALIB_ERROR_NO_OPEN 1
/**
 * Could not allocate memory to read the file
 */
#define YK__BHALIB_ERROR_NO_MEM 2
/**
 * Could not read the full file
 */
#define YK__BHALIB_ERROR_NO_READ 3
/**
 * Read a file
 * @param path filepath
 * @param length pointer to receive read length
 * @param error pointer to receive error message
 *  (if there's no error this is set to zero)
 * @return buffer. (You need to call free on this)
 */
char *yk__bhalib_read_file(const char *path, size_t *length, int *error);
#ifdef YK__BHALIB_IMPLEMENTATION
char *yk__bhalib_read_file(const char *path, size_t *length, int *error) {
  // both length and error must be present
  if (length == NULL || error == NULL) { return NULL; }
  *error = 0;
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    *error = YK__BHALIB_ERROR_NO_OPEN;
    return NULL;
  }
  fseek(file, 0L, SEEK_END);
  *length = ftell(file);
  rewind(file);
  char *buffer = (char *) yk__bhalib_malloc(*length + 1);
  if (buffer == NULL) {
    fclose(file);
    *error = YK__BHALIB_ERROR_NO_MEM;
    return NULL;
  }
  size_t bytes_read = fread(buffer, sizeof(char), *length, file);
  if (bytes_read < *length) {
    fclose(file);
    yk__bhalib_free(buffer);
    *error = YK__BHALIB_ERROR_NO_READ;
    return NULL;
  }
  buffer[bytes_read] = '\0';
  fclose(file);
  return buffer;
}
#endif
#endif
/**
QuickSort implementation as a single file header by Bhathiya Perera

MIT License
Copyright (c) 2022 Bhathiya Perera

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

// ======================================================================= //
//                             References                                  //
// ======================================================================= //

## Reference - quick sort for integer
https://stackoverflow.com/a/55011578

Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
Copyright (C) 2019 chqrlie
Based on public-domain C implementation by Darel Rex Finley.

## Reference - quick sort generic
https://github.com/ismdeep/sort-algos-c/blob/master/include/sort-algos/quick-sort.c
https://github.com/ismdeep/sort-algos-c/blob/master/include/sort-base.h

MIT License
Copyright (c) 2020 ismdeep


## Reference - memswap
https://gist.github.com/JadenGeller/3ab6fbc3f75690103ea6
Unknown license, asked in above link
*/
#ifndef YK__SORT
#define YK__SORT
#include <stddef.h>
/**
 * Comparison function, returns 0 if equal > 0 for larger and < 0 for smaller
 */
typedef int (*yk__compare_function)(const void *, const void *);
/**
 * Perform a quick sort for given array
 * @param arr array
 * @param item_size single item size
 * @param elements number of elements
 * @param cmp_func compare function
 * @return 0 if successful, -1 if partial
 */
int yk__quicksort(void *arr, size_t item_size, size_t elements,
                  yk__compare_function cmp_func);
/**
 * Perform a quick sort for given array (no malloc)
 * @param arr array
 * @param item_size single item size
 * @param elements number of elements
 * @param cmp_func compare function
 * @param single_elem_buffer buffer for a single temporary element (item_size can be held)
 * @return 0 if successful, -1 if partial
 */
int yk__quicksort_ex(void *arr, size_t item_size, size_t elements,
                     yk__compare_function cmp_func, void *single_elem_buffer);
#ifdef YK__SORT_IMPLEMENTATION
#include <stdlib.h>// malloc
#include <string.h>// memcpy
#define YK__SORT_MAX_LEVELS 48
/**
 * Swap memory between a and b of given item_size
 * @param a pointer to position a
 * @param b pointer to position b
 * @param item_size single element size
 */
void yk__memswap(void *a, void *b, size_t item_size) {
  char *a_swap = (char *) a;
  char *b_swap = (char *) b;
  char *a_end = a_swap + item_size;
  while (a_swap < a_end) {
    char temp = *a_swap;
    *a_swap = *b_swap;
    *b_swap = temp;
    a_swap++;
    b_swap++;
  }
}
/**
 * Swap two elements of an array
 * @param arr array
 * @param pos1 position 1
 * @param pos2 position 2
 * @param item_size size of a single element
 */
#define yk__generic_swap(arr, pos1, pos2, item_size)                           \
  do {                                                                         \
    yk__memswap(((char *) arr) + ((pos1) * (item_size)),                       \
                ((char *) arr) + ((pos2) * (item_size)), item_size);           \
  } while (0)
/**
 * Get an element of an array
 * @param arr array
 * @param pos position in array
 * @param item_size size of a single element
 * @return
 */
#define yk__generic_get(arr, pos, item_size)                                   \
  ((void *) (((char *) arr) + ((pos) * (item_size))))
int yk__quicksort_ex(void *arr, size_t item_size, size_t elements,
                     yk__compare_function cmp_func, void *single_elem_buffer) {
  size_t beg[YK__SORT_MAX_LEVELS], end[YK__SORT_MAX_LEVELS], L, R;
  int i = 0;
  beg[0] = 0;
  end[0] = elements;
  // NOTE: You can probably change this to a some MAX_SIZE char[]
  void *piv = single_elem_buffer;
  while (i >= 0) {
    L = beg[i];
    R = end[i];
    if (R - L > 1) {
      size_t M = L + ((R - L) >> 1);
      // T piv = arr[M];
      memcpy(piv, yk__generic_get(arr, M, item_size), item_size);
      // arr[M] = arr[L];
      memcpy(yk__generic_get(arr, M, item_size),
             yk__generic_get(arr, L, item_size), item_size);
      if (i == YK__SORT_MAX_LEVELS - 1) { return -1; }
      R--;
      while (L < R) {
        // while (arr[R] >= piv && L < R)
        while (cmp_func(yk__generic_get(arr, R, item_size), piv) >= 0 &&
               L < R) {
          R--;
        }
        if (L < R) { yk__generic_swap(arr, L++, R, item_size); }
        // while (arr[L] <= piv && L < R)
        while (cmp_func(yk__generic_get(arr, L, item_size), piv) <= 0 &&
               L < R) {
          L++;
        }
        if (L < R) { yk__generic_swap(arr, R--, L, item_size); }
      }
      // arr[L] = piv;
      memcpy(yk__generic_get(arr, L, item_size), piv, item_size);
      M = L + 1;
      // while (L > beg[i] && arr[L - 1] == piv)
      while (L > beg[i] &&
             cmp_func(yk__generic_get(arr, L - 1, item_size), piv) == 0) {
        L--;
      }
      // while (M < end[i] && arr[M] == piv)
      while (M < end[i] &&
             cmp_func(yk__generic_get(arr, M, item_size), piv) == 0) {
        M++;
      }
      if (L - beg[i] > end[i] - M) {
        beg[i + 1] = M;
        end[i + 1] = end[i];
        end[i++] = L;
      } else {
        beg[i + 1] = beg[i];
        end[i + 1] = L;
        beg[i++] = M;
      }
    } else {
      i--;
    }
  }
  return 0;
}
int yk__quicksort(void *arr, size_t item_size, size_t elements,
                  yk__compare_function cmp_func) {
  char *single_elem_buffer = malloc(item_size + 1);
  if (NULL == single_elem_buffer) return -1;
  single_elem_buffer[item_size] = 0;
  int return_value =
      yk__quicksort_ex(arr, item_size, elements, cmp_func, single_elem_buffer);
  free(single_elem_buffer);
  return return_value;
}
#endif
#endif
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
// TODO move below
#ifndef YK__IO_BSTR
#define YK__IO_BSTR
#include "_include_bstr.h"
#ifdef YK__IO_BSTR_IMPLEMENTATION
#include "_include_bstr.c"
#endif
#endif
#ifndef YAKSHA_SKIP_2S_COMPLIMENT_CHECK
#if (-1 & 3) != 3
#error "Yaksha expects 2's compliment"
#endif
#endif
