QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addprocess.cpp \
    choosealgo.cpp \
    disktrack.cpp \
    fifo.cpp \
    jobschedule.cpp \
    jobschedule_widget.cpp \
    lru.cpp \
    main.cpp \
    mainwindow.cpp \
    opt.cpp \
    osdesign.cpp \
    pagereplacement.cpp \
    pcb.cpp \
    processitem.cpp \
    processmanager.cpp \
    processschedule.cpp

HEADERS += \
    addprocess.h \
    choosealgo.h \
    disktrack.h \
    fifo.h \
    jobschedule.h \
    jobschedule_widget.h \
    lru.h \
    mainwindow.h \
    opt.h \
    osdesign.h \
    pagereplacement.h \
    pcb.h \
    pcb_calculate.h \
    processitem.h \
    processmanager.h \
    processschedule.h

FORMS += \
    addprocess.ui \
    choosealgo.ui \
    jobschedule_widget.ui \
    mainwindow.ui \
    osdesign.ui \
    pagereplacement.ui \
    processitem.ui \
    processmanager.ui \
    processschedule.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    A.qml \
    AForm.ui.qml

RESOURCES += \
    resource.qrc
