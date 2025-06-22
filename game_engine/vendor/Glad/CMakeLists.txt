cmake_minimum_required(VERSION 3.15)
project(Glad C)

# Set output directories for binaries and intermediates
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-x64)
set(OBJ_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin-int/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-x64)

# Create static library target
add_library(Glad STATIC
    include/glad/glad.h
    include/KHR/khrplatform.h
    src/glad.c
)

# Set include directories
target_include_directories(Glad PUBLIC include)

# Set the output directories
set_target_properties(Glad PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
    INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
)

# Windows-specific settings
if (WIN32)
    set_target_properties(Glad PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
endif()

# Disable warnings (for GCC/Clang and MSVC)
if (MSVC)
    target_compile_options(Glad PRIVATE /w)
else()
    target_compile_options(Glad PRIVATE -w)
endif()
