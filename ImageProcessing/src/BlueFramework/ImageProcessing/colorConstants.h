/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2018 Technical University of Munich
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
#ifndef BlueFramework_ImageProcessing_ColorConstants_e730a33d_4053_4c52_bd16_ecf1fba26816_h
#define BlueFramework_ImageProcessing_ColorConstants_e730a33d_4053_4c52_bd16_ecf1fba26816_h

#include "BlueFramework/Core/Noncopyable.h"
#include "BlueFramework/Core/Math/RandomNumberGenerator.h"
#include "BlueFramework/Core/assert.h"

namespace BlueFramework
{
	namespace ImageProcessing
	{
		// Implements different color constants.
		template<typename ColorType>
		struct colorConstants
		{
			static ColorType aliceBlue()
			{
				return ColorType(240/255.0, 248/255.0, 255/255.0);
			};

			static ColorType antiqueWhite()
			{
				return ColorType(250/255.0, 235/255.0, 215/255.0);
			};

			static ColorType aqua()
			{
				return ColorType(0/255.0, 255/255.0, 255/255.0);
			};

			static ColorType aquaMarine()
			{
				return ColorType(127/255.0, 255/255.0, 212/255.0);
			};

			static ColorType azure()
			{
				return ColorType(240/255.0, 255/255.0, 255/255.0);
			};

			static ColorType beige()
			{
				return ColorType(245/255.0, 245/255.0, 220/255.0);
			};

			static ColorType bisque()
			{
				return ColorType(255/255.0, 228/255.0, 196/255.0);
			};

			static ColorType black()
			{
				return ColorType(0/255.0, 0/255.0, 0/255.0);
			};

			static ColorType blanchedalmond()
			{
				return ColorType(255/255.0, 235/255.0, 205/255.0);
			};

			static ColorType blue()
			{
				return ColorType(0/255.0, 0/255.0, 255/255.0);
			};

			static ColorType blueViolet()
			{
				return ColorType(138/255.0, 43/255.0, 226/255.0);
			};

			static ColorType brown()
			{
				return ColorType(165/255.0, 42/255.0, 42/255.0);
			};

			static ColorType burlywood()
			{
				return ColorType(222/255.0, 184/255.0, 135/255.0);
			};

			static ColorType cadetBlue()
			{
				return ColorType(95/255.0, 158/255.0, 160/255.0);
			};

			static ColorType chartreuse()
			{
				return ColorType(127/255.0, 255/255.0, 0/255.0);
			};

			static ColorType chocolate()
			{
				return ColorType(210/255.0, 105/255.0, 30/255.0);
			};

			static ColorType coral()
			{
				return ColorType(255/255.0, 127/255.0, 80/255.0);
			};

			static ColorType cornFlowerBlue()
			{
				return ColorType(100/255.0, 149/255.0, 237/255.0);
			};

			static ColorType cornsilk()
			{
				return ColorType(255/255.0, 248/255.0, 220/255.0);
			};

			static ColorType crimson()
			{
				return ColorType(220/255.0, 20/255.0, 60/255.0);
			};

			static ColorType cyan()
			{
				return ColorType(0/255.0, 255/255.0, 255/255.0);
			};

			static ColorType darkOliveGreen()
			{
				return ColorType(85/255.0, 107/255.0, 47/255.0);
			};

			static ColorType darkblue()
			{
				return ColorType(0/255.0, 0/255.0, 139/255.0);
			};

			static ColorType darkcyan()
			{
				return ColorType(0/255.0, 139/255.0, 139/255.0);
			};

			static ColorType darkgoldenrod()
			{
				return ColorType(184/255.0, 134/255.0, 11/255.0);
			};

			static ColorType darkgray()
			{
				return ColorType(169/255.0, 169/255.0, 169/255.0);
			};

			static ColorType darkgreen()
			{
				return ColorType(0/255.0, 100/255.0, 0/255.0);
			};

			static ColorType darkKhaki()
			{
				return ColorType(189/255.0, 183/255.0, 107/255.0);
			};

			static ColorType darkMagenta()
			{
				return ColorType(139/255.0, 0/255.0, 139/255.0);
			};

			static ColorType darkOrange()
			{
				return ColorType(255/255.0, 140/255.0, 0/255.0);
			};

			static ColorType darkOrchid()
			{
				return ColorType(153/255.0, 50/255.0, 204/255.0);
			};

			static ColorType darkRed()
			{
				return ColorType(139/255.0, 0/255.0, 0/255.0);
			};

			static ColorType darkSalmon()
			{
				return ColorType(233/255.0, 150/255.0, 122/255.0);
			};

			static ColorType darkseagreen()
			{
				return ColorType(143/255.0, 188/255.0, 143/255.0);
			};

			static ColorType darkslateblue()
			{
				return ColorType(72/255.0, 61/255.0, 139/255.0);
			};

			static ColorType darkslategray()
			{
				return ColorType(47/255.0, 79/255.0, 79/255.0);
			};

			static ColorType darkturquoise()
			{
				return ColorType(0/255.0, 206/255.0, 209/255.0);
			};

			static ColorType darkViolet()
			{
				return ColorType(148/255.0, 0/255.0, 211/255.0);
			};

			static ColorType deepPink()
			{
				return ColorType(255/255.0, 20/255.0, 147/255.0);
			};

			static ColorType deepskyblue()
			{
				return ColorType(0/255.0, 191/255.0, 255/255.0);
			};

			static ColorType dimgray()
			{
				return ColorType(105/255.0, 105/255.0, 105/255.0);
			};

			static ColorType dodgerblue()
			{
				return ColorType(30/255.0, 144/255.0, 255/255.0);
			};

			static ColorType firebrick()
			{
				return ColorType(178/255.0, 34/255.0, 34/255.0);
			};

			static ColorType floralwhite()
			{
				return ColorType(255/255.0, 250/255.0, 240/255.0);
			};

			static ColorType forestgreen()
			{
				return ColorType(34/255.0, 139/255.0, 34/255.0);
			};

			static ColorType fuchsia()
			{
				return ColorType(255/255.0, 0/255.0, 255/255.0);
			};

