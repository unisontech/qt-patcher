# the name of your project
project(qt-patcher)

# minimum version of cmake.
# Qt Version wrapper requires cmake 2.8.10 due to use of qt4_use_modules
cmake_minimum_required(VERSION 2.8.10)
set(CMAKE_VERBOSE_MAKEFILE true)

# platform settings
include(cmake/PlatformSettings.cmake)

include(cmake/ConfigureArtifactPath.cmake)
set_common_artifact_path()


# Common compiler settings
include(cmake/CommonCompilerFlags.cmake)


# Qt Framework
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC TRUE)
# find and setup Qt for this project
include(cmake/QtVersionWrapper.cmake)

find_qtX("4.8.0")

add_subdirectory(src)
