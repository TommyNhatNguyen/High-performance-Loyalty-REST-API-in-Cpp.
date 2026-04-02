#include "dtos/base-dto.hpp"
#include "utils/utils.hpp"

void BaseDTO::fromJson(const nlohmann::json &json, BaseDTO &dto) {
  dto.created_by = Utils::safeParseOptional<std::string>(json, "created_by");
  dto.created_at = Utils::safeParseOptional<std::string>(json, "created_at");
  dto.updated_at = Utils::safeParseOptional<std::string>(json, "updated_at");
  dto.deleted_at = Utils::safeParseOptional<std::string>(json, "deleted_at");
  dto.deleted = Utils::safeParseOptional<int>(json, "deleted");
};

void BaseDTO::toJson(nlohmann::json &json, const BaseDTO &dto) {
  json["created_by"] = dto.created_by;
  json["created_at"] = dto.created_at;
  json["updated_at"] = dto.updated_at;
  json["deleted_at"] = dto.deleted_at;
  json["deleted"] = dto.deleted;
};