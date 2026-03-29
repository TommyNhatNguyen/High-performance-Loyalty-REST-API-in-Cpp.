#pragma once
#include "dtos/base-dto.hpp"

class UserDTO : public BaseDTO {
public:
  UserDTO(const UserDTO &) = default;
  UserDTO(UserDTO &&) = default;
  UserDTO &operator=(const UserDTO &) = default;
  UserDTO &operator=(UserDTO &&) = default;
  UserDTO() = default;
  ~UserDTO() = default;
  static void fromJson(const nlohmann::json &json, UserDTO &dto);
  static void toJson(nlohmann::json &json, const UserDTO &dto);
  friend class UserMapper;

private:
  std::optional<std::string> id;
  std::optional<std::string> username;
  std::optional<std::string> password;
  std::optional<int> is_active;
};