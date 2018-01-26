/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2018 Technical University of Munich
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
