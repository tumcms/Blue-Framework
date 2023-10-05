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
