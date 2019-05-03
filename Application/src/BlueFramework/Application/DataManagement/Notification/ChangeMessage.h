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
