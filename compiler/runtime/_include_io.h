FILE *yk__io_fopen(struct yk__bstr path, struct yk__bstr mode);
bool yk__io_fclose(FILE *stream);
bool yk__io_fflush(FILE *stream);
size_t yk__io_fread(void *buffer, size_t size, size_t count, FILE *stream);
size_t yk__io_fwrite(void *buffer, size_t size, size_t count, FILE *stream);
int64_t yk__io_ftell(FILE *stream);
bool yk__io_fseek(FILE *stream, int64_t offset, int origin);
bool yk__io_fgetpos(FILE *stream, fpos_t *pos);
bool yk__io_fsetpos(FILE *stream, fpos_t *pos);
bool yk__io_feof(FILE *stream);
bool yk__io_ferror(FILE *stream);
void yk__io_clearerr(FILE *stream);
void yk__io_rewind(FILE *stream);
int yk__io_open(struct yk__bstr path, int mode);
bool yk__io_close(int fd);
#if defined(_WIN32) || defined(_WIN64)
#define YK__IO_O_RDONLY _O_RDONLY
#define YK__IO_O_WRONLY _O_WRONLY
#define YK__IO_O_RDWR _O_RDWR
#define YK__IO_O_CREAT _O_CREAT
#define YK__IO_O_EXCL _O_EXCL
#define YK__IO_O_APPEND _O_APPEND
#define YK__IO_O_ASYNC _O_ASYNC
#define YK__IO_O_CLOEXEC _O_CLOEXEC
#define YK__IO_O_NONBLOCK _O_NONBLOCK
#define YK__IO_O_TMPFILE _O_TMPFILE
#else
#define YK__IO_O_RDONLY O_RDONLY
#define YK__IO_O_WRONLY O_WRONLY
#define YK__IO_O_RDWR O_RDWR
#define YK__IO_O_CREAT O_CREAT
#define YK__IO_O_EXCL O_EXCL
#define YK__IO_O_APPEND O_APPEND
#define YK__IO_O_ASYNC O_ASYNC
#define YK__IO_O_CLOEXEC O_CLOEXEC
#define YK__IO_O_NONBLOCK O_NONBLOCK
#define YK__IO_O_TMPFILE O_TMPFILE
#endif
