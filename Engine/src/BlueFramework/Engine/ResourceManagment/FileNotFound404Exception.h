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