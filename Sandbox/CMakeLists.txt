project(Sandbox)

add_executable(Sandbox)

# Source files
file(GLOB_RECURSE SANDBOX_SRC CONFIGURE_DEPENDS src/*.cpp src/*.h)
target_sources(Sandbox PRIVATE ${SANDBOX_SRC})

# Includes
target_include_directories(Sandbox PRIVATE
    ${CMAKE_SOURCE_DIR}/game_engine/vendor/spdlog/include
    ${CMAKE_SOURCE_DIR}/game_engine/src
)

# Link with the engine
target_link_libraries(Sandbox PRIVATE game_engine)

# Definitions
target_compile_definitions(Sandbox PRIVATE GE_PLATFORM_WINDOWS)

# Output dirs
set_target_properties(Sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}/$<CONFIG>/Sandbox"
    ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}/$<CONFIG>/Sandbox"
    LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}/$<CONFIG>/Sandbox"
)

# Config-specific definitions
foreach(FLAG IN ITEMS Debug Release Dist)
    string(TOUPPER ${FLAG} FLAG_UPPER)
    target_compile_definitions(Sandbox PRIVATE
        $<$<CONFIG:${FLAG}>:GE_${FLAG_UPPER}>
    )
endforeach()
