cmake_minimum_required(VERSION 4.1)
project(una)

include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
        raylib
        GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
        GIT_TAG "master"
        GIT_PROGRESS TRUE
)

FetchContent_Declare(
        lua
        GIT_REPOSITORY "https://gitlab.com/codelibre/lua/lua-cmake.git"
        GIT_TAG "lua-cmake-5.4"
)


set(raylib_USE_STATIC_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(lua)

set(SOURCES
        src/main.cpp
        src/world/world.cpp
)
set(HEADERS
        include/game/world/world.h
        src/utils/numbers.cpp
        include/game/utils/numbers.h
        include/game/world/element.h
        include/game/world/elements/solid.h
        include/game/world/elements/gas.h
        include/game/world/elements/liquid.h
        include/game/world/elements/solid/movable.h
        include/game/world/elements/solid/immovable.h
        include/game/world/elements/solid/movable/sand.h
        src/world/elements/solid/movable/sand.cpp
        src/world/element.cpp
        src/world/elements/liquid/water.cpp
        include/game/world/elements/liquid/water.h
)

set(CMAKE_CXX_STANDARD 20)

add_executable(una ${SOURCES} ${HEADERS})

target_include_directories(una
        PUBLIC
        include
)

set_property(TARGET una PROPERTY C_STANDARD 17)

target_link_libraries(una PRIVATE raylib)
target_link_libraries(una PRIVATE lua_library)