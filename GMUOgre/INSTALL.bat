@echo off

REM Set environment variable %OGRE_HOME%

setx OGRE_HOME %cd%\Ogre

REM Copy .cfg files to %OGRE_HOME%

copy "Configs\Debug\" "%OGRE_HOME%\bin\Debug\"
copy "Configs\Release\" "%OGRE_HOME%\bin\Release\"

