// #pragma once
// #include <nlohmann/json.hpp>
#include "dtos/paginate-result-dto.hpp"

template <typename T>
void PaginateResultDTO<T>::fromJson(const nlohmann::json &json,
                                    PaginateResultDTO<T> &dto) {
  dto.page = json.value("page", 1);
  dto.pageSize = json.value("pageSize", 10);
  dto.total = json.value("total", 0);
};

template <typename T>
void PaginateResultDTO<T>::toJson(nlohmann::json &json,
                                  const PaginateResultDTO<T> &dto) {
  json["data"] = dto.data.has_value() ? dto.data.value() : nullptr;
  json["page"] = dto.page;
  json["pageSize"] = dto.pageSize;
  json["total"] = dto.total;
};