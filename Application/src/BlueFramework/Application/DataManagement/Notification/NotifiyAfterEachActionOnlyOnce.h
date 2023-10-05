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

#include "NotificationState.h"
#include <set>
#include "IMessage.h"
#include "ChangeMessage.h"

namespace BlueFramework
{
	namespace Application
	{
		namespace DataManagement
		{
			//! \brief Signals are only emitted after a action is completely executed. If a signal occurs more than once the signal is only emitted once and not as often as the action occurs.
			template <typename DataT>
			class NotifiyAfterEachActionOnlyOnce : public NotificationState
			{
			public:
				NotifiyAfterEachActionOnlyOnce();

				virtual ~NotifiyAfterEachActionOnlyOnce();

				//! Emits the change Signal This signal is emitted if the data model changes. All data in this class belongs to the data model.
				virtual void change()
				{
					if (!m_bCreateEvent)
					{	
						m_bCreateEvent = true;
						m_CollectedMessages.push_back(new ChangeMessage<DataT>());
					}
				}

				//! Is called if a action is started.
				virtual void beginAction();

				//! Is called if a action is ended.
				virtual void endAction();

			private:
				// Determines if a CreateEvent is in the collected messages list.
				bool m_bCreateEvent;

				//! Emits all collected events to the corresponding observers.
				void NotifyObservers();

				//! Collects all messages that should be send. This buffer will be cleared and all messages will be emitted if the execution of a macro ends.
				std::vector<IMessage*> m_CollectedMessages;

				//! Is incremented each time beginAction is called and decremented each time endAction is called.
				int m_iActionStackCounter;

				//! Protect unimplemented copy constructor from being called.
				/*
					\param[in] source	The source object that should be copied.
				*/
				NotifiyAfterEachActionOnlyOnce(const NotifiyAfterEachActionOnlyOnce &source);

				//! Protect unimplemented assignment operator from being called.
				/*
					\param[in] source	The source object that should be assigned.
				*/
				NotifiyAfterEachActionOnlyOnce& operator= (const NotifiyAfterEachActionOnlyOnce& source);
			}; // end class NotifiyAfterEachMacro
		} // end namespace DataManagement
	} // end namespace Blueform
} // end namespace BlueFramework

#include "NotifiyAfterEachActionOnlyOnce.inl"
