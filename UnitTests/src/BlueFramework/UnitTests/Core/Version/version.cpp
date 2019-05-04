/*! \verbatim
*  \copyright      Copyright (c) 2019 Technical University of Munich
*                  Chair of Computational Modeling and Simulation. All rights reserved.
*  \brief          This file is part of the BlueFramework.
*  \endverbatim
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