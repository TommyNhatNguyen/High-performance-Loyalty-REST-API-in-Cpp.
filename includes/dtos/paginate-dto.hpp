#pragma once
#include "utils/utils.hpp"
#include <nlohmann/json.hpp>
template <typename T> class PaginateDTO {
public:
  static void fromJson(const nlohmann::json &json, PaginateDTO<T> &dto) {
    dto.params = Utils::safeParseOptional<T>(json, "params");
    dto.page = json.value("page", 1);
    dto.pageSize = json.value("pageSize", 10);
  };
  static void toJson(nlohmann::json &json, const PaginateDTO<T> &dto) {
    json["params"] =
        dto.params.has_value() ? dto.params.value() : nlohmann::json::object();
    json["page"] = dto.page;
    json["pageSize"] = dto.pageSize;
  };
  std::optional<T> params = std::nullopt;
  int page = 1;
  int pageSize = 10;
};