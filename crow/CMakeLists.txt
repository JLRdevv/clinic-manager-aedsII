cmake_minimum_required(VERSION 3.10)
project(trabalho-aedsII)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
    crow
    GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
    GIT_TAG v1.2.0
)

FetchContent_MakeAvailable(crow)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(app ${SOURCES})

target_link_libraries(app PRIVATE Crow::Crow)
