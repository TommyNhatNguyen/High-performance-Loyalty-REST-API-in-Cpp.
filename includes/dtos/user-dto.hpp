#pragma once
#include "dtos/base-dto.hpp"

class CreateUserDTO : public BaseDTO {
public:
  static void fromJson(const nlohmann::json &json, CreateUserDTO &dto);
  static void toJson(nlohmann::json &json, const CreateUserDTO &dto);
  std::optional<std::string> username;
  std::optional<std::string> password;
  std::optional<int> is_active;
};

class UpdateUserDTO : public BaseDTO {
public:
  static void fromJson(const nlohmann::json &json, UpdateUserDTO &dto);
  static void toJson(nlohmann::json &json, const UpdateUserDTO &dto);
  std::optional<std::string> username;
  std::optional<int> is_active;
};

class UserParams : public BaseDTO {};