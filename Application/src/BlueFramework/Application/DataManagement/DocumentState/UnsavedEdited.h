/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2019 Technical University of Munich
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
#ifndef BlueFramework_Application_DataManagement_UnsavedEdited_3126a08e_50a4_43b5_9bf6_4e362fa5fa48_h
#define BlueFramework_Application_DataManagement_UnsavedEdited_3126a08e_50a4_43b5_9bf6_4e362fa5fa48_h

#include "BlueFramework/Application/DataManagement/DocumentState/IDocumentState.h"
#include "BlueFramework/Application/namespace.h"

BLUEFRAMEWORK_APPLICATION_DATAMANAGEMENT_NAMESPACE_BEGIN

//! \class UnsavedEdited
//! \brief A document state which refers to an unsaved but edited document.
template <typename DataT>
class UnsavedEdited : public IDocumentState<DataT>
{
public:
	//! Constructor.
	UnsavedEdited();

	virtual ~UnsavedEdited();

	//! The user redos a certain action.
	virtual void redo(Document<DataT> *document);

	//! The user undos a certain action.
	virtual void undo(Document<DataT> *document);

	//! The user executes a certain action.
	virtual void execute(Document<DataT> *document);

	//! The user creates a new document.
	virtual void newdoc(Document<DataT> *document);

	//! The user is opening a new document.
	virtual void open(Document<DataT> *document);

	//! The user hits the Save button.
	virtual void save(Document<DataT> *document);

	//! The user hits Save As button.
	virtual void saveAs(Document<DataT> *document);

	//! The user hits Import button.
	virtual void import(Document<DataT> *document);

	//! The user want to exit the application.
	virtual bool exit(Document<DataT> *document);

	//! Gets the filename of the document.
	virtual std::string getFilename();

private:
	//! Protect unimplemented copy constructor from being called.
	/*
	\param[in] source	The source object that should be copied.
	*/
	UnsavedEdited(const UnsavedEdited &source);

	//! Protect unimplemented assignment operator from being called.
	/*
	\param[in] source	The source object that should be assigned.
	*/
	UnsavedEdited& operator= (const UnsavedEdited& source);
}; // end class UnsavedEdited

BLUEFRAMEWORK_APPLICATION_DATAMANAGEMENT_NAMESPACE_END

#include "UnsavedEdited.inl"

#endif // end define BlueFramework_Application_DataManagement_UnsavedEdited_3126a08e_50a4_43b5_9bf6_4e362fa5fa48_h