#include "repositories/SqliteRepo.hpp"
#include "SQLiteCpp/Transaction.h"
#include "fstream"

std::unique_ptr<SqliteRepo> SqliteRepo::instance = nullptr;

SqliteRepo::SqliteRepo(const DatabaseConfig &config) : config(config) {
  db = std::make_unique<SQLite::Database>(
      config.filename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
};

void SqliteRepo::init(const DatabaseConfig &config) {
  if (!instance) {
    instance = std::unique_ptr<SqliteRepo>(new SqliteRepo(config));
  }
};

SqliteRepo &SqliteRepo::getInstance() {
  if (!instance) {
    throw std::runtime_error("SqliteRepo not initialized!");
  } else {
    return *instance;
  }
}

SQLite::Database &SqliteRepo::getDb() {
  if (!db) {
    throw std::runtime_error("Database not initialized!");
  }
  return *db;
}

void SqliteRepo::migrate(const std::string &filename = "init.sql") {
  try {

    auto current_path = std::filesystem::current_path() / filename;
    std::ifstream inputFile(current_path.string());
    std::string sql;
    if (inputFile.is_open()) {
      sql = std::string((std::istreambuf_iterator<char>(inputFile)),
                        std::istreambuf_iterator<char>());
    } else {
      throw std::runtime_error("Failed to open migration file: " +
                               current_path.string());
    }
    SQLite::Transaction transaction(getDb());
    getDb().exec(sql);
    transaction.commit();
  } catch (const std::exception &e) {
    throw std::runtime_error("Failed to migrate database: " +
                             std::string(e.what()));
  }
}