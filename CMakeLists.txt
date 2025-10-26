cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(FirstGame)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++ -pthread")

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  endif()
endif()

# Our Project

add_executable(FirstGame main.cpp
        functions.cpp
        functions.h
        main.h
        Player.cpp
        Player.h
        Macros.h
        Entity.cpp
        Entity.h
        EntityList.cpp
        EntityList.h
        EntityNode.cpp
        EntityNode.h
        Location.cpp
        Location.h
        Enemy.cpp
        Enemy.h
        DrawingFunctions.cpp
        DrawingFunctions.h
        SetupAndCleanUp.cpp
        SetupAndCleanUp.h
        Menu.cpp
        Menu.h
        AttackMenu.cpp
        AttackMenu.h
        Tile.cpp
        Tile.h
        Room.cpp
        Room.h
)
#set(raylib_VERBOSE 1)
target_link_libraries(FirstGame PRIVATE raylib)
target_include_directories(FirstGame PRIVATE ${raylib_SOURCE_DIR}/src)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    set_target_properties(${FirstGame} PROPERTIES SUFFIX ".html") # Tell Emscripten to build an example.html file.
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${FirstGame} "-framework IOKit")
    target_link_libraries(${FirstGame} "-framework Cocoa")
    target_link_libraries(${FirstGame} "-framework OpenGL")
endif()

add_custom_command(TARGET FirstGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/ImagesforGame"
        "$<TARGET_FILE_DIR:FirstGame>/ImagesforGame"
)