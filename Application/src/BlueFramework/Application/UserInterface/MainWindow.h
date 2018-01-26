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

#pragma once
#ifndef BlueFramework_Application_UserInterface_MainWindow_ae7569c4_7aed_4c32_a01c_ded9b763936f_h
#define BlueFramework_Application_UserInterface_MainWindow_ae7569c4_7aed_4c32_a01c_ded9b763936f_h

#include "BlueFramework/Application/namespace.h"
#include "BlueFramework/Application/DataManagement/Document.h"
#include <QCloseEvent>
#include <QMainWindow>
#include <boost/bind.hpp>

#ifdef BLUEFRAMEWORK_EXPORT
#define BLUEFRAMEWORK_API __declspec(dllexport)
#else
#define BLUEFRAMEWORK_API __declspec(dllimport)
#endif

BLUEFRAMEWORK_APPLICATION_UI_NAMESPACE_BEGIN

class BLUEFRAMEWORK_API MainWindowBase : public QMainWindow {
	Q_OBJECT;

public:
	//! Constructor.
	MainWindowBase(BlueFramework::Application::DataManagement::DocumentBase *document, QWidget *parent = 0, Qt::WindowFlags flags = 0);

	virtual ~MainWindowBase();

	void handle_actionNew_triggered();
	void handle_actionSave_triggered();
	void handle_actionSaveAs_triggered();
	void handle_actionOpen_triggered();
	void handle_actionUndo_triggered();
	void handle_actionRedo_triggered();
	void handle_actionImport_triggered();

protected:
	BlueFramework::Application::DataManagement::DocumentBase *m_pDocument;

	// Shows the actual status of the document state in the window title. For example it shows where an opened file is stored
	void updateWindowTitle(const std::string &documentTitle);

private:
	void updateWindowTitle2(const std::string &path);

	void closeEvent(QCloseEvent *e);

private:
	//! Protect unimplemented copy constructor from being called.
	/*
		\param[in] source	The source object that should be copied.
	*/
	MainWindowBase(const MainWindowBase &source) = delete;

	//! Protect unimplemented assignment operator from being called.
	/*
		\param[in] source	The source object that should be assigned.
	*/
	MainWindowBase &operator=(const MainWindowBase &source) = delete;
}; // end class MainWindow

class BLUEFRAMEWORK_API MainWindow : public MainWindowBase {
	Q_OBJECT;

public:
	//! Constructor.
	MainWindow(BlueFramework::Application::DataManagement::DocumentBase *document, QWidget *parent = 0, Qt::WindowFlags flags = 0)
		: MainWindowBase(document, parent, flags) {
	}

	virtual ~MainWindow() {
	}

public Q_SLOTS:
	void on_actionNew_triggered() {
		handle_actionNew_triggered();
	}
	void on_actionSave_triggered() {
		handle_actionSave_triggered();
	}
	void on_actionSaveAs_triggered() {
		handle_actionSaveAs_triggered();
	}
	void on_actionOpen_triggered() {
		handle_actionOpen_triggered();
	}
	void on_actionUndo_triggered() {
		handle_actionUndo_triggered();
	}
	void on_actionRedo_triggered() {
		handle_actionRedo_triggered();
	}
	void on_actionImport_triggered() {
		void handle_actionImport_triggered();
	}
};

BLUEFRAMEWORK_APPLICATION_UI_NAMESPACE_END

#endif // end define BlueFramework_Application_UserInterface_MainWindow_ae7569c4_7aed_4c32_a01c_ded9b763936f_h
