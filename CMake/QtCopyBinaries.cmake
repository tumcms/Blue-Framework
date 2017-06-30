# QtCopyBinaries
add_custom_target(Qt5CopyBinaries
  # Output Message
  COMMENT "Copying Ot binaries from '${Qt5Core_DIR}/../../bin/' to '${CMAKE_BINARY_DIR}'" VERBATIM

  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libEGLd.dll          ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libGLESv2d.dll        ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Cored.dll         ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Guid.dll          ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Networkd.dll        ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5OpenGLd.dll            ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Scriptd.dll            ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Sqld.dll               ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Widgetsd.dll           ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Xmld.dll               ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5XmlPatternsd.dll       ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Multimediad.dll        ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5MultimediaWidgetsd.dll ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5PrintSupportd.dll    ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Sensorsd.dll        ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Quickd.dll        ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Qmld.dll          ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Positioningd.dll      ${CMAKE_BINARY_DIR}/Debug
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Svgd.dll          ${CMAKE_BINARY_DIR}/Debug
  #COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icudt54.dll          ${CMAKE_BINARY_DIR}/Debug
  #COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icuin54.dll          ${CMAKE_BINARY_DIR}/Debug
  #COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icuuc54.dll          ${CMAKE_BINARY_DIR}/Debug

  # release version
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libEGL.dll         ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libGLESv2.dll        ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Core.dll         ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Gui.dll         ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Network.dll       ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5OpenGL.dll         ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Script.dll         ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Sql.dll         ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Widgets.dll       ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Xml.dll         ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5XmlPatterns.dll     ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Multimedia.dll      ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5MultimediaWidgets.dll  ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5PrintSupport.dll    ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Sensors.dll        ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Quick.dll        ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Qml.dll          ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Positioning.dll      ${CMAKE_BINARY_DIR}/Release
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Svg.dll          ${CMAKE_BINARY_DIR}/Release
  #COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icudt54.dll         ${CMAKE_BINARY_DIR}/Release
  #COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icuin54.dll         ${CMAKE_BINARY_DIR}/Release
  #COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icuuc54.dll         ${CMAKE_BINARY_DIR}/Release

  # RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libEGL.dll         ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/libGLESv2.dll        ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Core.dll         ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Gui.dll         ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Network.dll       ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5OpenGL.dll         ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Script.dll         ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Sql.dll         ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Widgets.dll       ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Xml.dll         ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5XmlPatterns.dll     ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Multimedia.dll      ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5MultimediaWidgets.dll  ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5PrintSupport.dll    ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Sensors.dll        ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Quick.dll        ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Qml.dll          ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Positioning.dll      ${CMAKE_BINARY_DIR}/RelWithDebInfo
  COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/Qt5Svg.dll          ${CMAKE_BINARY_DIR}/RelWithDebInfo
  #COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icudt54.dll         ${CMAKE_BINARY_DIR}/RelWithDebInfo
  #COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icuin54.dll         ${CMAKE_BINARY_DIR}/RelWithDebInfo
  #COMMAND  ${CMAKE_COMMAND} -E copy ${Qt5Core_DIR}/../../../bin/icuuc54.dll         ${CMAKE_BINARY_DIR}/RelWithDebInfo

  # Plugins
  COMMAND  ${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../plugins/platforms  ${CMAKE_BINARY_DIR}/Debug/platforms
  COMMAND  ${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../plugins/imageformats  ${CMAKE_BINARY_DIR}/Debug/imageformats
  COMMAND  ${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../plugins/platforms  ${CMAKE_BINARY_DIR}/Release/platforms
  COMMAND  ${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../plugins/imageformats  ${CMAKE_BINARY_DIR}/Release/imageformats
  COMMAND  ${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../plugins/platforms  ${CMAKE_BINARY_DIR}/RelWithDebInfo/platforms
  COMMAND  ${CMAKE_COMMAND} -E copy_directory ${Qt5Core_DIR}/../../../plugins/imageformats  ${CMAKE_BINARY_DIR}/RelWithDebInfo/imageformats
)
