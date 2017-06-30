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

#pragma once
#ifndef BlueFramework_Application_UserInterface_FileDialog_e0ec67c7_2af1_413c_b314_5d9563675139_h
#define BlueFramework_Application_UserInterface_FileDialog_e0ec67c7_2af1_413c_b314_5d9563675139_h

#include "BlueFramework/Core/NonCopyable.h"
#include "BlueFramework/Application/namespace.h"
#include <QString>
#include <QWidget>

BLUEFRAMEWORK_APPLICATION_UI_NAMESPACE_BEGIN

class FileDialog : buw::NonCopyable {
public:
	static QString
		getOpenFileName(QWidget *parent = 0, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString *selectedFilter = 0);

	static QString
		getSaveFileName(QWidget *parent = 0, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString *selectedFilter = 0);

private:
	FileDialog() {
	}

	virtual ~FileDialog() {
	}
};

BLUEFRAMEWORK_APPLICATION_UI_NAMESPACE_END

#endif // end define BlueFramework_Application_UserInterface_FileDialog_e0ec67c7_2af1_413c_b314_5d9563675139_h