# Set cmake minimum version.
cmake_minimum_required(VERSION 3.15)

# Set the project details.
set(PROJECT_NAME tests)
project(${PROJECT_NAME} LANGUAGES C)

# Set build type to debug by default.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Define the executable.
add_executable(${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)

# Find dependencies.
find_package(OpenGL REQUIRED)

# Add source files.
target_sources(${PROJECT_NAME} PRIVATE
        #This thing goes brrrrrooooooooommmmmmmm
        main.c
        )

# Include project header files.
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (MSVC)
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# Set compile flags.
target_compile_options(${PROJECT_NAME} PRIVATE
        # Clang
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Weverything -fcolor-diagnostics
        # Disable specific warnings.
        -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
        -Wno-deprecated-declarations -Wno-exit-time-destructors
        -Wno-switch-enum -Wno-weak-vtables -Wno-global-constructors>
        # GCC
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always>
        # Visual Studio
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        # Enable the clang sanitizer.
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>,$<PLATFORM_ID:${SANITIZER_OS}>>:${SANITIZER_FLAGS}>
        )

if (LINUX)
    target_link_libraries(${PROJECT_NAME} PRIVATE -lm -ldl -lpthread)
endif()

# Include and link against dependencies.
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL OpenGL::GLU glfw stb BigBalls::Physics lua ${CMAKE_DL_LIBS})