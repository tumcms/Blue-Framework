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
#ifndef BlueFramework_ImageProcessing_ColorConstants_e730a33d_4053_4c52_bd16_ecf1fba26816_h
#define BlueFramework_ImageProcessing_ColorConstants_e730a33d_4053_4c52_bd16_ecf1fba26816_h

#include "BlueFramework/Core/assert.h"
#include "BlueFramework/ImageProcessing/Color.h"

namespace BlueFramework
{
	namespace ImageProcessing
	{
		// Implements different color constants.
		template<typename ColorType>
		struct ColorConstants
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
		struct ColorConstants<Color3f>
		{
			static Color3f aliceBlue()
			{
				return Color3f(240/255.0f, 248/255.0f, 255/255.0f);
			};

			static Color3f antiqueWhite()
			{
				return Color3f(250/255.0f, 235/255.0f, 215/255.0f);
			};

			static Color3f aqua()
			{
				return Color3f(0/255.0f, 255/255.0f, 255/255.0f);
			};

			static Color3f aquaMarine()
			{
				return Color3f(127/255.0f, 255/255.0f, 212/255.0f);
			};

			static Color3f azure()
			{
				return Color3f(240/255.0f, 255/255.0f, 255/255.0f);
			};

			static Color3f beige()
			{
				return Color3f(245/255.0f, 245/255.0f, 220/255.0f);
			};

			static Color3f bisque()
			{
				return Color3f(255/255.0f, 228/255.0f, 196/255.0f);
			};

			static Color3f black()
			{
				return Color3f(0/255.0f, 0/255.0f, 0/255.0f);
			};

			static Color3f blanchedalmond()
			{
				return Color3f(255/255.0f, 235/255.0f, 205/255.0f);
			};

			static Color3f blue()
			{
				return Color3f(0/255.0f, 0/255.0f, 255/255.0f);
			};

			static Color3f blueViolet()
			{
				return Color3f(138/255.0f, 43/255.0f, 226/255.0f);
			};

			static Color3f brown()
			{
				return Color3f(165/255.0f, 42/255.0f, 42/255.0f);
			};

			static Color3f burlywood()
			{
				return Color3f(222/255.0f, 184/255.0f, 135/255.0f);
			};

			static Color3f cadetBlue()
			{
				return Color3f(95/255.0f, 158/255.0f, 160/255.0f);
			};

			static Color3f chartreuse()
			{
				return Color3f(127/255.0f, 255/255.0f, 0/255.0f);
			};

			static Color3f chocolate()
			{
				return Color3f(210/255.0f, 105/255.0f, 30/255.0f);
			};

			static Color3f coral()
			{
				return Color3f(255/255.0f, 127/255.0f, 80/255.0f);
			};

			static Color3f cornflowerblue()
			{
				return Color3f(100/255.0f, 149/255.0f, 237/255.0f);
			};

			static Color3f cornsilk()
			{
				return Color3f(255/255.0f, 248/255.0f, 220/255.0f);
			};

			static Color3f crimson()
			{
				return Color3f(220/255.0f, 20/255.0f, 60/255.0f);
			};

			static Color3f cyan()
			{
				return Color3f(0/255.0f, 255/255.0f, 255/255.0f);
			};

			static Color3f darkOlivegreen()
			{
				return Color3f(85/255.0f, 107/255.0f, 47/255.0f);
			};

			static Color3f darkblue()
			{
				return Color3f(0/255.0f, 0/255.0f, 139/255.0f);
			};

			static Color3f darkcyan()
			{
				return Color3f(0/255.0f, 139/255.0f, 139/255.0f);
			};

			static Color3f darkgoldenrod()
			{
				return Color3f(184/255.0f, 134/255.0f, 11/255.0f);
			};

			static Color3f darkgray()
			{
				return Color3f(169/255.0f, 169/255.0f, 169/255.0f);
			};

			static Color3f darkgreen()
			{
				return Color3f(0/255.0f, 100/255.0f, 0/255.0f);
			};

			static Color3f darkkhaki()
			{
				return Color3f(189/255.0f, 183/255.0f, 107/255.0f);
			};

			static Color3f darkmagenta()
			{
				return Color3f(139/255.0f, 0/255.0f, 139/255.0f);
			};

			static Color3f darkorange()
			{
				return Color3f(255/255.0f, 140/255.0f, 0/255.0f);
			};

			static Color3f darkorchid()
			{
				return Color3f(153/255.0f, 50/255.0f, 204/255.0f);
			};

			static Color3f darkRed()
			{
				return Color3f(139/255.0f, 0/255.0f, 0/255.0f);
			};

			static Color3f darksalmon()
			{
				return Color3f(233/255.0f, 150/255.0f, 122/255.0f);
			};

			static Color3f darkseagreen()
			{
				return Color3f(143/255.0f, 188/255.0f, 143/255.0f);
			};

			static Color3f darkslateblue()
			{
				return Color3f(72/255.0f, 61/255.0f, 139/255.0f);
			};

			static Color3f darkslategray()
			{
				return Color3f(47/255.0f, 79/255.0f, 79/255.0f);
			};

			static Color3f darkturquoise()
			{
				return Color3f(0/255.0f, 206/255.0f, 209/255.0f);
			};

			static Color3f darkviolet()
			{
				return Color3f(148/255.0f, 0/255.0f, 211/255.0f);
			};

			static Color3f deeppink()
			{
				return Color3f(255/255.0f, 20/255.0f, 147/255.0f);
			};

