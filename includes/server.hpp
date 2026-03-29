#pragma once
#include "configs/server-config.hpp"
#include "httplib.h"

class Server {
public:
  explicit Server(const ServerConfig &config = ServerConfig());
  ~Server() = default;

  void setup();
  void start();

private:
  ServerConfig _config;
  httplib::Server _app;
};
