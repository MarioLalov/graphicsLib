cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(recipe-07 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

set(CMAKE_BUILD_TYPE Debug)

add_executable(graphicsLib main.cpp)
add_executable(unitTest UnitTests/test.cpp)

# set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(nlohmann_json 3.11.3 REQUIRED)

add_subdirectory(Nodes)
add_subdirectory(Managers)

target_link_libraries(graphicsLib
  PRIVATE
    sfml-graphics
    nlohmann_json::nlohmann_json
    Nodes
    Managers
  )

target_link_libraries(unitTest
  PRIVATE
    sfml-graphics
    nlohmann_json::nlohmann_json
    Nodes
    Managers
  )

target_compile_features(graphicsLib PRIVATE cxx_std_17)
target_compile_features(unitTest PRIVATE cxx_std_17)