QT += core gui widgets sql network

greaterThan(QT_MAJOR_VERSION, 6): QT += widgets

CONFIG += c++17

INCLUDEPATH += "3rdParty/qmarkdowntextedit"
LIBS += -L3rdParty/qmarkdowntextedit -L$$OUT_PWD
win32: LIBS +=  -L$$OUT_PWD/release -L$$OUT_PWD/debug

SOURCES += \
    accountwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    settingswindow.cpp \
    syncwindow.cpp \
    commandPalette.cpp \
    keeperFunc/commandsFunc.cpp \
    settingsFunc/functional.cpp \
    keeperFunc/functional.cpp \
    keeperFunc/tasksFunc.cpp \
    keeperFunc/projectsFunc.cpp \
    keeperFunc/notesFunc.cpp \
    keeperFunc/getProjectInfo.cpp \
    accountFunc/functional.cpp \
    syncFunc/functional.cpp \
    sql_db/projectsDB.cpp \
    sql_db/tasksDB.cpp \
    gitFunc/cloneRepo.cpp \
    gitFunc/getUpdates.cpp \
    gitFunc/pushUpdates.cpp \
    keeperFunc/createMenu.cpp \
    keeperFunc/addConnects.cpp

HEADERS += \
    accountwindow.h \
    mainwindow.h \
    settingswindow.h \
    syncwindow.h \
    commandPalette.h \
    custom/clickableLabel/clickableLabel.h \
    custom/circleProgressbar/ProgressCircle.h \
    custom/circleChart/CircleChart.h \
    custom/ColorValueDisplay/ColorValueDisplay.h

RESOURCES += \
    ../resources/resources.qrc \
    stylesheet.qss \
    custom_stylesheet.qss \
    mac_dark_stylesheet.qss \
    custom_stylesheet_solarized.qss

include(3rdParty/qmarkdowntextedit/qmarkdowntextedit.pri)

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

TRANSLATIONS += \
    CodeKeeper_ru_RU.ts