			static ColorType gainsboro()
			{
				return ColorType(220/255.0, 220/255.0, 220/255.0);
			};

			static ColorType ghostwhite()
			{
				return ColorType(248/255.0, 248/255.0, 255/255.0);
			};

			static ColorType gold()
			{
				return ColorType(255/255.0, 215/255.0, 0/255.0);
			};

			static ColorType goldenrod()
			{
				return ColorType(218/255.0, 165/255.0, 32/255.0);
			};

			static ColorType gray()
			{
				return ColorType(128/255.0, 128/255.0, 128/255.0);
			};

			static ColorType green()
			{
				return ColorType(0/255.0, 128/255.0, 0/255.0);
			};

			static ColorType greenyellow()
			{
				return ColorType(173/255.0, 255/255.0, 47/255.0);
			};

			static ColorType honeydew()
			{
				return ColorType(240/255.0, 255/255.0, 240/255.0);
			};

			static ColorType hotpink()
			{
				return ColorType(255/255.0, 105/255.0, 180/255.0);
			};

			static ColorType indianred()
			{
				return ColorType(205/255.0, 92/255.0, 92/255.0);
			};

			static ColorType indigo()
			{
				return ColorType(75/255.0, 0/255.0, 130/255.0);
			};

			static ColorType ivory()
			{
				return ColorType(255/255.0, 255/255.0, 240/255.0);
			};

			static ColorType khaki()
			{
				return ColorType(240/255.0, 230/255.0, 140/255.0);
			};

			static ColorType lavender()
			{
				return ColorType(230/255.0, 230/255.0, 250/255.0);
			};

			static ColorType lavenderblush()
			{
				return ColorType(255/255.0, 240/255.0, 245/255.0);
			};

			static ColorType lawngreen()
			{
				return ColorType(124/255.0, 252/255.0, 0/255.0);
			};

			static ColorType lemonchiffon()
			{
				return ColorType(255/255.0, 250/255.0, 205/255.0);
			};

			static ColorType lightblue()
			{
				return ColorType(173/255.0, 216/255.0, 230/255.0);
			};

			static ColorType lightcoral()
			{
				return ColorType(240/255.0, 128/255.0, 128/255.0);
			};

			static ColorType lightcyan()
			{
				return ColorType(224/255.0, 255/255.0, 255/255.0);
			};

			static ColorType lightgoldenrodyellow()
			{
				return ColorType(250/255.0, 250/255.0, 210/255.0);
			};

			static ColorType lightgreen()
			{
				return ColorType(144/255.0, 238/255.0, 144/255.0);
			};

			static ColorType lightgrey()
			{
				return ColorType(211/255.0, 211/255.0, 211/255.0);
			};

			static ColorType lightpink()
			{
				return ColorType(255/255.0, 182/255.0, 193/255.0);
			};

			static ColorType lightsalmon()
			{
				return ColorType(255/255.0, 160/255.0, 122/255.0);
			};

			static ColorType lightseagreen()
			{
				return ColorType(32/255.0, 178/255.0, 170/255.0);
			};

			static ColorType lightskyblue()
			{
				return ColorType(135/255.0, 206/255.0, 250/255.0);
			};

			static ColorType lightslategray()
			{
				return ColorType(119/255.0, 136/255.0, 153/255.0);
			};

			static ColorType lightsteelblue()
			{
				return ColorType(176/255.0, 196/255.0, 222/255.0);
			};

			static ColorType lightyellow()
			{
				return ColorType(255/255.0, 255/255.0, 224/255.0);
			};

			static ColorType lime()
			{
				return ColorType(0/255.0, 255/255.0, 0/255.0);
			};

			static ColorType limegreen()
			{
				return ColorType(50/255.0, 205/255.0, 50/255.0);
			};

			static ColorType linen()
			{
				return ColorType(250/255.0, 240/255.0, 230/255.0);
			};

			static ColorType magenta()
			{
				return ColorType(255/255.0, 0/255.0, 255/255.0);
			};

			static ColorType maroon()
			{
				return ColorType(128/255.0, 0/255.0, 0/255.0);
			};

			static ColorType mediumaquamarine()
			{
				return ColorType(102/255.0, 205/255.0, 170/255.0);
			};

			static ColorType mediumblue()
			{
				return ColorType(0/255.0, 0/255.0, 205/255.0);
			};

			static ColorType mediumorchid()
			{
				return ColorType(186/255.0, 85/255.0, 211/255.0);
			};

			static ColorType mediumpurple()
			{
				return ColorType(147/255.0, 112/255.0, 219/255.0);
			};

			static ColorType mediumseagreen()
			{
				return ColorType(60/255.0, 179/255.0, 113/255.0);
			};

			static ColorType mediumslateblue()
			{
				return ColorType(123/255.0, 104/255.0, 238/255.0);
			};

			static ColorType mediumspringgreen()
			{
				return ColorType(0/255.0, 250/255.0, 154/255.0);
			};

			static ColorType mediumturquoise()
			{
				return ColorType(72/255.0, 209/255.0, 204/255.0);
			};

			static ColorType mediumvioletred()
			{
				return ColorType(199/255.0, 21/255.0, 133/255.0);
			};

			static ColorType midnightblue()
			{
				return ColorType(25/255.0, 25/255.0, 112/255.0);
			};

			static ColorType mintcream()
			{
				return ColorType(245/255.0, 255/255.0, 250/255.0);
			};

			static ColorType mistyrose()
			{
				return ColorType(255/255.0, 228/255.0, 225/255.0);
			};

			static ColorType moccasin()
			{
				return ColorType(255/255.0, 228/255.0, 181/255.0);
			};

			static ColorType navajowhite()
			{
				return ColorType(255/255.0, 222/255.0, 173/255.0);
			};

			static ColorType navy()
			{
				return ColorType(0/255.0, 0/255.0, 128/255.0);
			};

			static ColorType oldlace()
			{
				return ColorType(253/255.0, 245/255.0, 230/255.0);
			};

			static ColorType olive()
			{
				return ColorType(128/255.0, 128/255.0, 0/255.0);
			};

			static ColorType olivedrab()
			{
				return ColorType(107/255.0, 142/255.0, 35/255.0);
			};

