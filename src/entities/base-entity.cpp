#include "entities/base-entity.hpp"

void BaseEntity::fromJson(const nlohmann::json &json, BaseEntity &entity) {
  entity.created_at = json.value("created_at", "");
  entity.created_by = json.value("created_by", "");
  entity.updated_at = json.value("updated_at", "");
  entity.deleted_at = json.value("deleted_at", "");
  entity.deleted = json.value("deleted", 0);
};

void BaseEntity::toJson(nlohmann::json &json, const BaseEntity &entity) {
  json["created_by"] = entity.created_by;
  json["created_at"] = entity.created_at;
  json["updated_at"] = entity.updated_at;
  json["deleted_at"] = entity.deleted_at;
  json["deleted"] = entity.deleted;
};