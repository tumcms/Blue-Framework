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
#ifndef BlueFramework_Core_Diagnostics_log_033aae9c_3120_40b6_85fd_cb269570d072_h
#define BlueFramework_Core_Diagnostics_log_033aae9c_3120_40b6_85fd_cb269570d072_h

#pragma warning(disable : 4714)

#include "BlueFramework/Core/warnings.h"
#include "BlueFramework/Core/Singleton.h"
#include "BlueFramework/Core/namespace.h"
WARN_BOOST_INLINE_DISABLE
#include <boost/log/trivial.hpp>
#include <sstream>
#include <string>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

class BlueLogger {
public:
	typedef boost::log::trivial::severity_level severity_level;

public:
	BlueLogger(const severity_level& severity, const char* filename, const char* function, const int& line);

	template <typename T>
	BlueLogger& operator<<(const T& val) {
		stream_ << val;
		return *this;
	}

	~BlueLogger();

private:
	std::stringstream stream_;
	severity_level severity_;
	std::string filenameLong_, filenameShort_, functionLong_, functionShort_;
	int line_;
};

void initializeLogSystem(bool writeToLogFile, bool writeToDebugOutput);

void initializeLogSystem(std::string path, bool writeToLogFile, bool writeToDebugOutput);


BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(initializeLogSystem);

#define BLUE_LOG(sev) BlueFramework::Core::BlueLogger(BlueFramework::Core::BlueLogger::severity_level::sev, __FILE__, __FUNCTION__, __LINE__)

#endif // end define BlueFramework_Core_Diagnostics_log_033aae9c_3120_40b6_85fd_cb269570d072_h
