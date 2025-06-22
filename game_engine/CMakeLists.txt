project(game_engine)

add_library(game_engine SHARED)

# Precompiled headers
target_precompile_headers(game_engine PRIVATE src/gepch.h)

# Source files
file(GLOB_RECURSE ENGINE_SRC CONFIGURE_DEPENDS src/*.cpp src/*.h)
target_sources(game_engine PRIVATE ${ENGINE_SRC})

# Include directories
target_include_directories(game_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/game_engine/vendor/GLFW/include
    ${CMAKE_SOURCE_DIR}/game_engine/vendor/Glad/include
)

# Link libraries
target_link_libraries(game_engine
    PUBLIC
    GLFW
    Glad
    opengl32
)

# Platform and config-specific settings
target_compile_definitions(game_engine
    PRIVATE
    # GE_PLATFORM_WINDOWS
    GE_BUILD_DLL
    GLFW_INCLUDE_NONE
)

# Output dirs
set_target_properties(game_engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/$<CONFIG>/game_engine"
    ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}/$<CONFIG>/game_engine"
    LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}/$<CONFIG>/game_engine"
)

# Post-build: Copy DLL to Sandbox/bin
add_custom_command(TARGET game_engine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:game_engine> ${OUTPUT_DIR}/$<CONFIG>/Sandbox
)

# Config-specific definitions
foreach(FLAG IN ITEMS Debug Release Dist)
    string(TOUPPER ${FLAG} FLAG_UPPER)
    target_compile_definitions(game_engine PRIVATE
        $<$<CONFIG:${FLAG}>:GE_${FLAG_UPPER}>
    )
endforeach()
