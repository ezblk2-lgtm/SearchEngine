cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

add_executable(searchEngine 
        src/main.cpp
        src/InvertedIndex.cpp
        src/ConverterJson.cpp
        src/SearchServer.cpp)

target_link_libraries(searchEngine PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(searchEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)