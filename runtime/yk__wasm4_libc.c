/*
 * Minimal C library for use with w4
 * Copyright (C) 2022 Bhathiya Perera
 */
// =======================================
// Based on https://wasm4.org/docs/reference/memory
// Removing 8KB bytes of memory for storage
#define STMMR_POOL_SIZE (50784)
#define STMMR_CUSTOM_POOL
#define STMMR_IMPL
#include "stmmr.h"
#include "wasm4.h"
void *calloc(size_t number, size_t size) {
  void *data = stmmr_calloc(number, size);
#ifdef W4_TRACE_MEM_ALLOCATIONS
  tracef("calloc -> %d\n", data);
#endif
  return data;
}
void *realloc(void *ap, size_t size) {
  void *data = stmmr_realloc(ap, size);
#ifdef W4_TRACE_MEM_ALLOCATIONS
  tracef("realloc -> %d\n", data);
#endif
  return data;
}
void free(void *ap) { stmmr_free(ap); }
void *malloc(size_t size) {
  void *data = stmmr_alloc(size);
#ifdef W4_TRACE_MEM_ALLOCATIONS
  tracef("malloc -> %d\n", data);
#endif
  return data;
}
// Random numbers
// ----
// reference: https://stackoverflow.com/a/4768189
static unsigned long int next = 1;
int rand(void)// RAND_MAX assumed to be 32767
{
  next = next * 1103515245 + 12345;
  return (unsigned int) (next / 65536) % 32768;
}
void srand(unsigned int seed) { next = seed; }
// ---------
static uint8_t *memory_pool = NULL;
// Based on https://wasm4.org/docs/reference/memory
void wasm4_mem_init() { stmmr_init((void*)(0x19a0 + 1024 * 8 /* BASE + 8KB */)); }
void wasm4_mem_close() {}
// ----------------
// state
static void *w4_game_state = NULL;
void *yk__get_game_state() { return w4_game_state; }
void yk__set_game_state(void *data) { w4_game_state = data; }