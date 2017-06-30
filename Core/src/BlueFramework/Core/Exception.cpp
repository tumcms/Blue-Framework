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
