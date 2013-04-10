# the name of your project
project(qt-patcher)

# minimum version of cmake.
cmake_minimum_required(VERSION 2.8.7)
set(CMAKE_VERBOSE_MAKEFILE false)

# platform settings
include(cmake/PlatformSettings.cmake)

include(cmake/ConfigureArtifactPath.cmake)
set_common_artifact_path()

# Common compiler settings
include(cmake/CommonCompilerFlags.cmake)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(src)
