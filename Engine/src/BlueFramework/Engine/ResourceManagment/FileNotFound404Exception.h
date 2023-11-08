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
#ifndef BlueFramework_Engine_FileNotFound404Exception_788e6dc9_1ad9_47a7_b1ff_3f0455207e9f_h
#define BlueFramework_Engine_FileNotFound404Exception_788e6dc9_1ad9_47a7_b1ff_3f0455207e9f_h

#include "BlueFramework/Engine/namespace.h"
#include "BlueFramework/Core/Exception.h"
#include <string>

BLUEFRAMEWORK_ENGINE_NAMESPACE_BEGIN

class FileNotFound404Exception : public buw::Exception {
public:
	FileNotFound404Exception(const std::string& uri);

	const char* what() const;

	virtual ~FileNotFound404Exception();

private:
	std::string errorMessage_;
};

BLUEFRAMEWORK_ENGINE_NAMESPACE_END

BLUEFRAMEWORK_ENGINE_EMBED_INTO_BUW_NAMESPACE(FileNotFound404Exception)

#endif // end define BlueFramework_Engine_FileNotFound404Exception_788e6dc9_1ad9_47a7_b1ff_3f0455207e9f_h