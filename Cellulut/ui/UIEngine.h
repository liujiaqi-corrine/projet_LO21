#ifndef UIENGINE_H
#define UIENGINE_H

#include "main.h"
#include <QApplication>
#include "data/interfaces/InsideDataForUI.h"
#include "ui/interfaces/InsideUIForData.h"
#include "views/MainWindow.h"
#include "views/MainMenuView.h"
#include "views/SimulationView.h"
#include "views/SimulationViewV2.h"
#include "views/templates/CreateTemplateView.h"
#include "views/templates/LoadTemplateView.h"

class InsideDataForUI;
class InsideUIForData;
class MainWindow;

class UIEngine
{
private:
    static const int width  = 800;
    static const int height = 600;

    InsideDataForUI* insideDataForUI;
    InsideUIForData* insideUIForData;

    QApplication *qapp;

    MainWindow *mainWindow;

public:
    UIEngine(QApplication *app);

    InsideDataForUI* getInsideDataForUI()const{return this->insideDataForUI;}
    void setInsideDataForUI(InsideDataForUI *_insideDataForUI){this->insideDataForUI=_insideDataForUI;}
    InsideUIForData* getInsideUIForData()const{return this->insideUIForData;}
    void setInsideUIForData(InsideUIForData *_insideUIForData){this->insideUIForData=_insideUIForData;}

    void start();
    void initMainWindow();
    void changeToMainMenuView();
    void changeToSimulationView();
    void changeToCreateTemplateView();
    void changeToLoadTemplateView();
};

#endif // UIENGINE_H
