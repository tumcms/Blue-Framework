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