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

// see also: https://github.com/facebook/folly/blob/master/folly/Uri.h
#include "Uri.h"

#include <algorithm>
#include <cctype>
#include <functional>
#include <iterator> // std::back_inserter
#include <string>

using namespace std;

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

Uri::Uri(const std::string& url_s) {
	parse(url_s);
}

void Uri::parse(const std::string& url_s) {
	const string prot_end("://");
	string::const_iterator prot_i = search(url_s.begin(), url_s.end(), prot_end.begin(), prot_end.end());
	protocol_.reserve(distance(url_s.begin(), prot_i));
	transform(url_s.begin(), prot_i, back_inserter(protocol_), tolower); // protocol is icase
	if (prot_i == url_s.end())
		return;
	advance(prot_i, prot_end.length());
	string::const_iterator path_i = find(prot_i, url_s.end(), '/');
	host_.reserve(distance(prot_i, path_i));
	transform(prot_i, path_i, back_inserter(host_), tolower); // host is icase
	string::const_iterator query_i = find(path_i, url_s.end(), '?');
	path_.assign(path_i, query_i);
	if (query_i != url_s.end())
		++query_i;
	query_.assign(query_i, url_s.end());
}

BLUEFRAMEWORK_CORE_NAMESPACE_END