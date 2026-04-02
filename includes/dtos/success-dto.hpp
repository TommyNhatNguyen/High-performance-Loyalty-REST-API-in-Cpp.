#pragma once

#include <nlohmann/json.hpp>

class SuccessResponseDTO {
public:
  SuccessResponseDTO(const std::string &message, const nlohmann::json &data,
                     int status)
      : message(message), data(data), status(status), success(true) {}
  std::string message;
  nlohmann::json data;
  int status = 200;
  bool success = true;
  static nlohmann::json toJson(const SuccessResponseDTO &dto) {
    nlohmann::json json;
    json["message"] = dto.message;
    json["data"] = dto.data;
    json["status"] = dto.status;
    json["success"] = dto.success;
    return json;
  }
};