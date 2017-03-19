@echo off
cls

set DRIVE_LETTER =%1:
set MESH_NAME=%2
set GAME_PATH=%DRIVE_LETTER%/Users/Wade/Downloads

set OGRE_PATH=%GAME_PATH%/ogre_src_v1-8-1
set BOOST_PATH=%GAME_PATH%/boost_1_63_0
set FREEIMAGE_PATH=%GAME_PATH%/FreeImage3170WIN32WIN64/lib
set ZLIB_PATH=%GAME_PATH%/zlib-1.2.11
set TDM=%DRIVE_LETTER%/TDM-GCC-64

set PATH=%TDM%/bin;%OGRE_PATH%/build/bin;%BOOST_PATH%/stage/lib;%ZLIB_PATH%/lib;%FREEIMAGE_PATH%;c:/windows

OgreXMLConverter %MESH_NAME%.mesh.xml
OgreMeshUpgrader %MESH_NAME%.mesh