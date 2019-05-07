workspace(name = "BlueFramework")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# Bazel version
git_repository(
    name = "build_bazel_rules_nodejs",
    remote = "https://github.com/bazelbuild/rules_nodejs.git",
    #tag = "0.28.0",
	commit = "f18986bce027355bbb9724bddd279bb710ae16bb", 
	shallow_since = "1556214188 -0700",
)

load("@build_bazel_rules_nodejs//:defs.bzl", "check_bazel_version", "yarn_install")

check_bazel_version("0.24.1")

# googletest
git_repository(
    name = "googletest",
    remote = "https://github.com/google/googletest",
    # tag = "release-1.8.1",
    commit = "2fe3bd994b3189899d93f1d5a881e725e046fdc2", 
    shallow_since = "1535728917 -0400",
)

# Boost
git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "6d6fd834281cb8f8e758dd9ad76df86304bf1869",
    remote = "https://github.com/nelhage/rules_boost",
    shallow_since = "1543903644 -0800",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()
