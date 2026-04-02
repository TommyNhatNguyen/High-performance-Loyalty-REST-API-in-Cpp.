#pragma once
#include <nlohmann/json.hpp>
#include <string>

class BaseDTO {
public:
  static void fromJson(const nlohmann::json &json, BaseDTO &dto);
  static void toJson(nlohmann::json &json, const BaseDTO &dto);
  std::optional<std::string> created_by;
  std::optional<std::string> created_at;
  std::optional<std::string> updated_at;
  std::optional<std::string> deleted_at;
  std::optional<int> deleted;
};