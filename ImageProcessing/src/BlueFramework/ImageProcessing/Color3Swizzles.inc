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

// Color3Swizzles.inc: Swizzles for Color<T, 3>
inline const Color<T, 3> rrr() const
{ return Color<T, 3>( (*this)[0], (*this)[0], (*this)[0] ); }

inline const Color<T, 3> rrg() const
{ return Color<T, 3>( (*this)[0], (*this)[0], (*this)[1] ); }

inline const Color<T, 3> rrb() const
{ return Color<T, 3>( (*this)[0], (*this)[0], (*this)[2] ); }

inline const Color<T, 3> rgr() const
{ return Color<T, 3>( (*this)[0], (*this)[1], (*this)[0] ); }

inline const Color<T, 3> rgg() const
{ return Color<T, 3>( (*this)[0], (*this)[1], (*this)[1] ); }

inline const Color<T, 3> rgb() const
{ return Color<T, 3>( (*this)[0], (*this)[1], (*this)[2] ); }

inline const Color<T, 3> rbr() const
{ return Color<T, 3>( (*this)[0], (*this)[2], (*this)[0] ); }

inline const Color<T, 3> rbg() const
{ return Color<T, 3>( (*this)[0], (*this)[2], (*this)[1] ); }

inline const Color<T, 3> rbb() const
{ return Color<T, 3>( (*this)[0], (*this)[2], (*this)[2] ); }

inline const Color<T, 3> grr() const
{ return Color<T, 3>( (*this)[1], (*this)[0], (*this)[0] ); }

inline const Color<T, 3> grg() const
{ return Color<T, 3>( (*this)[1], (*this)[0], (*this)[1] ); }

inline const Color<T, 3> grb() const
{ return Color<T, 3>( (*this)[1], (*this)[0], (*this)[2] ); }

inline const Color<T, 3> ggr() const
{ return Color<T, 3>( (*this)[1], (*this)[1], (*this)[0] ); }

inline const Color<T, 3> ggg() const
{ return Color<T, 3>( (*this)[1], (*this)[1], (*this)[1] ); }

inline const Color<T, 3> ggb() const
{ return Color<T, 3>( (*this)[1], (*this)[1], (*this)[2] ); }

inline const Color<T, 3> gbr() const
{ return Color<T, 3>( (*this)[1], (*this)[2], (*this)[0] ); }

inline const Color<T, 3> gbg() const
{ return Color<T, 3>( (*this)[1], (*this)[2], (*this)[1] ); }

inline const Color<T, 3> gbb() const
{ return Color<T, 3>( (*this)[1], (*this)[2], (*this)[2] ); }

inline const Color<T, 3> brr() const
{ return Color<T, 3>( (*this)[2], (*this)[0], (*this)[0] ); }

inline const Color<T, 3> brg() const
{ return Color<T, 3>( (*this)[2], (*this)[0], (*this)[1] ); }

inline const Color<T, 3> brb() const
{ return Color<T, 3>( (*this)[2], (*this)[0], (*this)[2] ); }

inline const Color<T, 3> bgr() const
{ return Color<T, 3>( (*this)[2], (*this)[1], (*this)[0] ); }

inline const Color<T, 3> bgg() const
{ return Color<T, 3>( (*this)[2], (*this)[1], (*this)[1] ); }

inline const Color<T, 3> bgb() const
{ return Color<T, 3>( (*this)[2], (*this)[1], (*this)[2] ); }

inline const Color<T, 3> bbr() const
{ return Color<T, 3>( (*this)[2], (*this)[2], (*this)[0] ); }

inline const Color<T, 3> bbg() const
{ return Color<T, 3>( (*this)[2], (*this)[2], (*this)[1] ); }

inline const Color<T, 3> bbb() const
{ return Color<T, 3>( (*this)[2], (*this)[2], (*this)[2] ); }

