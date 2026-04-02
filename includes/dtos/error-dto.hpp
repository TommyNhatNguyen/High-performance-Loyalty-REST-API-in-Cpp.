#pragma once

#include <nlohmann/json.hpp>

class ErrorResponseDTO {
public:
  ErrorResponseDTO(const std::string &message, const nlohmann::json &data,
                   int status, int errorCode)
      : message(message), data(data), status(status), success(false),
        errorCode(errorCode) {}
  std::string message;
  nlohmann::json data;
  int status = 200;
  bool success = false;
  int errorCode;
  static nlohmann::json toJson(const ErrorResponseDTO &dto) {
    nlohmann::json json;
    json["message"] = dto.message;
    json["data"] = dto.data;
    json["status"] = dto.status;
    json["success"] = dto.success;
    json["errorCode"] = dto.errorCode;
    return json;
  }
};