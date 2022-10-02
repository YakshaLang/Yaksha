// ----- This file is to be directly included at the top of raylib game ---
void *yk__raylib_game_state = (void *) 0;
#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#define yk__rungameloop(nn__fps, nn__state)                                    \
  do {                                                                         \
    yk__raylib_game_state = nn__state;                                         \
    emscripten_set_main_loop(yk__game_loop_wrapper, nn__fps, 1);               \
  } while (0)
void yy__game_step(void *);
void yk__game_loop_wrapper() { yy__game_step(yk__raylib_game_state); }
#else
#define yk__rungameloop(nn__fps, nn__state)                                    \
  do {                                                                         \
    yk__raylib_game_state = nn__state;                                         \
    SetTargetFPS(nn__fps);                                                     \
    while (!WindowShouldClose()) { yy__game_step(yk__raylib_game_state); }     \
  } while (0)
#endif
// Copyright (C) 2022 Bhathiya Perera
