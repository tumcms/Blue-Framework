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

#include "BlueFramework/Core/Diagnostics/log.h"
#include <BlueFramework/Core/Diagnostics/ic/ic.hpp>
#include <BlueFramework/Core/assert.h>

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/attributes/mutable_constant.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/debug_output_backend.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>

#include <string>

namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

bool loggingInitialized = false;

struct ConsoleColor {
	ConsoleColor() : severity((BlueLogger::severity_level)-1) {
	}
	ConsoleColor(const BlueLogger::severity_level& sev) : severity(sev) {
	}

	BlueLogger::severity_level severity;
};

BlueLogger::BlueLogger(const severity_level& severity, const char* file, const char* function, const int& line)
    : severity_(severity), filenameLong_(file), functionLong_(function), line_(line) {
	//BLUE_ASSERT(severity != severity_level::error, "Error message triggerd.");

	filenameShort_ = filenameLong_.substr(filenameLong_.find_last_of("/\\") + 1);

	auto it = functionLong_.find_last_of("::");
	if (it != std::string::npos)
		it = functionLong_.find_last_of("::", it - 2);
	functionShort_ = functionLong_.substr(it + 1);
}

template <typename ValueType>
ValueType set_get_attrib(const char* name, ValueType value) {
	auto attr = boost::log::attribute_cast<boost::log::attributes::mutable_constant<ValueType>>(boost::log::core::get()->get_global_attributes()[name]);
	attr.set(value);
	return attr.get();
}

BlueLogger::~BlueLogger() {
	if (loggingInitialized) {
		BOOST_LOG_STREAM_WITH_PARAMS((buw::Singleton<boost::log::sources::severity_logger<boost::log::trivial::severity_level>>::instance()),
		                             (set_get_attrib("file_long", filenameLong_))(set_get_attrib("file_short", filenameShort_))(set_get_attrib("fn_long", functionLong_))(
		                               set_get_attrib("fn_short", functionShort_))(set_get_attrib("line", line_))(set_get_attrib("color", ConsoleColor(severity_)))(
		                               ::boost::log::keywords::severity = severity_))
		  << stream_.str();

		ic::shorties::textcolor(ic::TextColor::FG_WHITE);
		ic::shorties::textbackground(ic::BackgroundColor::BG_BLACK);
	}
}

template <typename CharT, typename TraitsT>
std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& strm, ConsoleColor const& color) {
	switch (color.severity) {
	case BlueLogger::severity_level::trace: ic::shorties::textcolor(ic::TextColor::FG_LIGHTGRAY); break;
	case BlueLogger::severity_level::debug: ic::shorties::textcolor(ic::TextColor::FG_LIGHTGRAY); break;
	case BlueLogger::severity_level::warning: ic::shorties::textcolor(ic::TextColor::FG_YELLOW); break;
	case BlueLogger::severity_level::error: ic::shorties::textcolor(ic::TextColor::FG_LIGHTRED); break;
	case BlueLogger::severity_level::fatal:
		ic::shorties::textcolor(ic::TextColor::FG_WHITE);
		ic::shorties::textbackground(ic::BackgroundColor::BG_RED);
		break;
	default: ic::shorties::textcolor(ic::TextColor::FG_WHITE); ic::shorties::textbackground(ic::BackgroundColor::BG_BLACK);
	}
	return strm;
}

void initializeLogSystem(bool writeToLogFile, bool writeToDebugOutput) {
	initializeLogSystem("", writeToLogFile, writeToDebugOutput);
}

void initializeLogSystem(std::string path, bool writeToLogFile, bool writeToDebugOutput) {
	ic::Console::getInstance().setBufferedMode(true);
	ic::Console::getInstance().setWindowSize(120, 25);

	logging::register_simple_formatter_factory<ConsoleColor, char>("Colors");

	logging::core::get()->add_global_attribute("file_long", attrs::mutable_constant<std::string>(""));
	logging::core::get()->add_global_attribute("file_short", attrs::mutable_constant<std::string>(""));
	logging::core::get()->add_global_attribute("fn_long", attrs::mutable_constant<std::string>(""));
	logging::core::get()->add_global_attribute("fn_short", attrs::mutable_constant<std::string>(""));
	logging::core::get()->add_global_attribute("line", attrs::mutable_constant<int>(0));
	logging::core::get()->add_global_attribute("color", attrs::mutable_constant<ConsoleColor>(ConsoleColor()));

	logging::add_console_log(std::cout,
		keywords::format =
		(expr::stream << expr::attr<ConsoleColor>("color") << " " << std::right << std::setw(7) << boost::log::trivial::severity << " | " << std::left
			<< std::setw(40)
			<< expr::attr<std::string>("fn_short")
			<< " | "
			<< expr::smessage));

	if(writeToLogFile) {
		std::string filename = path.append("log.txt");
		
		logging::add_file_log(keywords::file_name = filename,
			keywords::auto_flush = true,
			keywords::format =
			(expr::stream << "[" << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%d.%m.%Y %H:%M:%S.%f") << " : " << std::right << std::setw(8)
				<< boost::log::trivial::severity
				<< " | "
				<< expr::attr<std::string>("fn_long")
				<< "() | "
				<< expr::attr<std::string>("file_long")
				<< ":"
				<< ':'
				<< expr::attr<int>("line")
				<< "] "
				<< expr::smessage));
	}
#if _WIN32
	if(writeToDebugOutput) {
		typedef sinks::synchronous_sink<sinks::debug_output_backend> DebugOutput;

		boost::shared_ptr<DebugOutput> debugOutput(new DebugOutput());
		debugOutput->set_filter(expr::is_debugger_present());
		debugOutput->set_formatter(
			expr::stream << expr::attr<std::string>("file_long") << "(" << expr::attr<int>("line") << ") " << std::left << std::setw(7) << boost::log::trivial::severity << " | "
			<< expr::smessage
			<< "\n");

		logging::core::get()->add_sink(debugOutput);
	}
#endif
	logging::add_common_attributes();

	loggingInitialized = true;
}

BLUEFRAMEWORK_CORE_NAMESPACE_END
