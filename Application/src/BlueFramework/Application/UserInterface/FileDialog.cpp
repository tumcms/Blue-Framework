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
		
	// Funktioniert auch nicht - Vermutung: würde ohne Stylesheet schon funktionieren 
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