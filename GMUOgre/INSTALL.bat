@echo off

REM Setting Temp OGRE_HOME variable to access it in
REM same cmd context

set OGRE_HOME=%cd%\Ogre

REM Set environment variable %OGRE_HOME%

REM Referencing setx.exe so user doesn't need to add PATH

C:\Windows\System32\setx.exe OGRE_HOME "%cd%\Ogre"

REM Copy .cfg files to %OGRE_HOME%

copy "Configs\DebugCfg\" "%OGRE_HOME%\bin\Debug\"
copy "Configs\ReleaseCfg\" "%OGRE_HOME%\bin\Release\"

