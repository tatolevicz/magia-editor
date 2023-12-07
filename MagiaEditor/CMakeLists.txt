project(mg_editor VERSION 0.1 LANGUAGES CXX)

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

add_library(${PROJECT_NAME} ${PROJECT_INCLUDES} ${PROJECT_SOURCES} )

add_subdirectory(external/scintilla)
add_subdirectory(external/lua)
add_subdirectory(external/sol2)
add_subdirectory(external/lexilla)

target_include_directories(${PROJECT_NAME} PUBLIC
    external/lexilla/include
    external/lexilla/access
    external/Lua/lua-5.4.6/include
    external/sol2/include
    include
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    scintilla-qt-edit
    lexzilla
    lua_static
    sol2
)
