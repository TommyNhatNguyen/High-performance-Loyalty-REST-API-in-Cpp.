#pragma once
#include "dtos/paginate-dto.hpp"
#include "dtos/paginate-result-dto.hpp"
#include "dtos/user-dto.hpp"
#include "entities/user-entity.hpp"
#include "repositories/user-repo.hpp"
#include <string>

class UserService {

public:
  UserService(UserRepo &repo);
  static std::string hashPassword(const std::string &password);
  static bool verifyPassword(const std::string &password,
                             const std::string &hash);
  std::optional<User> get(const std::string &id) const;
  std::optional<User> getByUsername(const std::string &id);
  PaginateResultDTO<User> paginate(const PaginateDTO<UserParams> &params);
  void insert(const CreateUserDTO &payload);
  void update(const std::string &id, const UpdateUserDTO &payload);
  void softDelete(const std::string &id);

private:
  UserRepo &repo;
};