QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activity.cpp \
    activityrepository.cpp \
    admin_page.cpp \
    adminloginpage.cpp \
    course.cpp \
    courserepository.cpp \
    dashboard.cpp \
    eventrepository.cpp \
    main.cpp \
    register.cpp \
    user.cpp \
    student.cpp \
    admin.cpp \
    event.cpp \
    email.cpp \
    utils.cpp \
    mainwindow.cpp

HEADERS += mainwindow.h \
    activity.h \
    activityrepository.h \
    admin_page.h \
    adminloginpage.h \
    course.h \
    courserepository.h \
    dashboard.h \
    eventrepository.h \
    register.h \
    user.h \
    student.h \
    admin.h \
    event.h \
    email.h \
    utils.h \

FORMS += mainwindow.ui \
    admin_page.ui \
    adminloginpage.ui \
    dashboard.ui \
    register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    courses-prerequisites.csv \
    courses.csv \
    events.csv

RESOURCES +=
