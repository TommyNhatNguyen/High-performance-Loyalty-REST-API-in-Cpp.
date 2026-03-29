#pragma once
#include "dtos/user-dto.hpp"
#include "entities/user-entity.hpp"

class UserMapper {
public:
  static User toEntity(const UserDTO &dto);
  static UserDTO toDTO(const User &entity);
};