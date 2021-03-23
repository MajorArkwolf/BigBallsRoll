# Set compile flags.
target_compile_options(${PROJECT_NAME} PRIVATE
        # Clang
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Wno-everything>
        # GCC
        $<$<CXX_COMPILER_ID:GNU>:-w>
        # Visual Studio
        $<$<CXX_COMPILER_ID:MSVC>:/W0>
)
add_subdirectory(lua)
add_subdirectory(Physics)
add_subdirectory(stb)
cmake_policy(PUSH)
OPTION(BUILD_PROGRAMS OFF)
OPTION(BUILD_EXAMPLES OFF)
OPTION(BUILD_TESTING OFF)
cmake_policy(SET CMP0077 OLD)
set(CMAKE_POLICY_DEFAULT_CMP0077 OLD)
add_subdirectory(libsndfile)
cmake_policy(POP)
OPTION(ALSOFT_UTILS OFF)
OPTION(ALSOFT_EXAMPLES OFF)
OPTION(ALSOFT_NO_CONFIG_UTIL ON)
OPTION(ALSOFT_INSTALL OFF)
OPTION(ALSOFT_INSTALL_CONFIG OFF)
OPTION(ALSOFT_INSTALL_UTILS OFF)
add_subdirectory(openal)
OPTION(BUILD_SHARED_LIBS OFF)
OPTION(GLFW_BUILD_EXAMPLES OFF)
OPTION(GLFW_BUILD_TESTS OFF)
OPTION(GLFW_BUILD_DOCS OFF)
OPTION(GLFW_INSTALL OFF)
add_subdirectory(glfw)
add_subdirectory(libcester)
