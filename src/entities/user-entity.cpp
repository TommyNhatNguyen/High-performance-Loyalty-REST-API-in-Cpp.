#include "entities/user-entity.hpp"

void User::fromJson(const nlohmann::json &json, User &entity) {
  BaseEntity::fromJson(json, entity);
  entity.id = json["id"].get<std::string>();
  entity.username = json["username"].get<std::string>();
  entity.hash_password = json["hash_password"].get<std::string>();
  entity.is_active = json["is_active"].get<int>();
};

void User::toJson(nlohmann::json &json, const User &entity) {
  BaseEntity::toJson(json, entity);
  json["id"] = entity.id;
  json["username"] = entity.username;
  json["hash_password"] = entity.hash_password;
  json["is_active"] = entity.is_active;
};