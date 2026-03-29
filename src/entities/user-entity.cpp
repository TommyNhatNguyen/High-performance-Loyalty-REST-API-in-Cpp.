#include "entities/user-entity.hpp"

User User::fromJson(const nlohmann::json &json) {
  User user;
  BaseEntity::fromJson(json, user);
  user.id = json.value("id", "");
  user.username = json.value("username", "");
  user.hash_password = json.value("hash_password", "");
  user.is_active = json.value("is_active", 0);
  return user;
};

nlohmann::json User::toJson(const User &entity) {
  nlohmann::json j;
  BaseEntity::toJson(j, entity);
  j["id"] = entity.id;
  j["username"] = entity.username;
  j["hash_password"] = entity.hash_password;
  j["is_active"] = entity.is_active;
  return j;
};