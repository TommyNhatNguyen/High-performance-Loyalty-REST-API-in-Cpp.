#pragma once
#include <nlohmann/json.hpp>
#include <string>

class BaseEntity {

public:
  static void fromJson(const nlohmann::json &json, BaseEntity &entity);
  static void toJson(nlohmann::json &json, const BaseEntity &entity);
  std::string created_by;
  std::string created_at;
  std::string updated_at;
  std::string deleted_at;
  int deleted = 0;
};