			static ColorType orange()
			{
				return ColorType(255/255.0, 165/255.0, 0/255.0);
			};

			static ColorType orangered()
			{
				return ColorType(255/255.0, 69/255.0, 0/255.0);
			};

			static ColorType orchid()
			{
				return ColorType(218/255.0, 112/255.0, 214/255.0);
			};

			static ColorType palegoldenrod()
			{
				return ColorType(238/255.0, 232/255.0, 170/255.0);
			};

			static ColorType palegreen()
			{
				return ColorType(152/255.0, 251/255.0, 152/255.0);
			};

			static ColorType paleturquoise()
			{
				return ColorType(175/255.0, 238/255.0, 238/255.0);
			};

			static ColorType palevioletred()
			{
				return ColorType(219/255.0, 112/255.0, 147/255.0);
			};

			static ColorType papayawhip()
			{
				return ColorType(255/255.0, 239/255.0, 213/255.0);
			};

			static ColorType peachpuff()
			{
				return ColorType(255/255.0, 218/255.0, 185/255.0);
			};

			static ColorType peru()
			{
				return ColorType(205/255.0, 133/255.0, 63/255.0);
			};

			static ColorType pink()
			{
				return ColorType(255/255.0, 192/255.0, 203/255.0);
			};

			static ColorType plum()
			{
				return ColorType(221/255.0, 160/255.0, 221/255.0);
			};

			static ColorType powderblue()
			{
				return ColorType(176/255.0, 224/255.0, 230/255.0);
			};

			static ColorType purple()
			{
				return ColorType(128/255.0, 0/255.0, 128/255.0);
			};

			static ColorType red()
			{
				return ColorType(255/255.0, 0/255.0, 0/255.0);
			};

			static ColorType rosybrown()
			{
				return ColorType(188/255.0, 143/255.0, 143/255.0);
			};

			static ColorType royalblue()
			{
				return ColorType(65/255.0, 105/255.0, 225/255.0);
			};

			static ColorType saddlebrown()
			{
				return ColorType(139/255.0, 69/255.0, 19/255.0);
			};

			static ColorType salmon()
			{
				return ColorType(250/255.0, 128/255.0, 114/255.0);
			};

			static ColorType sandybrown()
			{
				return ColorType(244/255.0, 164/255.0, 96/255.0);
			};

			static ColorType seagreen()
			{
				return ColorType(46/255.0, 139/255.0, 87/255.0);
			};

			static ColorType seashell()
			{
				return ColorType(255/255.0, 245/255.0, 238/255.0);
			};

			static ColorType sienna()
			{
				return ColorType(160/255.0, 82/255.0, 45/255.0);
			};

			static ColorType silver()
			{
				return ColorType(192/255.0, 192/255.0, 192/255.0);
			};

			static ColorType skyblue()
			{
				return ColorType(135/255.0, 206/255.0, 235/255.0);
			};

			static ColorType slateblue()
			{
				return ColorType(106/255.0, 90/255.0, 205/255.0);
			};

			static ColorType slategray()
			{
				return ColorType(112/255.0, 128/255.0, 144/255.0);
			};

			static ColorType snow()
			{
				return ColorType(255/255.0, 250/255.0, 250/255.0);
			};

			static ColorType springGreen()
			{
				return ColorType(0/255.0, 255/255.0, 127/255.0);
			};

			static ColorType steelBlue()
			{
				return ColorType(70/255.0, 130/255.0, 180/255.0);
			};

			static ColorType tan()
			{
				return ColorType(210/255.0, 180/255.0, 140/255.0);
			};

			static ColorType teal()
			{
				return ColorType(0/255.0, 128/255.0, 128/255.0);
			};

			static ColorType thistle()
			{
				return ColorType(216/255.0, 191/255.0, 216/255.0);
			};

			static ColorType tomato()
			{
				return ColorType(255/255.0, 99/255.0, 71/255.0);
			};

			static ColorType turquoise()
			{
				return ColorType(64/255.0, 224/255.0, 208/255.0);
			};

			static ColorType violet()
			{
				return ColorType(238/255.0, 130/255.0, 238/255.0);
			};

			static ColorType wheat()
			{
				return ColorType(245/255.0, 222/255.0, 179/255.0);
			};

			static ColorType white()
			{
				return ColorType(255/255.0, 255/255.0, 255/255.0);
			};

			static ColorType whiteSmoke()
			{
				return ColorType(245/255.0, 245/255.0, 245/255.0);
			};

			static ColorType yellow()
			{
				return ColorType(255/255.0, 255/255.0, 0/255.0);
			};

			static ColorType yellowGreen()
			{
				return ColorType(154/255.0, 205/255.0, 50/255.0);
			};
		};

		template<>
		struct colorConstants<color3f>
		{
			static color3f aliceBlue()
			{
				return color3f(240/255.0f, 248/255.0f, 255/255.0f);
			};

			static color3f antiqueWhite()
			{
				return color3f(250/255.0f, 235/255.0f, 215/255.0f);
			};

			static color3f aqua()
			{
				return color3f(0/255.0f, 255/255.0f, 255/255.0f);
			};

			static color3f aquaMarine()
			{
				return color3f(127/255.0f, 255/255.0f, 212/255.0f);
			};

			static color3f azure()
			{
				return color3f(240/255.0f, 255/255.0f, 255/255.0f);
			};

			static color3f beige()
			{
				return color3f(245/255.0f, 245/255.0f, 220/255.0f);
			};

			static color3f bisque()
			{
				return color3f(255/255.0f, 228/255.0f, 196/255.0f);
			};

			static color3f black()
			{
				return color3f(0/255.0f, 0/255.0f, 0/255.0f);
			};

			static color3f blanchedalmond()
			{
				return color3f(255/255.0f, 235/255.0f, 205/255.0f);
			};

			static color3f blue()
			{
				return color3f(0/255.0f, 0/255.0f, 255/255.0f);
			};

			static color3f blueViolet()
			{
				return color3f(138/255.0f, 43/255.0f, 226/255.0f);
			};

			static color3f brown()
			{
				return color3f(165/255.0f, 42/255.0f, 42/255.0f);
			};

