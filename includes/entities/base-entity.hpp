#pragma once

#include <nlohmann/json.hpp>
#include <string>

class BaseEntity {

public:
  BaseEntity(const BaseEntity &) = default;
  BaseEntity(BaseEntity &&) = default;
  BaseEntity &operator=(const BaseEntity &) = default;
  BaseEntity &operator=(BaseEntity &&) = default;
  BaseEntity() = default;
  ~BaseEntity() = default;
  static void fromJson(const nlohmann::json &json, BaseEntity &entity);
  static void toJson(nlohmann::json &json, const BaseEntity &entity);
  friend class UserMapper;

protected:
  std::string created_by;
  std::string created_at;
  std::string updated_at;
  std::string deleted_at;
  int deleted;
};