			static Color3f deepskyblue()
			{
				return Color3f(0/255.0f, 191/255.0f, 255/255.0f);
			};

			static Color3f dimgray()
			{
				return Color3f(105/255.0f, 105/255.0f, 105/255.0f);
			};

			static Color3f dodgerblue()
			{
				return Color3f(30/255.0f, 144/255.0f, 255/255.0f);
			};

			static Color3f firebrick()
			{
				return Color3f(178/255.0f, 34/255.0f, 34/255.0f);
			};

			static Color3f floralwhite()
			{
				return Color3f(255/255.0f, 250/255.0f, 240/255.0f);
			};

			static Color3f forestgreen()
			{
				return Color3f(34/255.0f, 139/255.0f, 34/255.0f);
			};

			static Color3f fuchsia()
			{
				return Color3f(255/255.0f, 0/255.0f, 255/255.0f);
			};

			static Color3f gainsboro()
			{
				return Color3f(220/255.0f, 220/255.0f, 220/255.0f);
			};

			static Color3f ghostwhite()
			{
				return Color3f(248/255.0f, 248/255.0f, 255/255.0f);
			};

			static Color3f gold()
			{
				return Color3f(255/255.0f, 215/255.0f, 0/255.0f);
			};

			static Color3f goldenrod()
			{
				return Color3f(218/255.0f, 165/255.0f, 32/255.0f);
			};

			static Color3f gray()
			{
				return Color3f(128/255.0f, 128/255.0f, 128/255.0f);
			};

			static Color3f green()
			{
				return Color3f(0/255.0f, 128/255.0f, 0/255.0f);
			};

			static Color3f greenyellow()
			{
				return Color3f(173/255.0f, 255/255.0f, 47/255.0f);
			};

			static Color3f honeydew()
			{
				return Color3f(240/255.0f, 255/255.0f, 240/255.0f);
			};

			static Color3f hotpink()
			{
				return Color3f(255/255.0f, 105/255.0f, 180/255.0f);
			};

			static Color3f indianred()
			{
				return Color3f(205/255.0f, 92/255.0f, 92/255.0f);
			};

			static Color3f indigo()
			{
				return Color3f(75/255.0f, 0/255.0f, 130/255.0f);
			};

			static Color3f ivory()
			{
				return Color3f(255/255.0f, 255/255.0f, 240/255.0f);
			};

			static Color3f khaki()
			{
				return Color3f(240/255.0f, 230/255.0f, 140/255.0f);
			};

			static Color3f lavender()
			{
				return Color3f(230/255.0f, 230/255.0f, 250/255.0f);
			};

			static Color3f lavenderblush()
			{
				return Color3f(255/255.0f, 240/255.0f, 245/255.0f);
			};

			static Color3f lawngreen()
			{
				return Color3f(124/255.0f, 252/255.0f, 0/255.0f);
			};

			static Color3f lemonchiffon()
			{
				return Color3f(255/255.0f, 250/255.0f, 205/255.0f);
			};

			static Color3f lightblue()
			{
				return Color3f(173/255.0f, 216/255.0f, 230/255.0f);
			};

			static Color3f lightcoral()
			{
				return Color3f(240/255.0f, 128/255.0f, 128/255.0f);
			};

			static Color3f lightcyan()
			{
				return Color3f(224/255.0f, 255/255.0f, 255/255.0f);
			};

			static Color3f lightgoldenrodyellow()
			{
				return Color3f(250/255.0f, 250/255.0f, 210/255.0f);
			};

			static Color3f lightgreen()
			{
				return Color3f(144/255.0f, 238/255.0f, 144/255.0f);
			};

			static Color3f lightgrey()
			{
				return Color3f(211/255.0f, 211/255.0f, 211/255.0f);
			};

			static Color3f lightpink()
			{
				return Color3f(255/255.0f, 182/255.0f, 193/255.0f);
			};

			static Color3f lightsalmon()
			{
				return Color3f(255/255.0f, 160/255.0f, 122/255.0f);
			};

			static Color3f lightseagreen()
			{
				return Color3f(32/255.0f, 178/255.0f, 170/255.0f);
			};

			static Color3f lightskyblue()
			{
				return Color3f(135/255.0f, 206/255.0f, 250/255.0f);
			};

			static Color3f lightslategray()
			{
				return Color3f(119/255.0f, 136/255.0f, 153/255.0f);
			};

			static Color3f lightsteelblue()
			{
				return Color3f(176/255.0f, 196/255.0f, 222/255.0f);
			};

			static Color3f lightyellow()
			{
				return Color3f(255/255.0f, 255/255.0f, 224/255.0f);
			};

			static Color3f lime()
			{
				return Color3f(0/255.0f, 255/255.0f, 0/255.0f);
			};

			static Color3f limegreen()
			{
				return Color3f(50/255.0f, 205/255.0f, 50/255.0f);
			};

			static Color3f linen()
			{
				return Color3f(250/255.0f, 240/255.0f, 230/255.0f);
			};

			static Color3f magenta()
			{
				return Color3f(255/255.0f, 0/255.0f, 255/255.0f);
			};

			static Color3f maroon()
			{
				return Color3f(128/255.0f, 0/255.0f, 0/255.0f);
			};

			static Color3f mediumaquamarine()
			{
				return Color3f(102/255.0f, 205/255.0f, 170/255.0f);
			};

			static Color3f mediumblue()
			{
				return Color3f(0/255.0f, 0/255.0f, 205/255.0f);
			};

