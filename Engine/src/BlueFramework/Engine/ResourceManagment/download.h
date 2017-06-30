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

BLUEFRAMEWORK_ENGINE_NAMESPACE_END

BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(downloadDescription)
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(loadWebResources)
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(downloadFile)
BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(downloadFile)

#endif // end define BlueFramework_Engine_download_532ddd47_eda3_4c21_8657_5f09d670ff66_h
