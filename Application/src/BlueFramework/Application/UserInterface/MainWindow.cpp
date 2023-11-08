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
