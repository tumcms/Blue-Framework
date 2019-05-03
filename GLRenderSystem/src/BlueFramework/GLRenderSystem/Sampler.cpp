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
