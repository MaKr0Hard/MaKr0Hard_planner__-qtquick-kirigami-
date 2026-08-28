cmake_minimum_required(VERSION 3.16)

project(MaKr0Hard_Planner_4_4 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(ECM 6.0.0 REQUIRED NO_MODULE)
find_package(nlohmann_json 3.12.0 REQUIRED)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMFindQmlModule)
include(ECMQmlModule)
find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.10)

# Content of downloaded design from Figma to Qt or similar
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/importedcontent/CMakeLists.txt")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/importedcontent)
endif()





find_package(KF6 REQUIRED COMPONENTS
    Kirigami
    I18n
    CoreAddons

    IconThemes
)


find_package(Qt6 REQUIRED COMPONENTS
    Core
    Quick
    Test
    Gui
    QuickControls2
    Widgets
)


qt_add_executable(appMaKr0Hard_Planner_4
    main.cpp
)

qt_add_qml_module(appMaKr0Hard_Planner_4
    URI MaKr0Hard_Planner_4
    QML_FILES
        Main.qml
        SOURCES func_class.h func_class.cpp
        RESOURCES LICENSE
        RESOURCES README.md
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appMaKr0Hard_Planner_4 PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMaKr0Hard_Planner_4
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE

)

target_link_libraries(appMaKr0Hard_Planner_4
    PRIVATE Qt6::Quick
    Qt6::Qml
    Qt6::Gui
    Qt6::QuickControls2
    KF6::I18n
    KF6::CoreAddons
    KF6::IconThemes
    Qt6::Widgets
)
target_link_libraries(appMaKr0Hard_Planner_4 PRIVATE nlohmann_json::nlohmann_json)


install(TARGETS appMaKr0Hard_Planner_4
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
