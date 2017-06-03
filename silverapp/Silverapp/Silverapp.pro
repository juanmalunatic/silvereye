#-------------------------------------------------
#
# Project created by QtCreator 2016-09-10T18:17:27
#
#-------------------------------------------------


QT += core gui
QT += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

#DEFINES += QCUSTOMPLOT_USE_OPENGL

#QMAKE_CXXFLAGS_RELEASE += -O2

QMAKE_CXXFLAGS += /O2 #MSVC2013

TARGET = Silverapp
TEMPLATE = app


unix {
	# You may need to change this include directory
	INCLUDEPATH += /usr/include/OGRE
	CONFIG += link_pkgconfig
	PKGCONFIG += OGRE
}

win32 {
	LIBS *= user32.lib
	LIBS += -L$(OGRE_HOME)\\boost\\lib
	release:LIBS += -L$(OGRE_HOME)\\lib\\release
	debug:LIBS += -L$(OGRE_HOME)\\lib\\debug
	INCLUDEPATH += $(OGRE_HOME)\\include
	INCLUDEPATH += $(OGRE_HOME)\\include\\OIS
	INCLUDEPATH += $(OGRE_HOME)\\include\\OGRE
	INCLUDEPATH += $(OGRE_HOME)\\boost
	# If you are using Ogre 1.9 also include the following line:
	INCLUDEPATH += $(OGRE_HOME)\\include\\OGRE\\Overlay
}
debug {
	TARGET = $$join(TARGET,,,d)
	LIBS *= -lOgreMain_d -lOIS_d
	# If you are using Ogre 1.9 also include -lOgreOverlay_d, like this:
	LIBS *= -lOgreMain_d -lOIS_d -lOgreOverlay_d
}

release {
	LIBS *= -lOgreMain -lOIS
	# If you are using Ogre 1.9 also include -lOgreOverlay, like this:
	LIBS *= -lOgreMain -lOIS -lOgreOverlay
}


SOURCES += main.cpp\
        mainwindow.cpp \
    serialworker.cpp \
    imudata.cpp \
    qpanel.cpp \
    serialsettingspanel.cpp \
    systemstatuspanel.cpp \
    recordrawpanel.cpp \
    serialthread.cpp \
    modelcalibrationpanel.cpp \
    ogre3d_userlib/qtogrewindow.cpp \
    ogre3d_userlib/OgreGrid.cpp \
    humanmodelpanel.cpp \
	#ogre3d_userlib/OgreGpuCommandBufferFlush.cpp \
    qcustomplot.cpp \
	sagittalanglespanel.cpp \
    recordkinematicspanel.cpp

HEADERS  += mainwindow.h \
    serialworker.h \
    imudata.h \
    qpanel.h \
    serialsettingspanel.h \
    systemstatuspanel.h \
    recordrawpanel.h \
    serialthread.h \
    modelcalibrationpanel.h \
    ogre3d_userlib/sdkqtcameraman.h \
    ogre3d_userlib/qtogrewindow.h \
    ogre3d_userlib/OgreGrid.h \
    humanmodelpanel.h \
   #ogre3d_userlib/OgreGpuCommandBufferFlush.h \
    qcustomplot.h \
	sagittalanglespanel.h \
	quaternion2euler.h \
    recordkinematicspanel.h \
    anglewrap.h

FORMS    += mainwindow.ui \
    serialsettingspanel.ui \
    systemstatuspanel.ui \
    recordrawpanel.ui \
    modelcalibrationpanel.ui \
    sagittalanglespanel.ui \
    recordkinematicspanel.ui

RESOURCES += \
    img/silver_96_qt.qrc
