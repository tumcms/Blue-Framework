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

#include "IMessage.h"
#include "../Data.h"
#include "../DocumentManager.h"

namespace BlueFramework
{
	namespace Application
	{
		namespace DataManagement
		{
			template<typename DataT>
			class ChangeMessage : public IMessage
			{
			public:
				ChangeMessage()
				{
				}

				virtual ~ChangeMessage()
				{
				}

				virtual void send()
				{
					BlueFramework::Application::DataManagement::DocumentManager<DataT>::getInstance().getData().Change();
				}

			private:
				//! Protect unimplemented copy constructor from being called.
				/*
					\param[in] source	The source object that should be copied.
				*/
				ChangeMessage(const ChangeMessage &source);

				//! Protect unimplemented assignment operator from being called.
				/*
					\param[in] source	The source object that should be assigned.
				*/
				ChangeMessage& operator= (const ChangeMessage& source);
			}; // end class ChangeMessage
		} // end namespace DataManagement
	} // end namespace Blueform
} // end namespace BlueFramework
