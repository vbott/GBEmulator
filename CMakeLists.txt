cmake_minimum_required (VERSION 2.8)

project(GBemulator)
set(TARGET_NAME gbe)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

set(CMAKE_MACOSX_RPATH 1)

### SDL
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

set(SRCS
	main.cpp
	GBEmulator.hpp
	GBEmulator.cpp
	SDLInputModule.cpp
	SDLInputModule.hpp
	RendererModule.cpp
	RendererModule.hpp
)

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	if(APPLE)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	endif()
	add_definitions (-DID_HIERARCHY_LIST)
    if (CMAKE_COMPILER_IS_GNUCXX)
		add_definitions (-march=native -mtune=native -msse4.2)
		set (CMAKE_EXE_LINKER_FLAGS "-Wl,-O1,--sort-common,--as-needed,-z,relro")
		set (CMAKE_SHARED_LINKER_FLAGS "-Wl,-O1,--sort-common,--as-needed,-z,relro")
		set (CMAKE_MODULE_LINKER_FLAGS "-Wl,-O1,--sort-common,--as-needed,-z,relro")
    endif()
endif(UNIX)
if(WIN32)
	add_definitions (/MP)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /LARGEADDRESSAWARE")
endif()

##### Setting the output directory for the solution
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

add_executable(
	${TARGET_NAME}
	${SRCS}
)

include_directories (
	${SDL2_INCLUDE_DIR}
	"./"
)

if (APPLE)
	set (EXTRA_LIB pthread /usr/local/lib/libopus.dylib /usr/local/lib/libopenal.dylib /usr/local/lib/liblua5.1.dylib /usr/local/lib/libluabind.dylib)
	include_directories("/usr/local/include/lua-5.1/")
elseif(UNIX)
	include_directories("/usr/include/lua5.1/")
	set (EXTRA_LIB dl rt pthread opus openal luabind lua5.1)
else()
	include_directories ("C:/Development/Environment/openal-soft-1.17.2-bin/include/")
	set (EXTRA_LIB "C:/Development/Environment/openal-soft-1.17.2-bin/libs/Win32/libOpenAL32.dll.a")
	
	set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
	set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
endif()

target_link_libraries(
	${TARGET_NAME}
	${SDL2_LIBRARY}
	${SDL_IMAGE_LIBRARIES}
	${EXTRA_LIB}
)
