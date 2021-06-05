#include "main.h"
#include "C_MainWindow.h"
#include "../views/V_MainWindow.h"
#include "../views/V_SimulationConfigurationWidget.h"
#include "ui_v_mainwindow.h"

C_MainWindow::C_MainWindow(QApplication *q) {
    this->qapp = q;
    this->app = new Cellulut();
    this->view = new V_MainWindow(0, this); 

    qInfo() <<  "C_MainWindow::C_MainWindow - constructor OK";
}

C_MainWindow::~C_MainWindow()
{
    delete this->view;
    delete this->app;
}

void C_MainWindow::init(){
    this->app->init();
}

void C_MainWindow::onActionLaunchSimulation(){
 V_SimulationConfigurationWidget *simulationConfigurationWidget = new V_SimulationConfigurationWidget(this->view, this->app);
 this->view->setCentralWidget(simulationConfigurationWidget);
}
