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
#ifndef BlueFramework_ImageProcessing_namespace_ff83110f_bf4b_4e94_a468_8b87255855fd_h
#define BlueFramework_ImageProcessing_namespace_ff83110f_bf4b_4e94_a468_8b87255855fd_h

#define BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_BEGIN namespace BlueFramework { namespace ImageProcessing {
#define BLUEFRAMEWORK_IMAGEPROCESSING_NAMESPACE_END }}

#define BLUE_BLUEFRAMEWORK_IMAGEPROCESSING_EMBED_INTO_BUW_NAMESPACE(X) \
namespace buw {                                                        \
	using BlueFramework::ImageProcessing::X;                           \
}

#endif // end define BlueFramework_ImageProcessing_namespace_ff83110f_bf4b_4e94_a468_8b87255855fd_h
