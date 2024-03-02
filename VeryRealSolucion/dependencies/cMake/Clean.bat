
set BAT_DIR=%~dp0
set OGRE_BUILD=%BAT_DIR%..\Ogre\Builds
set BULLET_BUILD=%BAT_DIR%..\Bullet\Builds
set LUA_BUILD=%BAT_DIR%..\Lua\Builds
set BIN_DIR=%BAT_DIR%..\..\bin\

echo Borrando build de OGRE...
if exist %OGRE_BUILD% rmdir /s /q %OGRE_BUILD%
echo Build de OGRE borradas.

echo Borrando build de BULLET...
if exist %BULLET_BUILD% rmdir /s /q %BULLET_BUILD%
echo Build de BULLET borradas.

echo Borrando build de LUA...
if exist %LUA_BUILD% rmdir /s /q %LUA_BUILD%
echo Build de LUA borradas.

echo Borrando BIN...
if exist "%BIN_DIR%" (
    rem Navega a la ruta especificada
    pushd "%BIN_DIR%"
    
    rem Itera sobre cada archivo en la ruta
    for %%f in (*) do (
        rem Comprueba si el archivo actual no es la carpeta "Assets" ni tiene la extensión .cfg
        if "%%f" neq "Assets" (
            if "%%~xf" neq ".cfg" (
                rem Realiza una acción con cada archivo que no es la carpeta "Assets" ni tiene la extensión .cfg
                echo Eliminando archivo: %%f
                rem Elimina el archivo actual
                del "%%f"
                rem Puedes agregar aquí cualquier acción adicional que desees realizar después de eliminar el archivo
            )
        )
    )

    rem Regresa al directorio anterior
    popd
) else (
    echo La ruta especificada no existe.
)
echo BIN borrada.

echo Borrado listo.

