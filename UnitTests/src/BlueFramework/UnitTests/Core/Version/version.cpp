/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2019 Technical University of Munich
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
*/

#include <BlueFramework/Core/Diagnostics/log.h>
#include <BlueFramework/Core/Exception.h>
#include <BlueFramework/Core/Singleton.h>
#include <BlueFramework/Core/Version.h>
#include <BlueFramework/Core/filesystem.h>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>

#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

namespace {
	TEST(Version, Major) {
		EXPECT_TRUE(BlueFramework::Core::Version::getMajor() >= 3);

		std::vector<std::string> fileList = buw::getFileList("C:\\dev\\BlueFramework3\\Core\\src");

		std::ofstream ofs("C:\\dev\\BlueFramework3\\Tools\\runCLangFormat.bat", std::ofstream::out);

		for (auto filename : fileList) {
		    // ignore some core files
		    if (boost::algorithm::ends_with(filename, "ic\\ic.cpp") 
				|| boost::algorithm::ends_with(filename, "StackWalker.cpp")
		        || boost::algorithm::ends_with(filename, "StackWalker.h")
		        || boost::algorithm::ends_with(filename, "UtfConverter\\ConvertUTF.cpp")
		        || boost::algorithm::ends_with(filename, "UtfConverter\\ConvertUTF.h")
		        || boost::algorithm::ends_with(filename, "UtfConverter\\ConvertUTF.cpp")
		        || boost::algorithm::ends_with(filename, "UtfConverter\\CVTUTF7.cpp")
				|| boost::algorithm::ends_with(filename, "UtfConverter\\CVTUTF7.h")
				|| boost::algorithm::ends_with(filename, "tinyformat.h"))
			    continue;

		    if (boost::algorithm::ends_with(filename, ".cpp") || boost::algorithm::ends_with(filename, ".h")) {
				ofs << "C:\\dev\\CMakeDemos\\tools\\clang-format.exe " << filename << " > " << filename << "_XXXX" << std::endl;
				ofs << "del " << filename << std::endl;
				ofs << "move " << filename << "_XXXX " << filename << std::endl;
			}
		}

		ofs.close();
	}
}