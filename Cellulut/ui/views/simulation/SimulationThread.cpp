#include "SimulationThread.h"

SimulationThread::SimulationThread(QObject *parent, bool b):QThread(parent), Stop(b)
{
    this->sleepDuration = MIN_SIMULATION_TICK;
}

void SimulationThread::run(){
    while(true){
        if(this->Stop) return;
        emit nextStepCalculated();
        this->msleep(this->sleepDuration);
    }
}
