cmake_minimum_required(VERSION 3.5)

project(TP_PlatLog VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


# Trouver les paquets Qt nécessaires
find_package(Qt6 COMPONENTS Core Sql Test REQUIRED)

set(PROJECT_SOURCES
        main.cpp



)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TP_PlatLog
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Application.h
        UserStorage.h
        LoginManager.h
        User.h
        UserRights.h
        Profile.h
        Application.cpp
        application.ui


        LoginManager.cpp
        Profil.cpp
        User.cpp
        UserRights.cpp
        UserStorage.cpp
        signinform.h signinform.cpp signinform.ui
        loginform.h loginform.cpp loginform.ui
        UserFile.json
        userdeserializer.h userdeserializer.cpp
        userserializer.h userserializer.cpp
        databasemanager.cpp databasemanager.h userdataview.cpp userdataview.h userdataview.ui




    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TP_PlatLog APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TP_PlatLog SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TP_PlatLog
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Utiliser les modules Qt trouvés

target_link_libraries(TP_PlatLog PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Test)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.TP_PlatLog)
endif()
set_target_properties(TP_PlatLog PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TP_PlatLog
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TP_PlatLog)
endif()