			static color3f burlywood()
			{
				return color3f(222/255.0f, 184/255.0f, 135/255.0f);
			};

			static color3f cadetBlue()
			{
				return color3f(95/255.0f, 158/255.0f, 160/255.0f);
			};

			static color3f chartreuse()
			{
				return color3f(127/255.0f, 255/255.0f, 0/255.0f);
			};

			static color3f chocolate()
			{
				return color3f(210/255.0f, 105/255.0f, 30/255.0f);
			};

			static color3f coral()
			{
				return color3f(255/255.0f, 127/255.0f, 80/255.0f);
			};

			static color3f cornflowerblue()
			{
				return color3f(100/255.0f, 149/255.0f, 237/255.0f);
			};

			static color3f cornsilk()
			{
				return color3f(255/255.0f, 248/255.0f, 220/255.0f);
			};

			static color3f crimson()
			{
				return color3f(220/255.0f, 20/255.0f, 60/255.0f);
			};

			static color3f cyan()
			{
				return color3f(0/255.0f, 255/255.0f, 255/255.0f);
			};

			static color3f darkOlivegreen()
			{
				return color3f(85/255.0f, 107/255.0f, 47/255.0f);
			};

			static color3f darkblue()
			{
				return color3f(0/255.0f, 0/255.0f, 139/255.0f);
			};

			static color3f darkcyan()
			{
				return color3f(0/255.0f, 139/255.0f, 139/255.0f);
			};

			static color3f darkgoldenrod()
			{
				return color3f(184/255.0f, 134/255.0f, 11/255.0f);
			};

			static color3f darkgray()
			{
				return color3f(169/255.0f, 169/255.0f, 169/255.0f);
			};

			static color3f darkgreen()
			{
				return color3f(0/255.0f, 100/255.0f, 0/255.0f);
			};

			static color3f darkkhaki()
			{
				return color3f(189/255.0f, 183/255.0f, 107/255.0f);
			};

			static color3f darkmagenta()
			{
				return color3f(139/255.0f, 0/255.0f, 139/255.0f);
			};

			static color3f darkorange()
			{
				return color3f(255/255.0f, 140/255.0f, 0/255.0f);
			};

			static color3f darkorchid()
			{
				return color3f(153/255.0f, 50/255.0f, 204/255.0f);
			};

			static color3f darkRed()
			{
				return color3f(139/255.0f, 0/255.0f, 0/255.0f);
			};

			static color3f darksalmon()
			{
				return color3f(233/255.0f, 150/255.0f, 122/255.0f);
			};

			static color3f darkseagreen()
			{
				return color3f(143/255.0f, 188/255.0f, 143/255.0f);
			};

			static color3f darkslateblue()
			{
				return color3f(72/255.0f, 61/255.0f, 139/255.0f);
			};

			static color3f darkslategray()
			{
				return color3f(47/255.0f, 79/255.0f, 79/255.0f);
			};

			static color3f darkturquoise()
			{
				return color3f(0/255.0f, 206/255.0f, 209/255.0f);
			};

			static color3f darkviolet()
			{
				return color3f(148/255.0f, 0/255.0f, 211/255.0f);
			};

			static color3f deeppink()
			{
				return color3f(255/255.0f, 20/255.0f, 147/255.0f);
			};

			static color3f deepskyblue()
			{
				return color3f(0/255.0f, 191/255.0f, 255/255.0f);
			};

			static color3f dimgray()
			{
				return color3f(105/255.0f, 105/255.0f, 105/255.0f);
			};

			static color3f dodgerblue()
			{
				return color3f(30/255.0f, 144/255.0f, 255/255.0f);
			};

			static color3f firebrick()
			{
				return color3f(178/255.0f, 34/255.0f, 34/255.0f);
			};

			static color3f floralwhite()
			{
				return color3f(255/255.0f, 250/255.0f, 240/255.0f);
			};

			static color3f forestgreen()
			{
				return color3f(34/255.0f, 139/255.0f, 34/255.0f);
			};

			static color3f fuchsia()
			{
				return color3f(255/255.0f, 0/255.0f, 255/255.0f);
			};

			static color3f gainsboro()
			{
				return color3f(220/255.0f, 220/255.0f, 220/255.0f);
			};

			static color3f ghostwhite()
			{
				return color3f(248/255.0f, 248/255.0f, 255/255.0f);
			};

			static color3f gold()
			{
				return color3f(255/255.0f, 215/255.0f, 0/255.0f);
			};

			static color3f goldenrod()
			{
				return color3f(218/255.0f, 165/255.0f, 32/255.0f);
			};

			static color3f gray()
			{
				return color3f(128/255.0f, 128/255.0f, 128/255.0f);
			};

			static color3f green()
			{
				return color3f(0/255.0f, 128/255.0f, 0/255.0f);
			};

			static color3f greenyellow()
			{
				return color3f(173/255.0f, 255/255.0f, 47/255.0f);
			};

			static color3f honeydew()
			{
				return color3f(240/255.0f, 255/255.0f, 240/255.0f);
			};

			static color3f hotpink()
			{
				return color3f(255/255.0f, 105/255.0f, 180/255.0f);
			};

			static color3f indianred()
			{
				return color3f(205/255.0f, 92/255.0f, 92/255.0f);
			};

			static color3f indigo()
			{
				return color3f(75/255.0f, 0/255.0f, 130/255.0f);
			};

			static color3f ivory()
			{
				return color3f(255/255.0f, 255/255.0f, 240/255.0f);
			};

			static color3f khaki()
			{
				return color3f(240/255.0f, 230/255.0f, 140/255.0f);
			};

			static color3f lavender()
			{
				return color3f(230/255.0f, 230/255.0f, 250/255.0f);
			};

			static color3f lavenderblush()
			{
				return color3f(255/255.0f, 240/255.0f, 245/255.0f);
			};

			static color3f lawngreen()
			{
				return color3f(124/255.0f, 252/255.0f, 0/255.0f);
			};

			static color3f lemonchiffon()
			{
				return color3f(255/255.0f, 250/255.0f, 205/255.0f);
			};

