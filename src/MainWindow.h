#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Qt includes
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <QKeyEvent>
#include <QMetaObject>

//Synthesis component includes
#include "Component.h"
#include "AudioIO.h"
#include "Oscillator.h"
#include "LFO.h"
#include "Filter.h"
#include "Wavetable.h"
#include "VolumeMixer.h"

class MainWindow : public QWidget
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();  

  private slots:
    void onFrequencyUpdate(int);

  protected:
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

  private:
    //Widgets
    QSlider * frequencySlider;
    QLabel * frequencyLabel;
   
    //Audio objects
    AudioIO* io;
    Oscillator* osc1;
    Oscillator* osc2;
    Oscillator* osc3;
    VolumeMixer* mixer;
    LFO* lfo1;
    LFO* lfo2;
    Filter* filter;
};

#endif
