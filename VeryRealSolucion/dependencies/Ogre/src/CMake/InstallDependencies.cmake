#-------------------------------------------------------------------
# This file is part of the CMake build system for OGRE
#     (Object-oriented Graphics Rendering Engine)
# For the latest info, see http://www.ogre3d.org/
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

#####################################################
# Install dependencies 
#####################################################

set(OGRE_DEP_DIR ${OGREDEPS_PATH})

set(INITVAL FALSE)
if(WIN32 OR APPLE OR EMSCRIPTEN)
  set(INITVAL TRUE)
endif()
option(OGRE_INSTALL_DEPENDENCIES "Install dependency libs needed for samples" ${INITVAL})
cmake_dependent_option(OGRE_COPY_DEPENDENCIES "Copy dependency libs to the build directory" TRUE "WIN32" FALSE)

macro(install_debug INPUT)
  if (EXISTS ${OGRE_DEP_DIR}/bin/debug/${INPUT})
    if (IS_DIRECTORY ${OGRE_DEP_DIR}/bin/debug/${INPUT})
      install(DIRECTORY ${OGRE_DEP_DIR}/bin/debug/${INPUT} DESTINATION bin/debug CONFIGURATIONS Debug)
    else ()
      install(FILES ${OGRE_DEP_DIR}/bin/debug/${INPUT} DESTINATION bin/debug CONFIGURATIONS Debug)
    endif ()
  else()
    message(send_error "${OGRE_DEP_DIR}/bin/debug/${INPUT} did not exist, can't install!")
  endif ()
endmacro()

macro(install_release INPUT)
  if (EXISTS ${OGRE_DEP_DIR}/bin/release/${INPUT})
    if (IS_DIRECTORY ${OGRE_DEP_DIR}/bin/release/${INPUT})
      install(DIRECTORY ${OGRE_DEP_DIR}/bin/release/${INPUT} DESTINATION bin/release CONFIGURATIONS Release None "")
      install(DIRECTORY ${OGRE_DEP_DIR}/bin/release/${INPUT} DESTINATION bin/relwithdebinfo CONFIGURATIONS RelWithDebInfo)
      install(DIRECTORY ${OGRE_DEP_DIR}/bin/release/${INPUT} DESTINATION bin/minsizerel CONFIGURATIONS MinSizeRel)
    else ()
      install(FILES ${OGRE_DEP_DIR}/bin/release/${INPUT} DESTINATION bin/release CONFIGURATIONS Release None "")
      install(FILES ${OGRE_DEP_DIR}/bin/release/${INPUT} DESTINATION bin/relwithdebinfo CONFIGURATIONS RelWithDebInfo)
      install(FILES ${OGRE_DEP_DIR}/bin/release/${INPUT} DESTINATION bin/minsizerel CONFIGURATIONS MinSizeRel)
    endif ()
  else()
    message(send_error "${OGRE_DEP_DIR}/bin/release/${INPUT} did not exist, can't install!")
  endif ()
endmacro()

macro(copy_debug INPUT)
  if (EXISTS ${OGRE_DEP_DIR}/lib/debug/${INPUT})
    if (MINGW OR NMAKE)
      configure_file(${OGRE_DEP_DIR}/lib/debug/${INPUT} ${PROJECT_BINARY_DIR}/lib/${INPUT} COPYONLY)
	else ()
      if (IS_DIRECTORY ${OGRE_DEP_DIR}/lib/debug/${INPUT})
        install(DIRECTORY ${OGRE_DEP_DIR}/lib/debug/${INPUT} DESTINATION lib/debug)
      else ()
        configure_file(${OGRE_DEP_DIR}/lib/debug/${INPUT} ${PROJECT_BINARY_DIR}/lib/debug/${INPUT} COPYONLY)
      endif ()
	endif ()
  endif ()
endmacro()

macro(copy_release INPUT)
  if (EXISTS ${OGRE_DEP_DIR}/lib/release/${INPUT})
    if (MINGW OR NMAKE)
      configure_file(${OGRE_DEP_DIR}/lib/release/${INPUT} ${PROJECT_BINARY_DIR}/lib/${INPUT} COPYONLY)
	else ()
      if (IS_DIRECTORY ${OGRE_DEP_DIR}/lib/release/${INPUT})
        install(DIRECTORY ${OGRE_DEP_DIR}/lib/release/${INPUT} DESTINATION lib/release CONFIGURATIONS Release None "")
        install(DIRECTORY ${OGRE_DEP_DIR}/lib/release/${INPUT} DESTINATION lib/relwithdebinfo CONFIGURATIONS RelWithDebInfo)
        install(DIRECTORY ${OGRE_DEP_DIR}/lib/release/${INPUT} DESTINATION lib/minsizerel CONFIGURATIONS MinSizeRel)
      else ()
        configure_file(${OGRE_DEP_DIR}/lib/release/${INPUT} ${PROJECT_BINARY_DIR}/lib/release/${INPUT} COPYONLY)
        configure_file(${OGRE_DEP_DIR}/lib/release/${INPUT} ${PROJECT_BINARY_DIR}/lib/relwithdebinfo/${INPUT} COPYONLY)
        configure_file(${OGRE_DEP_DIR}/lib/release/${INPUT} ${PROJECT_BINARY_DIR}/lib/minsizerel/${INPUT} COPYONLY)
      endif ()
	endif ()
  endif ()
endmacro ()

