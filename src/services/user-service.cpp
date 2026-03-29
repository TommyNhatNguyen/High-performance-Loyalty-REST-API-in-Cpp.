#include "services/user-service.hpp"
// #include "mappers/user-mapper.hpp"
#include <sodium/crypto_pwhash.h>

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
  return repo.findById(id);
};

// std::optional<User> UserService::getByUsername(const std::string &username) {
//   return repo.findByUsername(username);
// };
// PaginateResultDTO<User> UserService::paginate(PaginateDTO<UserDTO> params) {
//   return repo.paginate(params);
// };
// void UserService::insert(const UserDTO &payload) {
//   auto data = UserMapper::toEntity(payload);
//   repo.insert(data);
// };
// void UserService::update(const std::string &id, const UserDTO &payload) {
//   auto updatedData = get(id);
//   if (updatedData.has_value()) {
//     auto data = UserMapper::toEntity(payload);
//     repo.update(id, data);
//   } else {
//     throw std::runtime_error("User not found!");
//   }
// };
// void UserService::softDelete(const std::string &id) { repo.softDelete(id); };
