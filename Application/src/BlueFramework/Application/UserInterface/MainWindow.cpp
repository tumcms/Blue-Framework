/*
    This file is part of BlueFramework, a simple 3D engine.
	Copyright (c) 2018 Technical University of Munich
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

#include "MainWindow.h"

#include <QApplication>

#include <sstream>
#include "BlueFramework/Core/Path.h"
#include "BlueFramework/Core/Diagnostics/log.h"

BlueFramework::Application::UserInterface::MainWindowBase::MainWindowBase( 
	BlueFramework::Application::DataManagement::DocumentBase *document, 
	QWidget *parent /*= 0*/, 
	Qt::WindowFlags flags /*= 0*/ ) 
	: QMainWindow(parent, flags),
	m_pDocument(document)
{
	m_pDocument->DocumentStateChange.connect(boost::bind(&MainWindowBase::updateWindowTitle2, this, _1));
}

BlueFramework::Application::UserInterface::MainWindowBase::~MainWindowBase()
{

}

void BlueFramework::Application::UserInterface::MainWindowBase::handle_actionNew_triggered()
{
	m_pDocument->newdoc();
}

void BlueFramework::Application::UserInterface::MainWindowBase::handle_actionSave_triggered()
{
	m_pDocument->save();
}

void BlueFramework::Application::UserInterface::MainWindowBase::handle_actionSaveAs_triggered()
{
	m_pDocument->saveAs();
}

void BlueFramework::Application::UserInterface::MainWindowBase::handle_actionOpen_triggered()
{
	m_pDocument->open();
}

void BlueFramework::Application::UserInterface::MainWindowBase::handle_actionUndo_triggered()
{
	m_pDocument->undo();
}

void BlueFramework::Application::UserInterface::MainWindowBase::handle_actionRedo_triggered()
{
	m_pDocument->redo();
}

void BlueFramework::Application::UserInterface::MainWindowBase::handle_actionImport_triggered()
{
	m_pDocument->import();
}

void BlueFramework::Application::UserInterface::MainWindowBase::updateWindowTitle( const std::string& documentTitle )
{
	std::stringstream sstr;
	
	sstr<< m_pDocument->getDataPtr()->getApplicationName()
		<< " "
		<< m_pDocument->getDataPtr()->getApplicationVersionString()
		<< " -  [" + documentTitle + "]";
	setWindowTitle(sstr.str().c_str());
}

void BlueFramework::Application::UserInterface::MainWindowBase::updateWindowTitle2( const std::string& path )
{
	buw::Path p(path.c_str());
	updateWindowTitle( p.getFilename() );
}

void BlueFramework::Application::UserInterface::MainWindowBase::closeEvent( QCloseEvent *e )
{
	if(!m_pDocument->exit())
	{
		e->ignore();
	}
	else
	{
		QApplication::quit();
	}
}