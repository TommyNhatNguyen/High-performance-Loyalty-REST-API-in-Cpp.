#pragma once
#include "base-entity.hpp"

class User : public BaseEntity {
public:
  static void fromJson(const nlohmann::json &json, User &entity);
  static void toJson(nlohmann::json &json, const User &entity);
  std::string id;
  std::string username;
  std::string hash_password;
  int is_active;
};