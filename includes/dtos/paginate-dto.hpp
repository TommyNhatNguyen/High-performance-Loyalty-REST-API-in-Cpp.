#pragma once
#include <nlohmann/json.hpp>
template <typename T> class PaginateDTO {
public:
  static void fromJson(const nlohmann::json &json, PaginateDTO<T> &dto);
  static void toJson(nlohmann::json &json, const PaginateDTO<T> &dto);
  std::optional<T> params = std::nullopt;
  int page;
  int pageSize;
  int total;
};