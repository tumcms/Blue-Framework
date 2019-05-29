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
#ifndef BlueFramework_Core_Diagnostics_log_033aae9c_3120_40b6_85fd_cb269570d072_h
#define BlueFramework_Core_Diagnostics_log_033aae9c_3120_40b6_85fd_cb269570d072_h

#pragma warning(disable : 4714)

#include "BlueFramework/Core/warnings.h"
#include "BlueFramework/Core/Singleton.h"
#include "BlueFramework/Core/namespace.h"

#if  _WIN32
WARN_BOOST_INLINE_DISABLE
#endif

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
