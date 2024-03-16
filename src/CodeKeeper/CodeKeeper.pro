QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

LIBS += -lQMarkdownTextedit -L$$OUT_PWD

win32: LIBS +=  -L$$OUT_PWD/release -L$$OUT_PWD/debug

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingswindow.cpp

HEADERS += \
    mainwindow.h \
    settingswindow.h

RESOURCES += \
    ../resources/resources.qrc \
    ../stylesheet/stylesheet.qss \
    ../stylesheet/stylesheet_setting_window.qss

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