			static Color3f mediumorchid()
			{
				return Color3f(186/255.0f, 85/255.0f, 211/255.0f);
			};

			static Color3f mediumpurple()
			{
				return Color3f(147/255.0f, 112/255.0f, 219/255.0f);
			};

			static Color3f mediumseagreen()
			{
				return Color3f(60/255.0f, 179/255.0f, 113/255.0f);
			};

			static Color3f mediumslateblue()
			{
				return Color3f(123/255.0f, 104/255.0f, 238/255.0f);
			};

			static Color3f mediumspringgreen()
			{
				return Color3f(0/255.0f, 250/255.0f, 154/255.0f);
			};

			static Color3f mediumturquoise()
			{
				return Color3f(72/255.0f, 209/255.0f, 204/255.0f);
			};

			static Color3f mediumvioletred()
			{
				return Color3f(199/255.0f, 21/255.0f, 133/255.0f);
			};

			static Color3f midnightblue()
			{
				return Color3f(25/255.0f, 25/255.0f, 112/255.0f);
			};

			static Color3f mintcream()
			{
				return Color3f(245/255.0f, 255/255.0f, 250/255.0f);
			};

			static Color3f mistyrose()
			{
				return Color3f(255/255.0f, 228/255.0f, 225/255.0f);
			};

			static Color3f moccasin()
			{
				return Color3f(255/255.0f, 228/255.0f, 181/255.0f);
			};

			static Color3f navajowhite()
			{
				return Color3f(255/255.0f, 222/255.0f, 173/255.0f);
			};

			static Color3f navy()
			{
				return Color3f(0/255.0f, 0/255.0f, 128/255.0f);
			};

			static Color3f oldlace()
			{
				return Color3f(253/255.0f, 245/255.0f, 230/255.0f);
			};

			static Color3f olive()
			{
				return Color3f(128/255.0f, 128/255.0f, 0/255.0f);
			};

			static Color3f olivedrab()
			{
				return Color3f(107/255.0f, 142/255.0f, 35/255.0f);
			};

			static Color3f orange()
			{
				return Color3f(255/255.0f, 165/255.0f, 0/255.0f);
			};

			static Color3f orangered()
			{
				return Color3f(255/255.0f, 69/255.0f, 0/255.0f);
			};

			static Color3f orchid()
			{
				return Color3f(218/255.0f, 112/255.0f, 214/255.0f);
			};

			static Color3f palegoldenrod()
			{
				return Color3f(238/255.0f, 232/255.0f, 170/255.0f);
			};

			static Color3f palegreen()
			{
				return Color3f(152/255.0f, 251/255.0f, 152/255.0f);
			};

			static Color3f paleturquoise()
			{
				return Color3f(175/255.0f, 238/255.0f, 238/255.0f);
			};

			static Color3f palevioletred()
			{
				return Color3f(219/255.0f, 112/255.0f, 147/255.0f);
			};

			static Color3f papayawhip()
			{
				return Color3f(255/255.0f, 239/255.0f, 213/255.0f);
			};

			static Color3f peachpuff()
			{
				return Color3f(255/255.0f, 218/255.0f, 185/255.0f);
			};

			static Color3f peru()
			{
				return Color3f(205/255.0f, 133/255.0f, 63/255.0f);
			};

			static Color3f pink()
			{
				return Color3f(255/255.0f, 192/255.0f, 203/255.0f);
			};

			static Color3f plum()
			{
				return Color3f(221/255.0f, 160/255.0f, 221/255.0f);
			};

			static Color3f powderblue()
			{
				return Color3f(176/255.0f, 224/255.0f, 230/255.0f);
			};

			static Color3f purple()
			{
				return Color3f(128/255.0f, 0/255.0f, 128/255.0f);
			};

			static Color3f red()
			{
				return Color3f(255/255.0f, 0/255.0f, 0/255.0f);
			};

			static Color3f rosybrown()
			{
				return Color3f(188/255.0f, 143/255.0f, 143/255.0f);
			};

			static Color3f royalblue()
			{
				return Color3f(65/255.0f, 105/255.0f, 225/255.0f);
			};

			static Color3f saddlebrown()
			{
				return Color3f(139/255.0f, 69/255.0f, 19/255.0f);
			};

			static Color3f salmon()
			{
				return Color3f(250/255.0f, 128/255.0f, 114/255.0f);
			};

			static Color3f sandybrown()
			{
				return Color3f(244/255.0f, 164/255.0f, 96/255.0f);
			};

			static Color3f seagreen()
			{
				return Color3f(46/255.0f, 139/255.0f, 87/255.0f);
			};

			static Color3f seashell()
			{
				return Color3f(255/255.0f, 245/255.0f, 238/255.0f);
			};

			static Color3f sienna()
			{
				return Color3f(160/255.0f, 82/255.0f, 45/255.0f);
			};

			static Color3f silver()
			{
				return Color3f(192/255.0f, 192/255.0f, 192/255.0f);
			};

			static Color3f skyblue()
			{
				return Color3f(135/255.0f, 206/255.0f, 235/255.0f);
			};

			static Color3f slateblue()
			{
				return Color3f(106/255.0f, 90/255.0f, 205/255.0f);
			};

			static Color3f slategray()
			{
				return Color3f(112/255.0f, 128/255.0f, 144/255.0f);
			};

			static Color3f snow()
			{
				return Color3f(255/255.0f, 250/255.0f, 250/255.0f);
			};

			static Color3f springgreen()
			{
				return Color3f(0/255.0f, 255/255.0f, 127/255.0f);
			};

