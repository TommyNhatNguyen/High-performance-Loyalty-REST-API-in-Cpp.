#pragma once

#include <string>

struct DatabaseConfig {
  const std::string filename =
      std::string(BUILD_PATH) + std::string("/loyalty.db");
};