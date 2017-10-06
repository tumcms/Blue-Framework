set dest=C:\thirdparty\vs2017\x64
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"
wget.exe --no-check-certificate https://sourceforge.net/projects/glew/files/glew/2.0.0/glew-2.0.0.zip/download -O%cd%\glew-2.0.0.zip
7za.exe x %cd%\glew-2.0.0.zip -o%dest%
%cmake_command% -G"Visual Studio 15 2017 Win64" -H%dest%\glew-2.0.0\build\cmake -B%dest%\glew-2.0.0\build
del  %cd%\glew-2.0.0.zip
C:
cd %dest%\glew-2.0.0\build
%cmake_command% --build . --config Debug --target glew_s
%cmake_command% --build . --config Release --target glew_s
%cmake_command% --build . --config RelWithDebInfo --target glew_s