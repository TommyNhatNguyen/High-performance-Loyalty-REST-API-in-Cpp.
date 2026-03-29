#pragma once
#include <nlohmann/json.hpp>
#include <string>

class BaseDTO {
public:
  BaseDTO(const BaseDTO &) = default;
  BaseDTO(BaseDTO &&) = default;
  BaseDTO &operator=(const BaseDTO &) = default;
  BaseDTO &operator=(BaseDTO &&) = default;
  BaseDTO() = default;
  ~BaseDTO() = default;
  static void fromJson(const nlohmann::json &json, BaseDTO &dto);
  static void toJson(nlohmann::json &json, const BaseDTO &dto);
  friend class UserMapper;

private:
  std::string created_by;
  std::string created_at;
  std::string updated_at;
  std::string deleted_at;
  int deleted;
};