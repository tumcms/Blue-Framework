# Building

## Prerequisites for Windows

### Get the source code

Checkout the source from Bitbucket (https://bitbucket.org/tumcms/blueframework3-public) using the Mercurial Hg version control system. Mercurial is a distributed source control management tool. It can be downloaded from http://mercurial.selenic.com/. After installing you can clone a repository. For instance, to clone the Eigen repository (https://bitbucket.org/eigen/eigen) you can type `hg clone ssh://hg@bitbucket.org/eigen/eigen `into a console window or you can use the graphical user interface:

![TortoiseHg](images/thgui.png)

Now you can specify a source and a destination.

![TortoiseHg](images/thgui2.png)

After pressing the ```Clone``` button the repository is cloned to the destination folder. Procede in the same way with the BlueFramework repository.

To check out the source code of the BlueFramwork proced as describe in the following instructions:

1. Install mercurial from http://mercurial.selenic.com/. It comes with TortoiseHg on Windows:
![TortoiseHg](images/thg.png)
2. Now clone the code by typing `hg clone https://bitbucket.org/tumcms/blueframework3-public`

### Third-party dependencies

Install the following third-party libraries

1. Windows 10 SDK (https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk)

2. Boost: 1.63.0: Download a prebuild version from https://sourceforge.net/projects/boost/files/boost-binaries/1.63.0/ or build it yourself. For the second option you can use BlueGo see https://bitbucket.org/Vertexwahn/bluego)
Not all parts of boost are required. You just need: filesystem, python, signals and system.
![BlueGo](images/BlueGo.png)
Building Boost can take some time and consumes a lot of disk space. To build it faster with less memory wastage you can build only the parts of boost that are needed. Use this command:
`C:\thirdparty\vs2013\x64\boost_1_57_0>b2 address-model=64 toolset=msvc-12.0 --build-type=complete stage --with-filesystem --with-signals --with-system --with-date_time --with-regex`

3. Qt 5.8.0 from https://www.qt.io/

4. LunarG Vulkan SDK 1.0.39.1 from https://www.lunarg.com/vulkan-sdk/

- Start CMake (https://cmake.org/) and select as source folder the previous checked out BlueFramework3 folder

## How to build BlueFramework with CMake Step by Step

BlueFramework version 3.0.0.0 and up compiles with Visual Studio 2015 x64 Update 3. Currently, we are not aiming at supporting any other compilers.

Start CMake select where the source code is located and where to build the binaries: