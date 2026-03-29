#include "utils/utils.hpp"

int Utils::findColumnIndex(const SQLite::Statement &statement,
                           const std::string &columnName) noexcept {
  for (auto i = 0; i < statement.getColumnCount(); i++) {
    if (columnName.compare(statement.getColumnName(i)) == 0) {
      return i;
    }
  }
  return -1;
}