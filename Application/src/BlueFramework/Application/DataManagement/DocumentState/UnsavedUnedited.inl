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

#include "UnsavedEdited.h"
#include "UnsavedUnedited.h"
#include "SavedUnedited.h"
#include <QFileDialog>
#include <QString>
#include "../Data.h"

#include "../../UserInterface/FileDialog.h"

template <typename DataT>
int BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::m_InstanceCounter = 0;

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::open( Document<DataT> *document )
{	
	std::string strFilter = std::string(document->getDataPtr()->getApplicationOpenFileFilter());

	QString fileName = BlueFramework::Application::UserInterface::FileDialog::getOpenFileName(
		nullptr, 
		"Open File", 
		"", 
		strFilter.c_str());	

	if (!fileName.isEmpty())
	{
		std::string filename = fileName.toUtf8().data();

		document->clear();
		document->getData().open(filename);
		document->changeState(new SavedUnedited<DataT>(filename));
	}
}

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::save( Document<DataT> *document )
{
	saveAs(document);
}

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::saveAs( Document<DataT> *document )
{
	std::string strFilter = std::string(document->getDataPtr()->getApplicationSaveFileFilter());

	QString fileName = BlueFramework::Application::UserInterface::FileDialog::getSaveFileName(
		nullptr, 
		"Save File",	
		"",	
		strFilter.c_str());

	if (!fileName.isEmpty())
	{
		document->getData().save(fileName.toUtf8().data());
		document->changeState(new SavedUnedited<DataT>(fileName.toUtf8().data()));
	}
}

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::import(Document<DataT> *document)
{
	std::string strFilter = std::string(document->getDataPtr()->getApplicationImportFileFilter());

	QString fileName = BlueFramework::Application::UserInterface::FileDialog::getOpenFileName(
		nullptr, 
		"Open", 
		"", 
		strFilter.c_str());	
	
	//QFileDialog fd  TODO: title import

	if (!fileName.isEmpty())
	{
		std::string filename = fileName.toUtf8().data();

		document->clear();
		document->getData().import(filename);
		document->changeState(new UnsavedUnedited());
	}
}

template <typename DataT>
std::string BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::getFilename()
{
	if (m_InstanceCounter > 1)
	{
		std::stringstream sstr;
		sstr<<"Untitled "<<m_InstanceCounter;
		return sstr.str();
	}

	return "Untitled";
}

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::redo( Document<DataT> *document )
{
	document->changeState(new UnsavedEdited<DataT>());
}

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::undo( Document<DataT> *document )
{
	document->changeState(new UnsavedEdited<DataT>());
}

template <typename DataT>
BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::~UnsavedUnedited()
{

}

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::execute( Document<DataT> *document )
{
	document->changeState(new UnsavedEdited<DataT>());
}

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::newdoc( Document<DataT> *document )
{
	document->clear();

	document->changeState(new UnsavedUnedited<DataT>());
}

template <typename DataT>
bool BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::exit( Document<DataT> *document )
{
	assert(document);
	// nothing to save
	return true;
}

template <typename DataT>
BlueFramework::Application::DataManagement::UnsavedUnedited<DataT>::UnsavedUnedited()
{
	m_InstanceCounter++;
}
