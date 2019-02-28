project(openck)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.12.1/5.12.1/msvc2017_64")
find_package(Qt5Widgets REQUIRED)

set(
    SOURCES
    main.cpp
    editor.cpp
    view/viewmediator.cpp
    view/window/mainwindow.cpp
)
set(
    HEADERS
    editor.h
    ../files/filepath.h
    view/viewmediator.h
    view/window/mainwindow.h
)
set(
    FORMS
    ../ui/mainwindow.ui
)

add_executable(openck ${SOURCES} ${HEADERS} ${FORMS})
target_link_libraries(openck Qt5::Widgets)
