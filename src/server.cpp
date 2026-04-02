#include "server.hpp"
#include "handlers/user-handler.hpp"
#include "repositories/user-repo.hpp"
#include "services/user-service.hpp"

Server::Server(const ServerConfig &config) : _config(config) {}

void Server::setup() {
  std::cout << "Server setup..." << std::endl;

  // ================= DB =================
  SqliteRepo::init(DatabaseConfig());

  _userRepo = std::make_unique<UserRepo>(SqliteRepo::getInstance());
  _userService = std::make_unique<UserService>(*_userRepo);

  // ================= HANDLERS =================
  _handlers.push_back(std::make_unique<UserHandler>(*_userService));

  // ================= REGISTER ROUTES =================
  for (auto &handler : _handlers) {
    handler->setup(_app);
  }
}

void Server::start() {
  setup();
  std::cout << "Server is running at: http://" << _config.HOST << ":"
            << _config.PORT << std::endl;
  _app.listen(_config.HOST, _config.PORT);
}