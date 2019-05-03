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
