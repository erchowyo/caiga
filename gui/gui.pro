include(../common.pri)

QT       += gui multimedia multimediawidgets printsupport

TEMPLATE  = app

TARGET    = caiga

FORMS    += cameradialog.ui \
            mainwindow.ui \
            optionsdialog.ui \
            parametersdialog.ui \
            watershedmarkerdialog.ui
         
SOURCES  += main.cpp \
            cameradialog.cpp \
            mainwindow.cpp \
            optionsdialog.cpp \
            qimageviewer.cpp \
            qimagedrawer.cpp \
            qimageinteractivedrawer.cpp \
            parametersdialog.cpp \
            livepixelviewer.cpp \
            watershedmarkerdialog.cpp \
            analysisitemdelegate.cpp \
            reporter.cpp \
            3rdparty/qcustomplot.cpp \
            3rdparty/qcpdocumentobject.cpp \
            zoomer.cpp
           
HEADERS  += cameradialog.h \
            mainwindow.h \
            optionsdialog.h \
            qimageviewer.h \
            qimagedrawer.h \
            qimageinteractivedrawer.h \
            parametersdialog.h \
            livepixelviewer.h \
            watershedmarkerdialog.h \
            analysisitemdelegate.h \
            reporter.h \
            3rdparty/qcustomplot.h \
            3rdparty/qcpdocumentobject.h \
            zoomer.h

RESOURCES+= caiga.qrc
windows: {
    RESOURCES   += icons.qrc
    RC_FILE      = winicon.rc
    OTHER_FILES += winicon.rc
}

windows:CONFIG(release, debug|release): LIBS += -L../core/release -lcore
else:windows:CONFIG(debug, debug|release): LIBS += -L../core/debug -lcore
else:unix: LIBS += -L../core -lcore

INCLUDEPATH += ../core
DEPENDPATH  += ../core
