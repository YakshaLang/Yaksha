// Reference -- https://mrl.cs.nyu.edu/~perlin/noise/
// Library created by Bhathiya Perera
// This is used for random.yaka and perlin.yaka
#include <stdint.h>
/**
 * Get perlin noise in 3 dimensions
 * @param x
 * @param y
 * @param z
 * @return
 */
double yk__perlin3d(double x, double y, double z);
/**
 * Get perlin noise in 2 dimensions
 * @param x
 * @param y
 * @return
 */
double yk__perlin2d(double x, double y);
/**
 * Get perlin noise in 1d (calls 3d with hardcoded y,z values)
 * @param x
 * @return
 */
double yk__perlin1d(double x);
/**
 * Initialize random number generation with time(NULL) and return as a uint64
 * @return
 */
uint64_t yk__init_random();
/**
 * Get a random -> unsigned 64bit number
 * @return
 */
uint64_t yk__random_u64();