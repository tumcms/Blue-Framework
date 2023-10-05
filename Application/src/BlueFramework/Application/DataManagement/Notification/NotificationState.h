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
