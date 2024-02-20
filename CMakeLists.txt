cmake_minimum_required(VERSION 3.16)
include_guard(DIRECTORY)

project(
  efl-config
  VERSION 1.2.3
  LANGUAGES CXX
)

option(EFL_CONFIG_SINGLE "Enable the inclusion of `ConfigSingle.hpp`" OFF)
option(EFL_PCH "Precompile `Config.hpp`" OFF)

add_library(__efl_config INTERFACE)
add_library(efl::config ALIAS __efl_config)
target_include_directories(__efl_config INTERFACE include)
target_compile_definitions(__efl_config INTERFACE EFL_CONFIG_VERSION="${PROJECT_VERSION}")

if(EFL_PCH)
  target_compile_definitions(__efl_config INTERFACE EFLI_CONFIG_PCH_=1)
  target_precompile_headers(__efl_config INTERFACE
    include/Config.hpp include/Undefs.hpp
  )
endif()

if(EFL_CONFIG_SINGLE)
  target_include_directories(__efl_config INTERFACE single-include)
endif()
