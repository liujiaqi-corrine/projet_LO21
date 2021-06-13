#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, UIEngine *_uiEngine) :
    QMainWindow(parent),
    uiEngine(_uiEngine)
{
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    mainMenuAct = new QAction(tr("&Main menu"), this);
    mainMenuAct->setStatusTip(tr("Go to main menu"));

    loadModelAct = new QAction(tr("&Load model"), this);
    loadModelAct->setStatusTip(tr("Load a model for the simulation"));

    simulationAct = new QAction(tr("&Simulation"), this);
    simulationAct->setStatusTip(tr("Go to the simulation"));

    this->menuBar()->addAction(mainMenuAct);
    this->menuBar()->addAction(loadModelAct);
    this->menuBar()->addAction(simulationAct);

    connect(mainMenuAct, &QAction::triggered, this->uiEngine, &UIEngine::changeToMainMenuView);
    connect(loadModelAct, &QAction::triggered, this->uiEngine, &UIEngine::changeToLoadModelFormView);
    connect(simulationAct, &QAction::triggered, this->uiEngine, &UIEngine::changeToSimulationView);

    qInfo() << "MainWindow::MainWindow - constructor";
}

MainWindow::~MainWindow()
{
    delete mainMenuAct;
    delete loadModelAct;
    delete simulationAct;

    qInfo() << "MainWindow::~MainWindow - destructor";
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Escape)
    {
         QCoreApplication::quit();
    }
    else
        QWidget::keyPressEvent(event);
}
