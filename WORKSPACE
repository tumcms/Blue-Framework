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
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

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
    commit = "f0d2a15d6dd5f0667cdaa6da9565ccf87b84c468",
    remote = "https://github.com/Vertexwahn/rules_boost",
    shallow_since = "1557766870 +0200"
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

# Eigen
http_archive(
  name = "eigen_archive",
  url = "https://bitbucket.org/eigen/eigen/get/c5e90d9.tar.gz",
  sha256 = "3a66f9bfce85aff39bc255d5a341f87336ec6f5911e8d816dd4a3fdc500f8acf",
  build_file = "eigen.BUILD",
)
