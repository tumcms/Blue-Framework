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
