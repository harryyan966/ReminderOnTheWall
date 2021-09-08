cmake_minimum_required (VERSION 3.8)

# default build type
if (NOT CMAKE_BUILD_TYPE)
   set (CMAKE_BUILD_TYPE "RelWithDebInfo")
   message (
      STATUS "Using default build type: ${CMAKE_BUILD_TYPE}"
   )
endif ()

# specify the C++ standard 
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# the project
project (generate-wallpaper VERSION 1.0.0)
configure_file (${PROJECT_SOURCE_DIR}/include/generate-wallpaper.h.in ${PROJECT_SOURCE_DIR}/include/generate-wallpaper.h)

# Dependencies
find_package (OpenCV REQUIRED)                                  # OpenCV
add_subdirectory ("${PROJECT_SOURCE_DIR}/3rdparty/libconfig")   # libconfig

# set binary output path
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)
set (CMKAE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${PROJECT_SOURCE_DIR}/bin)
# add the executable
add_executable (generate-wallpaper ${PROJECT_SOURCE_DIR}/source/generate-wallpaper.cpp)

# include paths
include_directories (${PROJECT_SOURCE_DIR}/include
                     ${OpenCV_INCLUDE_DIRS}
                     "${PROJECT_SOURCE_DIR}/3rdparty/libconfig/lib")

# OpenCV libs
link_directories (${OpenCV_LIBRARY_DIRS})
target_link_libraries (generate-wallpaper ${OpenCV_LIBS})

# libconfig
link_directories (${CMAKE_BINARY_DIR}/out/${CMAKE_BUILD_TYPE})
target_link_libraries (generate-wallpaper libconfig++)

message (${CMAKE_INSTALL_LIBDIR})