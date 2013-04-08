#include <QApplication>
#include "synthesizer_window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    synthesizer_Window w;

    w.show();
    
    return a.exec();
}
