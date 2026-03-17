cmake_minimum_required(VERSION 3.10.0)

set(gtest_disable_pthreads ON)  
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Tests Test.cpp 
    ../searchEngineApp/src/InvertedIndex.cpp 
    ../searchEngineApp/src/SearchServer.cpp)
    
target_include_directories(Tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/searchEngineApp/include
)

target_link_libraries(Tests PRIVATE
    gtest_main
    gtest
)

target_include_directories(Tests PRIVATE ${CMAKE_SOURCE_DIR}/searchEngineApp)

include(GoogleTest)
gtest_discover_tests(Tests)