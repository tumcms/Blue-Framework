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

#include "IAction.h"
#include <vector>

namespace BlueFramework
{
	namespace Application
	{
		namespace DataManagement
		{
			namespace Action
			{
				//! \class Macro
				//! \brief A macro consists of a number of actions which are executed one after another.
				class BLUEAPPLICATION_API Macro : public IAction
				{
				public:
					BLUE_DEF_SHARED_POINTER(Macro);

					//! Constructor.
					Macro();

					//! Virtual destructor.
					virtual ~Macro();

					void add(IAction::Ptr pAction);

					//! Execute action.
					virtual void redo();

					//! Undo action 
					virtual void undo();

					//! detemines if this command should be ignored as a successive command to a previous command on undo stack
					virtual bool ignoreSuccessiveCommand( const IAction &previousCommand ) const;

				private:
					//! A macro consists of a number of actions which are executed one after another.
					std::vector<IAction::Ptr> m_Actions;
				}; // end class Macro
			} // end namespace Action
		} // end namespace DataManagement
	} // end namespace Application
} // end namespace BlueFramework
