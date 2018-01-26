/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2018 Technical University of Munich
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
