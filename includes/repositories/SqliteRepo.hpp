#pragma once
#include "configs/db-config.hpp"
#include <SQLiteCpp/Database.h>
#include <memory>

class SqliteRepo {
public:
  SqliteRepo(const SqliteRepo &) = delete;
  SqliteRepo(SqliteRepo &&) = delete;
  SqliteRepo &operator=(const SqliteRepo &) = delete;
  SqliteRepo &operator=(SqliteRepo &&) = delete;
  ~SqliteRepo() = default;
  static void init(const DatabaseConfig &config);
  static SqliteRepo &getInstance();
  SQLite::Database &getDb();
  void migrate(const std::string &path);

private:
  SqliteRepo(const DatabaseConfig &config);

private:
  std::unique_ptr<SQLite::Database> db;
  DatabaseConfig config;
  static std::unique_ptr<SqliteRepo> instance;
};