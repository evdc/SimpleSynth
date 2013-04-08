#ifndef SYNTHESIZER_WINDOW_H
#define SYNTHESIZER_WINDOW_H


#include <QWidget>
#include <iostream>
#include <QKeyEvent>

#include "AudioIO.h"
#include "Component.h"
#include "Filter.h"
#include "includes.h"
#include "LFO.h"
#include "Oscillator.h"
#include "portaudio.h"
#include "VolumeMixer.h"
#include "Wavetable.h"

namespace Ui {
class synthesizer_Window;
}

class synthesizer_Window : public QWidget
{
    Q_OBJECT
    
public:
    explicit synthesizer_Window(QWidget *parent = 0);
    ~synthesizer_Window();

protected:
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

private slots:
    //Oscillator 1 Slots
    void osc1AmpUpdate(double);
    void osc1AmpLFOUpdate(int);
    void osc1AmpDial();
    void osc1AmpSpin();
    void osc1FreqUpdate(int);
    void osc1FreqLFOUpdate(int);
    void osc1Sine();
    void osc1Saw();
    void osc1Sqr();
    void osc1Noi();

    //Oscillator 2 Slots
    void osc2AmpUpdate(double);
    void osc2AmpLFOUpdate(int);
    void osc2AmpDial();
    void osc2AmpSpin();
    void osc2FreqUpdate(int);
    void osc2FreqLFOUpdate(int);
    void osc2Sine();
    void osc2Saw();
    void osc2Sqr();
    void osc2Noi();

    //Oscillator 3 Slots
    void osc3AmpUpdate(double);
    void osc3AmpLFOUpdate(int);
    void osc3AmpDial();
    void osc3AmpSpin();
    void osc3FreqUpdate(int);
    void osc3FreqLFOUpdate(int);
    void osc3Sine();
    void osc3Saw();
    void osc3Sqr();
    void osc3Noi();

    //LFO 1 Slots
    void lfo1AmpUpdate(double);
    void lfo1AmpSpin();
    void lfo1AmpDial();
    void lfo1FreqUpdate(double);
    void lfo1FreqDial();
    void lfo1FreqSpin();
    void lfo1AmpLFOUpdate(int);
    void lfo1FreqLFOUpdate(int);
    void lfo1Sine();
    void lfo1Saw();
    void lfo1Sqr();
    void lfo1Noi();

    //LFO 2 Slots
    void lfo2AmpUpdate(double);
    void lfo2AmpSpin();
    void lfo2AmpDial();
    void lfo2FreqUpdate(double);
    void lfo2FreqDial();
    void lfo2FreqSpin();
    void lfo2AmpLFOUpdate(int);
    void lfo2FreqLFOUpdate(int);
    void lfo2Sine();
    void lfo2Saw();
    void lfo2Sqr();
    void lfo2Noi();

    //Filter Slots
    void enableFilter(bool);
    void filterSetHigh();
    void filterSetLow();
    void filterCutOffUpdate(int);
    void cutOffFreqLFOUpdate(int);

    //Pan slots
    void panSliderUpdate();
    void panSpinUpdate();
    void panUpdate();

    //Volume Slots
    void volumeUpdate();
    void volumeSpin();
    void volumeSlider();
    
private:
    Ui::synthesizer_Window *ui;

    //Audio Objects
    AudioIO* io;
    Oscillator* osc1;
    Oscillator* osc2;
    Oscillator* osc3;
    LFO* lfo1;
    LFO* lfo2;
    Filter* filter;
    VolumeMixer* mixer;
};

#endif // SYNTHESIZER_WINDOW_H
