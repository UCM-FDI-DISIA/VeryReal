@echo off

rem Directorios
set BAT_DIR=%~dp0

set FMOD_CORE_ORIGIN=%BAT_DIR%\src\api\core\lib\x64
set FMOD_STUDIO_ORIGIN=%BAT_DIR%\src\api\studio\lib\x64

set DLL_FOLDERS=%BAT_DIR%bin


rem Se crea el directorio si no está ya creado

if exist "%DLL_FOLDERS%" (
    rmdir /s /q "%DLL_FOLDERS%"
    mkdir "%DLL_FOLDERS%"
    echo Directorio existente borrado y recreado.
) else (
    mkdir "%DLL_FOLDERS%"
    echo Directorio creado.
)

    echo Copia de DLLs en Debug

    mkdir "%DLL_FOLDERS%\Debug"

    XCOPY /y /s "%FMOD_CORE_ORIGIN%\fmodL.dll" "%DLL_FOLDERS%\Debug\"
    XCOPY /y /s "%FMOD_STUDIO_ORIGIN%\fmodstudioL.dll" "%DLL_FOLDERS%\Debug\"
    echo Copia en %DLL_FOLDERS%\Debug completada

    echo Copia de DLLs en Release

    mkdir "%DLL_FOLDERS%\Release"

    XCOPY /y /s "%FMOD_CORE_ORIGIN%\fmod.dll" "%DLL_FOLDERS%\Release\"
    XCOPY /y /s "%FMOD_STUDIO_ORIGIN%\fmodstudio.dll" "%DLL_FOLDERS%\Release\"
    echo Copia en %DLL_FOLDERS%\Release completada

	

    echo Terminada la copia de DLLs de FMOD
pause