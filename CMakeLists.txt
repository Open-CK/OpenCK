project(openck)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets 5.10 REQUIRED)

set(
    SOURCES
    src/main.cpp
    src/editor.cpp
    libs/files/data/strings.cpp
    libs/files/esm/esmreader.cpp
    libs/files/esm/esmwriter.cpp
    libs/files/esm/glob.cpp
    libs/files/esm/gmst.cpp
    libs/files/esm/lcrt.cpp
    libs/files/esm/records.cpp
    libs/files/esm/tes4.cpp
    libs/files/esm/variant.cpp
    src/model/doc/document.cpp
    src/model/doc/documentmediator.cpp
    src/model/doc/loader.cpp
    src/model/doc/messages.cpp
    src/model/tools/reports.cpp
    src/model/window/datatable.cpp
    src/model/window/masterslist.cpp
    src/model/world/basecollection.cpp
    src/model/world/basecolumn.cpp
    src/model/world/baseidtable.cpp
    src/model/world/ckid.cpp
    src/model/world/columns.cpp
    src/model/world/data.cpp
    src/model/world/idtable.cpp
    src/model/world/metadata.cpp
    src/model/world/record.cpp
    src/view/doc/loader.cpp
    src/view/messageboxhelper.cpp
    src/view/viewmediator.cpp
    src/view/window/datadialog.cpp
    src/view/window/gmstdialog.cpp
    src/view/window/mainwindow.cpp
    src/view/world/enumdelegate.cpp
    src/view/world/genericdelegate.cpp
    src/view/world/variantdelegate.cpp
)
set(
    HEADERS
    src/editor.hpp
    libs/files/data/strings.hpp
    libs/files/esm/common.hpp
    libs/files/esm/esmfile.hpp
    libs/files/esm/esmreader.hpp
    libs/files/esm/esmwriter.hpp
    libs/files/esm/glob.hpp
    libs/files/esm/gmst.hpp
    libs/files/esm/lcrt.hpp
    libs/files/esm/records.hpp
    libs/files/esm/tes4.hpp
    libs/files/filepaths.hpp
    libs/files/esm/variant.hpp
    src/model/doc/document.hpp
    src/model/doc/documentmediator.hpp
    src/model/doc/documentstate.hpp
    src/model/doc/loader.hpp
    src/model/doc/messages.hpp
    src/model/tools/reports.hpp
    src/model/window/datatable.hpp
    src/model/window/fileinfo.hpp
    src/model/window/masterslist.hpp
    src/model/world/basecollection.hpp
    src/model/world/basecolumn.hpp
    src/model/world/baseidtable.hpp
    src/model/world/ckid.hpp
    src/model/world/collection.hpp
    src/model/world/columnimp.hpp
    src/model/world/columns.hpp
    src/model/world/data.hpp
    src/model/world/idcollection.hpp
    src/model/world/idtable.hpp
    src/model/world/metadata.hpp
    src/model/world/record.hpp
    src/view/doc/loader.hpp
    src/view/messageboxhelper.hpp
    src/view/viewmediator.hpp
    src/view/window/datadialog.hpp
    src/view/window/gmstdialog.hpp
    src/view/window/mainwindow.hpp
    src/view/world/delegatefactory.hpp
    src/view/world/enumdelegate.hpp
    src/view/world/genericdelegate.hpp
    src/view/world/variantdelegate.hpp
)
set(
    FORMS
    ui/datadialog.ui
    ui/gmstdialog.ui
    ui/loaderdialog.ui
    ui/mainwindow.ui
)
set(RESOURCES_DIR ../data)

# Copy settings file to build directory
# This will run post-build, so all changes between are transferred
add_custom_target(copy_ini ALL)
add_custom_command(
    TARGET copy_ini POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "../data/editor.ini" ${CMAKE_BINARY_DIR}
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
    ${CMAKE_CURRENT_SOURCE_DIR}/data/manifest/openck.rc
    ${RESOURCES_DIR}/resources.qrc
)
target_link_libraries(openck Qt5::Widgets)
