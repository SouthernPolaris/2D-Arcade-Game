# Specify the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(GameProject)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the directories for source, header, and assets
set(SOURCE_DIR src)
set(HEADER_DIR include)
set(TEST_DIR tests)
set(ASSETS_DIR assets)

# Collect all source files in the src directory
file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

# Collect all header files in the include directory
file(GLOB HEADERS ${HEADER_DIR}/*.h)

# Option to enable or disable unit tests
option(ENABLE_TESTS "Enable unit testing" OFF)

if (ENABLE_TESTS)
    # Collect unit test sources from tests directory, excluding main.cpp
    file(GLOB TEST_SOURCES ${TEST_DIR}/*.cpp)
    set(TEST_SOURCES_EXCLUDE ${SOURCE_DIR}/main.cpp)
    list(REMOVE_ITEM TEST_SOURCES ${TEST_SOURCES_EXCLUDE})

    # Define the unit test executable
    add_executable(UNIT_TEST ${TEST_SOURCES} ${HEADERS})
    target_link_libraries(UNIT_TEST sfml-graphics sfml-window sfml-system)
endif()

# Find the installed SFML library
find_package(SFML COMPONENTS graphics window system REQUIRED)

if (SFML_FOUND)
    message(STATUS "SFML found: ${SFML_VERSION}")
else()
    message(FATAL_ERROR "SFML not found")
endif()

# Include directories for header files
include_directories(${HEADER_DIR})

# Define the main game executable
add_executable(game ${SOURCES} ${HEADERS})
target_link_libraries(game sfml-graphics sfml-window sfml-system)

# Copy assets to the build directory after the game is built
add_custom_command(
    TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${ASSETS_DIR}
        $<TARGET_FILE_DIR:game>/${ASSETS_DIR}
)
