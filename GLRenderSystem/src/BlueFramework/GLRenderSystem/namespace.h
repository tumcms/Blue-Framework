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

#ifndef __NAMESPACE_H_63DA257C4F6A4B51B073A296E1D637FE__
#define __NAMESPACE_H_63DA257C4F6A4B51B073A296E1D637FE__

#define BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN namespace BlueFramework { namespace GLRenderSystem {
#define BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END }}

#define BLUE_BLUEFRAMEWORK_GLRENDERSYSTEM_EMBED_INTO_BUW_NAMESPACE(X)	\
namespace buw {																\
	using BlueFramework::GLRenderSystem::X;							    \
}

#endif // __NAMESPACE_H_63DA257C4F6A4B51B073A296E1D637FE__
