# Set cmake minimum version.
cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME libcester)
project(${PROJECT_NAME} LANGUAGES C)

add_library(${PROJECT_NAME} INTERFACE)
#set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
#set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
#target_sources(${PROJECT_NAME} PRIVATE .)
target_include_directories(${PROJECT_NAME} INTERFACE .)
