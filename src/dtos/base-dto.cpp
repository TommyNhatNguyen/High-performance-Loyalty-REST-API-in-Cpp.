#include "dtos/base-dto.hpp"

void BaseDTO::fromJson(const nlohmann::json &json, BaseDTO &dto) {
  dto.created_by = json.value("created_by", "");
  dto.created_at = json.value("created_at", "");
  dto.updated_at = json.value("updated_at", "");
  dto.deleted_at = json.value("deleted_at", "");
  dto.deleted = json.value("deleted", 0);
};

void BaseDTO::toJson(nlohmann::json &json, const BaseDTO &dto) {
  json["created_by"] = dto.created_by;
  json["created_at"] = dto.created_at;
  json["updated_at"] = dto.updated_at;
  json["deleted_at"] = dto.deleted_at;
  json["deleted"] = dto.deleted;
};