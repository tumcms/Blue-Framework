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
