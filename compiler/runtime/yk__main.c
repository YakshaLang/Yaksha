#define YK__SDS_IMPLEMENTATION
#define YK__BHALIB_IMPLEMENTATION
#define YK__STB_DS_IMPLEMENTATION
#define YK__SORT_IMPLEMENTATION
#define YK__IO_BSTR_IMPLEMENTATION
#include "yk__system.h"
#if defined(_WIN32) || defined(_WIN64)
#include <fcntl.h>
#include <io.h>
#include <windows.h>
#endif
////// Get Arguments implementation that we have in yk__system ///
static struct yk__arguments *yk__arguments_copy;
struct yk__arguments *yk__get_args() { return yk__arguments_copy; }
// ---------------- standard main ---------------------
#if !defined(YK__MINIMAL_MAIN) && !defined(YK__WASM4) && !defined(YK__CR_DLL)
int main(int argc, char *argv[]) {
#if defined(_WIN32) || defined(_WIN64)
  int result_mode;
  result_mode = _setmode(_fileno(stdout), _O_U16TEXT);
#if !defined(YK_IGNORE_WINDOWS_CONSOLE_SET_MODE_ERROR)
  // If we can't set the mode, return -1
  //   only a concern for a console application
  //   otherwise, we can ignore this error and let things continue as is
  if (result_mode == -1) { return -1; }
#endif
#if defined(YK__WINDOWS_HIDE_CONSOLE)
  ShowWindow(GetConsoleWindow(), SW_HIDE);
  FreeConsole();
#endif
#endif
  yk__arguments_copy = yk__copy_args(argc, argv);
  int result = yy__main();
  // Free sds strings created for arguments
  for (int j = 0; j < argc; j++) { yk__sdsfree(yk__arguments_copy->argv[j]); }
  yk__arrfree(yk__arguments_copy->argv);
  free(yk__arguments_copy);
  return result;
}
#endif
// ╦ ╦╔═╗╔═╗╔╦╗   ┌─┐┌─┐┬ ┬┬─┐
// ║║║╠═╣╚═╗║║║───├┤ │ ││ │├┬┘
// ╚╩╝╩ ╩╚═╝╩ ╩   └  └─┘└─┘┴└─
#if defined(YK__WASM4) && !defined(YK__MINIMAL_MAIN)
#include "yk__wasm4_libc.h"
void yy__game_step(void *);
void wasm4_mem_init();
void update() { yy__game_step(yk__get_game_state()); }
void start() {
  wasm4_mem_init();
  yk__arguments_copy = malloc(sizeof(struct yk__arguments));
  yk__arguments_copy->argv = NULL;
  yk__arguments_copy->argc = 0;
  yy__main();
  free(yk__arguments_copy);
}
#endif
// ╦ ╦┌─┐┌┬┐  ╦═╗┌─┐┬  ┌─┐┌─┐┌┬┐┬┌┐┌┌─┐
// ╠═╣│ │ │   ╠╦╝├┤ │  │ │├─┤ │││││││ ┬
// ╩ ╩└─┘ ┴   ╩╚═└─┘┴─┘└─┘┴ ┴─┴┘┴┘└┘└─┘
#if defined(YK__CR_DLL) && !defined(YK__MINIMAL_MAIN)
#ifdef YK__CR_DEBUG
#define CR_DEBUG
#endif
#include "cr.h"
#include "cr_userdata.h"
void yy__game_step(void *);
void yy__del_state(void *);
void *yk__get_game_state();
bool WindowShouldClose(void);
void yk__CloseWindow(void);
typedef struct Vector2 {
  float x;
  float y;
} Vector2;
Vector2 GetWindowPosition(void);
void SetWindowPosition(int, int);
#if defined(_WIN32) || defined(_WIN64)
#define print_message(x) wprintf(L##x)
#else
#define print_message(x) printf(x)
#endif
CR_EXPORT int cr_main(struct cr_plugin *ctx, enum cr_op operation) {
  assert(ctx);
  struct yk__user_data *ud = ctx->userdata;
  if (operation == CR_LOAD) {
    print_message("[CR_LOAD]\n");
    if (ud != NULL) {
      yy__main();
      /* So we can pass it to game step */
      ud->real_user_data = yk__get_game_state();
      ud->should_die = false;
      // If we are not running in first time, set the window position
      if (ud->first_time) {
        ud->first_time = false;
      } else if (ud->window_position_set) {
        SetWindowPosition(ud->x, ud->y);
      }
    }
    return 0;
  } else if (operation == CR_UNLOAD) {
    print_message("[CR_UNLOAD]\n");
    if (ud != NULL && ud->real_user_data != NULL) {
      yy__del_state(ud->real_user_data);
    }
    Vector2 pos = GetWindowPosition();
    ud->x = (int) pos.x;
    ud->y = (int) pos.y;
    ud->window_position_set = true;
    yk__CloseWindow();
    return 0;
  } else if (operation == CR_CLOSE) {
    print_message("[CR_CLOSE]\n");
    if (ud != NULL && ud->real_user_data != NULL) {
      yy__del_state(ud->real_user_data);
    }
    yk__CloseWindow();
    return 0;
  } else if (operation == CR_STEP) {
    void *game_data = NULL;
    if (ud != NULL) {
      game_data = ud->real_user_data;
      ud->should_die = WindowShouldClose();
    } else {
      print_message("[CR_STEP] Error userdata is null :(");
      return 1;
    }
    yy__game_step(game_data);
    return 0;
  }
  return 1;
}
#endif
