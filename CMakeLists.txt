cmake_minimum_required(VERSION 3.19)

project(Apery VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()
set(CMAKE_AUTORCC ON)

qt_add_executable(Apery WIN32 MACOSX_BUNDLE
    main.cpp
    tiling/cell_tiles.cpp
    tiling/lists.cpp
    tiling/universe.cpp
    tiling/deflate.cpp
    tiling/cellfield.cpp
    ui/aperyvport.cpp
    ui/rhombdrawer.cpp
    ui/celldrawer.cpp
    ui/aperywindow.cpp
    ui/dimensions.cpp
    ui/rhombloader.cpp
    rsrc/masks.qrc
    tiling/cells.cpp
    tiling/cells.h
)

target_include_directories(Apery PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Apery PRIVATE Qt6::Widgets)
