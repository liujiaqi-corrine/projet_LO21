#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent, UIEngine *_uiEngine) :
    QMainWindow(parent),
    uiEngine(_uiEngine)
{
    this->resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    mainMenuAct = new QAction(tr("&Menu principal"), this);
    mainMenuAct->setStatusTip(tr("Aller au menu principal"));

    loadModelAct = new QAction(tr("&Charger un modèle"), this);
    loadModelAct->setStatusTip(tr("Charger un modèle pour la simulation"));

    simulationAct = new QAction(tr("&Simulation"), this);
    simulationAct->setStatusTip(tr("Aller à la vue Simulation"));

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
