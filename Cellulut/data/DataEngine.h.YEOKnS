#ifndef DATAENGINE_H
#define DATAENGINE_H

#include "main.h"
#include "data/interfaces/InsideDataForUI.h"
#include "ui/interfaces/InsideUIForData.h"

class InsideDataForUI;
class InsideUIForData;

class DataEngine
{
private:
    InsideDataForUI* insideDataForUI;
    InsideUIForData* insideUIForData;
public:
    DataEngine();

    InsideDataForUI* getInsideDataForUI()const{return this->insideDataForUI;}
    void setInsideDataForUI(InsideDataForUI *_insideDataForUI){this->insideDataForUI=_insideDataForUI;}
    InsideUIForData* getInsideUIForData()const{return this->insideUIForData;}
    void setInsideUIForData(InsideUIForData *_insideUIForData){this->insideUIForData=_insideUIForData;}
};

#endif // DATAENGINE_H
