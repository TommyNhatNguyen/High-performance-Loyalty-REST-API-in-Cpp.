#pragma once
#include "configs/server-config.hpp"
#include "httplib.h"
#include "interfaces/handler-interface.hpp"
#include "services/user-service.hpp"

class Server {
public:
  explicit Server(const ServerConfig &config = ServerConfig());
  ~Server() = default;

  void setup();
  void start();
  void registerRoutes();

private:
  std::unique_ptr<UserRepo> _userRepo;
  std::unique_ptr<UserService> _userService;

  ServerConfig _config;
  httplib::Server _app;
  std::vector<std::unique_ptr<IHandler>> _handlers;
};
