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
#ifndef BlueFramework_Application_DataManagement_SaveEdited_495b493b_2ad4_4ef2_b068_cd7469b3d975_h
#define BlueFramework_Application_DataManagement_SaveEdited_495b493b_2ad4_4ef2_b068_cd7469b3d975_h

#include "BlueFramework/Core/assert.h"
#include "BlueFramework/Application/DataManagement/DocumentState/IDocumentState.h"
#include "BlueFramework/Application/namespace.h"

BLUEFRAMEWORK_APPLICATION_DATAMANAGEMENT_NAMESPACE_BEGIN

//! \class SavedEdited
//! \brief A document state which refers to an saved but edited document.
template <typename DataT>
class SavedEdited : public IDocumentState<DataT> {
public:
	//! Constructor.
	SavedEdited(const std::string &filename);

	virtual ~SavedEdited();

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
	virtual void import(Document<DataT> *document) {
		BLUE_ASSERT(document);
	}

	//! The user want to exit the application.
	virtual bool exit(Document<DataT> *document);

	//! Gets the filename of the document.
	virtual std::string getFilename();

private:
	//! Filename.
	std::string m_Filename;

	//! Protect unimplemented copy constructor from being called.
	/*
	\param[in] source	The source object that should be copied.
	*/
	SavedEdited(const SavedEdited &source);

	//! Protect unimplemented assignment operator from being called.
	/*
	\param[in] source	The source object that should be assigned.
	*/
	SavedEdited &operator=(const SavedEdited &source);
}; // end class SavedEdited

BLUEFRAMEWORK_APPLICATION_DATAMANAGEMENT_NAMESPACE_END

#include "SavedEdited.inl"

#endif // end define BlueFramework_Application_DataManagement_SaveEdited_495b493b_2ad4_4ef2_b068_cd7469b3d975_h
