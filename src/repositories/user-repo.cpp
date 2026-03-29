#include "repositories/user-repo.hpp"
#include "constants/collections.hpp"
#include "fmt/format.h"

UserRepo::UserRepo(SqliteRepo &db) : db(db) {};

std::optional<User> UserRepo::findById(const std::string &id) {
  // Prepare statement
  auto query =
      fmt::format("SELECT * FROM {} WHERE id = :id", COLLECTIONS::USERS);

  SQLite::Statement statement(db.getDb(), query);
  // Binds values
  statement.bind(":id", id);
  // Execute statement
  if (statement.executeStep()) {
    nlohmann::json json;
    json["id"] = statement.getColumn("id").getString();
    json["username"] = statement.getColumn("username").getString();
    json["hash_password"] = statement.getColumn("hash_password").getString();
    json["is_active"] = statement.getColumn("is_active").getInt();
    return User::fromJson(json);
  }
  return std::nullopt;
};

// std::optional<User> UserRepo::findByUsername(const std::string &username) {
//   return db.findByUsername(username);
// }

// PaginateResultDTO<User> UserRepo::paginate(const PaginateDTO<UserDTO>
// &params) {
//   return db.paginate(params);
// }

// void UserRepo::insert(const User &user) { db.insert(user); }

// void UserRepo::update(const std::string &id, const User &user) {
//   db.update(id, user);
// }

// void UserRepo::softDelete(const std::string &id) { db.softDelete(id); }
