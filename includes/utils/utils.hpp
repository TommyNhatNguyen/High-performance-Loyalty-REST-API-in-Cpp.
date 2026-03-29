#pragma once
#include <SQLiteCpp/Statement.h>
#include <string>

class Utils {
public:
  static int findColumnIndex(const SQLite::Statement &statement,
                             const std::string &columnName) noexcept;
};