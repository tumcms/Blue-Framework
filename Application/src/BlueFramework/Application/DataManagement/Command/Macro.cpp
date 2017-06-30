/*! \verbatim
 *	\copyright	Copyright (c) 2009-2014 Julian Amann. All rights reserved.
 *  \created_on 2009-11-17 22:34
 *	\license	This project is released under the BlueLicense (see BlueLicense.txt).
 *	\author		Julian Amann (julian.amann@tum.de)
 *	\brief		This file is part of the BlueFramework source code.
 *	\endverbatim
 */

#include "Macro.h"

BlueFramework::Application::DataManagement::Action::Macro::Macro()
{

}

BlueFramework::Application::DataManagement::Action::Macro::~Macro()
{
	// free actions
	for (unsigned int i = 0; i < m_Actions.size(); i++)
	{
		m_Actions[i] = nullptr;
	}
}

void BlueFramework::Application::DataManagement::Action::Macro::add( IAction::Ptr pAction )
{
	m_Actions.push_back(pAction);
}

void BlueFramework::Application::DataManagement::Action::Macro::redo()
{
	for(std::vector<IAction*>::size_type i = 0; i < m_Actions.size(); i++)
	{
		m_Actions[i]->redo();
	}
}

void BlueFramework::Application::DataManagement::Action::Macro::undo()
{
	for(int i = m_Actions.size()-1; i >= 0; i--)
	{
		m_Actions[i]->undo();
	}
}

bool BlueFramework::Application::DataManagement::Action::Macro::ignoreSuccessiveCommand( const IAction &previousCommand ) const
{
	try
	{
		const Macro &macro = dynamic_cast<const Macro&>(previousCommand);

		if (m_Actions.size() != macro.m_Actions.size())
			return false;

		for (int i = 0; i < m_Actions.size(); i++)
		{
			if(! m_Actions[i]->ignoreSuccessiveCommand(*macro.m_Actions[i]))
				return false;
		}

		return true;
	}
	catch (const std::bad_cast&)
	{
		return false;
	}
}