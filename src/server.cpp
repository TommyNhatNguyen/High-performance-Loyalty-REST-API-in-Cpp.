#include "server.hpp"
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
  _app.Get("/api/v1/users/:id",
           [this, &userService](const httplib::Request &req,
                                httplib::Response &res) {
             try {
               nlohmann::json json;
               auto id = req.path_params.at("id");
               auto user = userService.get(id);
               if (user.has_value()) {
                 User::toJson(json, user.value());
                 res.status = 200;
                 res.set_content(json.dump(), "application/json");
               } else {
                 res.status = 204;
                 res.set_content("User not found!", "application/json");
               }
             } catch (const std::exception &e) {
               res.status = 500;
               res.set_content(e.what(), "text/plain");
             }
           });

  _app.Post("/api/v1/users", [this, &userService](const httplib::Request &req,
                                                  httplib::Response &res) {
    try {
      CreateUserDTO payload;
      auto reqBody = nlohmann::json::parse(req.body);
      CreateUserDTO::fromJson(reqBody, payload);
      userService.insert(payload);
      res.status = 200;
      res.set_content(
          nlohmann::json({{"message", "User created successfully"}}).dump(),
          "application/json");
    } catch (const std::exception &e) {
      res.status = 500;
      res.set_content(e.what(), "text/plain");
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
          res.status = 200;
          res.set_content(nlohmann::json({{"message", "User updated"}}).dump(),
                          "application/json");
        } catch (const std::exception &e) {
          res.status = 500;
          res.set_content(e.what(), "text/plain");
        }
      });

  _app.Delete("/api/v1/users/:id",
              [this, &userService](const httplib::Request &req,
                                   httplib::Response &res) {
                try {
                  auto id = req.path_params.at("id");
                  userService.softDelete(id);
                  res.status = 200;
                  res.set_content("User deleted", "application/json");

                } catch (const std::exception &e) {
                  res.status = 500;
                  res.set_content(e.what(), "text/plain");
                }
              });

  _app.listen(_config.HOST, _config.PORT);
};