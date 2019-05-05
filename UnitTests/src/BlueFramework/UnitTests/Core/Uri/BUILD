genrule(
    name = "main_for_unit_test",
    srcs = [],
    outs = ["main.cpp"],
    cmd = "cp $(location)/../../main.cpp $(location)/main.cpp",
)

cc_test(
    name = "UriTest",
    srcs = [
		"UriTest.cpp",
		#"//UnitTests/src/BlueFramework/UnitTests/Core/Uri:main_for_unit_test:gen"
	],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@googletest//:gtest_main",
        "//Core:BlueFramework.Core",
    ],
)