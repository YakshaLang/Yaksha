#ifndef CR_USERDATA_H
#define CR_USERDATA_H
#include <stdbool.h>
/**
 * User data struct
 */
struct yk__user_data {
  /**
   * Game state saved here to be passed to CR_STEP
   */
  void* real_user_data;
  /**
   * Are we running in very first time?
   */
  bool first_time;
  /**
   * Screen X location of window
   */
  int x;
  /**
   * Screen Y location of window
   */
  int y;
  /**
   * Should the reload host die?
   */
  bool should_die;
  /**
   * We saved window position to X and Y at least once
   */
  bool window_position_set;
};
#endif
