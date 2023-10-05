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

#pragma once

#include <chrono>
#include <type_traits>

#include "BlueFramework/Core/namespace.h"

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

class Stopwatch final {
public:
	Stopwatch() {
		reset();
	}

	void reset() {
		reset_time = clock.now();
	}

	std::chrono::duration<float> elapsed() {
		typedef std::chrono::duration<float> Duration;
	
		Duration fs = reset_time - clock.now();

		return fs;
	}

private:
	std::chrono::high_resolution_clock clock;
	std::chrono::high_resolution_clock::time_point reset_time;
};

BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(Stopwatch)
