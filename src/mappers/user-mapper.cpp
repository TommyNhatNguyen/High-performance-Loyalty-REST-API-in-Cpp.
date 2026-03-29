#include "mappers/user-mapper.hpp"
#include "services/user-service.hpp"

User UserMapper::toEntity(const UserDTO &dto) {
  User entity;

  // Base fields
  entity.created_by = dto.created_by;
  entity.created_at = dto.created_at;
  entity.updated_at = dto.updated_at;
  entity.deleted_at = dto.deleted_at;
  entity.deleted = dto.deleted;

  // User fields
  if (dto.id.has_value()) {
    entity.id = dto.id.value();
  }
  if (dto.username.has_value()) {
    entity.username = dto.username.value();
  }
  if (dto.password.has_value()) {
    entity.hash_password = UserService::hashPassword(dto.password.value());
  }
  if (dto.is_active.has_value()) {
    entity.is_active = dto.is_active.value();
  }

  return entity;
}

UserDTO UserMapper::toDTO(const User &entity) {
  UserDTO dto;

  // Base fields
  dto.created_by = entity.created_by;
  dto.created_at = entity.created_at;
  dto.updated_at = entity.updated_at;
  dto.deleted_at = entity.deleted_at;
  dto.deleted = entity.deleted;

  // User fields
  dto.id = entity.id;
  dto.username = entity.username;
  dto.is_active = entity.is_active;
  dto.password = entity.hash_password;
  return dto;
}