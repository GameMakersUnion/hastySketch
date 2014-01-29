@echo off

REM Set environment variable %OGRE_HOME%

setx OGRE_HOME %cd%\Ogre

REM Copy .cfg files to %OGRE_HOME%

copy "Configs\DebugCfg\" "%OGRE_HOME%\bin\Debug\"
copy "Configs\ReleaseCfg\" "%OGRE_HOME%\bin\Release\"

