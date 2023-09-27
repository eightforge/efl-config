cmake_minimum_required(VERSION 3.13)

option(EFL_CONFIG_SINGLE "Enable the inclusion of `ConfigSingle.hpp`" OFF)

add_library(efl-config INTERFACE)
add_library(efl::config ALIAS efl-config)

target_include_directories(efl-config INTERFACE include)

if(EFL_CONFIG_SINGLE)
    target_include_directories(efl-config INTERFACE single-include)
endif()
unset(EFL_CONFIG_SINGLE CACHE)