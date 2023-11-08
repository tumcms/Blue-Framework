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

#include "BlueFramework/Application/DataManagement/Command/ICommand.h"
#include "BlueFramework/Core/Noncopyable.h"
#include "BlueFramework/Core/memory.h"
#include <boost/signals2.hpp>
#include <stack>

// forward declarations
namespace BlueFramework
{
	namespace Application
	{
		namespace DataManagement
		{
			class Data;

			template <typename DataT>
			class IDocumentState;
		}
	}
}

namespace BlueFramework
{
	namespace Application
	{
		namespace DataManagement
		{
			// Interface for Documents
			class DocumentBase : private buw::NonCopyable
			{
			public:
				virtual ~DocumentBase() {};

				//! Deletes document data and undo and redo stacks
				virtual void clear() = 0;

				//! The user redos a certain action.
				virtual void redo() = 0;

				//! The user undos a certain action.
				virtual void undo() = 0;

				//! The user executes a certain action.
				virtual void execute(buw::ReferenceCounted<BlueFramework::Application::DataManagement::Command::ICommand> action) = 0;

				//! The user creates a new document.
				virtual void newdoc() = 0;

				//! The user is opening a new document.
				virtual void open() = 0;

				//! The user hits the Save button.
				virtual void save() = 0;

				//! The user hits Save As button.
				virtual void saveAs() = 0;

				//! The user hits Import button.
				virtual void import() = 0;

				//! The user want to exit the application.
				virtual bool exit() = 0;

				//! Get access to the data
				virtual Data* getDataPtr() = 0;

				/// <summary>
				/// Wird aufgerufen, wenn sich der Zustand des Dokuments ver�ndert
				/// </summary>
				//! This signal is emited if the state of the document changes.
				/*!
					\param[in] filename
				*/
				boost::signals2::signal<void (const std::string& )> DocumentStateChange;

				//! Is emitted if the redo stack changes
				/*!
					\param[in] int	Number of actions on redo stack.
				*/
				boost::signals2::signal<void (size_t)> RedoStackChanged;

				//! Is emitted if the undo stack changes
				/*!
					\param[in] int	Number of actions on undo stack.
				*/
				boost::signals2::signal<void (size_t)> UndoStackChanged;
			}; // end class IDocument
			
			template<typename DataT>
			class Document : public DocumentBase
			{
			public:
				Document();

				virtual ~Document();

				/// <summary>
				/// Deletes document data and undo and redo stacks
				/// </summary>
				void clear();

				//! The user redos a certain action.
				void redo();

				//! The user undos a certain action.
				void undo();

				//! The user executes a certain action.
				void execute(buw::ReferenceCounted<Command::ICommand> action);

				//! The user creates a new document.
				void newdoc();

				//! The user is opening a new document.
				void open();

				//! The user hits the Save button.
				void save();

				//! The user hits Save As button.
				void saveAs();

				//! The user hits Import button.
				void import();

				//! The user want to exit the application.
				bool exit();

				DataT& getData();

				Data* getDataPtr()
				{
					return data_;
				}

				//! Change document state
				void changeState(IDocumentState<DataT>* pState);

			private:
				//! Frees the memory allocated by the undo and redo stack.
				void freeUndoAndRedoStack();

				//! Application Data.
				DataT* data_;
				
				//! State of document.
				IDocumentState<DataT> *m_pDocumentState;

				//! Stack for redo actions.
				std::stack<buw::ReferenceCounted<Command::ICommand>> redoStack_;

				//! Stack for undo actions.
				std::stack<buw::ReferenceCounted<Command::ICommand>> undoStack_;
			}; // end class Document
		} // end namespace DataManagement
	} // end namespace Application
} // end namespace BlueFramework

#include "Document.inl"
