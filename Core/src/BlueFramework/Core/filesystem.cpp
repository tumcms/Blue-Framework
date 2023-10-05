/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2023 Technical University of Munich
    Chair of Computational Modeling and Simulation.

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "BlueFramework/Core/namespace.h"
#include <boost/filesystem.hpp>
#include <string>
#include <vector>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

std::vector<std::string> getFileList(const std::string& directorPath, const bool ignoreDirectories /* = true */) {
	std::vector<std::string> result;

	if (!directorPath.empty()) {
		boost::filesystem::path path(directorPath);
		boost::filesystem::recursive_directory_iterator end;

		for (boost::filesystem::recursive_directory_iterator i(path); i != end; ++i) {
			const boost::filesystem::path cp = (*i);

			if (ignoreDirectories && boost::filesystem::is_directory(cp)) {
				continue;
			}

			result.push_back(cp.string());
		}
	}
	return result;
}

BLUEFRAMEWORK_CORE_NAMESPACE_END
