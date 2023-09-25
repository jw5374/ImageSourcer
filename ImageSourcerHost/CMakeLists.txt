# === From https://cliutils.gitlab.io/modern-cmake/chapters/basics/example.html ===

# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.1...3.27)

SET(CMAKE_CXX_COMPILER C:/ProgramData/chocolatey/lib/mingw/tools/install/mingw64/bin/g++.exe) # JW: sets the c++ compiler
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON) # JW: generates the compile_commands.json used with clangd LSP
SET(LIBRARY_PATH "${CMAKE_SOURCE_DIR}/lib")
SET(CMAKE_CXX_STANDARD 14)

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables

# JW: Project name potentially needs to match the directory of the project?
project(
	ImageSourcerHost
	VERSION 1.0
	LANGUAGES CXX)

find_package(exiv2 CONFIG REQUIRED)

# JW: This adds the binary targets you want the source to build to
add_executable(imsrc main.cpp)
add_executable(create_reg_key create_reg.cpp)

# JW: Making build static so it can be standalone
# JW: This is to mitigate the json parsing library issues mentioned
target_link_libraries(imsrc -static)
target_link_libraries(imsrc exiv2lib)

target_include_directories(imsrc PUBLIC ${LIBRARY_PATH})
