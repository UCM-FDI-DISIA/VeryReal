call Clean.bat
 echo CLEAN
call Ogre.bat
 echo OGRE
call Bullet.bat
 echo BULLET
call Lua.bat
 echo LUA
call FMOD.bat
 echo FMOD
msbuild "VeryReal.sln" /p:configuration=Debug
msbuild "VeryReal.sln" /p:configuration=Release