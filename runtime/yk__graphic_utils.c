#include "yk__graphic_utils.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
// Reference -- https://mrl.cs.nyu.edu/~perlin/noise/
const int p[512] = {
    151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233, 7,
    225, 140, 36,  103, 30,  69,  142, 8,   99,  37,  240, 21,  10,  23,  190,
    6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203, 117,
    35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125, 136,
    171, 168, 68,  175, 74,  165, 71,  134, 139, 48,  27,  166, 77,  146, 158,
    231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,  41,  55,  46,
    245, 40,  244, 102, 143, 54,  65,  25,  63,  161, 1,   216, 80,  73,  209,
    76,  132, 187, 208, 89,  18,  169, 200, 196, 135, 130, 116, 188, 159, 86,
    164, 100, 109, 198, 173, 186, 3,   64,  52,  217, 226, 250, 124, 123, 5,
    202, 38,  147, 118, 126, 255, 82,  85,  212, 207, 206, 59,  227, 47,  16,
    58,  17,  182, 189, 28,  42,  223, 183, 170, 213, 119, 248, 152, 2,   44,
    154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,   129, 22,  39,  253,
    19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246, 97,
    228, 251, 34,  242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,  51,
    145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157, 184,
    84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205, 93,
    222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,  156,
    180, 151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233,
    7,   225, 140, 36,  103, 30,  69,  142, 8,   99,  37,  240, 21,  10,  23,
    190, 6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203,
    117, 35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125,
    136, 171, 168, 68,  175, 74,  165, 71,  134, 139, 48,  27,  166, 77,  146,
    158, 231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,  41,  55,
    46,  245, 40,  244, 102, 143, 54,  65,  25,  63,  161, 1,   216, 80,  73,
    209, 76,  132, 187, 208, 89,  18,  169, 200, 196, 135, 130, 116, 188, 159,
    86,  164, 100, 109, 198, 173, 186, 3,   64,  52,  217, 226, 250, 124, 123,
    5,   202, 38,  147, 118, 126, 255, 82,  85,  212, 207, 206, 59,  227, 47,
    16,  58,  17,  182, 189, 28,  42,  223, 183, 170, 213, 119, 248, 152, 2,
    44,  154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,   129, 22,  39,
    253, 19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246,
    97,  228, 251, 34,  242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,
    51,  145, 235, 249, 14,  239, 107, 49,  192, 214, 31,  181, 199, 106, 157,
    184, 84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205,
    93,  222, 114, 67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,
    156, 180};
