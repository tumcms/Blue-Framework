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

