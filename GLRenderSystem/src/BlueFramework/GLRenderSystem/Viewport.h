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

#ifndef __VIEWPORT_H_4A13ECE77CBE43929DB3C1E07899B25B__
#define __VIEWPORT_H_4A13ECE77CBE43929DB3C1E07899B25B__

#include <BlueFramework/GLRenderSystem/namespace.h>

#include <BlueFramework/Rasterizer/Resources/IViewport.h>
#include <BlueFramework/Rasterizer/renderDescriptors.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

class Viewport : public buw::IViewport
{
public:
	explicit Viewport(buw::viewportDescription const& vd);
	virtual ~Viewport();

	void resize(buw::viewportDescription const&) override;
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __VIEWPORT_H_4A13ECE77CBE43929DB3C1E07899B25B__
