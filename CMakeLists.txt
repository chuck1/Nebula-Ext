CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)

INCLUDE($ENV{HOME}/.config.cmake)

PROJECT(nebula_ext)

FIND_PACKAGE(CMakeHelper)
FIND_PACKAGE(glfw)
FIND_PACKAGE(PhysX)
FIND_PACKAGE(maze)

FIND_PACKAGE(Galaxy COMPONENTS
	std
	log
	console
	REQUIRED)

FIND_PACKAGE(Nebula COMPONENTS
	core
	physx
	gfx
	final
	REQUIRED)

FIND_PACKAGE(Boost 1.55 COMPONENTS
	python
	REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -D_DEBUG -std=c++0x")

INCLUDE_DIRECTORIES("/usr/include/python2.7")
include_directories("/usr/include/freetype2")
include_directories("./maze/include")
include_directories("./glm")
#include_directories(${physx_INCLUDE_DIR})

link_directories("./maze/Debug")

ADD_DEFINITIONS("-D_DEBUG -DGAL_NET_USE_BOOST -DGLM_FORCE_RADIANS")

SET(libs ${libs}
	${Nebula_LIBRARIES}
	${Galaxy_LIBRARIES}
	${Boost_LIBRARIES}
	glfw3
	GL
	GLU
	GLEW
	freetype
	png
	rt
	pthread
	X11
	Xrandr
	Xi
	Xcursor
	)

cmh_static_library()

ADD_SUBDIRECTORY(test)

set(CPACK_GENERATOR "DEB")
include(CPack)


