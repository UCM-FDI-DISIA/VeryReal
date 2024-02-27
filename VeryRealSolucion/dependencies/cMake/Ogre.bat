@echo off

rem Directorios
set BAT_DIR=%~dp0
set OGRE_SRC=%BAT_DIR%..\Ogre\src
set OGRE_BUILD=%BAT_DIR%..\Ogre\Builds\
set OGRE_SLN=%BAT_DIR%..\Ogre\Builds\OGRE.sln
set DLL_FOLDERS=%BAT_DIR%..\..\bin
rem Se crea el directorio si no está ya creado

    mkdir %OGRE_BUILD%

    cmake ^
        -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
        -D OGRE_BUILD_COMPONENT_BITES:BOOL=FALSE ^
	-D OGRE_BUILD_COMPONENT_BULLET:BOOL="0" ^
 	-D OGRE_BUILD_COMPONENT_CSHARP:BOOL=FALSE ^
 	-D OGRE_BUILD_COMPONENT_JAVA:BOOL=FALSE ^
	-D OGRE_BUILD_COMPONENT_MESHLODGENERATOR:BOOL=TRUE ^
	-D OGRE_BUILD_COMPONENT_OVERLAY:BOOL=TRUE ^
 	-D OGRE_BUILD_COMPONENT_OVERLAY_IMGUI:BOOL=TRUE ^
 	-D OGRE_BUILD_COMPONENT_PAGING:BOOL=TRUE ^
 	-D OGRE_BUILD_COMPONENT_PROPERTY:BOOL=TRUE ^
 	-D OGRE_BUILD_COMPONENT_PYTHON:BOOL=FALSE ^
 	-D OGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL=TRUE ^
        -D OGRE_BUILD_COMPONENT_TERRAIN:BOOL=TRUE ^
        -D OGRE_BUILD_COMPONENT_VOLUME:BOOL=TRUE ^
 	-D OGRE_BUILD_DEPENDENCIES:BOOL=TRUE ^
 	-D OGRE_BUILD_MSVC_MP:BOOL=TRUE ^
	-D OGRE_BUILD_MSVC_ZM:BOOL=TRUE ^
        -D OGRE_BUILD_PLUGIN_ASSIMP:BOOL=TRUE ^
        -D OGRE_BUILD_PLUGIN_BSP:BOOL=TRUE ^
        -D OGRE_BUILD_PLUGIN_DOT_SCENE:BOOL=FALSE ^
        -D OGRE_BUILD_PLUGIN_GLSLANG:BOOL=FALSE ^
        -D OGRE_BUILD_PLUGIN_OCTREE:BOOL=TRUE ^
        -D OGRE_BUILD_PLUGIN_PCZ:BOOL=TRUE ^
        -D OGRE_BUILD_PLUGIN_PFX:BOOL=TRUE ^
        -D OGRE_BUILD_PLUGIN_RSIMAGE:BOOL=FALSE ^
        -D OGRE_BUILD_PLUGIN_STBI:BOOL=TRUE ^
        -D OGRE_BUILD_RENDERSYSTEM_D3D11:BOOL=FALSE ^
        -D OGRE_BUILD_RENDERSYSTEM_GL:BOOL=TRUE ^
	-D OGRE_BUILD_RENDERSYSTEM_GL3PLUS:BOOL=FALSE ^
        -D OGRE_BUILD_RENDERSYSTEM_GLES2:BOOL=FALSE ^
	-D OGRE_BUILD_RENDERSYSTEM_TINY:BOOL=FALSE ^
	-D OGRE_BUILD_RENDERSYSTEM_VULKAN:BOOL=FALSE ^
	-D OGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL=TRUE ^
	-D OGRE_BUILD_TOOLS:BOOL=TRUE ^
    -D OGRE_CONFIG_ENABLE_QUAD_BUFFER_STEREO:BOOL=FALSE ^
    -D OGRE_CONFIG_FILESYSTEM_UNICODE:BOOL=TRUE ^
    -D OGRE_ENABLE_PRECOMPILED_HEADERS:BOOL=TRUE ^
    -D OGRE_INSTALL_DEPENDENCIES:BOOL=TRUE ^
    -D OGRE_INSTALL_DOCS:BOOL=TRUE ^
    -D OGRE_INSTALL_PDB:BOOL=TRUE ^
    -D OGRE_INSTALL_TOOLS:BOOL=TRUE ^
    -D OGRE_INSTALL_VSPROPS:BOOL=FALSE ^
    -D OGRE_NODELESS_POSITIONING:BOOL=FALSE ^
    -D OGRE_PROJECT_FOLDERS:BOOL=TRUE ^
    -S %OGRE_SRC% -B %OGRE_BUILD%

    cd %OGRE_BUILD%
    rem Compilacion de la solucion en Debug y en Release
    msbuild "OGRE.sln" /p:configuration=Debug /maxcpucount
    msbuild "OGRE.sln" /p:configuration=Release /maxcpucount
    
    
    XCOPY /y /s .\bin\debug\OgreMain_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %OGRE_MAIN_D%
    XCOPY /y /s .\bin\release\OgreMain.dll %DLL_FOLDERS%\RomeRender\release\
       echo %OGRE_MAIN%
    XCOPY /y /s .\bin\debug\OgreRTShaderSystem_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %OGRERTSHADERSYSTEM_D%
    XCOPY /y /s .\bin\release\OgreRTShaderSystem.dll %DLL_FOLDERS%\RomeRender\release\
       echo %OGRERTSHADERSYSTEM%
    XCOPY /y /s .\bin\debug\Codec_STBI_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %CODEC_D%
    XCOPY /y /s .\bin\release\Codec_STBI.dll %DLL_FOLDERS%\RomeRender\release\
       echo %CODEC%
    XCOPY /y /s .\bin\debug\OgreMeshLodGenerator_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %OGREMESH_D%
    XCOPY /y /s .\bin\release\OgreMeshLodGenerator.dll %DLL_FOLDERS%\RomeRender\release\
       echo %OGREMESH%
    XCOPY /y /s .\bin\debug\OgreOverlay_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %OGREOVERLAY_D%
    XCOPY /y /s .\bin\release\OgreOverlay.dll %DLL_FOLDERS%\RomeRender\release\
       echo %OGREOVERLAY%
    XCOPY /y /s .\bin\debug\OgrePaging_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %OGREPAGING_D%
    XCOPY /y /s .\bin\release\OgrePaging.dll %DLL_FOLDERS%\RomeRender\release\
       echo %OGREPAGING%
    XCOPY /y /s .\bin\debug\OgreProperty_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %OGREPROPERY_D%
    XCOPY /y /s .\bin\release\OgreProperty.dll %DLL_FOLDERS%\RomeRender\release\
       echo %OGREPROPERY%
    XCOPY /y /s .\bin\debug\OgreTerrain_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %OGRETERRAIN_D%
    XCOPY /y /s .\bin\release\OgreTerrain.dll %DLL_FOLDERS%\RomeRender\release\
       echo %OGRETERRAIN%
    XCOPY /y /s .\bin\debug\OgreVolume_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %OGREVOLUME_D%
    XCOPY /y /s .\bin\release\OgreVolume.dll %DLL_FOLDERS%\RomeRender\release\
       echo %OGREVOLUME%
    XCOPY /y /s .\bin\debug\Plugin_BSPSceneManager_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %PLUGINBSPS_D%
    XCOPY /y /s .\bin\release\Plugin_BSPSceneManager.dll %DLL_FOLDERS%\RomeRender\release\
       echo %PLUGINBSPS%
    XCOPY /y /s .\bin\debug\Plugin_OctreeSceneManager_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %PLUGINOCTREE_D%
    XCOPY /y /s .\bin\release\Plugin_OctreeSceneManager.dll %DLL_FOLDERS%\RomeRender\release\
       echo %PLUGINOCTREE%
    XCOPY /y /s .\bin\debug\Plugin_OctreeZone_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %PLUGINOCTREEZONE_D%
    XCOPY /y /s .\bin\release\Plugin_OctreeZone.dll %DLL_FOLDERS%\RomeRender\release\
       echo %PLUGINOCTREEZONE%
    XCOPY /y /s .\bin\debug\Plugin_ParticleFX_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %PLUGINPARTICLE%
    XCOPY /y /s .\bin\release\Plugin_ParticleFX.dll %DLL_FOLDERS%\RomeRender\release\
       echo %PLUGINPARTICLE%
    XCOPY /y /s .\bin\debug\Plugin_PCZSceneManager_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %PLUGINPCZ_D%
    XCOPY /y /s .\bin\release\Plugin_PCZSceneManager.dll %DLL_FOLDERS%\RomeRender\release\
       echo %PLUGINPCZ%
    XCOPY /y /s .\bin\debug\RenderSystem_GL_d.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %RENDERSYSTEMGL_D%
    XCOPY /y /s .\bin\release\RenderSystem_GL.dll %DLL_FOLDERS%\RomeRender\release\
       echo %RENDERSYSTEMGL%
    XCOPY /y /s .\bin\debug\zlib.dll %DLL_FOLDERS%\RomeRender\debug\
       echo %ZLIB%
    XCOPY /y /s .\bin\release\SDL2.dll %DLL_FOLDERS%\SDL2\
       echo %DLL_FOLDERS%
	


if exist .\bullet3-3.25 (
    rd /s /q .\bullet3-3.25
) else (
    echo La carpeta no existe.
)


    echo Terminada la build de Ogre
pause