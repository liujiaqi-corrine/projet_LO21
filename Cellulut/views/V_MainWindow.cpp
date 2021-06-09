#include "main.h"
#include "V_MainWindow.h"
#include "ui_v_mainwindow.h"

V_MainWindow::V_MainWindow(QWidget *parent, C_MainWindow *c) : QMainWindow(parent), ui(new Ui::V_MainWindow)
{
    this->ui->setupUi(this);
    this->controller = c;
}

V_MainWindow::~V_MainWindow()
{
    delete this->ui;
}

// UI EVENTS BINDING

void V_MainWindow::on_actionLancer_une_simulation_triggered()
{
    qInfo() << "V_MainWindow::on_actionLancer_une_simulation_triggered()";
    this->controller->onActionLaunchSimulation();
}

