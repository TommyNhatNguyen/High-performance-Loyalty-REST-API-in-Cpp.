#include "dtos/user-dto.hpp"

void UserDTO::fromJson(const nlohmann::json &json, UserDTO &dto) {
  BaseDTO::fromJson(json, dto);
  dto.id = json.value("id", std::optional<std::string>());
  dto.username = json.value("username", std::optional<std::string>());
  dto.password = json.value("password", std::optional<std::string>());
  dto.is_active = json.value("is_active", std::optional<int>());
};

void UserDTO::toJson(nlohmann::json &json, const UserDTO &dto) {
  BaseDTO::toJson(json, dto);
  json["id"] = dto.id.value_or(nullptr);
  json["username"] = dto.username.value_or(nullptr);
  json["password"] = dto.password.value_or(nullptr);
  json["is_active"] = dto.is_active.value_or(0);
};