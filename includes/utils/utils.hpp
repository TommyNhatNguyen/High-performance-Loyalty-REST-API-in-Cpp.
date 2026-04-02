#pragma once
#include <SQLiteCpp/Statement.h>
#include <nlohmann/json.hpp>
#include <string>

class Utils {
public:
  static int findColumnIndex(const SQLite::Statement &statement,
                             const std::string &columnName) noexcept;
  static std::string getCurrentDate();

  template <typename T>
  static std::optional<T> safeParseOptional(const nlohmann::json &j,
                                     const std::string &key) {
    if (!j.contains(key) || j.at(key).is_null()) {
      return std::nullopt;
    }
    return j.at(key).get<T>();
  }
};