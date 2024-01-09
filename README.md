# efl::config

This is the core directory for my build system. The structure is likely to change over time.
I will be (and currently am) using this for compatibility in my other projects.

## CMake Usage

CMake integration is very simple. When added to a project, ``efl::config``
will be defined. If the option ``CMAKE_CONFIG_SINGLE`` is enabled, 
``ConfigSingle.hpp`` will be included alongside the efl header.

## Standalone Usage [DEPRECATED]

``ConfigSingle.hpp`` has drag-and-drop capabilities, just add it anywhere in
your own projects. Just keep in mind it will majorly pollute the namespace.
