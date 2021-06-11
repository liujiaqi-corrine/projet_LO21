#ifndef SIMULATIONBUTTONSBAR_H
#define SIMULATIONBUTTONSBAR_H

#include "main.h"

class SimulationButtonsBar : public QWidget
{
    Q_OBJECT
public:
    SimulationButtonsBar(QWidget *parent = nullptr);
    ~SimulationButtonsBar();
signals:
    void start();
    void stepForward();
    void pause();
    void forward();
private:
    QHBoxLayout *hboxLayout;
    QPushButton *startButton;
    QPushButton *stepForwardButton;
    QPushButton *stopButton;
};

#endif // SIMULATIONBUTTONSBAR_H
