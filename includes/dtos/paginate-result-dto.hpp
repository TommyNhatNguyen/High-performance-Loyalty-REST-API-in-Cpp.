#pragma once
#include <nlohmann/json.hpp>

template <typename T> class PaginateResultDTO {
public:
  static void fromJson(const nlohmann::json &json, PaginateResultDTO<T> &dto) {
    dto.page = json.value("page", 1);
    dto.pageSize = json.value("pageSize", 10);
    dto.total = json.value("total", 0);
  };
  static void toJson(nlohmann::json &json, const PaginateResultDTO<T> &dto) {
    json["data"] = nlohmann::json::array();
    for (const auto &item : dto.data) {
      nlohmann::json itemJson;
      T::toJson(itemJson, item);
      json["data"].push_back(itemJson);
    }
    json["page"] = dto.page;
    json["pageSize"] = dto.pageSize;
    json["total"] = dto.total;
  };
  std::vector<T> data;
  int page;
  int pageSize;
  int total = 0;
};