			static Color3f steelblue()
			{
				return Color3f(70/255.0f, 130/255.0f, 180/255.0f);
			};

			static Color3f tan()
			{
				return Color3f(210/255.0f, 180/255.0f, 140/255.0f);
			};

			static Color3f teal()
			{
				return Color3f(0/255.0f, 128/255.0f, 128/255.0f);
			};

			static Color3f thistle()
			{
				return Color3f(216/255.0f, 191/255.0f, 216/255.0f);
			};

			static Color3f tomato()
			{
				return Color3f(255/255.0f, 99/255.0f, 71/255.0f);
			};

			static Color3f turquoise()
			{
				return Color3f(64/255.0f, 224/255.0f, 208/255.0f);
			};

			static Color3f violet()
			{
				return Color3f(238/255.0f, 130/255.0f, 238/255.0f);
			};

			static Color3f wheat()
			{
				return Color3f(245/255.0f, 222/255.0f, 179/255.0f);
			};

			static Color3f white()
			{
				return Color3f(255/255.0f, 255/255.0f, 255/255.0f);
			};

			static Color3f whitesmoke()
			{
				return Color3f(245/255.0f, 245/255.0f, 245/255.0f);
			};

			static Color3f yellow()
			{
				return Color3f(255/255.0f, 255/255.0f, 0/255.0f);
			};

			static Color3f yellowgreen()
			{
				return Color3f(154/255.0f, 205/255.0f, 50/255.0f);
			};

			/*static Color3f random()
			{
				const int color_array_size = 140;
				static Color3f colors[color_array_size] =
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
			}*/
		};

		template<>
		struct ColorConstants<Color4f>
		{
			static Color4f black()
			{
				return Color4f(0/255.0f, 0/255.0f, 0/255.0f, 1.0f);
			};

			static Color4f white()
			{
				return Color4f(255/255.0f, 255/255.0f, 255/255.0f, 1.0f);
			};
		};

		template<>
		struct ColorConstants<Color3b>
		{
			static Color3b aliceBlue()
			{
				return Color3b(240, 248, 255);
			};

			static Color3b antiqueWhite()
			{
				return Color3b(250, 235, 215);
			};

			static Color3b aqua()
			{
				return Color3b(0, 255, 255);
			};

			static Color3b aquaMarine()
			{
				return Color3b(127, 255, 212);
			};

			static Color3b azure()
			{
				return Color3b(240, 255, 255);
			};

			static Color3b beige()
			{
				return Color3b(245, 245, 220);
			};

			static Color3b bisque()
			{
				return Color3b(255, 228, 196);
			};

			static Color3b black()
			{
				return Color3b(0, 0, 0);
			};

			static Color3b blanchedalmond()
			{
				return Color3b(255, 235, 205);
			};

			static Color3b blue()
			{
				return Color3b(0, 0, 255);
			};

			static Color3b blueViolet()
			{
				return Color3b(138, 43, 226);
			};

			static Color3b brown()
			{
				return Color3b(165, 42, 42);
			};

			static Color3b burlywood()
			{
				return Color3b(222, 184, 135);
			};

			static Color3b cadetBlue()
			{
				return Color3b(95, 158, 160);
			};

			static Color3b chartreuse()
			{
				return Color3b(127, 255, 0);
			};

			static Color3b chocolate()
			{
				return Color3b(210, 105, 30);
			};

			static Color3b coral()
			{
				return Color3b(255, 127, 80);
			};

			static Color3b cornflowerblue()
			{
				return Color3b(100, 149, 237);
			};

			static Color3b cornsilk()
			{
				return Color3b(255, 248, 220);
			};

			static Color3b crimson()
			{
				return Color3b(220, 20, 60);
			};

			static Color3b cyan()
			{
				return Color3b(0, 255, 255);
			};

			static Color3b darkOlivegreen()
			{
				return Color3b(85, 107, 47);
			};

			static Color3b darkblue()
			{
				return Color3b(0, 0, 139);
			};

			static Color3b darkcyan()
			{
				return Color3b(0, 139, 139);
			};

			static Color3b darkgoldenrod()
			{
				return Color3b(184, 134, 11);
			};

			static Color3b darkgray()
			{
				return Color3b(169, 169, 169);
			};

			static Color3b darkgreen()
			{
				return Color3b(0, 100, 0);
			};

			static Color3b darkkhaki()
			{
				return Color3b(189, 183, 107);
			};

			static Color3b darkmagenta()
			{
				return Color3b(139, 0, 139);
			};

			static Color3b darkorange()
			{
				return Color3b(255, 140, 0);
			};

			static Color3b darkorchid()
			{
				return Color3b(153, 50, 204);
			};

			static Color3b darkRed()
			{
				return Color3b(139, 0, 0);
			};

			static Color3b darksalmon()
			{
				return Color3b(233, 150, 122);
			};

			static Color3b darkseagreen()
			{
				return Color3b(143, 188, 143);
			};

			static Color3b darkslateblue()
			{
				return Color3b(72, 61, 139);
			};

			static Color3b darkslategray()
			{
				return Color3b(47, 79, 79);
			};

			static Color3b darkturquoise()
			{
				return Color3b(0, 206, 209);
			};

			static Color3b darkviolet()
			{
				return Color3b(148, 0, 211);
			};

			static Color3b deeppink()
			{
				return Color3b(255, 20, 147);
			};

			static Color3b deepskyblue()
			{
				return Color3b(0, 191, 255);
			};

