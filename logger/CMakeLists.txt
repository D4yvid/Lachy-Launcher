cmake_minimum_required (VERSION 3.10)

project(logger LANGUAGES CXX)

# Use spdlog as header-only to support 32-bit builds
include(FetchContent)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.14.1
)
FetchContent_MakeAvailable(spdlog)

add_library(logger include/log.h src/log.cpp)
target_include_directories(logger PUBLIC include/)
target_link_libraries(logger PUBLIC spdlog::spdlog_header_only)