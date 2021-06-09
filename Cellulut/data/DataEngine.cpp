#include "DataEngine.h"

DataEngine::DataEngine()
{
    this->insideDataForUI = new InsideDataForUI(this);
    qInfo() << "DataEngine::DataEngine - constructor";
}
