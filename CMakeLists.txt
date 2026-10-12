cmake_minimum_required(VERSION 3.15)
project(BallGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

# --- raylib ---
find_package(raylib QUIET)

if(raylib_FOUND)
    message(STATUS "Using system-installed raylib")
else()
    message(STATUS "System raylib not found, fetching from GitHub...")
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.5
        GIT_SHALLOW    TRUE
    )
    FetchContent_MakeAvailable(raylib)
endif()

# --- Sources ---
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(game ${GAME_SOURCES})

target_include_directories(game PRIVATE src)

target_link_libraries(game PRIVATE raylib)

# --- Platform ---
if(APPLE)
    target_link_libraries(game PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreFoundation"
        "-framework CoreGraphics"
        "-framework OpenGL"
    )
endif()

if(WIN32)
    target_link_libraries(game PRIVATE winmm)
endif()

if(UNIX AND NOT APPLE)
    target_link_libraries(game PRIVATE m pthread dl)
endif()

# --- Windows CLANG64: static link runtime so no libc++/libgcc DLLs are needed ---
if(MINGW AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_link_options(game PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
    )
endif()
