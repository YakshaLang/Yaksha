#include <chrono>
#include <filesystem>
#include <iostream>
#include <thread>
#ifndef PROGRAM_NAME
#define PROGRAM_NAME "ykreload"
#endif
#ifdef YK__CR_DEBUG
#define CR_DEBUG
#endif
#define CR_HOST CR_DISABLE
#include "../runtime/cr.h"
#include "../runtime/cr_userdata.h"
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Invalid usage. Use as: " << PROGRAM_NAME << " libgame.so"
              << std::endl;
    return -1;
  }
  std::filesystem::path plugin_file{argv[1]};
  auto abs_path = std::filesystem::absolute(plugin_file);
  if (!std::filesystem::exists(abs_path)) {
    std::cerr << "[YKRELOAD] File not found. File:" << abs_path.string()
              << std::endl;
    return -1;
  }
  auto plugin_str = abs_path.string();
  std::cout << "[YKRELOAD] Loading plugin:" << plugin_str << "\n";
  cr_plugin ctx{};
  yk__user_data my_userdata{(void *) 0, true, 0, 0,
                            false,      false};// NOLINT(modernize-use-nullptr)
  ctx.userdata = &my_userdata;
  bool success = cr_plugin_open(ctx, plugin_str.c_str());
  std::cout << "[YKRELOAD] Initial load completed \n";
  while (success) {
    cr_plugin_update(ctx);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    auto *data = static_cast<yk__user_data *>(ctx.userdata);
    if (data != nullptr && data->should_die) {
      std::cout << "[YKRELOAD] Should die received\n";
      break;
    }
  }
  cr_plugin_close(ctx);
  return 0;
}