			static Color3b dimgray()
			{
				return Color3b(105, 105, 105);
			};

			static Color3b dodgerblue()
			{
				return Color3b(30, 144, 255);
			};

			static Color3b firebrick()
			{
				return Color3b(178, 34, 34);
			};

			static Color3b floralwhite()
			{
				return Color3b(255, 250, 240);
			};

			static Color3b forestgreen()
			{
				return Color3b(34, 139, 34);
			};

			static Color3b fuchsia()
			{
				return Color3b(255, 0, 255);
			};

			static Color3b gainsboro()
			{
				return Color3b(220, 220, 220);
			};

			static Color3b ghostwhite()
			{
				return Color3b(248, 248, 255);
			};

			static Color3b gold()
			{
				return Color3b(255, 215, 0);
			};

			static Color3b goldenrod()
			{
				return Color3b(218, 165, 32);
			};

			static Color3b gray()
			{
				return Color3b(128, 128, 128);
			};

			static Color3b green()
			{
				return Color3b(0, 128, 0);
			};

			static Color3b greenyellow()
			{
				return Color3b(173, 255, 47);
			};

			static Color3b honeydew()
			{
				return Color3b(240, 255, 240);
			};

			static Color3b hotpink()
			{
				return Color3b(255, 105, 180);
			};

			static Color3b indianred()
			{
				return Color3b(205, 92, 92);
			};

			static Color3b indigo()
			{
				return Color3b(75, 0, 130);
			};

			static Color3b ivory()
			{
				return Color3b(255, 255, 240);
			};

			static Color3b khaki()
			{
				return Color3b(240, 230, 140);
			};

			static Color3b lavender()
			{
				return Color3b(230, 230, 250);
			};

			static Color3b lavenderblush()
			{
				return Color3b(255, 240, 245);
			};

			static Color3b lawngreen()
			{
				return Color3b(124, 252, 0);
			};

			static Color3b lemonchiffon()
			{
				return Color3b(255, 250, 205);
			};

			static Color3b lightblue()
			{
				return Color3b(173, 216, 230);
			};

			static Color3b lightcoral()
			{
				return Color3b(240, 128, 128);
			};

			static Color3b lightcyan()
			{
				return Color3b(224, 255, 255);
			};

			static Color3b lightgoldenrodyellow()
			{
				return Color3b(250, 250, 210);
			};

			static Color3b lightgreen()
			{
				return Color3b(144, 238, 144);
			};

			static Color3b lightgrey()
			{
				return Color3b(211, 211, 211);
			};

			static Color3b lightpink()
			{
				return Color3b(255, 182, 193);
			};

			static Color3b lightsalmon()
			{
				return Color3b(255, 160, 122);
			};

			static Color3b lightseagreen()
			{
				return Color3b(32, 178, 170);
			};

			static Color3b lightskyblue()
			{
				return Color3b(135, 206, 250);
			};

			static Color3b lightslategray()
			{
				return Color3b(119, 136, 153);
			};

			static Color3b lightsteelblue()
			{
				return Color3b(176, 196, 222);
			};

			static Color3b lightyellow()
			{
				return Color3b(255, 255, 224);
			};

			static Color3b lime()
			{
				return Color3b(0, 255, 0);
			};

			static Color3b limegreen()
			{
				return Color3b(50, 205, 50);
			};

			static Color3b linen()
			{
				return Color3b(250, 240, 230);
			};

			static Color3b magenta()
			{
				return Color3b(255, 0, 255);
			};

			static Color3b maroon()
			{
				return Color3b(128, 0, 0);
			};

			static Color3b mediumaquamarine()
			{
				return Color3b(102, 205, 170);
			};

			static Color3b mediumblue()
			{
				return Color3b(0, 0, 205);
			};

			static Color3b mediumorchid()
			{
				return Color3b(186, 85, 211);
			};

			static Color3b mediumpurple()
			{
				return Color3b(147, 112, 219);
			};

			static Color3b mediumseagreen()
			{
				return Color3b(60, 179, 113);
			};

			static Color3b mediumslateblue()
			{
				return Color3b(123, 104, 238);
			};

			static Color3b mediumspringgreen()
			{
				return Color3b(0, 250, 154);
			};

			static Color3b mediumturquoise()
			{
				return Color3b(72, 209, 204);
			};

			static Color3b mediumvioletred()
			{
				return Color3b(199, 21, 133);
			};

			static Color3b midnightblue()
			{
				return Color3b(25, 25, 112);
			};

			static Color3b mintcream()
			{
				return Color3b(245, 255, 250);
			};

			static Color3b mistyrose()
			{
				return Color3b(255, 228, 225);
			};

			static Color3b moccasin()
			{
				return Color3b(255, 228, 181);
			};

			static Color3b navajowhite()
			{
				return Color3b(255, 222, 173);
			};

			static Color3b navy()
			{
				return Color3b(0, 0, 128);
			};

			static Color3b oldlace()
			{
				return Color3b(253, 245, 230);
			};

			static Color3b olive()
			{
				return Color3b(128, 128, 0);
			};

			static Color3b olivedrab()
			{
				return Color3b(107, 142, 35);
			};

			static Color3b orange()
			{
				return Color3b(255, 165, 0);
			};

			static Color3b orangered()
			{
				return Color3b(255, 69, 0);
			};

			static Color3b orchid()
			{
				return Color3b(218, 112, 214);
			};

			static Color3b palegoldenrod()
			{
				return Color3b(238, 232, 170);
			};

