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

//! \brief Implementation file of class FileDialog

#include "FileDialog.h"
#include <QFileDialog>

#include "BlueFramework/Core/String.h"

#include <string>
using namespace std;

QString BlueFramework::Application::UserInterface::FileDialog::getOpenFileName( 
	QWidget * /*parent*/ /*= 0*/, 
	const QString & /*caption *//*= QString()*/, 
	const QString & /*dir*/ /*= QString()*/, 
	const QString & filter /*= QString()*/, 
	QString * /*selectedFilter*/ /*= 0*/ )
{
	QStringList filters = filter.split(";;");
	QFileDialog dialog;
	dialog.setNameFilters(filters);
	dialog.setAcceptMode(QFileDialog::AcceptOpen);
	dialog.setFileMode(QFileDialog::AnyFile);
			
	if(QDialog::Accepted == dialog.exec()) 
	{
		QString destination = dialog.selectedFiles()[0];
		return destination;
	}
	else
	{
		return "";
	}
		
	// Funktioniert auch nicht - Vermutung: w�rde ohne Stylesheet schon funktionieren 
	//QString fileName = QFileDialog::getOpenFileName(parent, caption, dir, filter);
	//return fileName;

	// WinAPI direkt verwenden funktioniert nicht
	/*
	OPENFILENAME ofn;
	wchar_t szFile[MAX_PATH] = {0};

	ZeroMemory( &ofn , sizeof( ofn));

	ofn.lStructSize = sizeof ( ofn );	
	ofn.hwndOwner = nullptr;
	ofn.lpstrFilter =  APPLICATION_NAMEW L" files (*.bff)\0*.bff\0";//  APPLICATION_NAMEW L" files (*.bff);;All Files (*.*)";
	ofn.lpstrFile = szFile ;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof( szFile );
	ofn.nFilterIndex =1;
	ofn.lpstrFileTitle = nullptr ;
	ofn.nMaxFileTitle = 0 ;
	ofn.lpstrInitialDir=nullptr ;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY; //OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST ;

	GetOpenFileName( &ofn );

	std::string fn = UtfConverter::ToUtf8(szFile);

	QString fileName = fn.c_str();

	return fileName;
	*/
}

QString BlueFramework::Application::UserInterface::FileDialog::getSaveFileName( 
	QWidget * /*parent*/ /*= 0*/, 
	const QString &/*caption*/ /*= QString()*/, 
	const QString &/*dir*/ /*= QString()*/, 
	const QString &filter /*= QString()*/, 
	QString * /*selectedFilter*/ /*= 0*/ )
{
	QStringList filters = filter.split(";;");
	QFileDialog dialog;
	dialog.setNameFilters(filters);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setFileMode(QFileDialog::AnyFile);

	if(QDialog::Accepted == dialog.exec()) 
	{
		QString destination = dialog.selectedFiles()[0];
		return destination;
	}
	else
	{
		return "";
	}
}
