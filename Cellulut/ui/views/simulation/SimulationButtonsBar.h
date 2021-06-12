#ifndef SIMULATIONBUTTONSBAR_H
#define SIMULATIONBUTTONSBAR_H

#include "main.h"

class SimulationButtonsBar : public QWidget
{
    Q_OBJECT
    public:
        SimulationButtonsBar(QWidget *parent = nullptr);
        ~SimulationButtonsBar();

        void setStartButtonDisabled(bool _disabled){this->startButton->setDisabled(_disabled);}
        void setStopButtonDisabled(bool _disabled){this->stopButton->setDisabled(_disabled);}
        void setStepForwardButtonDisabled(bool _disabled){this->stepForwardButton->setDisabled(_disabled);}

    signals:
        void start();
        void stepForward();
        void stop();

    private:
        QHBoxLayout *hboxLayout;
        QPushButton *startButton;
        QPushButton *stepForwardButton;
        QPushButton *stopButton;
};

#endif // SIMULATIONBUTTONSBAR_H
