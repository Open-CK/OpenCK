project(openck)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets 5.10 REQUIRED)

set(
    SOURCES
    main.cpp
    editor.cpp
    ../files/esm/esmreader.cpp
    ../files/esm/esmwriter.cpp
    ../files/esm/glob.cpp
    ../files/esm/gmst.cpp
    ../files/esm/lcrt.cpp
    ../files/esm/records.cpp
    ../files/esm/tes4.cpp
    ../files/esm/variant.cpp
    model/doc/document.cpp
    model/doc/documentmediator.cpp
	model/doc/messages.cpp
	model/tools/reports.cpp
    model/window/datatable.cpp
    model/window/masterslist.cpp
    model/world/basecollection.cpp
	model/world/ckid.cpp
    model/world/data.cpp
    model/world/metadata.cpp
    model/world/record.cpp
    view/messageboxhelper.cpp
    view/viewmediator.cpp
    view/window/datadialog.cpp
    view/window/mainwindow.cpp
)
set(
    HEADERS
    editor.hpp
    ../files/esm/common.h
    ../files/esm/esmfile.hpp
    ../files/esm/esmreader.hpp
    ../files/esm/esmwriter.hpp
    ../files/esm/glob.hpp
    ../files/esm/gmst.hpp
    ../files/esm/lcrt.hpp
    ../files/esm/records.hpp
    ../files/esm/tes4.hpp
    ../files/filepaths.hpp
    ../files/esm/variant.hpp
    model/doc/document.hpp
    model/doc/documentmediator.hpp
	model/doc/messages.hpp
	model/tools/reports.hpp
    model/window/datatable.hpp
    model/window/fileinfo.hpp
    model/window/masterslist.hpp
    model/world/basecollection.hpp
	model/world/ckid.hpp
    model/world/collection.hpp
    model/world/data.hpp
    model/world/idcollection.hpp
    model/world/metadata.hpp
    model/world/record.hpp
    view/messageboxhelper.hpp
    view/viewmediator.hpp
    view/window/datadialog.hpp
    view/window/mainwindow.hpp
)
set(
    FORMS
    ../ui/mainwindow.ui
    ../ui/datadialog.ui
)
set(RESOURCES_DIR ../resources)

# Copy settings file to build directory
# This will run post-build, so all changes between are transferred
add_custom_target(copy_ini ALL)
add_custom_command(
    TARGET copy_ini POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "../resources/editor.ini" ${CMAKE_BINARY_DIR}
)

# Disable embedded manifest on Windows platforms
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS /MANIFEST:NO)
endif(WIN32)

add_executable(
    openck
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${PROJECT_RESOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/../manifest/openck.rc
	${RESOURCES_DIR}/resources.qrc
)
target_link_libraries(openck Qt5::Widgets)
