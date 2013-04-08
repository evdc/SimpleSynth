#-------------------------------------------------
#
# Project created by QtCreator 2013-03-05T21:38:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleSynth
TEMPLATE = app
DEPENDPATH += src
INCLUDEPATH += src

#Put these somewhere other than the main directory, for cleanliness sake
OBJECTS_DIR = tmp
MOC_DIR = tmp

HEADERS += src/AudioIO.h \
           src/Component.h \
           src/Filter.h \
           src/includes.h \
           src/LFO.h \
           src/Oscillator.h \
           src/Wavetable.h \
           src/portaudio.h \
           src/SynthesizerWindow.h \
	   src/VolumeMixer.h

SOURCES += src/AudioIO.cpp \
           src/Component.cpp \
           src/Filter.cpp \
           src/LFO.cpp \
           src/main.cpp \
           src/Oscillator.cpp \
	   src/SynthesizerWindow.cpp \
	   src/VolumeMixer.cpp \
           src/Wavetable.cpp


#LIBS += -L/usr/lib64/libportaudio.so.2 /usr/lib64/libportaudio.so.2 /usr/lib64/libportaudio.so.2.0.0 /usr/lib64/libportaudiocpp.so.0 /usr/lib64/libportaudiocpp.so.0.0.12
LIBS += -L./lib -lportaudio

FORMS    += src/SynthesizerWindow.ui

CONFIG += warn_off
