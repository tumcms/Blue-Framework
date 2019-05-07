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

workspace(name = "BlueFramework")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

# Bazel version
git_repository(
    name = "build_bazel_rules_nodejs",
    remote = "https://github.com/bazelbuild/rules_nodejs.git",
    tag = "0.27.8",
)

load("@build_bazel_rules_nodejs//:defs.bzl", "check_bazel_version", "yarn_install")

check_bazel_version("0.24.1")

# googletest
git_repository(
    name = "googletest",
    remote = "https://github.com/google/googletest",
    tag = "release-1.8.1",
)

# Boost
git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "6d6fd834281cb8f8e758dd9ad76df86304bf1869",
    remote = "https://github.com/nelhage/rules_boost",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()
