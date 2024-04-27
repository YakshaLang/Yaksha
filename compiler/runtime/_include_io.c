#if defined(_WIN32) || defined(_WIN64)
#define YK_IO_WIN 1
#include <share.h>
#else
#define YK_IO_UNIX 1
#endif

#if defined(YK_IO_WIN) && defined(_MSC_VER)
#define YK_IO_MSVC 1
#endif

FILE *yk__io_fopen(struct yk__bstr fpath, struct yk__bstr mode) {
  FILE *file;
#if defined(YK_IO_WIN)
  // ---------- BEGIN WINDOWS -----------------
  wchar_t *wpath = yk__utf8_to_utf16_null_terminated(yk__bstr_get_reference(fpath));
  wchar_t *wmode = yk__utf8_to_utf16_null_terminated(yk__bstr_get_reference(mode));
  if (wpath == NULL || wmode == NULL) {
    if (wpath != NULL) { free(wpath); }
    if (wmode != NULL) { free(wmode); }
    return NULL;
  }
#if defined(YK_IO_MSVC)// WINDOWS + MSVC
  errno_t openerr = _wfopen_s(&file, wpath, wmode);
  if (0 != openerr) {
    if (NULL != file) { fclose(file); }
    free(wpath);
    free(wmode);
    return NULL;
  }
#else// WINDOWS + GCC/MingW
  file = _wfopen(wpath, wmode);
  if (file == NULL) {
    free(wpath);
    free(wmode);
    return NULL;
  }
#endif
  // ---------- END WINDOWS -----------------
#else
  // ---------- BEGIN UNIX -----------------
  file = fopen(yk__bstr_get_reference(fpath), yk__bstr_get_reference(mode));
  if (file == NULL) {
    return NULL;
  }
  // ---------- END UNIX -----------------
#endif
// ----- RETURNING FILE* ------
#if defined(YK_IO_WIN)
  free(wpath);
  free(wmode);
#endif
  return file;
}
bool yk__io_fclose(FILE *stream) {
  return stream != NULL && fclose(stream) == 0;
}
bool yk__io_fflush(FILE *stream) {
  return stream != NULL && fflush(stream) == 0;
}
size_t yk__io_fread(void *buffer, size_t size, size_t count, FILE *stream) {
  if (stream == NULL || buffer == NULL) { return 0; }
  return fread(buffer, size, count, stream);
}
size_t yk__io_fwrite(void *buffer, size_t size, size_t count, FILE *stream) {
  if (stream == NULL || buffer == NULL) { return 0; }
  return fwrite(buffer, size, count, stream);
}
int64_t yk__io_ftell(FILE *stream) {
  if (stream == NULL) { return -1; }
#if defined(YK_IO_WIN)
  return _ftelli64(stream);
#else
  return ftell(stream);
#endif
}
bool yk__io_fseek(FILE *stream, int64_t offset, int origin) {
  return stream != NULL && fseek(stream, (long)offset, origin) == 0;
}
bool yk__io_fgetpos(FILE *stream, fpos_t *pos) {
  return stream != NULL && pos != NULL && fgetpos(stream, pos) == 0;
}
bool yk__io_fsetpos(FILE *stream, fpos_t *pos) {
  return stream != NULL && pos != NULL && fsetpos(stream, pos) == 0;
}
bool yk__io_feof(FILE *stream) { return stream != NULL && feof(stream) != 0; }
bool yk__io_ferror(FILE *stream) {
  return stream != NULL && ferror(stream) != 0;
}
void yk__io_clearerr(FILE *stream) {
  if (stream == NULL) { return; }
  clearerr(stream);
}
void yk__io_rewind(FILE *stream) {
  if (stream == NULL) { return; }
  rewind(stream);
}
int yk__io_open(struct yk__bstr fpath, int mode) {
  int fd = -1;
#if defined(YK_IO_WIN)
  // ---------- BEGIN WINDOWS -----------------
  wchar_t *wpath = yk__utf8_to_utf16_null_terminated(yk__bstr_get_reference(fpath));
  if (wpath == NULL) {
    return fd;
  }
#if defined(YK_IO_MSVC)// WINDOWS + MSVC
  errno_t openerr =
      _wsopen_s(&fd, wpath, mode, _SH_DENYRD, _S_IREAD | _S_IWRITE);
  if (0 != openerr) {
    if (-1 != fd) { _close(fd); }
    free(wpath);
    fd = -1;
    return fd;
  }
#else// WINDOWS + GCC/MingW
  fd = _wsopen(wpath, mode, _SH_DENYRD);
#endif
  // ---------- END WINDOWS -----------------
#else
  // ---------- BEGIN UNIX -----------------
  fd = open(yk__bstr_get_reference(fpath), mode);
  // ---------- END UNIX -----------------
#endif
// ----- RETURNING FILE* ------
#if defined(YK_IO_WIN)
  free(wpath);
#endif
  return fd;
}
bool yk__io_close(int fd) {
#if defined(YK_IO_WIN)
  return fd != -1 && _close(fd) == 0;
#else
  return fd != -1 && close(fd) == 0;
#endif
}
