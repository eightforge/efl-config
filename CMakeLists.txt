cmake_minimum_required(VERSION 3.13)
include_guard(DIRECTORY)

project(
    efl-config
    VERSION 1.0.1
    LANGUAGES CXX
)

option(EFL_CONFIG_SINGLE "Enable the inclusion of `ConfigSingle.hpp`" OFF)

add_library(__efl_config INTERFACE)
add_library(efl::config ALIAS __efl_config)
target_include_directories(__efl_config INTERFACE include)

if(EFL_CONFIG_SINGLE)
    target_include_directories(__efl_config INTERFACE single-include)
endif()