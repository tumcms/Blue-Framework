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
