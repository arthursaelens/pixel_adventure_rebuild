cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
set(CMAKE_CXX_STANDARD 17)
project(pgm-project)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)

if(NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)

  if(NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()

  FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
  )
  FetchContent_MakeAvailable(tomlplusplus)
endif()

find_package(tomlplusplus QUIET)

if(NOT tomlplusplus_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
    GIT_TAG v3.4.0
  )
  FetchContent_MakeAvailable(tomlplusplus)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
  set(CMAKE_CXX_FLAGS "-fsanitize=address -fno-omit-frame-pointer -fno-common")
endif()

set(ASSETS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/assets)
set(ASSETS_DEST_DIR ${CMAKE_CURRENT_BINARY_DIR}/assets)

file(GLOB_RECURSE GAME_SRCS CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE GAME_HEADER CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*.hpp")
file(GLOB_RECURSE GAME_CHEADER CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/include/*.h")
message(STATUS "Source files: ${GAME_SRCS}")
message(STATUS "Header files: ${GAME_HEADER} ${GAME_CHEADER}")
add_executable(
  ${PROJECT_NAME}
  ${GAME_HEADER}
  ${GAME_CHEADER}
  ${GAME_SRCS}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ${ASSETS_SOURCE_DIR} ${ASSETS_DEST_DIR}
  COMMENT "Copying assets to ${ASSETS_DEST_DIR} directory"
)

# set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} tomlplusplus::tomlplusplus)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if(APPLE)
  target_link_libraries(${PROJECT_NAME} "-framework IOKit")
  target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
  target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
