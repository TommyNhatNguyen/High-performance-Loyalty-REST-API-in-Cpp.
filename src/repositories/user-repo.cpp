#include "repositories/user-repo.hpp"
#include "constants/collections.hpp"
#include "fmt/format.h"
#include <SQLiteCpp/Transaction.h>
#include <optional>
#include <stdexcept>

UserRepo::UserRepo(SqliteRepo &db) : db(db) {};

std::optional<User> UserRepo::findById(const std::string &id) {
  nlohmann::json json;
  User user;
  // Prepare statement
  auto query =
      fmt::format("SELECT * FROM {} WHERE id = :id", COLLECTIONS::USERS);

  SQLite::Statement statement(db.getDb(), query);
  // Binds values
  statement.bind(":id", id);
  // Execute statement
  if (statement.executeStep()) {
    json["id"] = statement.getColumn("id").getString();
    json["username"] = statement.getColumn("username").getString();
    json["hash_password"] = statement.getColumn("hash_password").getString();
    json["is_active"] = statement.getColumn("is_active").getInt();
    json["created_by"] = statement.getColumn("created_by").getString();
    json["created_at"] = statement.getColumn("created_at").getString();
    json["updated_at"] = statement.getColumn("updated_at").getString();
    json["deleted_at"] = statement.getColumn("deleted_at").getString();
    json["deleted"] = statement.getColumn("deleted").getInt();
    User::fromJson(json, user);
  } else {
    return std::nullopt;
  }
  return user;
};

std::optional<User> UserRepo::findByUsername(const std::string &username) {
  nlohmann::json json;
  User user;
  auto query = fmt::format("SELECT * FROM {} WHERE username = :username",
                           COLLECTIONS::USERS);
  SQLite::Statement statement(db.getDb(), query);
  statement.bind(":username", username);
  if (statement.executeStep()) {
    json["id"] = statement.getColumn("id").getString();
    json["username"] = statement.getColumn("username").getString();
    json["hash_password"] = statement.getColumn("hash_password").getString();
    json["is_active"] = statement.getColumn("is_active").getInt();
    json["created_by"] = statement.getColumn("created_by").getString();
    json["created_at"] = statement.getColumn("created_at").getString();
    json["updated_at"] = statement.getColumn("updated_at").getString();
    json["deleted_at"] = statement.getColumn("deleted_at").getString();
    json["deleted"] = statement.getColumn("deleted").getInt();
    User::fromJson(json, user);
  } else {
    return std::nullopt;
  }
  return user;
}

PaginateResultDTO<User>
UserRepo::paginate(const PaginateDTO<UserParams> &params) {
  PaginateResultDTO<User> result = PaginateResultDTO<User>();
  return result;
}

void UserRepo::insert(const User &user) {
  SQLite::Transaction transaction(db.getDb());
  auto query =
      fmt::format("INSERT INTO {} (username, hash_password, is_active, "
                  "created_by, created_at, updated_at, deleted_at, deleted) "
                  "VALUES (:username, :hash_password, :is_active, :created_by, "
                  ":created_at, :updated_at, :deleted_at, :deleted)",
                  COLLECTIONS::USERS);
  SQLite::Statement statement(db.getDb(), query);

  statement.bind(":username", user.username);
  statement.bind(":hash_password", user.hash_password);
  statement.bind(":is_active", user.is_active);
  statement.bind(":created_by", user.created_by);
  statement.bind(":created_at", user.created_at);
  statement.bind(":updated_at", user.updated_at);
  statement.bind(":deleted_at", user.deleted_at);
  statement.bind(":deleted", user.deleted);
  statement.executeStep();

  transaction.commit();
}

void UserRepo::update(const std::string &id, const User &user) {
  SQLite::Transaction transaction(db.getDb());
  auto query = fmt::format("UPDATE {} SET username = :username, is_active = "
                           ":is_active WHERE id = {}",
                           COLLECTIONS::USERS, id);
  SQLite::Statement statement(db.getDb(), query);
  statement.bind(":username", user.username);
  statement.bind(":is_active", user.is_active);
  statement.executeStep();

  transaction.commit();
}

void UserRepo::softDelete(const std::string &id, const User &user) {
  SQLite::Transaction transaction(db.getDb());
  auto query = fmt::format("UPDATE {} SET deleted = :deleted, deleted_at = "
                           ":deleted_at WHERE id = :id",
                           COLLECTIONS::USERS);
  SQLite::Statement statement(db.getDb(), query);
  statement.bind(":id", id);
  statement.bind(":deleted_at", user.deleted_at);
  statement.bind(":deleted", user.deleted);
  statement.executeStep();
  transaction.commit();
}
