cmake_minimum_required(VERSION 3.16)

project(ChessPairer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
    main.cpp
    ChessPairer.cpp
    ChessPairer.h
    MVC.h
    MVC.cpp
    PlayerListModel.h
    PlayerListView.h PlayerListView.cpp
    PlayerListController.h PlayerListController.cpp
    Database.h Database.cpp
    PlayerListModel.cpp
    SettingsView.h SettingsView.cpp
    SettingsModel.h SettingsModel.cpp
    SettingsController.h SettingsController.cpp
    TournamentListModel.h TournamentListModel.cpp
    Interfaces.h
    ListModel.h
    TournamentListView.h TournamentListView.cpp
    TournamentListController.h TournamentListController.cpp
    Logger.h Logger.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ChessPairer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ChessPairer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ChessPairer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ChessPairer
            ${PROJECT_SOURCES}
            TournamentPlayersView.h TournamentPlayersView.cpp
            TournamentPlayersModel.h TournamentPlayersModel.cpp
            TournamentPlayersController.h TournamentPlayersController.cpp
            TournamentPlayer.h TournamentPlayer.cpp
            Tournament.h Tournament.cpp
            Player.h Player.cpp

        )
    endif()
endif()

target_link_libraries(ChessPairer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.ChessPairer)
endif()
set_target_properties(ChessPairer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ChessPairer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ChessPairer)
endif()