if (OGRE_INSTALL_DEPENDENCIES)
  if (OGRE_STATIC)
    # for static builds, projects must link against all Ogre dependencies themselves, so copy full include and lib dir
    if (EXISTS ${OGRE_DEP_DIR}/include/)
      install(DIRECTORY ${OGRE_DEP_DIR}/include/ DESTINATION include)
    endif ()
    
    if (EXISTS ${OGRE_DEP_DIR}/lib/)
        install(DIRECTORY ${OGRE_DEP_DIR}/lib/ DESTINATION ${OGRE_LIB_DIRECTORY})
    endif ()
  else ()
    if(WIN32 AND MINGW)
      install(FILES DESTINATION lib/debug CONFIGURATIONS Debug)
      install(FILES DESTINATION lib/relwithdebinfo CONFIGURATIONS RelWithDebInfo)
      install(FILES DESTINATION lib/release CONFIGURATIONS Release)
      install(FILES DESTINATION lib/minsizerel CONFIGURATIONS MinSizeRel)
    elseif(UNIX)
      if (EXISTS ${OGRE_DEP_DIR}/lib/)
        install(DIRECTORY ${OGRE_DEP_DIR}/lib/ DESTINATION ${OGRE_LIB_DIRECTORY})
      endif()
    endif()

    if (EXISTS ${OGRE_DEP_DIR}/bin/)
      install(DIRECTORY ${OGRE_DEP_DIR}/bin/ DESTINATION ${OGRE_BIN_DIRECTORY})
    endif ()
  endif ()

  if(OGRE_BUILD_DEPENDENCIES AND OGRE_BUILD_COMPONENT_BULLET)
    install(DIRECTORY ${OGRE_DEP_DIR}/include/bullet DESTINATION include)
  endif()

  if(WIN32)
    if(OGRE_BUILD_SAMPLES OR OGRE_BUILD_TESTS)
      if(EXISTS "${SDL2_BINARY}")
        file(COPY ${SDL2_BINARY} DESTINATION ${PROJECT_BINARY_DIR}/bin/debug)
        file(COPY ${SDL2_BINARY} DESTINATION ${PROJECT_BINARY_DIR}/bin/release)
        file(COPY ${SDL2_BINARY} DESTINATION ${PROJECT_BINARY_DIR}/bin/relwithdebinfo)
        file(COPY ${SDL2_BINARY} DESTINATION ${PROJECT_BINARY_DIR}/bin/minsizerel)
      endif()
    endif()

    if (OGRE_BUILD_PLUGIN_CG)
      # if MinGW or NMake, the release/debug cg.dll's would conflict, so just pick one
      if (MINGW OR (CMAKE_GENERATOR STREQUAL "NMake Makefiles"))
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
          install_debug(cg.dll)
        else ()
          install_release(cg.dll)
        endif ()
      else ()
        install_debug(cg.dll)
        install_release(cg.dll)
      endif ()
    endif () # OGRE_BUILD_PLUGIN_CG

    # install GLES2 dlls
    if (OGRE_BUILD_RENDERSYSTEM_GLES2)
      install_debug(libGLESv2.dll)
      install_release(libEGL.dll)
    endif ()
  endif () # WIN32
endif ()

if (OGRE_COPY_DEPENDENCIES)
  # copy the required DLLs to the build directory
  file(GLOB DLLS ${OGRE_DEP_DIR}/bin/*.dll)
  file(COPY ${DLLS} DESTINATION ${PROJECT_BINARY_DIR}/bin/debug)
  file(COPY ${DLLS} DESTINATION ${PROJECT_BINARY_DIR}/bin/release)
  file(COPY ${DLLS} DESTINATION ${PROJECT_BINARY_DIR}/bin/relwithdebinfo)
  file(COPY ${DLLS} DESTINATION ${PROJECT_BINARY_DIR}/bin/minsizerel)

  if (OGRE_BUILD_PLUGIN_CG)
    if (EXISTS ${Cg_BINARY_DBG} AND EXISTS ${Cg_BINARY_REL})
      # if MinGW or NMake, the release/debug cg.dll's would conflict, so just pick one
      if (MINGW OR (CMAKE_GENERATOR STREQUAL "NMake Makefiles"))
        if (CMAKE_BUILD_TYPE STREQUAL "Debug")
          file(COPY ${Cg_BINARY_DBG} DESTINATION ${PROJECT_BINARY_DIR}/bin/debug)
        else ()
          file(COPY ${Cg_BINARY_REL} DESTINATION ${PROJECT_BINARY_DIR}/bin/release)
          file(COPY ${Cg_BINARY_REL} DESTINATION ${PROJECT_BINARY_DIR}/bin/relwithdebinfo)
          file(COPY ${Cg_BINARY_REL} DESTINATION ${PROJECT_BINARY_DIR}/bin/minsizerel)
        endif ()
      else ()
          file(COPY ${Cg_BINARY_DBG} DESTINATION ${PROJECT_BINARY_DIR}/bin/debug)
        file(COPY ${Cg_BINARY_REL} DESTINATION ${PROJECT_BINARY_DIR}/bin/release)
        file(COPY ${Cg_BINARY_REL} DESTINATION ${PROJECT_BINARY_DIR}/bin/relwithdebinfo)
        file(COPY ${Cg_BINARY_REL} DESTINATION ${PROJECT_BINARY_DIR}/bin/minsizerel)
      endif ()
    endif()
  endif()
endif ()
