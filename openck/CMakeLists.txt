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
)
set(
    HEADERS
    editor.h
)
set(
    FORMS
    ../ui/editor.ui
)

add_executable(openck ${SOURCES} ${HEADERS} ${FORMS})
target_link_libraries(openck Qt5::Widgets)
