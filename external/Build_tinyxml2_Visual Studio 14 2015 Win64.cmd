set dest=C:\thirdparty\vs2015\x64
set cmake_command=cmake
if NOT [%1]==[] set dest=%~1
if NOT [%2]==[] set cmake_command="%~2"
wget.exe --no-check-certificate https://github.com/leethomason/tinyxml2/archive/master.zip -O %cd%\master.zip
7za.exe x %cd%\master.zip -o%dest%
del %cd%\master.zip
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" amd64
C:
cd %dest%\tinyxml2-master
%cmake_command% ^
-DBUILD_STATIC_LIBS=ON ^
-G "Visual Studio 14 2015 Win64" ^
-H%dest%\tinyxml2-master ^
-B%dest%\tinyxml2-master\build
cd %dest%\tinyxml2-master\build
%cmake_command% --build . --config Debug --target tinyxml2_static
%cmake_command% --build . --config Release --target tinyxml2_static
%cmake_command% --build . --config RelWithDebInfo --target tinyxml2_static