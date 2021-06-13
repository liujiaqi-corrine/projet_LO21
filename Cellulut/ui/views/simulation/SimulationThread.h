#ifndef SIMULATIONTHREAD_H
#define SIMULATIONTHREAD_H

#include "main.h"

class SimulationThread : public QThread
{
    Q_OBJECT
public:
    SimulationThread(QObject *parent = 0, bool b=false);
    void run();
    bool Stop;
    int sleepDuration;

    void setSleepDuration(int _sleepDuration){this->sleepDuration=_sleepDuration;}
signals:
    void nextStepCalculated();
};

#endif // SIMULATIONTHREAD_H
