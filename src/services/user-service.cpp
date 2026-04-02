#include "services/user-service.hpp"
#include "utils/utils.hpp"
#include <ctime>
#include <optional>
#include <sodium/crypto_pwhash.h>
#include <stdexcept>

UserService::UserService(UserRepo &repo) : repo(repo) {};

std::string UserService::hashPassword(const std::string &password) {
  char hash[crypto_pwhash_STRBYTES];

  if (crypto_pwhash_str(hash, password.c_str(), password.size(),
                        crypto_pwhash_OPSLIMIT_INTERACTIVE,
                        crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
    throw std::runtime_error("Password hashing failed");
  }

  return std::string(hash);
};

bool UserService::verifyPassword(const std::string &password,
                                 const std::string &hash) {
  return crypto_pwhash_str_verify(hash.c_str(), password.c_str(),
                                  password.size()) == 0;
}

std::optional<User> UserService::get(const std::string &id) const {
  auto user = repo.findById(id);
  if (!user.has_value()) {
    throw 404;
  }
  return user;
};

std::optional<User> UserService::getByUsername(const std::string &username) {
  auto user = repo.findByUsername(username);
  if (!user.has_value()) {
    throw 404;
  }
  return user;
};

PaginateResultDTO<User>
UserService::paginate(const PaginateDTO<UserParams> &params) {
  return repo.paginate(params);
};

void UserService::insert(const CreateUserDTO &payload) {
  try {
    User user = User();
    user.username = payload.username.value();
    user.hash_password = this->hashPassword(payload.password.value());
    user.is_active = 1;
    user.created_at = Utils::getCurrentDate();
    user.updated_at = Utils::getCurrentDate();
    user.deleted = 0;
    repo.insert(user);
  } catch (const std::exception &e) {
    throw std::runtime_error("Failed to create user: " + std::string(e.what()));
  }
};

void UserService::update(const std::string &id, const UpdateUserDTO &payload) {
  try {
    auto updatedUser = this->get(id);
    if (!updatedUser.has_value()) {
      throw 404;
    }
    User user = updatedUser.value();
    user.username = payload.username.has_value() ? payload.username.value()
                                                 : updatedUser.value().username;
    user.is_active = payload.is_active.has_value()
                         ? payload.is_active.value()
                         : updatedUser.value().is_active;
    user.updated_at = Utils::getCurrentDate();
    repo.update(id, user);
  } catch (const std::exception &e) {
    throw std::runtime_error("Failed to update user: " + std::string(e.what()));
  }
};

void UserService::softDelete(const std::string &id) {
  try {
    auto updatedUser = this->get(id);
    if (!updatedUser.has_value()) {
      throw 404;
    }
    User user = updatedUser.value();
    user.deleted_at = Utils::getCurrentDate();
    user.deleted = 1;
    repo.softDelete(id, user);
  } catch (const std::exception &e) {
    throw std::runtime_error("Failed to update user: " + std::string(e.what()));
  }
};
