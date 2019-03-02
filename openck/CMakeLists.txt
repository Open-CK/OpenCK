project(openck)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets REQUIRED)

set(
    SOURCES
    main.cpp
    editor.cpp
    ../files/esm/esmreader.cpp
    ../files/esm/tes4.cpp
    model/window/datatable.cpp
    view/messageboxhelper.cpp
    view/viewmediator.cpp
    view/window/datadialog.cpp
    view/window/mainwindow.cpp
)
set(
    HEADERS
    editor.h
    ../files/esm/esmfile.h
    ../files/esm/esmreader.h
    ../files/esm/records.h
    ../files/esm/tes4.h
    ../files/filepath.h
    model/window/datatable.h
    view/messageboxhelper.h
    view/viewmediator.h
    view/window/datadialog.h
    view/window/mainwindow.h
)
set(
    FORMS
    ../ui/mainwindow.ui
    ../ui/datadialog.ui
)

set(RESOURCES_DIR ../resources)
qt5_add_resources(PROJECT_RESOURCE ${RESOURCES_DIR}/resources.qrc)

# Copy settings file to build directory
# This will run post-build, so all changes between are transferred
add_custom_target(copy_ini ALL)
add_custom_command(
    TARGET copy_ini POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "../resources/editor.ini" ${CMAKE_BINARY_DIR}
)

add_executable(openck ${SOURCES} ${HEADERS} ${FORMS} ${PROJECT_RESOURCES})
target_link_libraries(openck Qt5::Widgets)
