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

#include <boost/noncopyable.hpp>
#include <memory>
#include <string>

namespace BlueFramework
{
	//! \namespace BlueFramework::Application
	//! \brief Provides basic services for applications like undo/redo functionality.
	namespace Application
	{
		//! \namespace BlueFramework::Application::DataManagement
		//! \brief Provides basic services for action handling.
		namespace DataManagement
		{
			namespace Command
			{
				//! \brief A action is something that can be executed on a document. It changes the document somehow.
				class ICommand : private boost::noncopyable
				{
				public:
					ICommand() {}

					virtual ~ICommand()	{}

					//! Execute action.
					virtual void execute() = 0;

					//! Undo action 
					virtual void unexecute() = 0;

					//! Determines if this command should be ignored as a successive command to a previous command on the undo stack.
					virtual bool ignoreSuccessiveCommand( const ICommand & ) const
					{
						return false;
					}

					//! Describes what the action does.
					const char* getRedoDescription() const { return description_.c_str(); }	

					//! Describes what the undo action does.
					const char* getUndoDescription() const { return undoDescription_.c_str(); }

				private:
					//! Describes what the action does.
					std::string description_;

					//! Describes what the undo action does.
					std::string undoDescription_;
				}; // end class ICommand
			} // end namespace Command
		} // end namespace DataManagement
	} // end namespace Application
} // end namespace BlueFramework

namespace buw
{
	using BlueFramework::Application::DataManagement::Command::ICommand;
}
