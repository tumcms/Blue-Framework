#
#   This file is part of BlueFramework, a simple 3D engine.
#	Copyright (c) 2019 Technical University of Munich
#	Chair of Computational Modeling and Simulation.
#   
#   BlueFramework is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License Version 3
#   as published by the Free Software Foundation.
#   
#   BlueFramework is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#   GNU General Public License for more details.
#   
#   You should have received a copy of the GNU General Public License
#   along with this program. If not, see <http://www.gnu.org/licenses/>.
#

add_definitions(-DNOMINMAX)
add_definitions(-DBLUEFRAMEWORK_EXPORT)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Unicode rules!
add_definitions(-D_UNICODE -DQT_NO_KEYWORDS)
if (WIN32)
    # TODO: for now this only works on windows. Change BlueApplication.h to support GCC
    add_definitions(-DBLUEAPPLICATION_EXPORT)
endif(WIN32)

file(GLOB BlueFramework_Application_Data_Source                            src/BlueFramework/Application/Data/*.*)
file(GLOB BlueFramework_Application_DataManagement_Command_ENTITY_Source   src/BlueFramework/Application/DataManagement/Command/Entity/*.*)
file(GLOB BlueFramework_Application_DataManagement_Command_Source          src/BlueFramework/Application/DataManagement/Command/*.*)
file(GLOB BlueFramework_Application_DataManagement_DocumentState_Source    src/BlueFramework/Application/DataManagement/DocumentState/*.*)
file(GLOB BlueFramework_Application_DataManagement_Notification_Source     src/BlueFramework/Application/DataManagement/Notification/*.*)
file(GLOB BlueFramework_Application_DataManagement_Source                  src/BlueFramework/Application/DataManagement/*.*)
file(GLOB BlueFramework_Application_Source                                 src/BlueFramework/Application/*.*)
file(GLOB BlueFramework_Application_UserInterface_Source                   src/BlueFramework/Application/UserInterface/*.*)
file(GLOB BlueFramework_Application_UserInterface_ViewPanel_Source         src/BlueFramework/Application/UserInterface/ViewPanel/*.*)

source_group(BlueFramework\\Application                                   FILES ${BlueFramework_Application_Source})
source_group(BlueFramework\\Application\\Data                             FILES ${BlueFramework_Application_Data_Source})
source_group(BlueFramework\\Application\\DataManagement                   FILES ${BlueFramework_Application_DataManagement_Source})
source_group(BlueFramework\\Application\\DataManagement\\Command          FILES ${BlueFramework_Application_DataManagement_Command_Source})
source_group(BlueFramework\\Application\\DataManagement\\Command\\Entity  FILES ${BlueFramework_Application_DataManagement_Command_ENTITY_Source})
source_group(BlueFramework\\Application\\DataManagement\\DocumentState    FILES ${BlueFramework_Application_DataManagement_DocumentState_Source})
source_group(BlueFramework\\Application\\DataManagement\\Notification     FILES ${BlueFramework_Application_DataManagement_Notification_Source})
source_group(BlueFramework\\Application\\UserInterface                    FILES ${BlueFramework_Application_UserInterface_Source})
source_group(BlueFramework\\Application\\UserInterface\\ViewPanel         FILES ${BlueFramework_Application_UserInterface_ViewPanel_Source})

add_library(BlueFramework.Application SHARED
  ${BLUECORE_MOCS}
  ${BLUECORE_UIS_H}
  ${BLUECORE_UIS}
  ${BlueFramework_Application_Data_Source}
  ${BlueFramework_Application_DataManagement_Command_ENTITY_Source}
  ${BlueFramework_Application_DataManagement_DocumentState_Source}
  ${BlueFramework_Application_DataManagement_Notification_Source}
  ${BlueFramework_Application_DataManagement_Source}
  ${BlueFramework_Application_Source}
  ${BlueFramework_Application_UserInterface_Source}
  ${BlueFramework_Application_UserInterface_ViewPanel_Source}
  ${BlueFramework_BLUAPPLICATION_Application_Source}
)

target_include_directories(BlueFramework.Application
	PUBLIC
		src
	PRIVATE
		${TINYXML2_INCLUDE_DIR}
)

target_link_libraries(BlueFramework.Application
  BlueFramework.Core
  BlueFramework.ImageProcessing
  BlueFramework.Rasterizer
  BlueFramework.Engine
  # Qt5
  Qt5::Core
  Qt5::Widgets
  Qt5::Xml
  Qt5::XmlPatterns
)

add_dependencies(BlueFramework.Application
  BlueFramework.Core
)

# Use the Widgets module from Qt 5.
qt5_use_modules(BlueFramework.Application Widgets Xml XmlPatterns)

install(TARGETS BlueFramework.Application
   ARCHIVE DESTINATION lib/${MSVC_VERSION}/${CMAKE_VS_PLATFORM_NAME}/$<CONFIG>
   COMPONENT library_files
)

install(DIRECTORY src/BlueFramework/Application/
		DESTINATION include/BlueFramework/Application
		COMPONENT include
		FILES_MATCHING PATTERN "*.h" PATTERN "*.inl"
)

install(DIRECTORY src/BlueFramework/Application/ DESTINATION src/BlueFramework/Application
		COMPONENT source
        FILES_MATCHING PATTERN "*.cpp" PATTERN "*.h"
)
