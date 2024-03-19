cmake_minimum_required(VERSION 3.5)

project(risc-emu VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories("D:\\program\\ThirdParty\\rapidjson-1.1.0\\include")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(risc-emu
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        tomasuloview.h tomasuloview.cpp tomasuloview.ui
        codeeditor.h codeeditor.cpp codeeditor.ui
        Instruction.h
        btype_instruction.h btype_instruction.cpp
        opcode.json
        utils.h utils.cpp
        itype_instruction.h itype_instruction.cpp
        r4type_instruction.h r4type_instruction.cpp
        rtype_instruction.h rtype_instruction.cpp
        stype_instruction.h stype_instruction.cpp
        ujtype_instruction.h ujtype_instruction.cpp
        utype_instruction.h utype_instruction.cpp
        isa.h isa.cpp
        register.h register.cpp
        rf_config.json
        elf.h elf.cpp
        RV32F.json
        RV32I.json
        RV32M.json
        program.h program.cpp
        datamemory.h datamemory.cpp
        instructionbuffer.h instructionbuffer.cpp
        registerstatus.h registerstatus.cpp

        tomasulo.h tomasulo.cpp

        registerviewer.h registerviewer.cpp registerviewer.ui
        regstatusviewer.h regstatusviewer.cpp regstatusviewer.ui
        resstationsviewer.h resstationsviewer.cpp resstationsviewer.ui
        confwindow.h confwindow.cpp confwindow.ui
        datamemoryviewer.h datamemoryviewer.cpp datamemoryviewer.ui
        instbufferviewer.h instbufferviewer.cpp instbufferviewer.ui
        resstationsviewer.h resstationsviewer.cpp resstationsviewer.ui
        reservationstation.h reservationstation.cpp






    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET risc-emu APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(risc-emu SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(risc-emu
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(risc-emu PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.risc-emu)
endif()
set_target_properties(risc-emu PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS risc-emu
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(risc-emu)
endif()
