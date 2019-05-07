package(default_visibility = ["//visibility:public"])

filegroup(
    name = "BlueFramework_Core_Math_Source",
    srcs = glob([
        "src/BlueFramework/Core/Math/*.*",
    ]),
)

cc_library(
	name = "BlueFramework.Core",
	srcs = [
		#"src/BlueFramework/Core/assert.cpp",
		#"src/BlueFramework/Core/assert.h",

#		"src/BlueFramework/Core/Path.cpp",
#		"src/BlueFramework/Core/Path.h",

		#"src/BlueFramework/Core/PropertySet.cpp",
		#"src/BlueFramework/Core/PropertySet.h",
		"src/BlueFramework/Core/memory.h",
		"src/BlueFramework/Core/NonCopyable.cpp",
		"src/BlueFramework/Core/NonCopyable.h",

		"src/BlueFramework/Core/Singleton.h",


		"src/BlueFramework/Core/tinyformat.h",
		"src/BlueFramework/Core/types.h",
        "src/BlueFramework/Core/namespace.h",
		"src/BlueFramework/Core/Uri.cpp",
		"src/BlueFramework/Core/Uri.h",
		"src/BlueFramework/Core/Version.cpp",
		"src/BlueFramework/Core/Version.h",
		#"//Core:BlueFramework_Core_Math_Source",
	],
	includes = ["src"],
)