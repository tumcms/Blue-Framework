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
#ifndef BlueFramework_Core_bassert_14e5fc9e_d952_446e_8e5c_c086a8e615fc_h
#define BlueFramework_Core_bassert_14e5fc9e_d952_446e_8e5c_c086a8e615fc_h

#include "BlueFramework/Core/Diagnostics/log.h"

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

bool isDebuggerConnected();

BLUEFRAMEWORK_CORE_NAMESPACE_END

#define BLUE_BREAKPOINT                                 \
	{                                                   \
		if (BlueFramework::Core::isDebuggerConnected()) \
			__debugbreak();                             \
	\
}

// macro overloading technique
// more details here: https://github.com/jason-deng/C99FunctionOverload
#define BLUE_ASSERT_FUNC_CHOOSER(_f1, _f2, _f3, ...) _f3
#define BLUE_ASSERT_FUNC_RECOMPOSER(argsWithParentheses) BLUE_ASSERT_FUNC_CHOOSER argsWithParentheses
#define BLUE_ASSERT_CHOOSE_FROM_ARG_COUNT(...) BLUE_ASSERT_FUNC_RECOMPOSER((__VA_ARGS__, BLUE_ASSERT_2, BLUE_ASSERT_1, ))
#define BLUE_ASSERT_MACRO_CHOOSER(...) BLUE_ASSERT_CHOOSE_FROM_ARG_COUNT(NO_ARG_EXPANDER __VA_ARGS__())

#define BLUE_ASSERT_1(condition)                                                                   \
	{                                                                                              \
		bool bAssertExpression = condition;                                                        \
		if (!bAssertExpression)                                                                    \
			BLUE_LOG(error) << "BLUE_ASSERT: Assertion failed in " << __FILE__ << ":" << __LINE__; \
		if (!bAssertExpression)                                                                    \
			BLUE_BREAKPOINT                                                                        \
		assert(bAssertExpression);                                                                 \
	\
}

/// Assertion with a customizable error explanation
#define BLUE_ASSERT_2(condition, explanation)                                                                             \
	{                                                                                                                     \
		bool bAssertExpression = condition;                                                                               \
		if (!bAssertExpression)                                                                                           \
			BLUE_LOG(error) << "BLUE_ASSERT: Assertion failed in " << __FILE__ << ":" << __LINE__ << "\n" << explanation; \
		if (!bAssertExpression)                                                                                           \
			BLUE_BREAKPOINT                                                                                               \
		assert(bAssertExpression);                                                                                        \
	\
}

#define BLUE_ASSERT(...) BLUE_ASSERT_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#endif // end define BlueFramework_Core_NAME_14e5fc9e_d952_446e_8e5c_c086a8e615fc_h
