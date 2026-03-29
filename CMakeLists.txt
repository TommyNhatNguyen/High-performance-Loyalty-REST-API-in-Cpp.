cmake_minimum_required(VERSION 3.20)
project(loyalty_backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(httplib CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)
find_package(unofficial-sodium CONFIG REQUIRED)
find_package(SQLiteCpp REQUIRED)

add_definitions(-DPROJECT_ROOT="${CMAKE_SOURCE_DIR}")
add_definitions(-DMIGRATION_PATH=\"${CMAKE_SOURCE_DIR}/src/migrations/init.sql\")
add_definitions(-DSEED_PATH=\"${CMAKE_SOURCE_DIR}/src/migrations/seeds.sql\")
# Load all cpp files
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/includes)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    unofficial::sqlite3::sqlite3
    httplib::httplib
    nlohmann_json::nlohmann_json
    spdlog::spdlog
    fmt::fmt
    jwt-cpp::jwt-cpp
    unofficial-sodium::sodium
    SQLiteCpp
)