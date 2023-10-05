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

#include <QMessageBox>
#include <QFileDialog>
#include "UnsavedUnedited.h"
#include "SavedEdited.h"
#include "SavedUnedited.h"
#include "BlueFramework/Application/DataManagement/Data.h"
#include "BlueFramework/Core/assert.h"
#include "BlueFramework/Application/UserInterface/FileDialog.h"


template <typename DataT>
BlueFramework::Application::DataManagement::SavedEdited<DataT>::SavedEdited( const std::string&  filename )
{
	m_Filename = filename;
}

template <typename DataT>
BlueFramework::Application::DataManagement::SavedEdited<DataT>::~SavedEdited()
{

}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedEdited<DataT>::redo( Document<DataT> *document )
{
	BLUE_ASSERT(document, "document is nullptr.");
	// remain in this state
}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedEdited<DataT>::undo( Document<DataT> *document )
{
	BLUE_ASSERT(document, "document is nullptr.");
	// remain in this state
}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedEdited<DataT>::execute( Document<DataT> *document )
{
	BLUE_ASSERT(document, "document is nullptr.");
	// remain in this state
}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedEdited<DataT>::newdoc( Document<DataT> *document )
{
	BLUE_ASSERT(document, "document is nullptr.");

	QMessageBox mb( document->getDataPtr()->getApplicationName(),
		"The document has been modified.\n"
		"\n"
		"Do you want to save your changes?",
		QMessageBox::Warning,
		QMessageBox::Yes | QMessageBox::Default,
		QMessageBox::No,
		QMessageBox::Cancel | QMessageBox::Escape );

	switch ( mb.exec() ) {
		case QMessageBox::Yes:
			// Yes was clicked
			{
				std::string strFilter = std::string(document->getDataPtr()->getApplicationSaveFileFilter());

				QString fileName = BlueFramework::Application::UserInterface::FileDialog::getSaveFileName(
					nullptr, 
					"Save File", 
					"",	
					strFilter.c_str());
			
				if ( !fileName.isEmpty() )
				{
					document->getData().save(fileName.toUtf8().data());
					document->changeState(new SavedUnedited<DataT>(fileName.toUtf8().data()));
				}
			}

			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			return;
			break;
		case QMessageBox::No:
			break;
		default:
			// should never be reached
			assert(false);
			break;
	}

	document->clear();
	document->changeState(new UnsavedUnedited<DataT>());
}

template <typename DataT>
std::string BlueFramework::Application::DataManagement::SavedEdited<DataT>::getFilename()
{
	return m_Filename + " *";
}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedEdited<DataT>::open( Document<DataT> *document )
{
	BLUE_ASSERT(document, "document is nullptr.");

	QMessageBox mb( document->getDataPtr()->getApplicationName(),
		"The document has been modified.\n"
		"\n"
		"Do you want to save your changes?",
		QMessageBox::Warning,
		QMessageBox::Yes | QMessageBox::Default,
		QMessageBox::No,
		QMessageBox::Cancel | QMessageBox::Escape );

	switch ( mb.exec() ) {
		case QMessageBox::Yes:
			// Yes was clicked
			{
				std::string strFilter = std::string(document->getDataPtr()->getApplicationSaveFileFilter());

				QString fileName = BlueFramework::Application::UserInterface::FileDialog::getSaveFileName(
					nullptr, 
					"Save File", 
					"",	
					strFilter.c_str());

				if ( !fileName.isEmpty() )
				{
					document->getData().save(fileName.toUtf8().data());
					document->changeState(new SavedUnedited<DataT>(fileName.toUtf8().data()));
				}
			}

			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			return;
			break;
		case QMessageBox::No:

			break;
		default:
			// should never be reached
			assert(false);
			break;
	}

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
void BlueFramework::Application::DataManagement::SavedEdited<DataT>::save( Document<DataT> *document )
{
	BLUE_ASSERT(document, "document is nullptr.");
	document->getData().save(m_Filename);
	document->changeState(new SavedUnedited<DataT>(m_Filename));
}

template <typename DataT>
void BlueFramework::Application::DataManagement::SavedEdited<DataT>::saveAs( Document<DataT> *document )
{
	BLUE_ASSERT(document, "document is nullptr.");

	std::string strFilter = std::string(document->getDataPtr()->getApplicationSaveFileFilter());

	QString fileName = BlueFramework::Application::UserInterface::FileDialog::getSaveFileName(
		nullptr, 
		"Save File",
		"",
		strFilter.c_str());

	document->getData().save(fileName.toUtf8().data());
	document->changeState(new SavedUnedited<DataT>(fileName.toUtf8().data()));
}

template <typename DataT>
bool BlueFramework::Application::DataManagement::SavedEdited<DataT>::exit( Document<DataT> *document )
{
	BLUE_ASSERT(document, "document is nullptr.");

	QMessageBox mb( document->getDataPtr()->getApplicationName(),
		"The document has been modified.\n"
		"\n"
		"Do you want to save your changes?",
		QMessageBox::Warning,
		QMessageBox::Yes | QMessageBox::Default,
		QMessageBox::No,
		QMessageBox::Cancel | QMessageBox::Escape );

	switch ( mb.exec() ) {
		case QMessageBox::Yes:
			// Yes was clicked
			{
				document->getData().save(m_Filename);
				document->changeState(new SavedUnedited<DataT>(m_Filename));
			}
			return true;
			
		case QMessageBox::Cancel:
			// Cancel was clicked
			return false;
			
		case QMessageBox::No:
			return true;

		default:
			// should never be reached
			assert(false);
			return true;
	}
}
