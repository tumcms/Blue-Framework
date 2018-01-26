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

#include "Document.h"

#include "BlueFramework/Application/DataManagement/Command/ICommand.h"
#include "DocumentState/IDocumentState.h"
#include "DocumentState/UnsavedUnedited.h"
#include "Data.h"
#include "Notification/NotificationState.h"

template<typename DataT>
BlueFramework::Application::DataManagement::Document<DataT>::Document()
{
	data_ = new DataT();
	m_pDocumentState = new BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>();
}

template<typename DataT>
BlueFramework::Application::DataManagement::Document<DataT>::~Document()
{
	// free undo and redo stack
	while(undoStack_.size() > 0)
	{
		undoStack_.top() = nullptr;
		undoStack_.pop();
	}

	while(redoStack_.size() > 0)
	{
		redoStack_.top() = nullptr;
		redoStack_.pop();
	}

	delete data_;
	delete m_pDocumentState;
}

template<typename DataT>
void BlueFramework::Application::DataManagement::Document<DataT>::clear()
{
	freeUndoAndRedoStack();
	data_->clear();
}

template<typename DataT>
void BlueFramework::Application::DataManagement::Document<DataT>::execute(buw::ReferenceCounted<Command::ICommand> action)
{
	// action != 0
	assert(action && "Invalid action.");

	// Eine Aktion kann abhängig von einer vorhergehenden Aktion ignoriert werden 
	// a action can be ignored depending on the previous action command
	if (undoStack_.size() > 0 && action->ignoreSuccessiveCommand(*undoStack_.top()))
	{
		return;
	}

	// now really do execute the command
	data_->getNotifiactionState()->beginAction();
	action->execute();
	data_->getNotifiactionState()->endAction();

	// push currently executed command on undo stack
	undoStack_.push(action);

	// inform observers
	UndoStackChanged(undoStack_.size());

	// has redo stack been touched?
	bool bChangedRedoStack = false;

	// clear redo stack 
	// why?
	// imagine following example
	//
	//     C5
	//     C4
	//     C3
	//     C2
	//     C1
	// Undo stack	Redo stack
	// 
	// No the user decides to undo command C5 and C4:
	//
	//     C3
	//     C2           C4
	//     C1           C5
	// Undo stack	Redo stack
	// 
	// No the user executes another command C6 - how should look the redo stack then?:
	//
	//     C6
	//     C3
	//     C2           
	//     C1           
	// Undo stack	Redo stack
	//
	// the commands C4 and C5 are just deleted and removed from the redo stack
	// C4 and C5 can not be redone. This is done because if the commands would reside on the redo stack, the user would be able to click on "Redo" and then command C4 would be executed
	// but this very confusing to the user because C4 was after C3 an not C6. Another idea would be that the user can not click on "Redo" until C6 is undone - but this is also a bit 
	// complicated to remember the correct order of executions - also this model would allow different multiply execution paths - which is also very confusing. The simples approach  
	// here is to allow only one execution path. This is the reason why the redo stack is cleaned if a new command is executed.
	while (redoStack_.size() > 0)
	{
		redoStack_.top() = nullptr;
		redoStack_.pop();
		bChangedRedoStack = true;
	}

	// if redo stack changed notify observers
	if(bChangedRedoStack)
		RedoStackChanged(redoStack_.size());

	// updated state of document
	m_pDocumentState->execute(this);
}

template<typename DataT>
void BlueFramework::Application::DataManagement::Document<DataT>::newdoc()
{
	m_pDocumentState->newdoc(this);
}

template<typename DataT>
void BlueFramework::Application::DataManagement::Document<DataT>::save()
{
	m_pDocumentState->save(this);
}

template<typename DataT>
void BlueFramework::Application::DataManagement::Document<DataT>::saveAs()
{
	m_pDocumentState->saveAs(this);
}

template<typename DataT>
void BlueFramework::Application::DataManagement::Document<DataT>::import()
{
	m_pDocumentState->import(this);
}

template<typename DataT>
bool BlueFramework::Application::DataManagement::Document<DataT>::exit()
{
	return m_pDocumentState->exit(this);
}

template<typename DataT>
void BlueFramework::Application::DataManagement::Document<DataT>::open()
{
	m_pDocumentState->open(this);
}

template<typename DataT>
DataT& BlueFramework::Application::DataManagement::Document<DataT>::getData()
{
	return *data_;
}

template<typename DataT>
void BlueFramework::Application::DataManagement::Document<DataT>::redo()
{
	assert(redoStack_.size() > 0);

	if (redoStack_.size() == 0)
		return;

	buw::ReferenceCounted<BlueFramework::Application::DataManagement::Command::ICommand> action = redoStack_.top();
	redoStack_.pop();

	data_->getNotifiactionState()->beginAction();
	action->execute();
	data_->getNotifiactionState()->endAction();

	undoStack_.push(action);
	
	UndoStackChanged(undoStack_.size());
	RedoStackChanged(redoStack_.size());

	m_pDocumentState->redo(this);
}

template<typename DataT>
void BlueFramework::Application::DataManagement::Document<DataT>::changeState( IDocumentState<DataT>* pState )
{
	if (m_pDocumentState)
	{
		delete m_pDocumentState;
	}

	m_pDocumentState = pState;

	DocumentStateChange(m_pDocumentState->getFilename());
}

template<typename DataT>
void BlueFramework::Application::DataManagement::Document<DataT>::undo()
{
	assert(undoStack_.size() > 0);

	if (undoStack_.size() == 0)
		return;

	buw::ReferenceCounted<BlueFramework::Application::DataManagement::Command::ICommand> action = undoStack_.top();
	undoStack_.pop();

	data_->getNotifiactionState()->beginAction();
	action->unexecute();
	data_->getNotifiactionState()->endAction();

	redoStack_.push(action);

	UndoStackChanged(undoStack_.size());
	RedoStackChanged(redoStack_.size());

	m_pDocumentState->undo(this);
}

template<typename DataT>
void BlueFramework::Application::DataManagement::Document<DataT>::freeUndoAndRedoStack()
{
	while(undoStack_.size() > 0)
	{
		undoStack_.top() = nullptr;
		undoStack_.pop();
	}

	while(redoStack_.size() > 0)
	{
		redoStack_.top() = nullptr;
		redoStack_.pop();
	}

	UndoStackChanged(undoStack_.size());
	RedoStackChanged(redoStack_.size());
}