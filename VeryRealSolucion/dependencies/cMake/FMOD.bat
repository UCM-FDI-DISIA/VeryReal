@echo off

rem Directorios
set BAT_DIR=%~dp0

set FMOD_CORE_ORIGIN=%BAT_DIR%\src\api\core\lib\x64
set FMOD_STUDIO_ORIGIN=%BAT_DIR%\src\api\studio\lib\x64

set DLL_FOLDERS=%BAT_DIR%..\..\bin


rem Se crea el directorio si no está ya creado

if exist "%DLL_FOLDERS%" (
    echo Directorio existente
) else (
    mkdir "%DLL_FOLDERS%"
    echo Directorio creado.
)

    echo Copia de DLLs en Debug

    mkdir "%DLL_FOLDERS%"

    XCOPY /y /s "%FMOD_CORE_ORIGIN%\fmodL.dll" "%DLL_FOLDERS%"
    XCOPY /y /s "%FMOD_STUDIO_ORIGIN%\fmodstudioL.dll" "%DLL_FOLDERS%"
    echo Copia en %DLL_FOLDERS% completada

    echo Copia de DLLs en Release

    mkdir "%DLL_FOLDERS%"

    XCOPY /y /s "%FMOD_CORE_ORIGIN%\fmod.dll" "%DLL_FOLDERS%"
    XCOPY /y /s "%FMOD_STUDIO_ORIGIN%\fmodstudio.dll" "%DLL_FOLDERS%"
    echo Copia en %DLL_FOLDERS% completada

	

    echo Terminada la copia de DLLs de FMOD
pause