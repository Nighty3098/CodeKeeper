cmake_minimum_required(VERSION 3.16)
project(CodeKeeper VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set up AUTOMOC and some sensible defaults for runtime execution
# When using Qt 6.3, you can replace the code block below with
# qt_standard_project_setup()
set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Network Sql Widgets)

qt_add_executable(CodeKeeper WIN32 MACOSX_BUNDLE
    3rdParty/qmarkdowntextedit/linenumberarea.h
    3rdParty/qmarkdowntextedit/markdownhighlighter.cpp 3rdParty/qmarkdowntextedit/markdownhighlighter.h
    3rdParty/qmarkdowntextedit/qmarkdowntextedit.cpp 3rdParty/qmarkdowntextedit/qmarkdowntextedit.h
    3rdParty/qmarkdowntextedit/qownlanguagedata.cpp 3rdParty/qmarkdowntextedit/qownlanguagedata.h
    3rdParty/qmarkdowntextedit/qplaintexteditsearchwidget.cpp 3rdParty/qmarkdowntextedit/qplaintexteditsearchwidget.h 3rdParty/qmarkdowntextedit/qplaintexteditsearchwidget.ui
    accountFunc/functional.cpp
    accountwindow.cpp accountwindow.h
    custom/ColorValueDisplay/ColorValueDisplay.h
    custom/circleChart/CircleChart.h
    custom/circleProgressbar/ProgressCircle.h
    gitFunc/cloneRepo.cpp
    gitFunc/getUpdates.cpp
    gitFunc/pushUpdates.cpp
    keeperFunc/addConnects.cpp
    keeperFunc/createMenu.cpp
    keeperFunc/functional.cpp
    keeperFunc/getProjectInfo.cpp
    keeperFunc/notesFunc.cpp
    keeperFunc/projectsFunc.cpp
    keeperFunc/tasksFunc.cpp
    main.cpp
    mainwindow.cpp mainwindow.h
    settingsFunc/functional.cpp
    settingswindow.cpp settingswindow.h
    sql_db/projectsDB.cpp
    sql_db/tasksDB.cpp
    syncFunc/functional.cpp
    syncwindow.cpp syncwindow.h
)
target_include_directories(CodeKeeper PRIVATE
    3rdParty/qmarkdowntextedit 3rdParty/qmarkdowntextedit 3rdParty/qmarkdowntextedit 3rdParty/qmarkdowntextedit
)

target_link_libraries(CodeKeeper PRIVATE
    # Remove: L${CMAKE_CURRENT_BINARY_DIR}
    # Remove: L3rdParty/qmarkdowntextedit
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Sql
    Qt::Widgets
)


# Resources:
set(resources_resource_files
    "../resources/MapleMono-ExtraBold.ttf"
    "../resources/Monoton-Regular.ttf"
    "../resources/about.png"
    "../resources/auto_sync_off.png"
    "../resources/auto_sync_on.png"
    "../resources/bold.png"
    "../resources/check-mark.png"
    "../resources/checkbox.png"
    "../resources/connected.png"
    "../resources/copy.png"
    "../resources/delete.png"
    "../resources/disconnected.png"
    "../resources/document.png"
    "../resources/down-arrow.png"
    "../resources/download.png"
    "../resources/edit.png"
    "../resources/expand.png"
    "../resources/export.png"
    "../resources/folder-open.png"
    "../resources/folder.png"
    "../resources/german.png"
    "../resources/git.png"
    "../resources/green.png"
    "../resources/greenHovered.png"
    "../resources/greenInHovered.png"
    "../resources/greenInPressed.png"
    "../resources/greenPressed.png"
    "../resources/h1.png"
    "../resources/h2.png"
    "../resources/h3.png"
    "../resources/home_dir.png"
    "../resources/icon.png"
    "../resources/italic.png"
    "../resources/japan.png"
    "../resources/link.png"
    "../resources/list.png"
    "../resources/logo.png"
    "../resources/main.png"
    "../resources/markdown.png"
    "../resources/new.png"
    "../resources/new_folder.png"
    "../resources/note.png"
    "../resources/numList.png"
    "../resources/open.png"
    "../resources/palette.png"
    "../resources/paste.png"
    "../resources/project.png"
    "../resources/quit.png"
    "../resources/quote.png"
    "../resources/read.png"
    "../resources/red.png"
    "../resources/redHovered.png"
    "../resources/redPressed.png"
    "../resources/refresh.png"
    "../resources/rename.png"
    "../resources/resize.png"
    "../resources/retry.png"
    "../resources/russian.png"
    "../resources/save.png"
    "../resources/search.png"
    "../resources/settings.png"
    "../resources/sorting.png"
    "../resources/spanish.png"
    "../resources/storage.png"
    "../resources/strikethrough.png"
    "../resources/sync.png"
    "../resources/table.png"
    "../resources/task.png"
    "../resources/tea.svg"
    "../resources/trash.png"
    "../resources/unfocusedButton.png"
    "../resources/up-arrow.png"
    "../resources/usa.png"
    "../resources/user.png"
    "../resources/view.png"
    "../resources/yellow.png"
    "../resources/yellowHovered.png"
    "../resources/yellowPressed.png"
)

qt_add_resources(CodeKeeper "resources"
    PREFIX
        "/"
    BASE
        "../resources"
    FILES
        ${resources_resource_files}
)
set(media_resource_files
    "3rdParty/qmarkdowntextedit/media/edit-find-replace.svg"
    "3rdParty/qmarkdowntextedit/media/format-text-superscript.svg"
    "3rdParty/qmarkdowntextedit/media/go-bottom.svg"
    "3rdParty/qmarkdowntextedit/media/go-top.svg"
    "3rdParty/qmarkdowntextedit/media/window-close.svg"
)

qt_add_resources(CodeKeeper "media"
    PREFIX
        "/"
    BASE
        "3rdParty/qmarkdowntextedit"
    FILES
        ${media_resource_files}
)
set(qmake_immediate_resource_files
    "../stylesheet/custom_stylesheet.qss"
    "../stylesheet/custom_stylesheet_light.qss"
    "../stylesheet/stylesheet.qss"
)

qt_add_resources(CodeKeeper "qmake_immediate"
    PREFIX
        "/"
    FILES
        ${qmake_immediate_resource_files}
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(CodeKeeper PRIVATE
        Qt::Widgets
    )
endif()

if(WIN32)
    target_link_libraries(CodeKeeper PRIVATE
        # Remove: L${CMAKE_CURRENT_BINARY_DIR}/debug
        # Remove: L${CMAKE_CURRENT_BINARY_DIR}/release
    )
endif()

install(TARGETS CodeKeeper
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Consider using qt_generate_deploy_app_script() for app deployment if
# the project can use Qt 6.3. In that case rerun qmake2cmake with
# --min-qt-version=6.3.
