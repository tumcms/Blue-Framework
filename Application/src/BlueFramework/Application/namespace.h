/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2019 Technical University of Munich
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
#ifndef BlueFramework_Application_namespace_0cb41693_1580_4b49_8445_d39864a543c3_h
#define BlueFramework_Application_namespace_0cb41693_1580_4b49_8445_d39864a543c3_h

#define BLUEFRAMEWORK_APPLICATION_NAMESPACE_BEGIN namespace BlueFramework { namespace Application {
#define BLUEFRAMEWORK_APPLICATION_NAMESPACE_END }}

#define BLUEFRAMEWORK_APPLICATION_UI_NAMESPACE_BEGIN namespace BlueFramework { namespace Application { namespace UserInterface {
#define BLUEFRAMEWORK_APPLICATION_UI_NAMESPACE_END }}}

#define BLUEFRAMEWORK_APPLICATION_DATAMANAGEMENT_NAMESPACE_BEGIN namespace BlueFramework { namespace Application { namespace DataManagement {
#define BLUEFRAMEWORK_APPLICATION_DATAMANAGEMENT_NAMESPACE_END }}}

#define BLUE_BLUEFRAMEWORK_APPLICATION_EMBED_INTO_BUW_NAMESPACE(X) \
namespace buw {                                                    \
	using BlueFramework::Application::X;                           \
}

#endif // end define BlueFramework_Application_namespace_0cb41693_1580_4b49_8445_d39864a543c3_h
