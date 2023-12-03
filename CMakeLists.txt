cmake_minimum_required(VERSION 3.5)

project(TestScintillaCmake VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        MyStyles.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TestScintillaCmake
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TestScintillaCmake APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TestScintillaCmake SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TestScintillaCmake
            ${PROJECT_SOURCES}
        )
    endif()
endif()


add_subdirectory(external/scintilla)
add_subdirectory(external/lua)
add_subdirectory(external/sol2)

target_include_directories(TestScintillaCmake PUBLIC
    external/lexilla/include
    external/lexilla/access
    external/Lua/lua-5.4.6/include
)

# Adicione o caminho da biblioteca estática
add_library(lexilla STATIC IMPORTED)
set_target_properties(lexilla PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/lexilla/bin/liblexilla.a")


target_link_libraries(TestScintillaCmake
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    scintilla-qt-edit
    lexilla
    lua_static
    sol2
)

set_target_properties(TestScintillaCmake PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS TestScintillaCmake
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TestScintillaCmake)
endif()