			static Color3b palegreen()
			{
				return Color3b(152, 251, 152);
			};

			static Color3b paleturquoise()
			{
				return Color3b(175, 238, 238);
			};

			static Color3b palevioletred()
			{
				return Color3b(219, 112, 147);
			};

			static Color3b papayawhip()
			{
				return Color3b(255, 239, 213);
			};

			static Color3b peachpuff()
			{
				return Color3b(255, 218, 185);
			};

			static Color3b peru()
			{
				return Color3b(205, 133, 63);
			};

			static Color3b pink()
			{
				return Color3b(255, 192, 203);
			};

			static Color3b plum()
			{
				return Color3b(221, 160, 221);
			};

			static Color3b powderblue()
			{
				return Color3b(176, 224, 230);
			};

			static Color3b purple()
			{
				return Color3b(128, 0, 128);
			};

			static Color3b red()
			{
				return Color3b(255, 0, 0);
			};

			static Color3b rosybrown()
			{
				return Color3b(188, 143, 143);
			};

			static Color3b royalblue()
			{
				return Color3b(65, 105, 225);
			};

			static Color3b saddlebrown()
			{
				return Color3b(139, 69, 19);
			};

			static Color3b salmon()
			{
				return Color3b(250, 128, 114);
			};

			static Color3b sandybrown()
			{
				return Color3b(244, 164, 96);
			};

			static Color3b seagreen()
			{
				return Color3b(46, 139, 87);
			};

			static Color3b seashell()
			{
				return Color3b(255, 245, 238);
			};

			static Color3b sienna()
			{
				return Color3b(160, 82, 45);
			};

			static Color3b silver()
			{
				return Color3b(192, 192, 192);
			};

			static Color3b skyblue()
			{
				return Color3b(135, 206, 235);
			};

			static Color3b slateblue()
			{
				return Color3b(106, 90, 205);
			};

			static Color3b slategray()
			{
				return Color3b(112, 128, 144);
			};

			static Color3b snow()
			{
				return Color3b(255, 250, 250);
			};

			static Color3b springgreen()
			{
				return Color3b(0, 255, 127);
			};

			static Color3b steelblue()
			{
				return Color3b(70, 130, 180);
			};

			static Color3b tan()
			{
				return Color3b(210, 180, 140);
			};

			static Color3b teal()
			{
				return Color3b(0, 128, 128);
			};

			static Color3b thistle()
			{
				return Color3b(216, 191, 216);
			};

			static Color3b tomato()
			{
				return Color3b(255, 99, 71);
			};

			static Color3b turquoise()
			{
				return Color3b(64, 224, 208);
			};

			static Color3b violet()
			{
				return Color3b(238, 130, 238);
			};

			static Color3b wheat()
			{
				return Color3b(245, 222, 179);
			};

			static Color3b white()
			{
				return Color3b(255, 255, 255);
			};

			static Color3b whitesmoke()
			{
				return Color3b(245, 245, 245);
			};

			static Color3b yellow()
			{
				return Color3b(255, 255, 0);
			};

			static Color3b yellowgreen()
			{
				return Color3b(154, 205, 50);
			};
		};

		template <>
		struct ColorConstants<Color4b> {
			static Color4b aliceBlue() {
				return Color4b(240, 248, 255, 255);
			};

			static Color4b antiqueWhite() {
				return Color4b(250, 235, 215, 255);
			};

			static Color4b aqua() {
				return Color4b(0, 255, 255, 255);
			};

			static Color4b aquaMarine() {
				return Color4b(127, 255, 212, 255);
			};

			static Color4b azure() {
				return Color4b(240, 255, 255, 255);
			};

			static Color4b beige() {
				return Color4b(245, 245, 220, 255);
			};

			static Color4b bisque() {
				return Color4b(255, 228, 196, 255);
			};

			static Color4b black() {
				return Color4b(0, 0, 0, 255);
			};

			static Color4b blanchedalmond() {
				return Color4b(255, 235, 205, 255);
			};

			static Color4b blue() {
				return Color4b(0, 0, 255, 255);
			};

			static Color4b blueViolet() {
				return Color4b(138, 43, 226, 255);
			};

			static Color4b brown() {
				return Color4b(165, 42, 42, 255);
			};

			static Color4b burlywood() {
				return Color4b(222, 184, 135, 255);
			};

			static Color4b cadetBlue() {
				return Color4b(95, 158, 160, 255);
			};

			static Color4b chartreuse() {
				return Color4b(127, 255, 0, 255);
			};

			static Color4b chocolate() {
				return Color4b(210, 105, 30, 255);
			};

			static Color4b coral() {
				return Color4b(255, 127, 80, 255);
			};

			static Color4b cornflowerblue() {
				return Color4b(100, 149, 237, 255);
			};

			static Color4b cornsilk() {
				return Color4b(255, 248, 220, 255);
			};

			static Color4b crimson() {
				return Color4b(220, 20, 60, 255);
			};

			static Color4b cyan() {
				return Color4b(0, 255, 255, 255);
			};

			static Color4b darkOlivegreen() {
				return Color4b(85, 107, 47, 255);
			};

			static Color4b darkblue() {
				return Color4b(0, 0, 139, 255);
			};

			static Color4b darkcyan() {
				return Color4b(0, 139, 139, 255);
			};

			static Color4b darkgoldenrod() {
				return Color4b(184, 134, 11, 255);
			};

			static Color4b darkgray() {
				return Color4b(169, 169, 169, 255);
			};

