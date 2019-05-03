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
