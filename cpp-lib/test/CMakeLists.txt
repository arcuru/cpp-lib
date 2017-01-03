# Basic CMake project
cmake_minimum_required(VERSION 2.8.11)

# Set default build type to Release
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release.")
    set(CMAKE_BUILD_TYPE "Release")
endif()

project(cpp-lib CXX)

# Enable compiler specific flags
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "(Clang|GNU|GCC)")
    add_definitions("-std=c++1z -Wall -Wextra -Wpedantic -Werror")
endif()
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_definitions("-fcolor-diagnostics")
endif()

# Add boost libraries
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework)

foreach(proj
        adjacency_list
        flat_set
        lru_cache
        trie
        union_find
    )

    # Find the project files
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../${proj}.cpp)
        set(proj_cpp ../${proj}.cpp)
    else()
        set(proj_cpp "")
    endif()

    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../${proj}.hpp)
        set(proj_hpp ../${proj}.hpp)
    else()
        set(proj_hpp "")
    endif()

    # Unit Tests?
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${proj}_test.cpp)

        # Build executable from sources and headers
        add_executable(${proj}_test ${proj_cpp} ${proj_hpp} ${proj}_test.cpp)

        # We need boost includes
        target_include_directories(${proj}_test PRIVATE ${Boost_INCLUDE_DIRS} ..)

        # We need boost libraries
        target_link_libraries(${proj}_test ${Boost_LIBRARIES})

        # Run the tests on every build
        add_custom_command(TARGET ${proj}_test POST_BUILD COMMAND ${proj}_test)

    endif()

    # Benchmarks?
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${proj}_benchmark.cpp)

        # Add benchmark executable
        add_executable(${proj}_benchmark ${proj_cpp} ${proj_hpp} ${proj}_benchmark.cpp)

        # We need boost includes
        target_include_directories(${proj}_benchmark PRIVATE ${Boost_INCLUDE_DIRS} ..)

        # We need boost libraries
        target_link_libraries(${proj}_benchmark ${Boost_LIBRARIES})

    endif()

endforeach(proj)
