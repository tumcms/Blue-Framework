/*! \verbatim
 *	\copyright	Copyright (c) 2009-2014 Julian Amann. All rights reserved.
 *  \created_on 2009-11-17 22:34
 *	\license	This project is released under the BlueLicense (see BlueLicense.txt).
 *	\author		Julian Amann (julian.amann@tum.de)
 *	\brief		This file is part of the BlueFramework source code.
 *	\endverbatim
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
