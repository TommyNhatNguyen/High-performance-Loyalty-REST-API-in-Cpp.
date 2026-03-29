#pragma once
#include "base-entity.hpp"

class User : public BaseEntity {

public:
  User(const User &) = default;
  User(User &&) = default;
  User &operator=(const User &) = default;
  User &operator=(User &&) = default;
  User() = default;
  ~User() = default;
  static User fromJson(const nlohmann::json &json);
  static nlohmann::json toJson(const User &entity);
  friend class UserMapper;

private:
  std::string id;
  std::string username;
  std::string hash_password;
  int is_active;
};