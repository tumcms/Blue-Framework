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

#include <GL/glew.h> // !! GLEW always first !!

#include <BlueFramework/GLRenderSystem/Sampler.h>
#include <BlueFramework/GLRenderSystem/namespace.h>
#include <BlueFramework/GLRenderSystem/RenderSystem.h>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

std::weak_ptr<Sampler> Sampler::_active;

Sampler::Sampler(RenderSystem* rs, buw::samplerStateDescription const& ssd)
	: buw::ISampler(rs, ssd)
	, std::enable_shared_from_this<Sampler>()
	, _ssd(ssd)
{
}

Sampler::~Sampler()
{
	if (_active.lock().get() == this) _active.reset(); // Actually not needed because we use a weak pointer.
}

void Sampler::setActive()
{
	if (_active.lock().get() == this) return;
	_active = shared_from_this();
}

buw::ReferenceCounted<Sampler> Sampler::getActive()
{
	return _active.lock();
}

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END
