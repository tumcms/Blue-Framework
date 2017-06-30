/*
    This file is part of BlueFramework, a simple 3D engine.
    Copyright (c) 2016-2017 Technical University of Munich
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

#pragma once
#ifndef BlueFramework_Core_filesystem_834d7cbc_025f_47c4_970f_ec7d2b6b5f44_h
#define BlueFramework_Core_filesystem_834d7cbc_025f_47c4_970f_ec7d2b6b5f44_h

#include "BlueFramework/Core/namespace.h"
#include <string>
#include <vector>

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

std::vector<std::string> getFileList(const std::string& directorPath, const bool ignoreDirectories = true);

BLUEFRAMEWORK_CORE_NAMESPACE_END

BLUEFRAMEWORK_CORE_EMBED_INTO_BUW_NAMESPACE(getFileList)

#endif // end define BlueFramework_Core_filesystem_834d7cbc_025f_47c4_970f_ec7d2b6b5f44_h
