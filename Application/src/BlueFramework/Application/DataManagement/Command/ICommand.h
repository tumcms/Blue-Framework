/*! \verbatim
 *  \copyright      Copyright (c) 2015 Julian Amann. All rights reserved.
 *  \author         Julian Amann <dev@vertexwahn.de> (http://vertexwahn.de/)
 *  \brief          This file is part of the BlueFramework.
 *  \endverbatim
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