# Copyright (C) 2020 Tero Koskinen <tero.koskinen@iki.fi>
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
#
# Example CMake invocation, using LLVM/CLang, Windows SDK, and Ninja
#
# set PATH=c:\llvm\llvm10\bin;C:\Program Files\CMake\bin;%PATH%
# "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" amd64
# mkdir build
# cd build
# cmake -DCMAKE_C_COMPILER=clang-cl -GNinja ..
# ninja

cmake_minimum_required(VERSION 3.5)
project (Lua)

option(SHARED_LIB "Build lua.dll instead of lua.lib" OFF)

set(LUA_CORE_SRC src/lapi.c src/lcode.c src/lctype.c src/ldebug.c src/ldo.c src/ldump.c src/lfunc.c src/lgc.c src/llex.c src/lmem.c src/lobject.c src/lopcodes.c src/lparser.c src/lstate.c src/lstring.c src/ltable.c src/ltm.c src/lundump.c src/lvm.c src/lzio.c)
set(LUA_LIB_SRC src/lauxlib.c src/lbaselib.c src/lcorolib.c src/ldblib.c src/liolib.c src/lmathlib.c src/loadlib.c src/loslib.c src/lstrlib.c src/ltablib.c src/lutf8lib.c src/linit.c)

if (SHARED_LIB)
  add_library(lua SHARED ${LUA_CORE_SRC} ${LUA_LIB_SRC})
else()
  add_library(lua STATIC ${LUA_CORE_SRC} ${LUA_LIB_SRC})
endif()

# Definir los nombres de las DLLs según la configuración
set_target_properties(lua PROPERTIES 
    DEBUG_OUTPUT_NAME lua_d
    RELEASE_OUTPUT_NAME lua
)

add_executable(luai ${LUA_CORE_SRC} ${LUA_LIB_SRC} src/lua.c src/lua.c)

if (WIN32)
target_compile_definitions(lua PRIVATE "-DLUA_COMPAT_5_3 -DLUA_BUILD_AS_DLL -DLUA_USE_WINDOWS")
target_compile_definitions(luai PRIVATE "-DLUA_COMPAT_5_3 -DLUA_USE_WINDOWS")
else()
target_compile_definitions(lua PRIVATE "-DLUA_COMPAT_5_3 -DLUA_BUILD_AS_DLL")
target_compile_definitions(luai PRIVATE "-DLUA_COMPAT_5_3")
endif()
