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
#ifndef BlueFramework_Application_DataManagement_UnsavedUnedited_fa7dfadc_1397_4fd0_8da9_9539320dad10_h
#define BlueFramework_Application_DataManagement_UnsavedUnedited_fa7dfadc_1397_4fd0_8da9_9539320dad10_h

#include "BlueFramework/Application/DataManagement/DocumentState/IDocumentState.h"
#include "BlueFramework/Application/namespace.h"

BLUEFRAMEWORK_APPLICATION_DATAMANAGEMENT_NAMESPACE_BEGIN

//! \class UnsavedUnedited
//! \brief A document state which refers to an saved but edited document.
template<typename DataT>
class UnsavedUnedited : public IDocumentState<DataT>
{
public:
	//! Constructor.
	UnsavedUnedited();

	virtual ~UnsavedUnedited();

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
	static int m_InstanceCounter;

	//! Protect unimplemented copy constructor from being called.
	/*
		\param[in] source	The source object that should be copied.
	*/
	UnsavedUnedited(const UnsavedUnedited &source);

	//! Protect unimplemented assignment operator from being called.
	/*
		\param[in] source	The source object that should be assigned.
	*/
	UnsavedUnedited& operator= (const UnsavedUnedited& source);
}; // end class UnsavedUnedited

BLUEFRAMEWORK_APPLICATION_DATAMANAGEMENT_NAMESPACE_END

#include "UnsavedUnedited.inl"

#endif // end define BlueFramework_Application_DataManagement_UnsavedUnedited_fa7dfadc_1397_4fd0_8da9_9539320dad10_h
