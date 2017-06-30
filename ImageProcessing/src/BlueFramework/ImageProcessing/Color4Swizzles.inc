/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2016-2017 Technical University of Munich
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

// Color4Swizzles.inc: Swizzles for Color<T, 4>
inline const Color<T, 4> rrrr() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> rrrg() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> rrrb() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> rrra() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> rrgr() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> rrgg() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> rrgb() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> rrga() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> rrbr() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> rrbg() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> rrbb() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> rrba() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> rrar() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> rrag() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> rrab() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> rraa() const
{ return Color<T, 4>( (*this)[0], (*this)[0], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> rgrr() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> rgrg() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> rgrb() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> rgra() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> rggr() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> rggg() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> rggb() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> rgga() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> rgbr() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> rgbg() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> rgbb() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> rgba() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> rgar() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> rgag() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> rgab() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> rgaa() const
{ return Color<T, 4>( (*this)[0], (*this)[1], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> rbrr() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> rbrg() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> rbrb() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> rbra() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> rbgr() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> rbgg() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> rbgb() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> rbga() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> rbbr() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> rbbg() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> rbbb() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> rbba() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> rbar() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> rbag() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> rbab() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> rbaa() const
{ return Color<T, 4>( (*this)[0], (*this)[2], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> rarr() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> rarg() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> rarb() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> rara() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> ragr() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> ragg() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> ragb() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> raga() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> rabr() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> rabg() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> rabb() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> raba() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> raar() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> raag() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> raab() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> raaa() const
{ return Color<T, 4>( (*this)[0], (*this)[3], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> grrr() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> grrg() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> grrb() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> grra() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> grgr() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> grgg() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> grgb() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> grga() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> grbr() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> grbg() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> grbb() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> grba() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> grar() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> grag() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> grab() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> graa() const
{ return Color<T, 4>( (*this)[1], (*this)[0], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> ggrr() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> ggrg() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> ggrb() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> ggra() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> gggr() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> gggg() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> gggb() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> ggga() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> ggbr() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> ggbg() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> ggbb() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> ggba() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> ggar() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> ggag() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> ggab() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> ggaa() const
{ return Color<T, 4>( (*this)[1], (*this)[1], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> gbrr() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> gbrg() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> gbrb() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> gbra() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> gbgr() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> gbgg() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> gbgb() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> gbga() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> gbbr() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> gbbg() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> gbbb() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> gbba() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> gbar() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> gbag() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> gbab() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> gbaa() const
{ return Color<T, 4>( (*this)[1], (*this)[2], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> garr() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> garg() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> garb() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> gara() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> gagr() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> gagg() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> gagb() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> gaga() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> gabr() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> gabg() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> gabb() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> gaba() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> gaar() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> gaag() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> gaab() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> gaaa() const
{ return Color<T, 4>( (*this)[1], (*this)[3], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> brrr() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> brrg() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> brrb() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> brra() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> brgr() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> brgg() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> brgb() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> brga() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> brbr() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> brbg() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> brbb() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> brba() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> brar() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> brag() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> brab() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> braa() const
{ return Color<T, 4>( (*this)[2], (*this)[0], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> bgrr() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> bgrg() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> bgrb() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> bgra() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> bggr() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> bggg() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> bggb() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> bgga() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> bgbr() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> bgbg() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> bgbb() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> bgba() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> bgar() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> bgag() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> bgab() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> bgaa() const
{ return Color<T, 4>( (*this)[2], (*this)[1], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> bbrr() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> bbrg() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> bbrb() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> bbra() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> bbgr() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> bbgg() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> bbgb() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> bbga() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> bbbr() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> bbbg() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> bbbb() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> bbba() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> bbar() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> bbag() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> bbab() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> bbaa() const
{ return Color<T, 4>( (*this)[2], (*this)[2], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> barr() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> barg() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> barb() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> bara() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> bagr() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> bagg() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> bagb() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> baga() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> babr() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> babg() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> babb() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> baba() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> baar() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> baag() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> baab() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> baaa() const
{ return Color<T, 4>( (*this)[2], (*this)[3], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> arrr() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> arrg() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> arrb() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> arra() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> argr() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> argg() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> argb() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> arga() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> arbr() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> arbg() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> arbb() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> arba() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> arar() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> arag() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> arab() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> araa() const
{ return Color<T, 4>( (*this)[3], (*this)[0], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> agrr() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> agrg() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> agrb() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> agra() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> aggr() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> aggg() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> aggb() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> agga() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> agbr() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> agbg() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> agbb() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> agba() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> agar() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> agag() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> agab() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> agaa() const
{ return Color<T, 4>( (*this)[3], (*this)[1], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> abrr() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> abrg() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> abrb() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> abra() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> abgr() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> abgg() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> abgb() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> abga() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> abbr() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> abbg() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> abbb() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> abba() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> abar() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> abag() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> abab() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> abaa() const
{ return Color<T, 4>( (*this)[3], (*this)[2], (*this)[3], (*this)[3] ); }

inline const Color<T, 4> aarr() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[0], (*this)[0] ); }

inline const Color<T, 4> aarg() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[0], (*this)[1] ); }

inline const Color<T, 4> aarb() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[0], (*this)[2] ); }

inline const Color<T, 4> aara() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[0], (*this)[3] ); }

inline const Color<T, 4> aagr() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[1], (*this)[0] ); }

inline const Color<T, 4> aagg() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[1], (*this)[1] ); }

inline const Color<T, 4> aagb() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[1], (*this)[2] ); }

inline const Color<T, 4> aaga() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[1], (*this)[3] ); }

inline const Color<T, 4> aabr() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[2], (*this)[0] ); }

inline const Color<T, 4> aabg() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[2], (*this)[1] ); }

inline const Color<T, 4> aabb() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[2], (*this)[2] ); }

inline const Color<T, 4> aaba() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[2], (*this)[3] ); }

inline const Color<T, 4> aaar() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[3], (*this)[0] ); }

inline const Color<T, 4> aaag() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[3], (*this)[1] ); }

inline const Color<T, 4> aaab() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[3], (*this)[2] ); }

inline const Color<T, 4> aaaa() const
{ return Color<T, 4>( (*this)[3], (*this)[3], (*this)[3], (*this)[3] ); }

