#include <map>
#include <string>

class UserErrors {
public:
  inline static const std::string USER_NOT_FOUND = "User not found";
  inline static const std::string USER_ALREADY_EXISTS = "User already exists";
  inline static const std::string USER_INVALID_CREDENTIALS =
      "Invalid credentials";
  inline static const std::string USER_INVALID_REQUEST = "Invalid request";
  inline static const std::string USER_INTERNAL_SERVER_ERROR =
      "Internal server error";

  inline static std::string getErrorMessage(int errorCode) {
    return errors[errorCode];
  }

private:
  inline static std::map<int, std::string> errors = {
      {404, USER_NOT_FOUND},
      {409, USER_ALREADY_EXISTS},
      {401, USER_INVALID_CREDENTIALS},
      {400, USER_INVALID_REQUEST},
      {500, USER_INTERNAL_SERVER_ERROR}};
};