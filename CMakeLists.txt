cmake_minimum_required(VERSION 3.16)
project(game_engine_workspace)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Dist" CACHE STRING "" FORCE)

# Output directory structure: bin/<Config>/<Project>
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(INT_DIR ${CMAKE_BINARY_DIR}/bin-int)

# Include subdirectories (order matters)
add_subdirectory(game_engine/vendor/GLFW)
add_subdirectory(game_engine/vendor/Glad)
add_subdirectory(game_engine)
add_subdirectory(Sandbox)
