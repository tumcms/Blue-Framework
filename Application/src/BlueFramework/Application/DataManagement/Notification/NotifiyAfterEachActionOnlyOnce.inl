/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2016-2017 Technical University of Munich
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

#include "NotifiyAfterEachActionOnlyOnce.h"
#include "ChangeMessage.h"
#include "../../DataManagement/Data.h"

template <typename DataT>
BlueFramework::Application::DataManagement::NotifiyAfterEachActionOnlyOnce<DataT>::NotifiyAfterEachActionOnlyOnce() :
m_iActionStackCounter(0),
m_bCreateEvent(false)
{

}

template <typename DataT>
BlueFramework::Application::DataManagement::NotifiyAfterEachActionOnlyOnce<DataT>::~NotifiyAfterEachActionOnlyOnce()
{
	for (unsigned int i = 0; i < m_CollectedMessages.size(); i++)
	{
		delete m_CollectedMessages[i];
	}
}



template <typename DataT>
void BlueFramework::Application::DataManagement::NotifiyAfterEachActionOnlyOnce<DataT>::beginAction()
{
	m_iActionStackCounter++;
}

template <typename DataT>
void BlueFramework::Application::DataManagement::NotifiyAfterEachActionOnlyOnce<DataT>::endAction()
{
	m_iActionStackCounter--;

	assert(m_iActionStackCounter >= 0);

	if (m_iActionStackCounter == 0)
	{
		NotifyObservers();
	}
}

template <typename DataT>
void BlueFramework::Application::DataManagement::NotifiyAfterEachActionOnlyOnce<DataT>::NotifyObservers()
{
	// Todo: Delete duplicated messages for instance one ChangeMessage is enough...? or don't add duplicateded messages...?

	for (unsigned int i = 0; i < m_CollectedMessages.size(); i++)
	{
		assert(m_CollectedMessages[i] != 0);
		m_CollectedMessages[i]->send();
		delete m_CollectedMessages[i];
		m_CollectedMessages[i] = 0;
	}

	m_CollectedMessages.clear();

	m_bCreateEvent = false;
}