#pragma once
#include "interfaces/handler-interface.hpp"
#include "services/user-service.hpp"

class UserHandler : public IHandler {
public:
  explicit UserHandler(UserService &userService);
  void setup(httplib::Server &app) override;

private:
  UserService &_userService;
  void getUsers(const httplib::Request &req, httplib::Response &res);
  void getUser(const httplib::Request &req, httplib::Response &res);
  void createUser(const httplib::Request &req, httplib::Response &res);
  void updateUser(const httplib::Request &req, httplib::Response &res);
  void deleteUser(const httplib::Request &req, httplib::Response &res);
};