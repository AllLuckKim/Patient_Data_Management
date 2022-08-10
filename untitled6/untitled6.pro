QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialog.cpp \
    dialogsave.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    dialog.h \
    dialogsave.h \
    mainwindow.h

FORMS += \
    dialog.ui \
    dialogsave.ui \
    mainwindow.ui
QT       += core gui sql
# Default rules for deployment.
TARGET = Patient_Data_Management_System
RC_ICON = Vceph.ico
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