			static color3f lightblue()
			{
				return color3f(173/255.0f, 216/255.0f, 230/255.0f);
			};

			static color3f lightcoral()
			{
				return color3f(240/255.0f, 128/255.0f, 128/255.0f);
			};

			static color3f lightcyan()
			{
				return color3f(224/255.0f, 255/255.0f, 255/255.0f);
			};

			static color3f lightgoldenrodyellow()
			{
				return color3f(250/255.0f, 250/255.0f, 210/255.0f);
			};

			static color3f lightgreen()
			{
				return color3f(144/255.0f, 238/255.0f, 144/255.0f);
			};

			static color3f lightgrey()
			{
				return color3f(211/255.0f, 211/255.0f, 211/255.0f);
			};

			static color3f lightpink()
			{
				return color3f(255/255.0f, 182/255.0f, 193/255.0f);
			};

			static color3f lightsalmon()
			{
				return color3f(255/255.0f, 160/255.0f, 122/255.0f);
			};

			static color3f lightseagreen()
			{
				return color3f(32/255.0f, 178/255.0f, 170/255.0f);
			};

			static color3f lightskyblue()
			{
				return color3f(135/255.0f, 206/255.0f, 250/255.0f);
			};

			static color3f lightslategray()
			{
				return color3f(119/255.0f, 136/255.0f, 153/255.0f);
			};

			static color3f lightsteelblue()
			{
				return color3f(176/255.0f, 196/255.0f, 222/255.0f);
			};

			static color3f lightyellow()
			{
				return color3f(255/255.0f, 255/255.0f, 224/255.0f);
			};

			static color3f lime()
			{
				return color3f(0/255.0f, 255/255.0f, 0/255.0f);
			};

			static color3f limegreen()
			{
				return color3f(50/255.0f, 205/255.0f, 50/255.0f);
			};

			static color3f linen()
			{
				return color3f(250/255.0f, 240/255.0f, 230/255.0f);
			};

			static color3f magenta()
			{
				return color3f(255/255.0f, 0/255.0f, 255/255.0f);
			};

			static color3f maroon()
			{
				return color3f(128/255.0f, 0/255.0f, 0/255.0f);
			};

			static color3f mediumaquamarine()
			{
				return color3f(102/255.0f, 205/255.0f, 170/255.0f);
			};

			static color3f mediumblue()
			{
				return color3f(0/255.0f, 0/255.0f, 205/255.0f);
			};

			static color3f mediumorchid()
			{
				return color3f(186/255.0f, 85/255.0f, 211/255.0f);
			};

			static color3f mediumpurple()
			{
				return color3f(147/255.0f, 112/255.0f, 219/255.0f);
			};

			static color3f mediumseagreen()
			{
				return color3f(60/255.0f, 179/255.0f, 113/255.0f);
			};

			static color3f mediumslateblue()
			{
				return color3f(123/255.0f, 104/255.0f, 238/255.0f);
			};

			static color3f mediumspringgreen()
			{
				return color3f(0/255.0f, 250/255.0f, 154/255.0f);
			};

			static color3f mediumturquoise()
			{
				return color3f(72/255.0f, 209/255.0f, 204/255.0f);
			};

			static color3f mediumvioletred()
			{
				return color3f(199/255.0f, 21/255.0f, 133/255.0f);
			};

			static color3f midnightblue()
			{
				return color3f(25/255.0f, 25/255.0f, 112/255.0f);
			};

			static color3f mintcream()
			{
				return color3f(245/255.0f, 255/255.0f, 250/255.0f);
			};

			static color3f mistyrose()
			{
				return color3f(255/255.0f, 228/255.0f, 225/255.0f);
			};

			static color3f moccasin()
			{
				return color3f(255/255.0f, 228/255.0f, 181/255.0f);
			};

			static color3f navajowhite()
			{
				return color3f(255/255.0f, 222/255.0f, 173/255.0f);
			};

			static color3f navy()
			{
				return color3f(0/255.0f, 0/255.0f, 128/255.0f);
			};

			static color3f oldlace()
			{
				return color3f(253/255.0f, 245/255.0f, 230/255.0f);
			};

			static color3f olive()
			{
				return color3f(128/255.0f, 128/255.0f, 0/255.0f);
			};

			static color3f olivedrab()
			{
				return color3f(107/255.0f, 142/255.0f, 35/255.0f);
			};

			static color3f orange()
			{
				return color3f(255/255.0f, 165/255.0f, 0/255.0f);
			};

			static color3f orangered()
			{
				return color3f(255/255.0f, 69/255.0f, 0/255.0f);
			};

			static color3f orchid()
			{
				return color3f(218/255.0f, 112/255.0f, 214/255.0f);
			};

			static color3f palegoldenrod()
			{
				return color3f(238/255.0f, 232/255.0f, 170/255.0f);
			};

			static color3f palegreen()
			{
				return color3f(152/255.0f, 251/255.0f, 152/255.0f);
			};

			static color3f paleturquoise()
			{
				return color3f(175/255.0f, 238/255.0f, 238/255.0f);
			};

			static color3f palevioletred()
			{
				return color3f(219/255.0f, 112/255.0f, 147/255.0f);
			};

			static color3f papayawhip()
			{
				return color3f(255/255.0f, 239/255.0f, 213/255.0f);
			};

			static color3f peachpuff()
			{
				return color3f(255/255.0f, 218/255.0f, 185/255.0f);
			};

			static color3f peru()
			{
				return color3f(205/255.0f, 133/255.0f, 63/255.0f);
			};

			static color3f pink()
			{
				return color3f(255/255.0f, 192/255.0f, 203/255.0f);
			};

			static color3f plum()
			{
				return color3f(221/255.0f, 160/255.0f, 221/255.0f);
			};

			static color3f powderblue()
			{
				return color3f(176/255.0f, 224/255.0f, 230/255.0f);
			};

			static color3f purple()
			{
				return color3f(128/255.0f, 0/255.0f, 128/255.0f);
			};

			static color3f red()
			{
				return color3f(255/255.0f, 0/255.0f, 0/255.0f);
			};

			static color3f rosybrown()
			{
				return color3f(188/255.0f, 143/255.0f, 143/255.0f);
			};

