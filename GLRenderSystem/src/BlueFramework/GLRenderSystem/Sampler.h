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

#ifndef __SAMPLER_H_7B12D25F42CC474DBA060D55F39E6688__
#define __SAMPLER_H_7B12D25F42CC474DBA060D55F39E6688__

#include <BlueFramework/GLRenderSystem/namespace.h>

#include <BlueFramework/Rasterizer/Resources/ISampler.h>
#include <BlueFramework/Rasterizer/renderDescriptors.h>

#include <memory>

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_BEGIN

class RenderSystem;

class Sampler : public buw::ISampler, public std::enable_shared_from_this<Sampler>
{
public:
	explicit Sampler(RenderSystem* rs, buw::samplerStateDescription const& ssd);
	virtual ~Sampler();

	void setActive();
	static buw::ReferenceCounted<Sampler> getActive();

	buw::samplerStateDescription getSamplerDescription() const { return _ssd; }

private:
	static std::weak_ptr<Sampler> _active;
	buw::samplerStateDescription const _ssd;
};

BLUE_NAMESPACE_BLUEFRAMEWORK_GLRENDERSYSTEM_END

#endif // __SAMPLER_H_7B12D25F42CC474DBA060D55F39E6688__
