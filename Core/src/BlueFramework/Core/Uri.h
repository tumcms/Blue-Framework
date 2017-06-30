// Copied and modified code from "Folly" library.
// This library is available under the Apache License version 2. Original copyright notice:

/*
 * Copyright 2016 Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// More details can be found in README.md file in the root directory.

#pragma once
#ifndef BlueFramework_Core_Uri_1c1cb5bc_4b6b_49fc_9f2c_7b9cd1b5a629_h
#define BlueFramework_Core_Uri_1c1cb5bc_4b6b_49fc_9f2c_7b9cd1b5a629_h

#include "BlueFramework/Core/namespace.h"
#include <string>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

class Uri {
public:
	Uri(const std::string& url_s);

	const std::string& getQuery() const {
		return query_;
	}
	const std::string& getPath() const {
		return path_;
	}
	const std::string& getHost() const {
		return host_;
	}
	const std::string& getProtocol() const {
		return protocol_;
	}

private:
	void parse(const std::string& url_s);

private:
	std::string protocol_;
	std::string host_;
	std::string path_;
	std::string query_;
}; // end class Uri

BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(Uri)

#endif // end define BlueFramework_Core_Uri_1c1cb5bc_4b6b_49fc_9f2c_7b9cd1b5a629_h