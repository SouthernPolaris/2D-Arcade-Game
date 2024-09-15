cmake_minimum_required(VERSION 3.10)

project(GameProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_DIR src)
set(HEADER_DIR include)
set(TEST_DIR tests)
set(ASSETS_DIR assets)

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)

file(GLOB HEADERS ${HEADER_DIR}/*.h)

option(ENABLE_TESTS "Enable unit testing" OFF)

if (ENABLE_TESTS)
    file(GLOB TEST_SOURCES ${TEST_DIR}/*.cpp)
    set(TEST_SOURCES_EXCLUDE ${SOURCE_DIR}/main.cpp)
    list(REMOVE_ITEM TEST_SOURCES ${TEST_SOURCES_EXCLUDE})

    add_executable(UNIT_TEST ${TEST_SOURCES} ${HEADERS})
    target_link_libraries(UNIT_TEST sfml-graphics sfml-window sfml-system)
endif()

find_package(SFML COMPONENTS graphics window system REQUIRED)

if (SFML_FOUND)
    message(STATUS "SFML found: ${SFML_VERSION}")
else()
    message(FATAL_ERROR "SFML not found. Please install SFML")
endif()

include_directories(${HEADER_DIR})

add_executable(game ${SOURCES} ${HEADERS})
target_link_libraries(game sfml-graphics sfml-window sfml-system)

add_custom_command(
    TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${ASSETS_DIR}
        $<TARGET_FILE_DIR:game>/${ASSETS_DIR}
)
