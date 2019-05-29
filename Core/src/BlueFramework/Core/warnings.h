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

// This one is tricky. It cannot be enclosed by push/pop but must be disabled for the
// whole compilation unit. Disables
// warning C4714: function 'boost::log::v2s_mt_nt6::aux::attribute_set_reference_proxy::operator boost::log::v2s_mt_nt6::aux::attribute_set_reference_proxy::mapped_type(void) noexcept const' marked as __forceinline not inlined
#define WARN_BOOST_INLINE_DISABLE __pragma(warning(disable: 4714));

#define WARN_QT_PUSH \
	__pragma(warning(push)) \
	__pragma(warning(disable: 4127))

#define WARN_POP __pragma(warning(pop))
