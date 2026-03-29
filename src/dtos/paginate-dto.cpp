#include "dtos/paginate-dto.hpp"

template <typename T>
void PaginateDTO<T>::fromJson(const nlohmann::json &json, PaginateDTO<T> &dto) {
  dto.params = json.value("params", std::optional<T>());
  dto.page = json.value("page", 1);
  dto.pageSize = json.value("pageSize", 10);
  dto.total = json.value("total", 0);
};

template <typename T>
void PaginateDTO<T>::toJson(nlohmann::json &json, const PaginateDTO<T> &dto) {
  json["params"] = dto.params.value_or(T());
  json["page"] = dto.page;
  json["pageSize"] = dto.pageSize;
  json["total"] = dto.total;
};
