cmake_minimum_required(VERSION 3.0.0)
project(httprequest VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_ARGS -DJSONCPP_INCLUDE_PREFIX=json)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(CTest)
enable_testing()

find_package(CURL QUIET REQUIRED) 
find_package(Jsoncpp REQUIRED)
include_directories(${CURL_INCLUDE_DIR} ${JSONCPP_INCLUDE_DIR})

message(JSONCPP_INCLUDE_DIR="${JSONCPP_INCLUDE_DIR}")

add_executable(httprequest main.cpp)
target_link_libraries(httprequest ${CURL_LIBRARIES} ${JSONCPP_LIBRARY})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
