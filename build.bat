@echo off
echo making folder 'build' if build doesn't exist
if not exist build mkdir build

echo go into build 
pushd build

echo dir cuz I want to see what is happening behind the scenes

dir

echo vcvars64 resets enviornment variables for making the correct builds

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"

echo cl configuration

cl

echo starting commands

cl /EHsc /NODEFAULTLIB: "msvcrt.lib" "libcmt.lib" "msvcrtd.lib" /MT /I "../dependencies\include" ../main.cpp ../renderer.cpp ../vertexbuffer.cpp ../indexbuffer.cpp /link /LIBPATH:"../dependencies\lib" opengl32.lib glfw3.lib glew32s.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib /out:main.exe

echo come out from build

popd