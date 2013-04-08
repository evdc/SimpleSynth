#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    //=================Widgets========================
    frequencySlider = new QSlider(Qt::Horizontal, this);
    frequencySlider->setGeometry(100, 50, 130, 30);
    frequencySlider->setMinimum(-12);
    frequencySlider->setMaximum(12);
    frequencyLabel = new QLabel(this);
    frequencyLabel->setGeometry(230, 50, 40, 30);
    
    //================[Audio objects]===================
    io = new AudioIO();

    //All of this is quite repetitive ... and could be made better with object-oriented programming

    //Construct wavetables
    Wavetable* sineTable = new Wavetable(32767);
    sineTable->addSines(1,1,1);
    Wavetable* sqrTable = new Wavetable(32767);
    sqrTable->addSines(20,2,1);
    Wavetable* sawTable = new Wavetable(32767);
    sawTable->addSines(51,1,1);

    //Oscillators
    osc1 = new Oscillator(440,1.0);
    osc1->setWaveformTable(0,sineTable);
    osc1->setWaveformTable(1,sqrTable);
    osc1->setWaveformTable(2,sawTable);
    osc1->setWaveform(0); //Sine

    osc2 = new Oscillator(440,1.0);
    osc2->setWaveformTable(0,sineTable);
    osc2->setWaveformTable(1,sqrTable);
    osc2->setWaveformTable(2,sawTable);
    osc2->setWaveform(1); //Square

    osc3 = new Oscillator(440,1.0);
    osc3->setWaveformTable(0,sineTable);
    osc3->setWaveformTable(1,sqrTable);
    osc3->setWaveformTable(2,sawTable);
    osc3->setWaveform(2); //Saw

    //LFO's (don't set them to modulate anything initially; let the user set this)
    lfo1 = new LFO(1,0.5,0);
    lfo2 = new LFO(2,0.5,0);

    //Mixer
    mixer = new VolumeMixer();
    mixer->addInput(osc1);
    mixer->addInput(osc2);
    mixer->addInput(osc3);

    //Filter
    filter = new Filter(880);
    filter->setInputSource(mixer,Component::INPUT_DATA);
	
	//Hidden filter: this one will not be exposed to UI, but just exists to attenuate some of the more annoying high-frequency components of the signal
    Filter *finalFilter = new Filter(16000);
    finalFilter->setInputSource(filter,Component::INPUT_DATA);

    //Final output
    io->setInputSource(finalFilter,Component::INPUT_DATA);
    //================[/Audio objects]===================
    

    //================Signals and Slots===================

    //Make the frequency label display the value of the frequency slider
    connect(frequencySlider, SIGNAL(valueChanged(int)), frequencyLabel, SLOT(setNum(int)) );

    //Make the frequency slider invoke the onFrequencyUpdate() event to change the frequency
    connect(frequencySlider, SIGNAL(valueChanged(int)), this, SLOT(onFrequencyUpdate(int)));
}

MainWindow::~MainWindow() { delete io; } //Exists to ensure AudioIO's destructor (& hence Pa_Terminate) gets called

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if(event->isAutoRepeat()) { event->ignore(); } 
    else 
    {
        //(re-)Start the playback
        io->play();  
    }     
}

void MainWindow::keyReleaseEvent(QKeyEvent * event)
{
    if(event->isAutoRepeat()) { event->ignore(); }
    else 
    {
        //Stop the playback
        io->stop();
    }
}

void MainWindow::onFrequencyUpdate(int value)
{
    osc1->setFrequencyDetune(value);
    osc2->setFrequencyDetune(value);
    osc3->setFrequencyDetune(value);
}

