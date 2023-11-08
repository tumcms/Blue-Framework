/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2023 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
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