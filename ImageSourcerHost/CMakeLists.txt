# === From https://cliutils.gitlab.io/modern-cmake/chapters/basics/example.html ===

# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.1...3.27)

SET(CMAKE_CXX_COMPILER C:/ProgramData/chocolatey/lib/mingw/tools/install/mingw64/bin/g++.exe) # JW: sets the c++ compiler
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON) # JW: generates the compile_commands.json used with clangd LSP

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables

# JW: Project name potentially needs to match the directory of the project?
project(
	ImageSourcerHost
	VERSION 1.0
	LANGUAGES CXX)

# JW: This adds the binary targets you want the source to build to
add_executable(imsrc main.cpp)
add_executable(create_reg_key create_reg.cpp)