			static color3f royalblue()
			{
				return color3f(65/255.0f, 105/255.0f, 225/255.0f);
			};

			static color3f saddlebrown()
			{
				return color3f(139/255.0f, 69/255.0f, 19/255.0f);
			};

			static color3f salmon()
			{
				return color3f(250/255.0f, 128/255.0f, 114/255.0f);
			};

			static color3f sandybrown()
			{
				return color3f(244/255.0f, 164/255.0f, 96/255.0f);
			};

			static color3f seagreen()
			{
				return color3f(46/255.0f, 139/255.0f, 87/255.0f);
			};

			static color3f seashell()
			{
				return color3f(255/255.0f, 245/255.0f, 238/255.0f);
			};

			static color3f sienna()
			{
				return color3f(160/255.0f, 82/255.0f, 45/255.0f);
			};

			static color3f silver()
			{
				return color3f(192/255.0f, 192/255.0f, 192/255.0f);
			};

			static color3f skyblue()
			{
				return color3f(135/255.0f, 206/255.0f, 235/255.0f);
			};

			static color3f slateblue()
			{
				return color3f(106/255.0f, 90/255.0f, 205/255.0f);
			};

			static color3f slategray()
			{
				return color3f(112/255.0f, 128/255.0f, 144/255.0f);
			};

			static color3f snow()
			{
				return color3f(255/255.0f, 250/255.0f, 250/255.0f);
			};

			static color3f springgreen()
			{
				return color3f(0/255.0f, 255/255.0f, 127/255.0f);
			};

			static color3f steelblue()
			{
				return color3f(70/255.0f, 130/255.0f, 180/255.0f);
			};

			static color3f tan()
			{
				return color3f(210/255.0f, 180/255.0f, 140/255.0f);
			};

			static color3f teal()
			{
				return color3f(0/255.0f, 128/255.0f, 128/255.0f);
			};

			static color3f thistle()
			{
				return color3f(216/255.0f, 191/255.0f, 216/255.0f);
			};

			static color3f tomato()
			{
				return color3f(255/255.0f, 99/255.0f, 71/255.0f);
			};

			static color3f turquoise()
			{
				return color3f(64/255.0f, 224/255.0f, 208/255.0f);
			};

			static color3f violet()
			{
				return color3f(238/255.0f, 130/255.0f, 238/255.0f);
			};

			static color3f wheat()
			{
				return color3f(245/255.0f, 222/255.0f, 179/255.0f);
			};

			static color3f white()
			{
				return color3f(255/255.0f, 255/255.0f, 255/255.0f);
			};

			static color3f whitesmoke()
			{
				return color3f(245/255.0f, 245/255.0f, 245/255.0f);
			};

			static color3f yellow()
			{
				return color3f(255/255.0f, 255/255.0f, 0/255.0f);
			};

			static color3f yellowgreen()
			{
				return color3f(154/255.0f, 205/255.0f, 50/255.0f);
			};

			static color3f random()
			{
				const int color_array_size = 140;
				static color3f colors[color_array_size] =
				{
					aliceBlue(),
					antiqueWhite(),
					aqua(),
					aquaMarine(),
					azure(),
					beige(),
					bisque(),
					black(),
					blanchedalmond(),
					blue(),
					blueViolet(),
					brown(),
					burlywood(),
					cadetBlue(),
					chartreuse(),
					chocolate(),
					coral(),
					cornflowerblue(),
					cornsilk(),
					crimson(),
					cyan(),
					darkOlivegreen(),
					darkblue(),
					darkcyan(),
					darkgoldenrod(),
					darkgray(),
					darkgreen(),
					darkkhaki(),
					darkmagenta(),
					darkorange(),
					darkorchid(),
					darkRed(),
					darksalmon(),
					darkseagreen(),
					darkslateblue(),
					darkslategray(),
					darkturquoise(),
					darkviolet(),
					deeppink(),
					deepskyblue(),
					dimgray(),
					dodgerblue(),
					firebrick(),
					floralwhite(),
					forestgreen(),
					fuchsia(),
					gainsboro(),
					ghostwhite(),
					gold(),
					goldenrod(),
					gray(),
					green(),
					greenyellow(),
					honeydew(),
					hotpink(),
					indianred(),
					indigo(),
					ivory(),
					khaki(),
					lavender(),
					lavenderblush(),
					lawngreen(),
					lemonchiffon(),
					lightblue(),
					lightcoral(),
					lightcyan(),
					lightgoldenrodyellow(),
					lightgreen(),
					lightgrey(),
					lightpink(),
					lightsalmon(),
					lightseagreen(),
					lightskyblue(),
					lightslategray(),
					lightsteelblue(),
					lightyellow(),
					lime(),
					limegreen(),
					linen(),
					magenta(),
					maroon(),
					mediumaquamarine(),
					mediumblue(),
					mediumorchid(),
					mediumpurple(),
					mediumseagreen(),
					mediumslateblue(),
					mediumspringgreen(),
					mediumturquoise(),
					mediumvioletred(),
					midnightblue(),
					mintcream(),
					mistyrose(),
					moccasin(),
					navajowhite(),
					navy(),
					oldlace(),
					olive(),
					olivedrab(),
					orange(),
					orangered(),
					orchid(),
					palegoldenrod(),
					palegreen(),
					paleturquoise(),
					palevioletred(),
					papayawhip(),
					peachpuff(),
					peru(),
					pink(),
					plum(),
					powderblue(),
					purple(),
					red(),
					rosybrown(),
					royalblue(),
					saddlebrown(),
					salmon(),
					sandybrown(),
					seagreen(),
					seashell(),
					sienna(),
					silver(),
					skyblue(),
					slateblue(),
					slategray(),
					snow(),
					springgreen(),
					steelblue(),
					tan(),
					teal(),
					thistle(),
					tomato(),
					turquoise(),
					violet(),
					wheat(),
					white(),
					whitesmoke(),
					yellow(),
					yellowgreen()
				};

				static buw::RandomNumberGenerator rng;
				int index = rng.getInteger(0, color_array_size-1);

				BLUE_ASSERT(index < color_array_size, "Invalid index.");

				return colors[index];
			}
		};

