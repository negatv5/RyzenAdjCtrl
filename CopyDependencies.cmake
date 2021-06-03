# Internal variable to avoid copying more than once
if(COPIED_DEPENDENCIES)
	return()
endif()

option(COPY_DEPENDENCIES "Automatically try copying all dependencies" ON)
if(NOT COPY_DEPENDENCIES)
	return()
endif()

#COPY DEPS
message("\nCopy Dependencies...\n")

set(COPIED_DEPENDENCIES TRUE CACHE BOOL "Dependencies have been copied, set to false to copy again" FORCE)

configure_file(Appfolder/Config/StyleSheet.xml ${PROJECT_BINARY_DIR}/Appfolder/Config/StyleSheet.xml COPYONLY)
configure_file(Appfolder/Theme/checkbox_checked.png ${PROJECT_BINARY_DIR}/Appfolder/Theme/checkbox_checked.png COPYONLY)
configure_file(Appfolder/Theme/checkbox_checked_disabled.png ${PROJECT_BINARY_DIR}/Appfolder/Theme/checkbox_checked_disabled.png COPYONLY)
configure_file(Appfolder/Theme/checkbox_checked_focus.png ${PROJECT_BINARY_DIR}/Appfolder/Theme/checkbox_checked_focus.png COPYONLY)
configure_file(Appfolder/Theme/checkbox_unchecked.png ${PROJECT_BINARY_DIR}/Appfolder/Theme/checkbox_unchecked.png COPYONLY)
configure_file(Appfolder/Theme/checkbox_unchecked_disabled.png ${PROJECT_BINARY_DIR}/Appfolder/Theme/checkbox_unchecked_disabled.png COPYONLY)
configure_file(Appfolder/Theme/checkbox_unchecked_focus.png ${PROJECT_BINARY_DIR}/Appfolder/Theme/checkbox_unchecked_focus.png COPYONLY)
configure_file(Appfolder/Theme/down_arrow.png ${PROJECT_BINARY_DIR}/Appfolder/Theme/down_arrow.png COPYONLY)
configure_file(Appfolder/Theme/down_arrow_disabled.png ${PROJECT_BINARY_DIR}/Appfolder/Theme/down_arrow_disabled.png COPYONLY)
configure_file(Appfolder/Theme/up_arrow.png ${PROJECT_BINARY_DIR}/Appfolder/Theme/up_arrow.png COPYONLY)
configure_file(Appfolder/Theme/up_arrow_disabled.png ${PROJECT_BINARY_DIR}/Appfolder/Theme/up_arrow_disabled.png COPYONLY)

# Doesn't really make sense anywhere else
if(NOT MSVC)
	return()
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../RyzenAdj/build/libryzenadj.dll ${PROJECT_BINARY_DIR}/Appfolder/libryzenadj.dll COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../RyzenAdj/win32/inpoutx64.dll ${PROJECT_BINARY_DIR}/Appfolder/inpoutx64.dll COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../RyzenAdj/win32/WinRing0x64.dll ${PROJECT_BINARY_DIR}/Appfolder/WinRing0x64.dll COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../RyzenAdj/win32/WinRing0x64.sys ${PROJECT_BINARY_DIR}/Appfolder/WinRing0x64.sys COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/LICENSE ${PROJECT_BINARY_DIR}/LICENSE COPYONLY)

if(NOT CMAKE_BUILD_TYPE MATCHES "Debug")

configure_file(${CMAKE_PREFIX_PATH}/bin/Qt${QT_VERSION_MAJOR}Core.dll ${PROJECT_BINARY_DIR}/Appfolder/Qt${QT_VERSION_MAJOR}Core.dll COPYONLY)
configure_file(${CMAKE_PREFIX_PATH}/bin/Qt${QT_VERSION_MAJOR}Gui.dll ${PROJECT_BINARY_DIR}/Appfolder/Qt${QT_VERSION_MAJOR}Gui.dll COPYONLY)
configure_file(${CMAKE_PREFIX_PATH}/bin/Qt${QT_VERSION_MAJOR}Widgets.dll ${PROJECT_BINARY_DIR}/Appfolder/Qt${QT_VERSION_MAJOR}Widgets.dll COPYONLY)
configure_file(${CMAKE_PREFIX_PATH}/plugins/imageformats/qico.dll ${PROJECT_BINARY_DIR}/Appfolder/ImageFormats/qico.dll COPYONLY)
configure_file(${CMAKE_PREFIX_PATH}/plugins/platforms/qwindows.dll ${PROJECT_BINARY_DIR}/Appfolder/Platforms/qwindows.dll COPYONLY)
configure_file(${CMAKE_PREFIX_PATH}/plugins/styles/qwindowsvistastyle.dll ${PROJECT_BINARY_DIR}/Appfolder/Styles/qwindowsvistastyle.dll COPYONLY)

else(NOT CMAKE_BUILD_TYPE MATCHES "Debug")

configure_file(${CMAKE_PREFIX_PATH}/bin/Qt${QT_VERSION_MAJOR}Cored.dll ${PROJECT_BINARY_DIR}/Appfolder/Qt${QT_VERSION_MAJOR}Cored.dll COPYONLY)
configure_file(${CMAKE_PREFIX_PATH}/bin/Qt${QT_VERSION_MAJOR}Guid.dll ${PROJECT_BINARY_DIR}/Appfolder/Qt${QT_VERSION_MAJOR}Guid.dll COPYONLY)
configure_file(${CMAKE_PREFIX_PATH}/bin/Qt${QT_VERSION_MAJOR}Widgetsd.dll ${PROJECT_BINARY_DIR}/Appfolder/Qt${QT_VERSION_MAJOR}Widgetsd.dll COPYONLY)
configure_file(${CMAKE_PREFIX_PATH}/plugins/imageformats/qicod.dll ${PROJECT_BINARY_DIR}/Appfolder/ImageFormats/qicod.dll COPYONLY)
configure_file(${CMAKE_PREFIX_PATH}/plugins/platforms/qwindowsd.dll ${PROJECT_BINARY_DIR}/Appfolder/Platforms/qwindowsd.dll COPYONLY)
configure_file(${CMAKE_PREFIX_PATH}/plugins/styles/qwindowsvistastyled.dll ${PROJECT_BINARY_DIR}/Appfolder/Styles/qwindowsvistastyled.dll COPYONLY)

endif(NOT CMAKE_BUILD_TYPE MATCHES "Debug")
