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
#ifndef BlueFramework_Application_DataManagement_Data_20a5244a_e366_45f5_9931_40de5ecb80e1_h
#define BlueFramework_Application_DataManagement_Data_20a5244a_e366_45f5_9931_40de5ecb80e1_h

#include "BlueFramework/Application/namespace.h"
#include <string>
#include <vector>
#include <map>
#include <boost/signals2.hpp>
#include "BlueFramework/Core/Noncopyable.h"
#include "Notification/NotificationState.h"
#include "BlueFramework/Core/NonCopyable.h"

BLUEFRAMEWORK_APPLICATION_DATAMANAGEMENT_NAMESPACE_BEGIN

//! \class Data
//! \brief This is the data layer/data model of the application. 
//!
//! All application data is contained in this class. The data is just manipulated in/through this class. 
//! This is necessary because the data model is responsible for sending events/signals if the event listers/observers if the data has changed.
//! The manipulator functions (functions that change the application data) should only be called from IActions.
class Data : private buw::NonCopyable
{
public:
	//! Constructor.
	Data(NotificationState *pNotifiactionState);

	virtual ~Data();

	//---------------------------------------------------------------------------//
	// Signals
	//---------------------------------------------------------------------------//

	//! This signal is emitted if the data model changes. All data in this class belongs to the data model.
	boost::signals2::signal<void ()> Change;

	//! This signal is emitted if the data model is cleared. 
	boost::signals2::signal<void ()> Clear;
								
	NotificationState * getNotifiactionState() { return m_pNotificationState; }

	void NotifiactionStateEmitCange();
		
	void save( const std::string&  filename );

	void open( const std::string&  filename );

	void import( const std::string&  filename );

	// Overwrite this to remove all entity objects todo: make default implementation delete all entity objects
	void clear();

	void clear(bool notifyObservers);

	// Retrieve the name of the application
	virtual const char* getApplicationName() = 0;
				
	// Retrieve the verstion string
	virtual const char* getApplicationVersionString() = 0;

	// Retrieve the name of the application
	virtual const char* getApplicationOpenFileFilter() = 0;

	virtual const char* getApplicationSaveFileFilter()
	{
		return getApplicationOpenFileFilter();
	}

	// Retrieve the name of the application
	virtual const char* getApplicationImportFileFilter() 
	{
		return getApplicationOpenFileFilter();
	}

	// Retrive string for xml file - the standard implementation of save saves all entity objects in an xml file. This string is
	// stored as application string in the xml file. It can be reused when loading a file to check if a file is compatible with this
	// version 
	virtual const char* getApplicationNameXML() = 0;

private:

	//! Determines the notification behavior of this class.
	NotificationState *m_pNotificationState;
}; // end class Data

BLUEFRAMEWORK_APPLICATION_DATAMANAGEMENT_NAMESPACE_END

#endif // end define BlueFramework_Application_DataManagement_Data_20a5244a_e366_45f5_9931_40de5ecb80e1_h
