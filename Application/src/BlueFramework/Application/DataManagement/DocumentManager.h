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

#include "Document.h"

namespace BlueFramework
{
	namespace Application
	{
		namespace DataManagement
		{
			//! \class DocumentManager
			//! \brief This class is a singleton implementation.
			//!
			//! The DocumentManger is used to manage a Single Document Interface (SDI), it could be easily extended to support Multiply Document Interface (MDI). SDI is preferred over 
			//! MDI because its not as confusing to the user as MDI. Also is it possible to open a number of other instances of the application.
			template<typename DataT>
			class DocumentManager
			{
			public:
				virtual ~DocumentManager();

				//! Get document instance.
				static Document<DataT>& getInstance();
			private:	
				//! Constructor.
				DocumentManager();

				//! Protect unimplemented copy constructor from being called.
				/*
					\param[in] source	The source object that should be copied.
				*/
				DocumentManager(const DocumentManager &source);

				//! Protect unimplemented assignment operator from being called.
				/*
					\param[in] source	The source object that should be assigned.
				*/
				DocumentManager& operator= (const DocumentManager& source);
			}; // end class DocumentManager
		} // end namespace DataManagement
	} // end namespace Blueform
} // end namespace BlueFramework

#include "DocumentManager.inl"