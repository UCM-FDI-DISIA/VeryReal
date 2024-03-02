set BAT_DIR=%~dp0
call Clean.bat
 echo CLEAN

cd %BAT_DIR%

call Ogre.bat
 echo OGRE

cd %BAT_DIR%

call Bullet.bat
 echo BULLET

cd %BAT_DIR%

call Lua.bat
 echo LUA

cd %BAT_DIR%

call FMOD.bat
 echo FMOD

cd %BAT_DIR%


cd ..\..\
msbuild "VeryRealSolucion.sln" /p:configuration=Debug
msbuild "VeryRealSolucion.sln" /p:configuration=Release