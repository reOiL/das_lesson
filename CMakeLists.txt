cmake_minimum_required(VERSION 3.21)

project(dasLesson)

# Set RelWithDebInfo cause das plugin isn't work in other configuration
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Build type" FORCE)

set(CMAKE_CXX_STANDARD 17)

# Disable unused deeps
set(DAS_BUILD_TUTORIAL NO)
set(DAS_BUILD_TEST NO)
set(DAS_BUILD_PROFILE NO)
set(DAS_STDDLG_DISABLED ON)
set(DAS_STBIMAGE_DISABLED ON)
set(DAS_STBTRUETYPE_DISABLED ON)
set(DAS_GLFW_DISABLED ON)
set(DAS_CLANG_BIND_DISABLED ON)
set(DAS_BUILD_TOOLS NO)

add_subdirectory(daScript)
include_directories(daScript/include)
