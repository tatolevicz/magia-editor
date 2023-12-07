cmake_minimum_required(VERSION 3.5)

project(MagiaEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
        Widgets
        Svg
        )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
        Widgets
        Svg
        )

set(PROJECT_INCLUDES
        include/MgStyles.h
        include/MagiaEditor.h
        include/MagiaDebugger.h
        include/ConsoleOutput.h
        include/MagiaEditorWidget.h
        )

set(PROJECT_SOURCES
        src/MagiaEditor.cpp
        src/MagiaDebugger.cpp
        src/MagiaEditorWiget.cpp
        src/ConsoleOutput.cpp
        )

add_library(MagiaEditor ${PROJECT_INCLUDES} ${PROJECT_SOURCES} )

add_subdirectory(external/scintilla)
add_subdirectory(external/lua)
add_subdirectory(external/sol2)
add_subdirectory(external/lexilla)

target_include_directories(${PROJECT_NAME} PUBLIC
    external/lexilla/include
    external/lexilla/access
    external/Lua/lua-5.4.6/include
    include
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Svg
    scintilla-qt-edit
    lexzilla
    lua_static
    sol2
)
