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
#include <BlueFramework/Core/Version.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

namespace BlueFramework {
	struct Foo {
		static void foo() {
			BLUE_LOG(trace) << "A trace severity message";
			BLUE_LOG(debug) << "A debug severity message";
			BLUE_LOG(info) << "A info severity message";
			BLUE_LOG(warning) << "A warning severity message";
			// BLUE_LOG(error) << "A error severity message"; // generates Exception
			BLUE_LOG(fatal) << "A fatal severity message";

			BLUE_LOG(debug) << "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam "
			                   "voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit "
			                   "amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod te";
		}
	};
} // namespace BlueFramework

namespace {
	TEST(Logging, All) {
		BlueFramework::Core::initializeLogSystem(true, true);

		BlueFramework::Foo::foo();
		BLUE_LOG(trace) << "A trace severity message";
		BLUE_LOG(debug) << "A debug severity message";
		BLUE_LOG(info) << "A info severity message";
		BLUE_LOG(warning) << "A warning severity message";
		// BLUE_LOG(error) << "A error severity message"; // generates Exception
		BLUE_LOG(fatal) << "A fatal severity message";
	}
} // namespace