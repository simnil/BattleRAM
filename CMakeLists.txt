cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project("BattleRAM")

# Version number
set(BattleRAM_VERSION_MAJOR 0)
set(BattleRAM_VERSION_MINOR 1)


if(MSVC)
	# MSVC compiler flags
	set(CMAKE_CXX_FLAGS "/W4 /Zi /EHsc /wd4514 /wd4668 /wd4710 /wd4711 /wd4820")
	set(CMAKE_CXX_FLAGS_RELEASE "/02 /NDEBUG")
	set(CMAKE_CXX_FLAGS_DEBUG "/Od /DEBUG")
else()
	# GCC / CLANG compiler flags
	set(CMAKE_CXX_FLAGS "-Wall -Wextra -Zi -Wno-c++11-extensions -std=c++11 -pthread")
	set(CMAKE_CXX_FLAGS_RELEASE "-02")
	set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
endif()

# Set up directories
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(EXTERNALS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals)
set(CMAKE_MODULES ${CMAKE_CURRENT_LIST_DIR}/cmake)

# Add cmake modules to module path.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_MODULES})

# Pass some CMake settings (Version number)
configure_file(
	"${SRC_DIR}/BattleRamConfig.hpp.in"
	"${SRC_DIR}/BattleRamConfig.hpp"
)

# Link SDL2
find_package(SDL2 REQUIRED)

# GLEW
add_definitions(-DGLEW_STATIC)
add_subdirectory(${EXTERNALS_DIR}/glew)

# OpenGL
find_package(OpenGL REQUIRED)

# Include directories
include_directories(
	${SRC_DIR}
	${INCLUDE_DIR}
	${SDL2_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${OPENGL_INCLUDE_DIRS}
)


# Source files

set(SOURCE_MATH
	${INCLUDE_DIR}/sini/math/Vector.hpp
	${INCLUDE_DIR}/sini/math/Vector.inl
	${INCLUDE_DIR}/sini/math/Matrix.hpp
	${INCLUDE_DIR}/sini/math/Matrix.inl
	${INCLUDE_DIR}/sini/math/Graph.hpp
	${INCLUDE_DIR}/sini/math/Node.hpp
)
source_group(sini_math FILES ${SOURCE_MATH})

set(SOURCE_UTIL
	${INCLUDE_DIR}/sini/util/GridTile.hpp
	    ${SRC_DIR}/sini/util/GridTile.cpp
	${INCLUDE_DIR}/sini/util/Grid.hpp
	    ${SRC_DIR}/sini/util/Grid.cpp
	${INCLUDE_DIR}/sini/util/Pathfinder.hpp
	${INCLUDE_DIR}/sini/util/Pathfinder.inl
)
source_group(sini_util FILES ${SOURCE_UTIL})

set(SOURCE_ALL
	${INCLUDE_DIR}/sini/CudaCompat.hpp
	${SRC_DIR}/test.cpp
	${SOURCE_MATH}
	${SOURCE_UTIL}
)



# Executable
add_executable(BattleRAM ${SOURCE_ALL})

# Link libraries
target_link_libraries(
	BattleRAM

	${SDL2_LIBRARY}
	${GLEW_LIBRARIES}
	${OPENGL_LIBRARIES}
)


message("Binary output directory: " ${CMAKE_BINARY_DIR}/bin)
install(TARGETS BattleRAM DESTINATION ${CMAKE_BINARY_DIR}/bin)

if(MSVC)
	file(COPY dll/SDL2.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug)

	file(COPY dll/SDL2.dll DESTINATION ${CMAKE_BINARY_DIR}/Release)
endif()