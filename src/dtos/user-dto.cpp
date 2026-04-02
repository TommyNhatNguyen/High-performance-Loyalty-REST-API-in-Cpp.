#include "dtos/user-dto.hpp"
#include "utils/utils.hpp"

void CreateUserDTO::fromJson(const nlohmann::json &json, CreateUserDTO &dto) {
  BaseDTO::fromJson(json, dto);
  dto.username = Utils::safeParseOptional<std::string>(json, "username");
  dto.password = Utils::safeParseOptional<std::string>(json, "password");
  dto.is_active = Utils::safeParseOptional<int>(json, "is_active");
};

void CreateUserDTO::toJson(nlohmann::json &json, const CreateUserDTO &dto) {
  BaseDTO::toJson(json, dto);
  json["username"] = dto.username;
  json["password"] = dto.password;
  json["is_active"] = dto.is_active;
};

void UpdateUserDTO::fromJson(const nlohmann::json &json, UpdateUserDTO &dto) {
  BaseDTO::fromJson(json, dto);
  dto.username = Utils::safeParseOptional<std::string>(json, "username");
  dto.is_active = Utils::safeParseOptional<int>(json, "is_active");
};

void UpdateUserDTO::toJson(nlohmann::json &json, const UpdateUserDTO &dto) {
  BaseDTO::toJson(json, dto);
  json["username"] = dto.username.has_value() ? dto.username.value() : nullptr;
  json["is_active"] = dto.is_active.has_value() ? dto.is_active.value() : NULL;
}
