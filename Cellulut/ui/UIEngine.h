#ifndef UIENGINE_H
#define UIENGINE_H

#include "main.h"
#include "views/MainWindow.h"
#include "views/menu/MainMenuView.h"
#include "views/simulation/SimulationView.h"
#include "views/forms/LoadModelFormView.h"

class InsideDataForUI;
class InsideUIForData;
class MainWindow;

class UIEngine : public QObject
{
private:
    QApplication *qapp;
    MainWindow *mainWindow;
public:
    UIEngine(QApplication *app);
    void start();
    void initMainWindow();
public slots:
    void changeToMainMenuView();
    void changeToSimulationView();
    void changeToLoadModelFormView();
};

#endif // UIENGINE_H
