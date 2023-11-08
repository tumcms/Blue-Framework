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

// Color2Swizzles.inc: Swizzles for Color<T, 2>

inline const Color<T, 2> rr() const
{ return Color<T, 2>( (*this)[0], (*this)[0] ); }

inline const Color<T, 2> rg() const
{ return Color<T, 2>( (*this)[0], (*this)[1] ); }

inline const Color<T, 2> gr() const
{ return Color<T, 2>( (*this)[1], (*this)[0] ); }

inline const Color<T, 2> gg() const
{ return Color<T, 2>( (*this)[1], (*this)[1] ); }

