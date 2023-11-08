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
#ifndef BlueFramework_Engine_download_532ddd47_eda3_4c21_8657_5f09d670ff66_h
#define BlueFramework_Engine_download_532ddd47_eda3_4c21_8657_5f09d670ff66_h

#include "BlueFramework/Engine/namespace.h"
#include <string>

BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN

struct downloadDescription {
	std::string uri;		//! url of file
	std::string localPath;	//! file name that is use to store the file
};

void loadWebResources(const char* filename);
void downloadFile(const downloadDescription& dd);
void downloadFile(const std::string& uri, const std::string& localPath);

std::vector<char> downloadBytes(const std::string& uri);

BLUEFRAMEWORK_ENGINE_NAMESPACE_END

BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(downloadDescription)
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(loadWebResources)
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(downloadFile)
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(downloadFile)
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(downloadBytes)

#endif // end define BlueFramework_Engine_download_532ddd47_eda3_4c21_8657_5f09d670ff66_h
