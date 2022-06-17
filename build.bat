@echo off
cls
color 8

set CONFIG=debug
@echo Building with "%CONFIG%" configuration...

set SOURCES=main.cpp external\imgui\imgui*.cpp
set LINK= external/SDL2/lib/*.lib external/everything/lib/Everything64.lib opengl32.lib winmm.lib gdi32.lib shell32.lib

REM /DUNICODE /D_UNICODE /utf-8
IF %CONFIG%==debug set CFLAGS=/MP /MTd /EHsc /Zi /FC /nologo /W1 /Od
IF %CONFIG%==sanitize set CFLAGS=/MP /MTd /EHsc /Zi /FC /nologo /W1 /Od /fsanitize=address
IF %CONFIG%==release set CFLAGS=/MP /MT /EHsc /FC /nologo /W1 /O2

set BUILD_DIR=/Fdbuild\ /Fobuild\
set EXE=build/out.exe

cl %CFLAGS% %BUILD_DIR% /Fe%EXE% /Iinclude %SOURCES% /link %LINK% /SUBSYSTEM:CONSOLE

IF %ERRORLEVEL% EQU 0 @echo ----------BUILD OK----------
color 6
