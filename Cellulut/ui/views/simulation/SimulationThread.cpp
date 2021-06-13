#include "SimulationThread.h"

#include "models/Automate.h"

SimulationThread::SimulationThread(QObject *parent, bool b):QThread(parent), Stop(b)
{
    this->sleepDuration = MIN_SIMULATION_TICK;
}

void SimulationThread::run()
{
    unsigned int nb_gen = 0;
    while(true){
        if(this->Stop) return;
        emit nextStepCalculated();
        this->msleep(this->sleepDuration);
        if(Automate::getAutomate()->check_stability())
        {
            qInfo() << "Stability after "<<nb_gen<<" generation(s)";
            qInfo() << "Execution stopped";
            this->Stop = true;
        }
        else
            nb_gen += 1;

    }
}
