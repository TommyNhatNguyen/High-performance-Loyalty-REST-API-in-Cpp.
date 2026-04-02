#include "handlers/user-handler.hpp"
#include "constants/errors.hpp"
#include "dtos/error-dto.hpp"
#include "dtos/success-dto.hpp"
#include "dtos/user-dto.hpp"

using json = nlohmann::json;

// ================= CONSTRUCTOR =================
UserHandler::UserHandler(UserService &userService)
    : _userService(userService) {}

// ================= SETUP ROUTES =================
void UserHandler::setup(httplib::Server &app) {
  app.Get("/api/v1/users",
          [this](const auto &req, auto &res) { this->getUsers(req, res); });

  app.Get("/api/v1/users/:id",
          [this](const auto &req, auto &res) { this->getUser(req, res); });

  app.Post("/api/v1/users",
           [this](const auto &req, auto &res) { this->createUser(req, res); });

  app.Put("/api/v1/users/:id",
          [this](const auto &req, auto &res) { this->updateUser(req, res); });

  app.Delete("/api/v1/users/:id", [this](const auto &req, auto &res) {
    this->deleteUser(req, res);
  });
}

// ================= HANDLERS =================

void UserHandler::getUsers(const httplib::Request &req,
                           httplib::Response &res) {
  json result;

  try {
    PaginateDTO<UserParams> params;
    params.page =
        req.has_param("page") ? std::stoi(req.get_param_value("page")) : 1;
    params.pageSize = req.has_param("pageSize")
                          ? std::stoi(req.get_param_value("pageSize"))
                          : 10;

    auto users = _userService.paginate(params);
    PaginateResultDTO<User>::toJson(result, users);

    auto response = SuccessResponseDTO::toJson(
        SuccessResponseDTO("Users fetched successfully", result, 200));

    res.status = response["status"].get<int>();
    res.set_content(response.dump(), "application/json");

  } catch (const std::exception &e) {
    auto response =
        ErrorResponseDTO::toJson(ErrorResponseDTO(e.what(), result, 500, 500));

    res.status = response["status"].get<int>();
    res.set_content(response.dump(), "application/json");
  }
}

// ------------------------------------------------

void UserHandler::getUser(const httplib::Request &req, httplib::Response &res) {
  json result;

  try {
    auto id = req.path_params.at("id");
    auto user = _userService.get(id);

    if (user.has_value()) {
      User::toJson(result, user.value());

      auto response = SuccessResponseDTO::toJson(
          SuccessResponseDTO("User fetched successfully", result, 200));

      res.status = response["status"].get<int>();
      res.set_content(response.dump(), "application/json");
    } else {
      throw 404;
    }

  } catch (int errorCode) {
    auto response = ErrorResponseDTO::toJson(ErrorResponseDTO(
        UserErrors::getErrorMessage(errorCode), result, 400, errorCode));

    res.status = response["status"].get<int>();
    res.set_content(response.dump(), "application/json");

  } catch (const std::exception &e) {
    auto response =
        ErrorResponseDTO::toJson(ErrorResponseDTO(e.what(), result, 500, 500));

    res.status = response["status"].get<int>();
    res.set_content(response.dump(), "application/json");
  }
}

// ------------------------------------------------

void UserHandler::createUser(const httplib::Request &req,
                             httplib::Response &res) {
  try {
    auto reqBody = json::parse(req.body);

    CreateUserDTO payload;
    CreateUserDTO::fromJson(reqBody, payload);

    _userService.insert(payload);

    auto response = SuccessResponseDTO::toJson(
        SuccessResponseDTO("User created successfully", json::object(), 200));

    res.status = response["status"].get<int>();
    res.set_content(response.dump(), "application/json");

  } catch (const std::exception &e) {
    auto response = ErrorResponseDTO::toJson(
        ErrorResponseDTO(e.what(), json::object(), 500, 500));

    res.status = response["status"].get<int>();
    res.set_content(response.dump(), "application/json");
  }
}

// ------------------------------------------------

void UserHandler::updateUser(const httplib::Request &req,
                             httplib::Response &res) {
  try {
    auto id = req.path_params.at("id");
    auto reqBody = json::parse(req.body);

    UpdateUserDTO payload;
    UpdateUserDTO::fromJson(reqBody, payload);

    _userService.update(id, payload);

    auto response = SuccessResponseDTO::toJson(
        SuccessResponseDTO("User updated successfully", json::object(), 200));

    res.status = response["status"].get<int>();
    res.set_content(response.dump(), "application/json");

  } catch (int errorCode) {
    auto response = ErrorResponseDTO::toJson(
        ErrorResponseDTO(UserErrors::getErrorMessage(errorCode), json::object(),
                         400, errorCode));

    res.status = response["status"].get<int>();
    res.set_content(response.dump(), "application/json");

  } catch (const std::exception &e) {
    auto response = ErrorResponseDTO::toJson(
        ErrorResponseDTO(e.what(), json::object(), 500, 500));

    res.status = response["status"].get<int>();
    res.set_content(response.dump(), "application/json");
  }
}

// ------------------------------------------------

void UserHandler::deleteUser(const httplib::Request &req,
                             httplib::Response &res) {
  try {
    auto id = req.path_params.at("id");

    _userService.softDelete(id);

    auto response = SuccessResponseDTO::toJson(
        SuccessResponseDTO("User deleted successfully", json::object(), 200));

    res.status = response["status"].get<int>();
    res.set_content(response.dump(), "application/json");

  } catch (int errorCode) {
    auto response = ErrorResponseDTO::toJson(
        ErrorResponseDTO(UserErrors::getErrorMessage(errorCode), json::object(),
                         400, errorCode));

    res.status = response["status"].get<int>();
    res.set_content(response.dump(), "application/json");

  } catch (const std::exception &e) {
    auto response = ErrorResponseDTO::toJson(
        ErrorResponseDTO(e.what(), json::object(), 500, 500));

    res.status = response["status"].get<int>();
    res.set_content(response.dump(), "application/json");
  }
}