#include "server.hpp"
#include "dtos/error-dto.hpp"
#include "dtos/success-dto.hpp"
#include "dtos/user-dto.hpp"
#include "entities/user-entity.hpp"
#include "repositories/SqliteRepo.hpp"
#include "repositories/user-repo.hpp"
#include "services/user-service.hpp"

Server::Server(const ServerConfig &config) : _config(config) {};

void Server::setup() {
  std::cout << "Server setup..." << std::endl;
  SqliteRepo::init(DatabaseConfig());
  // SqliteRepo::getInstance().migrate("src/migrations/init.sql");
  // SqliteRepo::getInstance().migrate("src/migrations/seeds.sql");
};

void Server::start() {
  this->setup();
  std::cout << "Server starting..." << std::endl;
  std::cout << "Server is running at: " << "http://" << _config.HOST << ":"
            << _config.PORT << "\n";
  auto userRepo = UserRepo(SqliteRepo::getInstance());
  UserService userService(userRepo);

  _app.Get("/api/v1/users", [this, &userService](const httplib::Request &req,
                                                 httplib::Response &res) {
    nlohmann::json result;
    try {
      PaginateDTO<UserParams> params;
      params.page =
          req.has_param("page") ? std::stoi(req.get_param_value("page")) : 1;
      params.pageSize = req.has_param("pageSize")
                            ? std::stoi(req.get_param_value("pageSize"))
                            : 10;
      auto users = userService.paginate(params);
      PaginateResultDTO<User>::toJson(result, users);
      auto response = SuccessResponseDTO::toJson(
          SuccessResponseDTO("Users fetched successfully", result, 200));
      res.set_content(response.dump(), "application/json");
    } catch (const std::exception &e) {
      auto response = ErrorResponseDTO::toJson(
          ErrorResponseDTO(e.what(), result, 500, 500));
      res.set_content(response.dump(), "application/json");
    }
  });

  _app.Get(
      "/api/v1/users/:id", [this, &userService](const httplib::Request &req,
                                                httplib::Response &res) {
        nlohmann::json result;
        try {
          auto id = req.path_params.at("id");
          auto user = userService.get(id);
          if (user.has_value()) {
            User::toJson(result, user.value());
            auto response = SuccessResponseDTO::toJson(
                SuccessResponseDTO("User fetched successfully", result, 200));
            res.set_content(response.dump(), "application/json");
          } else {
            auto response = ErrorResponseDTO::toJson(
                ErrorResponseDTO("User not found!", result, 204, 404));
            res.set_content(response.dump(), "application/json");
          }
        } catch (int errorCode) {
          auto response = ErrorResponseDTO::toJson(
              ErrorResponseDTO("User not found!", result, 204, errorCode));
          res.set_content(response.dump(), "application/json");
        } catch (const std::exception &e) {
          auto response = ErrorResponseDTO::toJson(
              ErrorResponseDTO(e.what(), result, 500, 500));
          res.set_content(response.dump(), "application/json");
        }
      });

  _app.Post("/api/v1/users", [this, &userService](const httplib::Request &req,
                                                  httplib::Response &res) {
    try {
      CreateUserDTO payload;
      auto reqBody = nlohmann::json::parse(req.body);
      CreateUserDTO::fromJson(reqBody, payload);
      userService.insert(payload);
      auto response = SuccessResponseDTO::toJson(SuccessResponseDTO(
          "User created successfully", nlohmann::json::object(), 200));
      res.set_content(response.dump(), "application/json");
    } catch (const std::exception &e) {
      auto response = ErrorResponseDTO::toJson(
          ErrorResponseDTO(e.what(), nlohmann::json::object(), 500, 500));
      res.set_content(response.dump(), "application/json");
    }
  });

  _app.Put(
      "/api/v1/users/:id", [this, &userService](const httplib::Request &req,
                                                httplib::Response &res) {
        try {
          UpdateUserDTO payload;
          auto id = req.path_params.at("id");
          auto reqBody = nlohmann::json::parse(req.body);
          UpdateUserDTO::fromJson(reqBody, payload);
          userService.update(id, payload);
          auto response = SuccessResponseDTO::toJson(SuccessResponseDTO(
              "User updated successfully", nlohmann::json::object(), 200));
          res.set_content(response.dump(), "application/json");
        } catch (int errorCode) {
          auto response = ErrorResponseDTO::toJson(ErrorResponseDTO(
              "User not found!", nlohmann::json::object(), 204, errorCode));
          res.set_content(response.dump(), "application/json");
        } catch (const std::exception &e) {
          auto response = ErrorResponseDTO::toJson(
              ErrorResponseDTO(e.what(), nlohmann::json::object(), 500, 500));
          res.set_content(response.dump(), "application/json");
        }
      });

  _app.Delete(
      "/api/v1/users/:id", [this, &userService](const httplib::Request &req,
                                                httplib::Response &res) {
        try {
          auto id = req.path_params.at("id");
          userService.softDelete(id);
          auto response = SuccessResponseDTO::toJson(SuccessResponseDTO(
              "User deleted successfully", nlohmann::json::object(), 200));
          res.set_content(response.dump(), "application/json");
        } catch (int errorCode) {
          auto response = ErrorResponseDTO::toJson(ErrorResponseDTO(
              "User not found!", nlohmann::json::object(), 204, errorCode));
          res.set_content(response.dump(), "application/json");
        } catch (const std::exception &e) {
          auto response = ErrorResponseDTO::toJson(
              ErrorResponseDTO(e.what(), nlohmann::json::object(), 500, 500));
          res.set_content(response.dump(), "application/json");
        }
      });

  _app.listen(_config.HOST, _config.PORT);
};