cmake_minimum_required(VERSION 3.19)
project(deepfind_gui LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

set(ENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")

qt_add_executable(deepfind_gui
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    "${ENGINE}/Indexer.cpp"
    "${ENGINE}/QueryEngine.cpp"
    "${ENGINE}/ranker.cpp"
)

target_include_directories(deepfind_gui PRIVATE "${ENGINE}")

target_link_libraries(deepfind_gui
    PRIVATE
        Qt::Core
        Qt::Widgets
)