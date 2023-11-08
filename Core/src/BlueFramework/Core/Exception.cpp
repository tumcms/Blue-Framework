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

#include "BlueFramework/Core/Exception.h"
#include "BlueFramework/Core/Diagnostics/log.h"
#include <iostream>

BlueFramework::Core::BlueStackWalker::BlueStackWalker() : StackWalker() {
}

BLUEFRAMEWORK_CORE_NAMESPACE_BEGIN

void BlueStackWalker::OnOutput(LPCSTR szText) {
	BLUE_LOG(error) << szText;
}

FileNotFoundException::FileNotFoundException(std::string Filename) : m_Filename(Filename), Exception("File not found.") {
}

FileNotFoundException::FileNotFoundException(const FileNotFoundException &src) : Exception("File not found.") {
	m_Filename = src.m_Filename;
}

FileNotFoundException &FileNotFoundException::operator=(const FileNotFoundException &src) {
	m_Filename = src.m_Filename;
	return *this;
}

std::ostream &operator<<(std::ostream &out, const FileNotFoundException &src) {
	out << src.m_Filename;
	return out;
};

NotImplementedYetException::NotImplementedYetException(const NotImplementedYetException &src) : Exception("NotImplementedYetException.") {
	m_Description = src.m_Description;
}

NotImplementedYetException::NotImplementedYetException(std::string description) : m_Description(description), Exception(description.c_str()) {
}

InvalidFileFormatException::InvalidFileFormatException(std::string filename) : FileNotFoundException(filename) {
}

BLUEFRAMEWORK_CORE_NAMESPACE_END