		template<>
		struct colorConstants<color4f>
		{
			static color4f black()
			{
				return color4f(0/255.0f, 0/255.0f, 0/255.0f, 1.0f);
			};

			static color4f white()
			{
				return color4f(255/255.0f, 255/255.0f, 255/255.0f, 1.0f);
			};
		};

		template<>
		struct colorConstants<color3b>
		{
			static color3b aliceBlue()
			{
				return color3b(240, 248, 255);
			};

			static color3b antiqueWhite()
			{
				return color3b(250, 235, 215);
			};

			static color3b aqua()
			{
				return color3b(0, 255, 255);
			};

			static color3b aquaMarine()
			{
				return color3b(127, 255, 212);
			};

			static color3b azure()
			{
				return color3b(240, 255, 255);
			};

			static color3b beige()
			{
				return color3b(245, 245, 220);
			};

			static color3b bisque()
			{
				return color3b(255, 228, 196);
			};

			static color3b black()
			{
				return color3b(0, 0, 0);
			};

			static color3b blanchedalmond()
			{
				return color3b(255, 235, 205);
			};

			static color3b blue()
			{
				return color3b(0, 0, 255);
			};

			static color3b blueViolet()
			{
				return color3b(138, 43, 226);
			};

			static color3b brown()
			{
				return color3b(165, 42, 42);
			};

			static color3b burlywood()
			{
				return color3b(222, 184, 135);
			};

			static color3b cadetBlue()
			{
				return color3b(95, 158, 160);
			};

			static color3b chartreuse()
			{
				return color3b(127, 255, 0);
			};

			static color3b chocolate()
			{
				return color3b(210, 105, 30);
			};

			static color3b coral()
			{
				return color3b(255, 127, 80);
			};

			static color3b cornflowerblue()
			{
				return color3b(100, 149, 237);
			};

			static color3b cornsilk()
			{
				return color3b(255, 248, 220);
			};

			static color3b crimson()
			{
				return color3b(220, 20, 60);
			};

			static color3b cyan()
			{
				return color3b(0, 255, 255);
			};

			static color3b darkOlivegreen()
			{
				return color3b(85, 107, 47);
			};

			static color3b darkblue()
			{
				return color3b(0, 0, 139);
			};

			static color3b darkcyan()
			{
				return color3b(0, 139, 139);
			};

			static color3b darkgoldenrod()
			{
				return color3b(184, 134, 11);
			};

			static color3b darkgray()
			{
				return color3b(169, 169, 169);
			};

			static color3b darkgreen()
			{
				return color3b(0, 100, 0);
			};

			static color3b darkkhaki()
			{
				return color3b(189, 183, 107);
			};

			static color3b darkmagenta()
			{
				return color3b(139, 0, 139);
			};

			static color3b darkorange()
			{
				return color3b(255, 140, 0);
			};

			static color3b darkorchid()
			{
				return color3b(153, 50, 204);
			};

			static color3b darkRed()
			{
				return color3b(139, 0, 0);
			};

			static color3b darksalmon()
			{
				return color3b(233, 150, 122);
			};

			static color3b darkseagreen()
			{
				return color3b(143, 188, 143);
			};

			static color3b darkslateblue()
			{
				return color3b(72, 61, 139);
			};

			static color3b darkslategray()
			{
				return color3b(47, 79, 79);
			};

			static color3b darkturquoise()
			{
				return color3b(0, 206, 209);
			};

			static color3b darkviolet()
			{
				return color3b(148, 0, 211);
			};

			static color3b deeppink()
			{
				return color3b(255, 20, 147);
			};

			static color3b deepskyblue()
			{
				return color3b(0, 191, 255);
			};

			static color3b dimgray()
			{
				return color3b(105, 105, 105);
			};

			static color3b dodgerblue()
			{
				return color3b(30, 144, 255);
			};

			static color3b firebrick()
			{
				return color3b(178, 34, 34);
			};

			static color3b floralwhite()
			{
				return color3b(255, 250, 240);
			};

			static color3b forestgreen()
			{
				return color3b(34, 139, 34);
			};

			static color3b fuchsia()
			{
				return color3b(255, 0, 255);
			};

			static color3b gainsboro()
			{
				return color3b(220, 220, 220);
			};

			static color3b ghostwhite()
			{
				return color3b(248, 248, 255);
			};

			static color3b gold()
			{
				return color3b(255, 215, 0);
			};

			static color3b goldenrod()
			{
				return color3b(218, 165, 32);
			};

			static color3b gray()
			{
				return color3b(128, 128, 128);
			};

			static color3b green()
			{
				return color3b(0, 128, 0);
			};

			static color3b greenyellow()
			{
				return color3b(173, 255, 47);
			};

			static color3b honeydew()
			{
				return color3b(240, 255, 240);
			};

			static color3b hotpink()
			{
				return color3b(255, 105, 180);
			};

			static color3b indianred()
			{
				return color3b(205, 92, 92);
			};

			static color3b indigo()
			{
				return color3b(75, 0, 130);
			};

			static color3b ivory()
			{
				return color3b(255, 255, 240);
			};

			static color3b khaki()
			{
				return color3b(240, 230, 140);
			};

			static color3b lavender()
			{
				return color3b(230, 230, 250);
			};

			static color3b lavenderblush()
			{
				return color3b(255, 240, 245);
			};

			static color3b lawngreen()
			{
				return color3b(124, 252, 0);
			};

			static color3b lemonchiffon()
			{
				return color3b(255, 250, 205);
			};

			static color3b lightblue()
			{
				return color3b(173, 216, 230);
			};

			static color3b lightcoral()
			{
				return color3b(240, 128, 128);
			};

			static color3b lightcyan()
			{
				return color3b(224, 255, 255);
			};

			static color3b lightgoldenrodyellow()
			{
				return color3b(250, 250, 210);
			};

			static color3b lightgreen()
			{
				return color3b(144, 238, 144);
			};

			static color3b lightgrey()
			{
				return color3b(211, 211, 211);
			};

			static color3b lightpink()
			{
				return color3b(255, 182, 193);
			};

