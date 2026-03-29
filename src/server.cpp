#include "server.hpp"
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
               auto id = req.path_params.at("id");
               auto user = userService.get(id);
               if (user.has_value()) {
                 nlohmann::json json = User::toJson(user.value());
                 res.status = 200;
                 res.set_content(json.dump(), "application/json");
               } else {
                 res.status = 404;
                 res.set_content("User not found", "text/plain");
               }
             } catch (const std::exception &e) {
               res.status = 500;
               res.set_content(e.what(), "text/plain");
             }
           });
  _app.listen(_config.HOST, _config.PORT);
};