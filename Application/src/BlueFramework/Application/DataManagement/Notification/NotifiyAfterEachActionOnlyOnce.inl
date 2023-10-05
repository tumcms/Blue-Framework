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
