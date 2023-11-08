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

#include "SavedEdited.h"
#include "SavedUnedited.h"
#include "UnsavedUnedited.h"
#include <QFileDialog>
#include <QString>
#include "../Data.h"

template <typename DataT>
BlueFramework::Application::DataManagement::SavedUnedited<DataT>::SavedUnedited( const std::string&  filename )
{
	m_Filename = filename;
}

template <typename DataT>
BlueFramework::Application::DataManagement::SavedUnedited<DataT>::~SavedUnedited()
{

}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedUnedited<DataT>::redo( Document<DataT> *document )
{
	document->changeState(new SavedEdited<DataT>(m_Filename));
}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedUnedited<DataT>::undo( Document<DataT> *document )
{
	document->changeState(new SavedEdited<DataT>(m_Filename));
}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedUnedited<DataT>::execute( Document<DataT> *document )
{
	document->changeState(new SavedEdited<DataT>(m_Filename));
}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedUnedited<DataT>::newdoc( Document<DataT> *document )
{
	document->clear();
	document->changeState(new UnsavedUnedited<DataT>());
}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedUnedited<DataT>::open( Document<DataT> *document )
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
		document->changeState(new SavedUnedited(filename));
	}
}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedUnedited<DataT>::save( Document<DataT> *document )
{
	document->getData().save(m_Filename);
}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedUnedited<DataT>::saveAs( Document<DataT> *document )
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
		document->changeState(new SavedUnedited(fileName.toUtf8().data()));
	}
}

template <typename DataT>
bool BlueFramework::Application::DataManagement::SavedUnedited<DataT>::exit( Document<DataT> *document )
{
	assert(document);
	// nothing to save
	return true;
}

template <typename DataT>
std::string BlueFramework::Application::DataManagement::SavedUnedited<DataT>::getFilename()
{
	return m_Filename;
}
