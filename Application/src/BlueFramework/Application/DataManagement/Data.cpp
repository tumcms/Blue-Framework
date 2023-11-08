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

#include "Data.h"

#include "Notification/NotifiyAfterEachActionOnlyOnce.h"
#include "BlueFramework/Core/Math/vector.h"
#include "BlueFramework/Core/Math/matrix.h"
#include "BlueFramework/Core/Exception.h"

#include <sstream>

#include <QFile>
#include <QtXml>
//#include <QXmlQuery>
//#include <QXmlResultItems>

#include <algorithm>

BlueFramework::Application::DataManagement::Data::Data(NotificationState *pNotifiactionState) :
m_pNotificationState(pNotifiactionState)
{
	//m_pNotifiactionState = new NotifiyAfterEachActionOnlyOnce();
}

BlueFramework::Application::DataManagement::Data::~Data()
{
	delete m_pNotificationState;
}

void BlueFramework::Application::DataManagement::Data::NotifiactionStateEmitCange()
{
	m_pNotificationState->change();
}

void BlueFramework::Application::DataManagement::Data::save( const std::string&  filename )
{
	QDomDocument doc;
	QDomProcessingInstruction header = doc.createProcessingInstruction( "xml", "version=\"1.0\"" );
	doc.appendChild( header );
	QDomElement root = doc.createElement( getApplicationNameXML() );
	root.setAttribute("version", getApplicationVersionString());
	doc.appendChild( root ); 

	// save entity objects
	QDomElement xmlEntityObjects = doc.createElement("EntityObjects");

	root.appendChild(xmlEntityObjects);

	QFile file( filename.c_str() );
	if( !file.open( QIODevice::WriteOnly ) )
	{
		//return -1;
	}

	QTextStream ts( &file );
	ts << doc.toString();

	file.close();

	file.close();
}

void BlueFramework::Application::DataManagement::Data::open( const std::string&  filename )
{
	// read file
	QDomDocument doc( getApplicationNameXML() );
	QFile file( filename.c_str() );
	if( !file.open( QIODevice::ReadOnly ) )
	{
		// file could not be opened
		throw BlueFramework::Core::FileNotFoundException(filename);
	}
	if( !doc.setContent( &file ) )
	{
		file.close();

		// file could not be read
		throw BlueFramework::Core::FileNotFoundException(filename);
	}

	// parse file
	QDomElement root = doc.documentElement();
	if( root.tagName() != getApplicationNameXML() )
	{
		throw BlueFramework::Core::InvalidFileFormatException(filename);
	}

	// read materials objects
	QDomElement xmlEntityObjects = root.firstChildElement("EntityObjects");
	for (QDomElement xmlEntity = xmlEntityObjects.firstChildElement("Entity"); !xmlEntity.isNull();  xmlEntity = xmlEntity.nextSiblingElement("Entity")) 
	{
		QString qstrEntityName = xmlEntity.attribute("entityName", "" );
		QString qstrID = xmlEntity.attribute("ID", "-1");

		std::string EntityName = qstrEntityName.toUtf8().data();// .toAscii().data();

		/*if (EntityName == "Material")
		{
			BlueFramework::SmartTrace::Data::Material material(qstrID.toInt(), EntityName);

			QDomElement xmlData  = xmlEntity.firstChildElement("data");
			readEntityData(xmlData, material);

			addEntityObject(material);
		}
		else*/
		{
			std::cout<<"Can not read "<< EntityName.c_str() <<std::endl;
		}
	}

	// inform all observer about the change in the data layer
	Change();
}

void BlueFramework::Application::DataManagement::Data::clear( bool notifyObservers )
{
	if (notifyObservers)
	{
		// The notification state is not used here, because a clear is not executed by an action.
		//m_pNotifiactionState->Change();

		Change();

		Clear();
	}
}

void BlueFramework::Application::DataManagement::Data::clear()
{
	clear(true);
}

void BlueFramework::Application::DataManagement::Data::import( const std::string&  /*filename*/ )
{

}
