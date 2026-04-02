#include "utils/utils.hpp"
#include <string>

int Utils::findColumnIndex(const SQLite::Statement &statement,
                           const std::string &columnName) noexcept {
  for (auto i = 0; i < statement.getColumnCount(); i++) {
    if (columnName.compare(statement.getColumnName(i)) == 0) {
      return i;
    }
  }
  return -1;
}

std::string Utils::getCurrentDate() {
  std::time_t now = std::time(nullptr);
  char buf[sizeof "2011-10-08T07:07:09Z"];
  std::strftime(buf, sizeof buf, "%FT%TZ", std::gmtime(&now));
  return buf;
}
