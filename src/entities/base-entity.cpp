#include "entities/base-entity.hpp"

void BaseEntity::fromJson(const nlohmann::json &json, BaseEntity &entity) {
  entity.created_at = json.at("created_at").get<std::string>();
  entity.created_by = json.at("created_by").get<std::string>();
  entity.updated_at = json.at("updated_at").get<std::string>();
  entity.deleted_at = json.at("deleted_at").get<std::string>();
  entity.deleted = json.at("deleted").get<int>();
};

void BaseEntity::toJson(nlohmann::json &json, const BaseEntity &entity) {
  json["created_by"] = entity.created_by;
  json["created_at"] = entity.created_at;
  json["updated_at"] = entity.updated_at;
  json["deleted_at"] = entity.deleted_at;
  json["deleted"] = entity.deleted;
};