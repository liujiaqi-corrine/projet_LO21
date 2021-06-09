#ifndef C_MAINWINDOW_H
#define C_MAINWINDOW_H

#include "views/V_MainWindow.h"
#include "models/managers/databasemanager.h"
#include "models/managers/modelsmanager.h"
#include "models/managers/statesmanager.h"
#include "models/Cellulut.h"

class V_MainWindow;

/*!
 *  Classe faisant le lien entre modèles et vues
 */

class C_MainWindow
{
private:
    QApplication* qapp;
    V_MainWindow* view; /*!< View */
    Cellulut *app;
public:
    C_MainWindow(QApplication* app);
    ~C_MainWindow();

    V_MainWindow* getView() const { return view; }

    void init();

    void onActionLaunchSimulation();
};

#endif // C_MAINWINDOW_H
