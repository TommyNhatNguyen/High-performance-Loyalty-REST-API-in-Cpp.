#pragma once
#include "dtos/paginate-dto.hpp"
#include "dtos/paginate-result-dto.hpp"
#include "dtos/user-dto.hpp"
#include "entities/user-entity.hpp"
#include "repositories/SqliteRepo.hpp"
#include <string>

class UserRepo {
public:
  UserRepo(SqliteRepo &db);
  ~UserRepo() = default;
  std::optional<User> findById(const std::string &id);
  std::optional<User> findByUsername(const std::string &username);
  PaginateResultDTO<User> paginate(const PaginateDTO<UserParams> &params);
  void insert(const User &user);
  void update(const std::string &id, const User &user);
  void softDelete(const std::string &id, const User &user);

private:
  SqliteRepo &db;
};