/*! \verbatim
*  \copyright      Copyright (c) 2016 Technical University of Munich
*                  Chair of Computational Modeling and Simulation. All rights reserved.
*  \brief          This file is part of the BlueFramework.
*  \endverbatim
*/

#include <BlueFramework/Core/Version.h>
#include <BlueFramework/Core/Diagnostics/log.h>
#include <BlueFramework/Core/Singleton.h>
#include <BlueFramework/Core/Exception.h>
#include <BlueFramework/Cheetah/Core/Renderer.h>
#include <gtest/gtest.h>
#include <string>
#include <iostream>

namespace {
	TEST(AmbientOcclusion, Cheetah) {
		BlueFramework::Core::initializeLogSystem(true, true);

		buw::raytrace();
	}
}