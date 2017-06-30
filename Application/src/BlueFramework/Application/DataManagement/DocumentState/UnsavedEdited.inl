/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2016-2017 Technical University of Munich
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

#include "UnsavedEdited.h"
#include "UnsavedUnedited.h"
#include "SavedUnedited.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QIcon>
#include "../Data.h"
#include "../../UserInterface/FileDialog.h"


template <typename DataT>
BlueFramework::Application::DataManagement::UnsavedEdited<DataT>::UnsavedEdited()
{

}

template <typename DataT>
BlueFramework::Application::DataManagement::UnsavedEdited<DataT>::~UnsavedEdited()
{

}

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedEdited<DataT>::undo( Document<DataT> *document )
{
	assert(document);
	// remain in this state
}

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedEdited<DataT>::execute( Document<DataT> *document )
{
	assert(document);
	// remain in this state
}

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedEdited<DataT>::newdoc( Document<DataT> *document )
{
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
		case QMessageBox::No:
			// Don't Save was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			return;
			break;
		default:
			// should never be reached
			break;
	}

	document->clear();
	document->changeState(new UnsavedUnedited<DataT>());
}
	
template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedEdited<DataT>::open( Document<DataT> *document )
{
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
void BlueFramework::Application::DataManagement::UnsavedEdited<DataT>::save( Document<DataT> *document )
{
	saveAs(document);
}

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedEdited<DataT>::saveAs( Document<DataT> *document )
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
void BlueFramework::Application::DataManagement::UnsavedEdited<DataT>::redo( Document<DataT> *document )
{
	assert(document);
	// remain in this state
}

template <typename DataT>
void BlueFramework::Application::DataManagement::UnsavedEdited<DataT>::import(Document<DataT> *document)
{
	QString fileName = BlueFramework::Application::UserInterface::FileDialog::getOpenFileName(nullptr, 
		"Open File", "", "All Files (*.*)");	

	//QFileDialog fd  TODO: title import

	if (!fileName.isEmpty())
	{
		std::string filename = fileName.toUtf8().data();

		document->clear();
		document->getData().import(filename);
		document->changeState(new UnsavedUnedited<DataT>());
	}
}

template <typename DataT>
bool BlueFramework::Application::DataManagement::UnsavedEdited<DataT>::exit( Document<DataT> *document )
{
	QMessageBox mb( document->getDataPtr()->getApplicationName(),
		"The document has been modified.\n"
		"\n"
		"Do you want to save your changes?",
		QMessageBox::Warning,
		QMessageBox::Yes | QMessageBox::Default,
		QMessageBox::No,
		QMessageBox::Cancel | QMessageBox::Escape );

// Problem: MessageBox sieht nicht so aus wie eine Windows MessageBox
//#if defined(Q_WS_WIN)
// 1. Workaround: Funktioniert nicht weil QT das einfach nicht kann.
//	//HWND hwnd = mb.winId();
//	//LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
//	//style &= ~WS_SYSMENU; // unset the system menu flag
//	//SetWindowLongPtr(hwnd, GWL_STYLE, style);
//	//// force Windows to refresh some cached window styles
//	//SetWindowPos(hwnd, 0, 0, 0, 0, 0, 
//	//	SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
//	
// 2. Workaround: Einfach WinAPI - funktiniert nicht weil Button in deutscher Sprache
//	#pragma comment(lib, "ComCtl32")
//
//	MessageBox(0, 
//		L"The document has been modified.\n"
//		L"\n"
//		L"Do you want to save your changes?",
//		APPLICATION_NAMEW,
//		MB_YESNOCANCEL|MB_ICONWARNING);
//
//	// http://www.c-plusplus.de/forum/viewtopic-var-t-is-254121.html
//	// http://www.c-plusplus.de/forum/viewtopic-var-t-is-253985.html
// 3. Workarund: eigenen MessageBox Dialog erstellen: sehr aufw�dnig
// Fazit: Einfach QT Variante akzeptieren - sp�ter vielleicht das Applikationsicon in der MessageBox verwenden
//#endif


	switch ( mb.exec() ) 
	{
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

template <typename DataT>
std::string BlueFramework::Application::DataManagement::UnsavedEdited<DataT>::getFilename()
{
	return "Untitled *";
}