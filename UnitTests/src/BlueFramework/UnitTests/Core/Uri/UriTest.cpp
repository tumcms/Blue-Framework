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

#include <BlueFramework/Core/Uri.h>

#include <gtest/gtest.h>

namespace {
	TEST(Uri, Uri) {
		buw::Uri uri("https://github.com/bazelbuild/bazel/releases/download/0.25.0/bazel-0.25.0-windows-x86_64.zip");
		std::cout << uri.getQuery() << std::endl;
		EXPECT_TRUE(uri.getProtocol() == "https");
		EXPECT_TRUE(uri.getPath() == "/bazelbuild/bazel/releases/download/0.25.0/bazel-0.25.0-windows-x86_64.zip");
		EXPECT_TRUE(uri.getHost() == "github.com");
		EXPECT_TRUE(uri.getQuery() == "");
	}

	TEST(UriWithQuery, Uri) {
		buw::Uri uri("foo://example.com:8042/over/there?name=ferret#nose");
		EXPECT_TRUE(uri.getProtocol() == "foo");
		EXPECT_TRUE(uri.getPath() == "/over/there");
		EXPECT_TRUE(uri.getHost() == "example.com:8042");
		EXPECT_TRUE(uri.getQuery() == "name=ferret#nose");
	}
}