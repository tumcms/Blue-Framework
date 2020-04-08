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
	}
}