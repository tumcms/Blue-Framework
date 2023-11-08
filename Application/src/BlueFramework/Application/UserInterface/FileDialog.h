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