			static Color4b darkgreen() {
				return Color4b(0, 100, 0, 255);
			};

			static Color4b darkkhaki() {
				return Color4b(189, 183, 107, 255);
			};

			static Color4b darkmagenta() {
				return Color4b(139, 0, 139, 255);
			};

			static Color4b darkorange() {
				return Color4b(255, 140, 0, 255);
			};

			static Color4b darkorchid() {
				return Color4b(153, 50, 204, 255);
			};

			static Color4b darkRed() {
				return Color4b(139, 0, 0, 255);
			};

			static Color4b darksalmon() {
				return Color4b(233, 150, 122, 255);
			};

			static Color4b darkseagreen() {
				return Color4b(143, 188, 143, 255);
			};

			static Color4b darkslateblue() {
				return Color4b(72, 61, 139, 255);
			};

			static Color4b darkslategray() {
				return Color4b(47, 79, 79, 255);
			};

			static Color4b darkturquoise() {
				return Color4b(0, 206, 209, 255);
			};

			static Color4b darkviolet() {
				return Color4b(148, 0, 211, 255);
			};

			static Color4b deeppink() {
				return Color4b(255, 20, 147, 255);
			};

			static Color4b deepskyblue() {
				return Color4b(0, 191, 255, 255);
			};

			static Color4b dimgray() {
				return Color4b(105, 105, 105, 255);
			};

			static Color4b dodgerblue() {
				return Color4b(30, 144, 255, 255);
			};

			static Color4b firebrick() {
				return Color4b(178, 34, 34, 255);
			};

			static Color4b floralwhite() {
				return Color4b(255, 250, 240, 255);
			};

			static Color4b forestgreen() {
				return Color4b(34, 139, 34, 255);
			};

			static Color4b fuchsia() {
				return Color4b(255, 0, 255, 255);
			};

			static Color4b gainsboro() {
				return Color4b(220, 220, 220, 255);
			};

			static Color4b ghostwhite() {
				return Color4b(248, 248, 255, 255);
			};

			static Color4b gold() {
				return Color4b(255, 215, 0, 255);
			};

			static Color4b goldenrod() {
				return Color4b(218, 165, 32, 255);
			};

			static Color4b gray() {
				return Color4b(128, 128, 128, 255);
			};

			static Color4b green() {
				return Color4b(0, 128, 0, 255);
			};

			static Color4b greenyellow() {
				return Color4b(173, 255, 47, 255);
			};

			static Color4b honeydew() {
				return Color4b(240, 255, 240, 255);
			};

			static Color4b hotpink() {
				return Color4b(255, 105, 180, 255);
			};

			static Color4b indianred() {
				return Color4b(205, 92, 92, 255);
			};

			static Color4b indigo() {
				return Color4b(75, 0, 130, 255);
			};

			static Color4b ivory() {
				return Color4b(255, 255, 240, 255);
			};

			static Color4b khaki() {
				return Color4b(240, 230, 140, 255);
			};

			static Color4b lavender() {
				return Color4b(230, 230, 250, 255);
			};

			static Color4b lavenderblush() {
				return Color4b(255, 240, 245, 255);
			};

			static Color4b lawngreen() {
				return Color4b(124, 252, 0, 255);
			};

			static Color4b lemonchiffon() {
				return Color4b(255, 250, 205, 255);
			};

			static Color4b lightblue() {
				return Color4b(173, 216, 230, 255);
			};

			static Color4b lightcoral() {
				return Color4b(240, 128, 128, 255);
			};

			static Color4b lightcyan() {
				return Color4b(224, 255, 255, 255);
			};

			static Color4b lightgoldenrodyellow() {
				return Color4b(250, 250, 210, 255);
			};

			static Color4b lightgreen() {
				return Color4b(144, 238, 144, 255);
			};

			static Color4b lightgrey() {
				return Color4b(211, 211, 211, 255);
			};

			static Color4b lightpink() {
				return Color4b(255, 182, 193, 255);
			};

			static Color4b lightsalmon() {
				return Color4b(255, 160, 122, 255);
			};

			static Color4b lightseagreen() {
				return Color4b(32, 178, 170, 255);
			};

			static Color4b lightskyblue() {
				return Color4b(135, 206, 250, 255);
			};

			static Color4b lightslategray() {
				return Color4b(119, 136, 153, 255);
			};

			static Color4b lightsteelblue() {
				return Color4b(176, 196, 222, 255);
			};

			static Color4b lightyellow() {
				return Color4b(255, 255, 224, 255);
			};

			static Color4b lime() {
				return Color4b(0, 255, 0, 255);
			};

			static Color4b limegreen() {
				return Color4b(50, 205, 50, 255);
			};

			static Color4b linen() {
				return Color4b(250, 240, 230, 255);
			};

			static Color4b magenta() {
				return Color4b(255, 0, 255, 255);
			};

			static Color4b maroon() {
				return Color4b(128, 0, 0, 255);
			};

			static Color4b mediumaquamarine() {
				return Color4b(102, 205, 170, 255);
			};

			static Color4b mediumblue() {
				return Color4b(0, 0, 205, 255);
			};

			static Color4b mediumorchid() {
				return Color4b(186, 85, 211, 255);
			};

			static Color4b mediumpurple() {
				return Color4b(147, 112, 219, 255);
			};

			static Color4b mediumseagreen() {
				return Color4b(60, 179, 113, 255);
			};

			static Color4b mediumslateblue() {
				return Color4b(123, 104, 238, 255);
			};

