set(DATA_SRC
	data/form.cpp
	data/form.h

	data/formcomponents.h

	data/functionindexes.h

	# Records
	data/records/classform.cpp
	data/records/classform.h

	data/records/factionform.cpp
	data/records/factionform.h

	data/records/gamesettingform.cpp
	data/records/gamesettingform.h

	data/records/globalvariableform.cpp
	data/records/globalvariableform.h

	data/records/rgbform.cpp
	data/records/rgbform.h

	data/records/tes4form.cpp
	data/records/tes4form.h

	data/records/texturesetform.cpp
	data/records/texturesetform.h

	# Subrecords
	data/subrecords/conditionitemcountfield.h

	data/subrecords/interfactionrelationsfield.h

	data/subrecords/objectboundsfield.h

	data/subrecords/conditionfield.h

	data/subrecords/functionparameter.h
)

set(IO_SRC
	io/formfactory.cpp
	io/formfactory.h

	io/parser.cpp
	io/parser.h

	io/reader.h
)

# QT models.
set(MODELS_SRC
	
	models/filemodel.cpp
	models/filemodel.h

	models/formmodel.cpp
	models/formmodel.h
)

# QT UI files and sources.
SET(UI_SRC

	ui/mainwindow.cpp
	ui/mainwindow.h
	ui/mainwindow.ui

	ui/datawindow.cpp
	ui/datawindow.h
	ui/datawindow.ui
	
	ui/renderwindow.cpp
	ui/renderwindow.h
	ui/renderwindow.ui
)

# QT widgets
set(WIDGETS_SRC
	
	widgets/scripteditor.cpp
	widgets/scripteditor.h

	widgets/clearablelineedit.cpp
	widgets/clearablelineedit.h

)

# QT views
set(VIEWS_SRC

	views/scripttreeview.cpp
	views/scripttreeview.h

	views/scriptcompiletreeview.cpp
	views/scriptcompiletreeview.h
)

# Pulls in all sources.
SET(SRC
	main.cpp
	
	version.cpp
	version.h

	${DATA_SRC}
	${IO_SRC}
	${MODELS_SRC}
	${UI_SRC}
	${WIDGETS_SRC}
	${VIEWS_SRC}
)

# QT .qrc resource files.
SET(QTRES
	../res/resources.qrc
)

# Set QT to automatically detect and run moc on our sources.
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_AUTORCC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Build executable target and link any libraries.
add_executable(${PROJECT_NAME} ${SRC} ${UI_SRC} ${QTRES})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Svg)

# Resolves QT offsets when debugging in visual studio.
if(MSVC)
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY LINK_FLAGS /NATVIS:${CMAKE_CURRENT_SOURCE_DIR}/qt5.natvis)
endif()

# Deploy required QT dlls for windows builds to the current binary directory.
if (WIN32)
	get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
	get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
	set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
					   COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_SOURCE_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
endif(WIN32)
