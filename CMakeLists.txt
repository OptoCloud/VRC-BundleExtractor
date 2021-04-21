cmake_minimum_required(VERSION 3.5)

set(project VRCE)
project(
    ${project}
    DESCRIPTION "Exports vrchat avatars"
    LANGUAGES CXX
)

# --- Configure default build ---
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
# --------------------------------

# --- Simplify build checking ---
math(EXPR VPTR_BITS "${CMAKE_SIZEOF_VOID_P}*8") # Convert 4/8 -> 32/64

if(UNIX AND NOT APPLE)
        set(BUILD_OS "linux")
        set(BUILD_OSL "linux")
elseif(WIN32)
        set(BUILD_OS "win")
        set(BUILD_OSL "windows")
endif()

string(TOLOWER ${CMAKE_CXX_COMPILER_ID} BUILD_COMPILER)

# Translate some stuff
if (${BUILD_COMPILER} STREQUAL "gnu")
  set(BUILD_COMPILER "gcc")
elseif (${BUILD_COMPILER} STREQUAL "intel")
  set(BUILD_COMPILER "icc")
endif()
# --------------------------------

# --- Set global C++ CMake settings ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
if(VERBOSE)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()
# -------------------------------

# --- Set compiler flags ---
# Debugging, and warnings
add_definitions(-DBUILDER_STATIC_DEFINE)
if(NOT ${CMAKE_BUILD_TYPE} MATCHES "Release")
    add_definitions(-DDEBUG)
    set(BUILD_TYPE "dbg")

    if(MSVC)
        # Remove all previously declared flags before adding new ones
        string(REGEX REPLACE "[/-]W[0-4] ?" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

        # Verboseeeee
        string(APPEND CMAKE_CXX_FLAGS " -Wall")
    else()
        # Verboseeeee
        string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra -pedantic -Wformat=2 -Wsign-conversion -Wundef -Wredundant-decls -Wwrite-strings -Wpointer-arith -Wcast-qual -Wmissing-include-dirs -Wcast-align -Wctor-dtor-privacy -Wdisabled-optimization -Winvalid-pch -Woverloaded-virtual -Wconversion -Wswitch-enum -Wno-ctor-dtor-privacy -Wno-format-nonliteral -Wnoexcept -Wno-dangling-else -Wno-unused-local-typedefs -Wdouble-promotion -Wtrampolines -Wzero-as-null-pointer-constant -Wuseless-cast -Wvector-operation-performance -Wsized-deallocation -Wshadow -Wshift-overflow=2 -Wnull-dereference -Wduplicated-cond")
    endif()
else()
    set(BUILD_TYPE "rel")
endif()

# Optimization and compiler specific fixes
if(MSVC)
    # Remove all previously declared flags before adding new ones
    string(REGEX REPLACE "[/-][ML][DT]d? ?" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    string(REGEX REPLACE "[/-]O[12bdgistxy] ?" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    string(REGEX REPLACE "[/-]DEBUG:[a-zA-Z]+ ?" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})

    # Enable max warnings (But dont spam the console)
    string(APPEND CMAKE_CXX_FLAGS " -DNOMINMAX -wo9025 -wo5054")

    if(${CMAKE_BUILD_TYPE} MATCHES "Release")
        string(APPEND CMAKE_CXX_FLAGS " -MT -DEBUG:NONE -O2")
    else()
        string(APPEND CMAKE_CXX_FLAGS " -MTd -DEBUG:FULL -Od")
    endif()
else()
    # 64-bit, and threading
    string(APPEND CMAKE_CXX_FLAGS " -m64 -pthread")

    if(${CMAKE_BUILD_TYPE} MATCHES "Release")
        string(APPEND CMAKE_CXX_FLAGS " -fstack-protector -O3 -g0")
        if (NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            string(APPEND CMAKE_CXX_FLAGS " -s")
        endif()
    else()
        string(APPEND CMAKE_CXX_FLAGS " -O0 -g3")
    endif()
endif()
# --------------------------

# -- Set global libraries --
if(WIN32)
    set(WIN_LIBS ws2_32 winmm Rpcrt4 Iphlpapi)
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

link_libraries(
    Threads::Threads
    ${CMAKE_DL_LIBS}
    ${WIN_LIBS}
    )
# --------------------------

message("Configuring ${project}...")

# --- Build ---
set(${project}_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/stream.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ibinaryreader.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/endianreader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/binaryreader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bundlereader.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/hash128.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/version.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fileidentifier.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bundlescene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bundleheader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/filescheme.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fileschemelist.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bundlefilescheme.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bundlerawwebheader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bundlefilestreamheader.cpp
)
set(${project}_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/stream.h
    ${CMAKE_CURRENT_SOURCE_DIR}/vecstreambuf.h

    ${CMAKE_CURRENT_SOURCE_DIR}/ibinaryreader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/ibundlereadable.h

    ${CMAKE_CURRENT_SOURCE_DIR}/endianreader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/binaryreader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/bundlereader.h

    ${CMAKE_CURRENT_SOURCE_DIR}/hash128.h
    ${CMAKE_CURRENT_SOURCE_DIR}/readerhelpers.h
    ${CMAKE_CURRENT_SOURCE_DIR}/bundleflags.h
    ${CMAKE_CURRENT_SOURCE_DIR}/endiantype.h
    ${CMAKE_CURRENT_SOURCE_DIR}/endianswap.h
    ${CMAKE_CURRENT_SOURCE_DIR}/version.h
    ${CMAKE_CURRENT_SOURCE_DIR}/versiontype.h
    ${CMAKE_CURRENT_SOURCE_DIR}/fileentrytype.h
    ${CMAKE_CURRENT_SOURCE_DIR}/fileidentifier.h
    ${CMAKE_CURRENT_SOURCE_DIR}/bundletype.h
    ${CMAKE_CURRENT_SOURCE_DIR}/compressiontype.h
    ${CMAKE_CURRENT_SOURCE_DIR}/bundlescene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/bundleheader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/filescheme.h
    ${CMAKE_CURRENT_SOURCE_DIR}/fileschemelist.h
    ${CMAKE_CURRENT_SOURCE_DIR}/bundleversion.h
    ${CMAKE_CURRENT_SOURCE_DIR}/bundlefilescheme.h
    ${CMAKE_CURRENT_SOURCE_DIR}/bundlerawwebheader.h
    ${CMAKE_CURRENT_SOURCE_DIR}/bundlefilestreamheader.h
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/include
)

add_executable(${project}
    main.cpp
    ${${project}_HEADERS}
    ${${project}_SOURCES}
)

target_link_directories(${project} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/static
)

target_link_libraries(${project} PRIVATE
    lz4
    lzma
)