double yk__fade(double t) { return t * t * t * (t * (t * 6 - 15) + 10); }
double yk__lerp(double t, double a, double b) { return a + t * (b - a); }
double yk__grad(int hash, double x, double y, double z) {
  int h = hash & 15;       // CONVERT LO 4 BITS OF HASH CODE
  double u = h < 8 ? x : y,// INTO 12 GRADIENT DIRECTIONS.
      v = h < 4                ? y
          : h == 12 || h == 14 ? x
                               : z;
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
double yk__perlin3d(double x, double y, double z) {
  int X = (int) floor(x) & 255,// FIND UNIT CUBE THAT
      Y = (int) floor(y) & 255,// CONTAINS POINT.
      Z = (int) floor(z) & 255;
  x -= floor(x);// FIND RELATIVE X,Y,Z
  y -= floor(y);// OF POINT IN CUBE.
  z -= floor(z);
  double u = yk__fade(x),// COMPUTE FADE CURVES
      v = yk__fade(y),   // FOR EACH OF X,Y,Z.
      w = yk__fade(z);
  int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z,    // HASH COORDINATES OF
      B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;// THE 8 CUBE CORNERS,
  return yk__lerp(
      w,
      yk__lerp(v,
               yk__lerp(u, yk__grad(p[AA], x, y, z),       // AND ADD
                        yk__grad(p[BA], x - 1, y, z)),     // BLENDED
               yk__lerp(u, yk__grad(p[AB], x, y - 1, z),   // RESULTS
                        yk__grad(p[BB], x - 1, y - 1, z))),// FROM  8
      yk__lerp(v,
               yk__lerp(u, yk__grad(p[AA + 1], x, y, z - 1),  // CORNERS
                        yk__grad(p[BA + 1], x - 1, y, z - 1)),// OF CUBE
               yk__lerp(u, yk__grad(p[AB + 1], x, y - 1, z - 1),
                        yk__grad(p[BB + 1], x - 1, y - 1, z - 1))));
}
/* Function to linearly interpolate between a0 and a1
 * Weight w should be in the range [0.0, 1.0]
 */
double yk__interpolate(double a0, double a1, double w) {
  /* // You may want clamping by inserting:
     * if (0.0 > w) return a0;
     * if (1.0 < w) return a1;
     */
  return (a1 - a0) * w + a0;
  /* // Use this cubic interpolation [[Smoothstep]] instead, for a smooth appearance:
     * return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
     *
     * // Use [[Smootherstep]] for an even smoother result with a second derivative equal to zero on boundaries:
     * return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
     */
}
typedef struct {
  double x, y;
} perlin_vector2;
/* Create pseudorandom direction vector
 */
perlin_vector2 yk__random_gradient(int ix, int iy) {
  // No precomputed gradients mean this works for any number of grid coordinates
  const unsigned w = 8 * sizeof(unsigned);
  const unsigned s = w / 2;// rotation width
  unsigned a = ix, b = iy;
  a *= 3284157443;
  b ^= a << s | a >> (w - s);
  b *= 1911520717;
  a ^= b << s | b >> (w - s);
  a *= 2048419325;
  double random = a * (3.14159265 / ~(~0u >> 1));// in [0, 2*Pi]
  perlin_vector2 v;
  v.x = sin(random);
  v.y = cos(random);
  return v;
}
// Computes the dot product of the distance and gradient vectors.
double yk__dot_grid_gradient(int ix, int iy, double x, double y) {
  // Get gradient from integer coordinates
  perlin_vector2 gradient = yk__random_gradient(ix, iy);
  // Compute the distance vector
  double dx = x - (double) ix;
  double dy = y - (double) iy;
  // Compute the dot-product
  return (dx * gradient.x + dy * gradient.y);
}
// Compute Perlin noise at coordinates x, y
double yk__perlin2d(double x, double y) {
  // Determine grid cell coordinates
  int x0 = (int) x;
  int x1 = x0 + 1;
  int y0 = (int) y;
  int y1 = y0 + 1;
  // Determine interpolation weights
  // Could also use higher order polynomial/s-curve here
  double sx = x - (double) x0;
  double sy = y - (double) y0;
  // Interpolate between grid point gradients
  double n0, n1, ix0, ix1, value;
  n0 = yk__dot_grid_gradient(x0, y0, x, y);
  n1 = yk__dot_grid_gradient(x1, y0, x, y);
  ix0 = yk__interpolate(n0, n1, sx);
  n0 = yk__dot_grid_gradient(x0, y1, x, y);
  n1 = yk__dot_grid_gradient(x1, y1, x, y);
  ix1 = yk__interpolate(n0, n1, sx);
  value = yk__interpolate(ix0, ix1, sy);
  return value;
}
double yk__perlin1d(double x) { return yk__perlin3d(x, 1.34345, 3.412); }
uint64_t yk__init_random() {
  uint64_t seed_value = time(NULL);
  srand((unsigned) seed_value);
  return seed_value;
}
// Reference - https://stackoverflow.com/a/33021408
#if defined(YK__WASM4)
uint64_t yk__random_u64_impl(void) {
  uint64_t r = 0;
  for (int i = 5; i > 0; i--) {
    r = r * (32767 + (uint64_t) 1) + rand();
  }
  return r;
}
#else
#define IMAX_BITS(m)                                                           \
  ((m) / ((m) % 255 + 1) / 255 % 255 * 8 + 7 - 86 / ((m) % 255 + 12))
#define RAND_MAX_WIDTH IMAX_BITS(RAND_MAX)
uint64_t yk__rand64_mersenne(void) {
  uint64_t r = 0;
  for (int i = 0; i < 64; i += RAND_MAX_WIDTH) {
    r <<= RAND_MAX_WIDTH;
    r ^= (unsigned) rand();
  }
  return r;
}
#if RAND_MAX / 256 >= 0xFFFFFFFFFFFFFF
#define LOOP_COUNT 1
#elif RAND_MAX / 256 >= 0xFFFFFF
#define LOOP_COUNT 2
#elif RAND_MAX / 256 >= 0x3FFFF
#define LOOP_COUNT 3
#elif RAND_MAX / 256 >= 0x1FF
#define LOOP_COUNT 4
#else
#define LOOP_COUNT 5
#endif
uint64_t yk__rand64(void) {
  uint64_t r = 0;
  for (int i = LOOP_COUNT; i > 0; i--) {
    r = r * (RAND_MAX + (uint64_t) 1) + rand();
  }
  return r;
}
#if ((RAND_MAX & (RAND_MAX + 1u)) == 0)
#define yk__random_u64_impl yk__rand64_mersenne
#else
#define yk__random_u64_impl yk__rand64
#endif
#endif
uint64_t yk__random_u64() {
  return yk__random_u64_impl();
}