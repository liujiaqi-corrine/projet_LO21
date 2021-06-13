#ifndef UIENGINE_H
#define UIENGINE_H

#include "main.h"
#include "views/MainWindow.h"
#include "views/menu/MainMenuView.h"
#include "views/simulation/SimulationView.h"
#include "views/forms/LoadModelFormView.h"
#include "views/forms/SurroundingFormView.h"
#include "views/library/LibraryView.h"

/*!
 *  \file UIEngine.h
 *  This file contains the UIEngine class
 */

class MainWindow;

/*!
 * \brief The UIEngine class
 */

class UIEngine : public QObject
{
private:
    QApplication *qapp;
    MainWindow *mainWindow;
public:
    UIEngine(QApplication *app);
    void start();
    void initMainWindow();

    MainWindow* getMainWindow() const {return this->mainWindow;}
public slots:
    void changeToMainMenuView();
    void changeToSimulationView();
    void changeToLoadModelFormView();
    void changeToCreateSurroundingFormView();
    void changeToLibraryView();
};

#endif // UIENGINE_H
