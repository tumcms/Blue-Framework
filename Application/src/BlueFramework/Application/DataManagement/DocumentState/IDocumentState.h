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

#include "../Document.h"

namespace BlueFramework
{
	namespace Application
	{
		namespace DataManagement
		{
			//! \class IDocumentState
			//! \brief A document can be exactly in one of four different states: UnsavedUnedited, UnsavedEdited, SavedUnedited and SavedEdited.
			//! For example depinding on the current state the user is asked if he/she wants to save an unsaved file.
			template<typename DataT>
			class IDocumentState
			{
			public:
				//! Constructor.
				IDocumentState()
				{

				}

				virtual ~IDocumentState()
				{
				}

				//! The user redos a certain action.
				virtual void redo(Document<DataT> *document) = 0;

				//! The user undos a certain action.
				virtual void undo(Document<DataT> *document) = 0;

				//! The user executes a certain action.
				virtual void execute(Document<DataT> *document) = 0;

				//! The user creates a new document.
				virtual void newdoc(Document<DataT> *document) = 0;

				//! The user is opening a new document.
				virtual void open(Document<DataT> *document) = 0;

				//! The user hits the Save button.
				virtual void save(Document<DataT> *document) = 0;

				//! The user hits Save As button.
				virtual void saveAs(Document<DataT> *document) = 0;

				//! The user hits Import button.
				virtual void import(Document<DataT> *document) = 0;

				//! The user want to exit the application.
				virtual bool exit(Document<DataT> *document) = 0;

				//! Gets the filename of the document.
				virtual std::string getFilename() = 0;

			private:
				//! Protect unimplemented copy constructor from being called.
				/*
				\param[in] source	The source object that should be copied.
				*/
				IDocumentState(const IDocumentState &source);

				//! Protect unimplemented assignment operator from being called.
				/*
				\param[in] source	The source object that should be assigned.
				*/
				IDocumentState& operator= (const IDocumentState& source);
			}; // end class IDocumentState
		} // end namespace DataManagement
	} // end namespace Blueform
} // end namespace BlueFramework
