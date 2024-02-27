@echo off

rem Directorios
set BAT_DIR=%~dp0
set BULLET_SRC=%BAT_DIR%..\Bullet\Src
set BULLET_BUILD=%BAT_DIR%..\Bullet\Builds
set DLL_FOLDERS=%BAT_DIR%..\..\bin

rem Crear el directorio de compilación si no existe
if not exist "%BULLET_BUILD%" mkdir "%BULLET_BUILD%"

cd %BULLET_BUILD%

echo Configurando la compilacion de Bullet
cmake ^
  -G "Visual Studio 17 2022" ^
  -A x64 ^
  -D BUILD_BULLET2_DEMOS=OFF ^
  -D BUILD_BULLET3=ON ^
  -D BUILD_BULLET_ROBOTICS_EXTRA=OFF ^
  -D BUILD_BULLET_ROBOTICS_GUI_EXTRA=OFF ^
  -D BUILD_CLSOCKET=OFF ^
  -D BUILD_CONVEX_DECOMPOSITION_EXTRA=OFF ^
  -D BUILD_CPU_DEMOS=OFF ^
  -D BUILD_ENET=OFF ^
  -D BUILD_EXTRAS=ON ^
  -D BUILD_GIMPACTUTILS_EXTRA=OFF ^
  -D BUILD_HACD_EXTRA=OFF ^
  -D BUILD_INVERSE_DYNAMIC_EXTRA=OFF ^
  -D BUILD_OPENGL3_DEMOS=OFF ^
  -D BUILD_PYBULLET=OFF ^
  -D BUILD_SERIALIZE_EXTRA=OFF ^
  -D BUILD_SHARED_LIBS=ON ^
  -D BUILD_UNIT_TESTS=OFF ^
  -D USE_DOUBLE_PRECISION=ON ^
  -D USE_GRAPHICAL_BENCHMARK=OFF ^
  -D USE_GLUT=OFF ^
  -D USE_MSVC_RUNTIME_LIBRARY_DLL=ON ^
  -D USE_SOFT_BODY_MULTI_BODY_DYNAMICS_WORLD=ON ^
  -D CMAKE_INSTALL_PREFIX="C:\Program Files (x86)\BULLET_PHYSICS" ^
  -D LIBRARY_OUTPUT_PATH="%BAT_DIR%..\Bullet\Builds\lib" ^
  -D CMAKE_CONFIGURATION_TYPES="Debug;Release;MinSizeRel;RelWithDebInfo" ^
  -D CMAKE_DEBUG_POSTFIX="_Debug" ^
  -D CMAKE_MINSIZEREL_POSTFIX="_MinSizeRel" ^
  -D CMAKE_RELWITHDEBINFO_POSTFIX="_RelWithDebInfo" ^
  -S "%BULLET_SRC%" ^
  -B "%BULLET_BUILD%"

echo Compilando Bullet
cmake --build . --config Release
cmake --build . --config Debug

echo Copiando DLLs a la carpeta correspondiente
xcopy /y /s "%BULLET_BUILD%\lib\Release\*.dll" "%DLL_FOLDERS%\Bullet\release\"
xcopy /y /s "%BULLET_BUILD%\lib\Debug\*.dll" "%DLL_FOLDERS%\Bullet\debug\"

echo Compilacion y copia de archivos completadas.
pause
