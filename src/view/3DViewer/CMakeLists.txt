cmake_minimum_required(VERSION 3.5)

project(3DViewer VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)


set(PROJECT_SOURCES
        main.cc
        mainwindow.cc
        mainwindow.h
        mainwindow.ui
        viewer.h
        viewer.cc
        ../../model/model.h
        ../../model/model.cc        
        ../../model/affine_rotate_adapter.cc
        ../../model/affine_rotate_adapter.h
        ../../model/affine_transformations_strategy.cc
        ../../model/affine_transformations_strategy.h
        ../../model/facade.cc
        ../../model/facade.h
        ../../model/save_settings.cc
        ../../model/save_settings.h
        ../../controller/controller.cc
        ../../controller/controller.h
        # data_saver.cpp
        # data_saver.h
        gif.h

	../3rdParty/giflib/gif_hash.h
        ../3rdParty/giflib/gif_lib_private.h
        ../3rdParty/giflib/gif_lib.h

        ../3rdParty/giflib/dgif_lib.c
        ../3rdParty/giflib/egif_lib.c
        ../3rdParty/giflib/gif_err.c
        ../3rdParty/giflib/gif_font.c
        ../3rdParty/giflib/gif_hash.c
        ../3rdParty/giflib/gifalloc.c
        ../3rdParty/giflib/quantize.c

        ../gifimage/qgifglobal.h
        ../gifimage/qgifimage_p.h
        ../gifimage/qgifimage.h
        ../gifimage/qgifimage.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3DViewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(3DViewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(3DViewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
# target_link_libraries(3dviewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# target_link_libraries(3dviewer PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
# target_link_libraries(3dviewer PRIVATE Qt${QT_VERSION_MAJOR}::Gui)


set_target_properties(3DViewer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer)
endif()
