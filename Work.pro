#-------------------------------------------------
#
# Project created by QtCreator 2019-07-28T21:54:23
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Work
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        login.cpp \
    regist.cpp \
    release_task.cpp \
    user.cpp \
    dbms.cpp \
    platform.cpp \
    task.cpp \
    subtask.cpp \
    show_all_tasks.cpp \
    info.cpp \
    choose_person_in_charge.cpp \
    choose_translator.cpp \
    translate.cpp \
    view_result.cpp \
    view_final_result.cpp \
    send_feedback.cpp

HEADERS += \
        login.h \
    regist.h \
    release_task.h \
    user.h \
    dbms.h \
    platform.h \
    task.h \
    subtask.h \
    show_all_tasks.h \
    info.h \
    choose_person_in_charge.h \
    choose_translator.h \
    translate.h \
    view_result.h \
    view_final_result.h \
    send_feedback.h

FORMS += \
        login.ui \
    regist.ui \
    release_task.ui \
    platform.ui \
    show_all_tasks.ui \
    info.ui \
    choose_person_in_charge.ui \
    choose_translator.ui \
    translate.ui \
    view_result.ui \
    view_final_result.ui \
    send_feedback.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
