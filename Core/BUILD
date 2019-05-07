#
#   This file is part of BlueFramework, a simple 3D engine.
#	Copyright (c) 2019 Technical University of Munich
#	Chair of Computational Modeling and Simulation.
#   
#   BlueFramework is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License Version 3
#   as published by the Free Software Foundation.
#   
#   BlueFramework is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public License
#   along with this program. If not, see <http://www.gnu.org/licenses/>.
#

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "BlueFramework_Core_Math_Source",
    srcs = glob([
        "src/BlueFramework/Core/Math/*.*",
    ]),
)

filegroup(
    name = "BlueFramework_Core_UtfConverter_Source",
    srcs = glob([
        "src/BlueFramework/Core/UtfConverter/*.*",
    ]),
)

filegroup(
    name = "BlueFramework_Core_Diagnostics_Source",
    srcs = glob([
        "src/BlueFramework/Core/Diagnostics/Stack*.*",
    ]),
)

cc_library(
	name = "BlueFramework.Core",
	srcs = [
		"src/BlueFramework/Core/assert.cpp",
		"src/BlueFramework/Core/assert.h",
		"src/BlueFramework/Core/deprecated.h",

		#"src/BlueFramework/Core/Exception.cpp",
		#"src/BlueFramework/Core/Exception.h",

		"src/BlueFramework/Core/Path.cpp",
		"src/BlueFramework/Core/Path.h",

		#"src/BlueFramework/Core/PropertySet.cpp",
		#"src/BlueFramework/Core/PropertySet.h",
		"src/BlueFramework/Core/filesystem.h",
		"src/BlueFramework/Core/flags.h",
		"src/BlueFramework/Core/Map.h",
		"src/BlueFramework/Core/memory.h",
		"src/BlueFramework/Core/NonCopyable.cpp",
		"src/BlueFramework/Core/NonCopyable.h",

		"src/BlueFramework/Core/Singleton.h",
		"src/BlueFramework/Core/Stopwatch.h",
		"src/BlueFramework/Core/string.cpp",
		"src/BlueFramework/Core/string.h",
		"src/BlueFramework/Core/tinyformat.h",
		"src/BlueFramework/Core/types.h",
        "src/BlueFramework/Core/namespace.h",
		"src/BlueFramework/Core/Uri.cpp",
		"src/BlueFramework/Core/Uri.h",
		"src/BlueFramework/Core/Version.cpp",
		"src/BlueFramework/Core/Version.h",
		#"//Core:BlueFramework_Core_Math_Source",
		"//Core:BlueFramework_Core_UtfConverter_Source",
		#"//Core:BlueFramework_Core_Diagnostics_Source",
	],
	includes = ["src"],
	deps = [
		"@boost//:filesystem"
	]
)