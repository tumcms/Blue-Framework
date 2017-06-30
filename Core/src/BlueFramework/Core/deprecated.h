// Copied and modified code from Stack Overflow posting "C++ mark as deprecated"
// More details here: http://stackoverflow.com/questions/295120/c-mark-as-deprecated

#include "BlueFramework/Core/namespace.h"

#pragma once
#ifndef BlueFramework_Core_deprecated_97388231_cd7a_4a31_83bf_104b35e44bcf_h
#define BlueFramework_Core_deprecated_97388231_cd7a_4a31_83bf_104b35e44bcf_h

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

#ifdef __GNUC__
#define BLUE_DEPRECATED(func) func __attribute__((deprecated))
#elif defined(_MSC_VER)
#define BLUE_DEPRECATED(func) __declspec(deprecated) func
#else
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define BLUE_DEPRECATED(func) func
#endif

BLUEFRAMEWORK_CORE_NAMESPACE_END

#endif // end define BlueFramework_Core_deprecated_97388231_cd7a_4a31_83bf_104b35e44bcf_h