			static color3b lightsalmon()
			{
				return color3b(255, 160, 122);
			};

			static color3b lightseagreen()
			{
				return color3b(32, 178, 170);
			};

			static color3b lightskyblue()
			{
				return color3b(135, 206, 250);
			};

			static color3b lightslategray()
			{
				return color3b(119, 136, 153);
			};

			static color3b lightsteelblue()
			{
				return color3b(176, 196, 222);
			};

			static color3b lightyellow()
			{
				return color3b(255, 255, 224);
			};

			static color3b lime()
			{
				return color3b(0, 255, 0);
			};

			static color3b limegreen()
			{
				return color3b(50, 205, 50);
			};

			static color3b linen()
			{
				return color3b(250, 240, 230);
			};

			static color3b magenta()
			{
				return color3b(255, 0, 255);
			};

			static color3b maroon()
			{
				return color3b(128, 0, 0);
			};

			static color3b mediumaquamarine()
			{
				return color3b(102, 205, 170);
			};

			static color3b mediumblue()
			{
				return color3b(0, 0, 205);
			};

			static color3b mediumorchid()
			{
				return color3b(186, 85, 211);
			};

			static color3b mediumpurple()
			{
				return color3b(147, 112, 219);
			};

			static color3b mediumseagreen()
			{
				return color3b(60, 179, 113);
			};

			static color3b mediumslateblue()
			{
				return color3b(123, 104, 238);
			};

			static color3b mediumspringgreen()
			{
				return color3b(0, 250, 154);
			};

			static color3b mediumturquoise()
			{
				return color3b(72, 209, 204);
			};

			static color3b mediumvioletred()
			{
				return color3b(199, 21, 133);
			};

			static color3b midnightblue()
			{
				return color3b(25, 25, 112);
			};

			static color3b mintcream()
			{
				return color3b(245, 255, 250);
			};

			static color3b mistyrose()
			{
				return color3b(255, 228, 225);
			};

			static color3b moccasin()
			{
				return color3b(255, 228, 181);
			};

			static color3b navajowhite()
			{
				return color3b(255, 222, 173);
			};

			static color3b navy()
			{
				return color3b(0, 0, 128);
			};

			static color3b oldlace()
			{
				return color3b(253, 245, 230);
			};

			static color3b olive()
			{
				return color3b(128, 128, 0);
			};

			static color3b olivedrab()
			{
				return color3b(107, 142, 35);
			};

			static color3b orange()
			{
				return color3b(255, 165, 0);
			};

			static color3b orangered()
			{
				return color3b(255, 69, 0);
			};

			static color3b orchid()
			{
				return color3b(218, 112, 214);
			};

			static color3b palegoldenrod()
			{
				return color3b(238, 232, 170);
			};

			static color3b palegreen()
			{
				return color3b(152, 251, 152);
			};

			static color3b paleturquoise()
			{
				return color3b(175, 238, 238);
			};

			static color3b palevioletred()
			{
				return color3b(219, 112, 147);
			};

			static color3b papayawhip()
			{
				return color3b(255, 239, 213);
			};

			static color3b peachpuff()
			{
				return color3b(255, 218, 185);
			};

			static color3b peru()
			{
				return color3b(205, 133, 63);
			};

			static color3b pink()
			{
				return color3b(255, 192, 203);
			};

			static color3b plum()
			{
				return color3b(221, 160, 221);
			};

			static color3b powderblue()
			{
				return color3b(176, 224, 230);
			};

			static color3b purple()
			{
				return color3b(128, 0, 128);
			};

			static color3b red()
			{
				return color3b(255, 0, 0);
			};

			static color3b rosybrown()
			{
				return color3b(188, 143, 143);
			};

			static color3b royalblue()
			{
				return color3b(65, 105, 225);
			};

			static color3b saddlebrown()
			{
				return color3b(139, 69, 19);
			};

			static color3b salmon()
			{
				return color3b(250, 128, 114);
			};

			static color3b sandybrown()
			{
				return color3b(244, 164, 96);
			};

			static color3b seagreen()
			{
				return color3b(46, 139, 87);
			};

			static color3b seashell()
			{
				return color3b(255, 245, 238);
			};

			static color3b sienna()
			{
				return color3b(160, 82, 45);
			};

			static color3b silver()
			{
				return color3b(192, 192, 192);
			};

			static color3b skyblue()
			{
				return color3b(135, 206, 235);
			};

			static color3b slateblue()
			{
				return color3b(106, 90, 205);
			};

			static color3b slategray()
			{
				return color3b(112, 128, 144);
			};

			static color3b snow()
			{
				return color3b(255, 250, 250);
			};

			static color3b springgreen()
			{
				return color3b(0, 255, 127);
			};

			static color3b steelblue()
			{
				return color3b(70, 130, 180);
			};

			static color3b tan()
			{
				return color3b(210, 180, 140);
			};

			static color3b teal()
			{
				return color3b(0, 128, 128);
			};

			static color3b thistle()
			{
				return color3b(216, 191, 216);
			};

			static color3b tomato()
			{
				return color3b(255, 99, 71);
			};

			static color3b turquoise()
			{
				return color3b(64, 224, 208);
			};

			static color3b violet()
			{
				return color3b(238, 130, 238);
			};

			static color3b wheat()
			{
				return color3b(245, 222, 179);
			};

			static color3b white()
			{
				return color3b(255, 255, 255);
			};

			static color3b whitesmoke()
			{
				return color3b(245, 245, 245);
			};

			static color3b yellow()
			{
				return color3b(255, 255, 0);
			};

			static color3b yellowgreen()
			{
				return color3b(154, 205, 50);
			};
		};

		typedef colorConstants<color3f> colorConstants3f;
		typedef colorConstants<color4f> colorConstants4f;
	} // end namespace ImageProcessing
} // end namespace BlueFramework

namespace buw
{
	using BlueFramework::ImageProcessing::colorConstants;
	using BlueFramework::ImageProcessing::colorConstants3f;
	using BlueFramework::ImageProcessing::colorConstants4f;
}

#endif // end define BlueFramework_ImageProcessing_ColorConstants_e730a33d_4053_4c52_bd16_ecf1fba26816_h
