cmake_minimum_required(VERSION 3.10)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

project("palace-engine")

set(CMKE_CXX_STANDARD 20)

# -----------------------------------------------------------------------------
# Utilities
# -----------------------------------------------------------------------------
include(cmake/utilities.cmake)

# -----------------------------------------------------------------------------
# Compiler Warnings
# -----------------------------------------------------------------------------
include(cmake/project_warnings.cmake)
add_library(project-warnings INTERFACE)
set_project_warnings(project-warnings)

# -----------------------------------------------------------------------------
# Compile definitions
# -----------------------------------------------------------------------------
add_library(project-definitions INTERFACE)
target_compile_definitions(project-definitions INTERFACE
  $<$<CONFIG:Debug>:PALACE_DEBUG>
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_definitions(project-definitions INTERFACE PALACE_COMPILER_CLANG)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_definitions(project-definitions INTERFACE PALACE_COMPILER_GCC)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    target_compile_definitions(project-definitions INTERFACE PALACE_COMPILER_INTEL)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    target_compile_definitions(project-definitions INTERFACE PALACE_COMPILER_MSVC)
endif ()

# -----------------------------------------------------------------------------
# Source files
# -----------------------------------------------------------------------------
add_library("palace-engine" STATIC
        # Source files
        src/platform/platform_object.cpp
        src/platform/platform.cpp

        # Header files
        include/debug/assert.hpp
        include/memory/heap_allocator.hpp
        include/os/application_context.hpp
        include/platform/disable_warnings.hpp
        include/platform/enable_warnings.hpp
        include/platform/entry_point.hpp
        include/platform/platform.hpp
        include/platform/platform_detection.hpp
        include/platform/platform_includes.hpp
        include/platform/platform_object.hpp
        include/types/string.hpp
)

create_filter("debug" "debug")
create_filter("info" "info")
create_filter("math" "math")
create_filter("memory" "memory")
create_filter("os" "os")
create_filter("os\\windows" "os/windows")
create_filter("platform" "platform")
create_filter("public" "public")
create_filter("systems" "systems")
create_filter("types" "types")
create_filter("utility" "utility")

# =========================================================
# gtest

include(FetchContent)
FetchContent_Declare(
    googletest
    URL
    https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set_property(TARGET gmock PROPERTY FOLDER "gtest")
set_property(TARGET gmock_main PROPERTY FOLDER "gtest")
set_property(TARGET gtest PROPERTY FOLDER "gtest")
set_property(TARGET gtest_main PROPERTY FOLDER "gtest")

enable_testing()

add_executable("palace-engine-test"
    # Source files
    test/sanity_test.cpp

    # Head files
)

target_link_libraries("palace-engine-test" PRIVATE
    gtest_main
    project-warnings
)

include(GoogleTest)
gtest_discover_tests("palace-engine-test")
