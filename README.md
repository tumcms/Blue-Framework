# BlueFramework3

## Info

BlueFramework3 compiles with Visual Studio 2015 x64 Update 3. Currently, we are not aiming at supporting any other compilers.

## License

Copyright (c) 2016 Technical University of Munich
Chair of Computational Modeling and Simulation.

BlueFramework is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License Version 3
as published by the Free Software Foundation.

BlueFramework is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

## Copyright notes
BlueFramework3 uses several software libraries. The corresponding licenses can be found in the Licenses folder distributed with this source code:

* boost 1.62.0 (http://www.boost.org/) (*Boost Software License*) ({root_dir}/Licenses/boost.LICENSE_1_0.txt)
* Eigen 3.3.0 (http://eigen.tuxfamily.org/) (*MPL2*) ({root_dir}/Licenses/Eigen.COPYING.MPL2)
* Google Test 1.7.0 (https://github.com/google/googletest) (*BSD 3-Clause License*) ({root_dir}/Licenses/GoogleTest.LICENSE)
* TinyXML-2 (https://github.com/leethomason/tinyxml2) (zlib license) ({root_dir}/Licenses/TinyXML-2.txt)
* Qt 5.7.0 (http://doc.qt.io/qt-5/lgpl.html) (LGPL version 3) ({root_dir}/Licenses/Qt.LGPL_version_3.txt)
* OGRE3D (http://www.ogre3d.org/) (MIT License) ({root_dir}/Licenses/OGRE3D.MIT.txt)
* json_spirit 4.08 (http://www.codeproject.com/Articles/20027/JSON-Spirit-A-C-JSON-Parser-Generator-Implemented) (MIT License)({root_dir}/Licenses/json_spirit.LICENSE.txt)

Some code has also been copied from the following projects:

* API DESIGN FOR C++ (http://www.apibook.com/) (MIT license) ({root_dir}/Licenses/apibook.LICENSE)
* appleseed (http://appleseedhq.net/) (MIT license) ({root_dir}/Licenses/appleseed.LICENSE.txt)
* CML (Configurable Math Library) (Boost Software License) ({root_dir}/Licenses/CML.LICENSE.txt)
* DirectX-Graphics-Samples (https://github.com/Microsoft/DirectX-Graphics-Samples) ({root_dir}/Licenses/DirectX-Graphics-Samples.LICENSE.txt)
* folly (https://github.com/facebook/folly) (Apache License Version 2.0) ({root_dir}/Licenses/folly.LICENSE.txt)
* GPUOpen-LibrariesAndSDKs/HelloD3D12 (https://github.com/GPUOpen-LibrariesAndSDKs/HelloD3D12) (BSD) ({root_dir}/Licenses/HelloD3D12.LICENSE.txt)
* Improved Console 5.0 (https://www.c-plusplus.net/code/ic/) ({root_dir}/Licenses/ic.License.txt)
* Nori Version 2 (https://github.com/wjakob/nori) (GPL v3) ({root_dir}/Licenses/Nori2.GPL_version_3.txt)
* Oryol (https://github.com/floooh/oryol) (MIT License) ({root_dir}/Licenses/Oryol.LICENSE)
* StackWalker (https://stackwalker.codeplex.com/) (New BSD License) ({root_dir}/Licenses/StackWalker.LICENSE.txt)
* tinyformat (https://github.com/c42f/tinyformat) (Boost Software License - Version 1.0) ({root_dir}/Licenses/tinyformat.LICENSE.txt)
* UtfConvert from  The LLVM Compiler Infrastructure (https://github.com/plenluno/convertutf/tree/19e1e918f4cb15bd8b61a26d00286688c6974f3b) (BSD) ({root_dir}/Licenses/LLVM_Release_License.txt)

Where appropriate the source code documents the original source.

> **Note**

> - BlueFramwork versions 0.4.1845 to 2.4.1077 where developed by Julian Amann and used code derived from niven that was not licensed in a correct way. The Copyright of niven belongs to Matthäus G. Chajdas. Those copyright issues have been fixed in this version (version 3.0.0 and up).
> - BlueFramework3 is developed by the Chair of Computational Modeling and Simulation of the Technical University of Munich. It is a complete rewrite.

## Documentation

### Coding

The code of BlueFramework3 should compile ~~compiles~~ with 0 ("zero") warnings at warning level 4 using Visual Studio 2015 x64 Update 3. Warnings form third party libraries are ignored.

### More
[Deployment](Docs/Deployment.md)

[Building](Docs/Building.md)

[Versioning](Docs/Versioning.md)

[UnitTests](Docs/UnitTests.md)