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

namespace BlueFramework {
	namespace Application {
		namespace DataManagement {
			//! \brief Determines when signals form the data layer a emitted.
			class NotificationState {
			public:
				NotificationState() {
				}

				virtual ~NotificationState() {
				}

				//! Emits the change Signal This signal is emitted if the data model changes. All data in this class belongs to the data model.
				virtual void change() = 0;

				//! Is called if a action is started. Exactly this means the function is called if the execution of a action is started, a redo of a action is started or a
				//! undo of an action is started.
				virtual void beginAction() = 0;

				//! Is called if a action is ended. Exactly this means the function is called if the execution of a action is ended, a redo of a action is started or a
				//! undo of an action is started.
				virtual void endAction() = 0;

			private:
				//! Protect unimplemented copy constructor from being called.
				/*
				    \param[in] source	The source object that should be copied.
				*/
				NotificationState(const NotificationState& source);

				//! Protect unimplemented assignment operator from being called.
				/*
				    \param[in] source	The source object that should be assigned.
				*/
				NotificationState& operator=(const NotificationState& source);
			}; // end class Impossible
		}      // end namespace DataManagement
	}          // end namespace Blueform
} // end namespace BlueFramework