			static Color4b mediumspringgreen() {
				return Color4b(0, 250, 154, 255);
			};

			static Color4b mediumturquoise() {
				return Color4b(72, 209, 204, 255);
			};

			static Color4b mediumvioletred() {
				return Color4b(199, 21, 133, 255);
			};

			static Color4b midnightblue() {
				return Color4b(25, 25, 112, 255);
			};

			static Color4b mintcream() {
				return Color4b(245, 255, 250, 255);
			};

			static Color4b mistyrose() {
				return Color4b(255, 228, 225, 255);
			};

			static Color4b moccasin() {
				return Color4b(255, 228, 181, 255);
			};

			static Color4b navajowhite() {
				return Color4b(255, 222, 173, 255);
			};

			static Color4b navy() {
				return Color4b(0, 0, 128, 255);
			};

			static Color4b oldlace() {
				return Color4b(253, 245, 230, 255);
			};

			static Color4b olive() {
				return Color4b(128, 128, 0, 255);
			};

			static Color4b olivedrab() {
				return Color4b(107, 142, 35, 255);
			};

			static Color4b orange() {
				return Color4b(255, 165, 0, 255);
			};

			static Color4b orangered() {
				return Color4b(255, 69, 0, 255);
			};

			static Color4b orchid() {
				return Color4b(218, 112, 214, 255);
			};

			static Color4b palegoldenrod() {
				return Color4b(238, 232, 170, 255);
			};

			static Color4b palegreen() {
				return Color4b(152, 251, 152, 255);
			};

			static Color4b paleturquoise() {
				return Color4b(175, 238, 238, 255);
			};

			static Color4b palevioletred() {
				return Color4b(219, 112, 147, 255);
			};

			static Color4b papayawhip() {
				return Color4b(255, 239, 213, 255);
			};

			static Color4b peachpuff() {
				return Color4b(255, 218, 185, 255);
			};

			static Color4b peru() {
				return Color4b(205, 133, 63, 255);
			};

			static Color4b pink() {
				return Color4b(255, 192, 203, 255);
			};

			static Color4b plum() {
				return Color4b(221, 160, 221, 255);
			};

			static Color4b powderblue() {
				return Color4b(176, 224, 230, 255);
			};

			static Color4b purple() {
				return Color4b(128, 0, 128, 255);
			};

			static Color4b red() {
				return Color4b(255, 0, 0, 255);
			};

			static Color4b rosybrown() {
				return Color4b(188, 143, 143, 255);
			};

			static Color4b royalblue() {
				return Color4b(65, 105, 225, 255);
			};

			static Color4b saddlebrown() {
				return Color4b(139, 69, 19, 255);
			};

			static Color4b salmon() {
				return Color4b(250, 128, 114, 255);
			};

			static Color4b sandybrown() {
				return Color4b(244, 164, 96, 255);
			};

			static Color4b seagreen() {
				return Color4b(46, 139, 87, 255);
			};

			static Color4b seashell() {
				return Color4b(255, 245, 238, 255);
			};

			static Color4b sienna() {
				return Color4b(160, 82, 45, 255);
			};

			static Color4b silver() {
				return Color4b(192, 192, 192, 255);
			};

			static Color4b skyblue() {
				return Color4b(135, 206, 235, 255);
			};

			static Color4b slateblue() {
				return Color4b(106, 90, 205, 255);
			};

			static Color4b slategray() {
				return Color4b(112, 128, 144, 255);
			};

			static Color4b snow() {
				return Color4b(255, 250, 250, 255);
			};

			static Color4b springgreen() {
				return Color4b(0, 255, 127, 255);
			};

			static Color4b steelblue() {
				return Color4b(70, 130, 180, 255);
			};

			static Color4b tan() {
				return Color4b(210, 180, 140, 255);
			};

			static Color4b teal() {
				return Color4b(0, 128, 128, 255);
			};

			static Color4b thistle() {
				return Color4b(216, 191, 216, 255);
			};

			static Color4b tomato() {
				return Color4b(255, 99, 71, 255);
			};

			static Color4b turquoise() {
				return Color4b(64, 224, 208, 255);
			};

			static Color4b violet() {
				return Color4b(238, 130, 238, 255);
			};

			static Color4b wheat() {
				return Color4b(245, 222, 179, 255);
			};

			static Color4b white() {
				return Color4b(255, 255, 255, 255);
			};

			static Color4b whitesmoke() {
				return Color4b(245, 245, 245, 255);
			};

			static Color4b yellow() {
				return Color4b(255, 255, 0, 255);
			};

			static Color4b yellowgreen() {
				return Color4b(154, 205, 50, 255);
			};
		};


		typedef ColorConstants<Color3f> ColorConstants3f;
		typedef ColorConstants<Color4f> ColorConstants4f;
		typedef ColorConstants<Color3b> ColorConstants3b;
		typedef ColorConstants<Color4b> ColorConstants4b;
	} // end namespace ImageProcessing
} // end namespace BlueFramework

namespace buw
{
	using BlueFramework::ImageProcessing::ColorConstants;
	using BlueFramework::ImageProcessing::ColorConstants3f;
	using BlueFramework::ImageProcessing::ColorConstants4f;
	using BlueFramework::ImageProcessing::ColorConstants4b;
	using BlueFramework::ImageProcessing::ColorConstants4b;
} // namespace buw

#endif // end define BlueFramework_ImageProcessing_ColorConstants_e730a33d_4053_4c52_bd16_ecf1fba26816_h
