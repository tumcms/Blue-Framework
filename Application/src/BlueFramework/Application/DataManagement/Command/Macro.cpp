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
