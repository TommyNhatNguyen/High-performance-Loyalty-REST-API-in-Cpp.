#pragma once
#include <nlohmann/json.hpp>

template <typename T> class PaginateResultDTO {
public:
  static void fromJson(const nlohmann::json &json, PaginateResultDTO<T> &dto);
  static void toJson(nlohmann::json &json, const PaginateResultDTO<T> &dto);
  std::optional<std::vector<T>> data;
  int page;
  int pageSize;
  int total;
};