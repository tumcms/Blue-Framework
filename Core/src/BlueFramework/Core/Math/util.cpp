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

#include "util.h"

#include "BlueFramework/Core/assert.h"
#include <iomanip>
#include <sstream>

double BlueFramework::Core::Math::round(const double val, const int precision) {
	double tmp = 0;
	std::stringstream s;
	s << std::setprecision(precision) << std::setiosflags(std::ios_base::fixed) << val;
	s >> tmp;
	return tmp;
}

double BlueFramework::Core::Math::factorial(const int n) {
	const int maxValue = 20;

	BLUE_ASSERT(n >= 0, "Invalid value.");
	BLUE_ASSERT(n <= maxValue, "Invalid value.");

	static double lookupTable[maxValue + 1] = {
	  1.0,                                    // 0!
	  1.0,                                    // 1!
	  2.0,                                    // 2!
	  6.0,                                    // 3!
	  24.0,                                   // 4!
	  24.0 * 5,                               // 5!
	  1 * 2 * 3 * 4 * 5 * 6,                  // 6!
	  1 * 2 * 3 * 4 * 5 * 6 * 7,              // 7!
	  1 * 2 * 3 * 4 * 5 * 6 * 7 * 8,          // 8!
	  1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9,      // 9!
	  1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10, // 10!
	  39916800,                               // 11!
	  479001600,                              // 12!
	  6227020800,                             // 13!
	  87178291200,                            // 14!
	  1307674368000,                          // 15!
	  20922789888000,                         // 16!
	  355687428096000,                        // 17!
	  6402373705728000,                       // 18!
	  121645100408832000,                     // 19!
	  2432902008176640000                     // 20!
	};

	return lookupTable[n];
}