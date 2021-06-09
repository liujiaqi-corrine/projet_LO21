#include "UIEngine.h"

UIEngine::UIEngine(QApplication* _app) : qapp(_app)
{
    this->insideUIForData = new InsideUIForData(this);
    this->mainWindow = new MainWindow(0,this);

    qInfo() << "UIEngine::UIEngine - constructor";
}

void UIEngine::start(){
    this->initMainWindow();
    this->changeToMainMenuView();
    this->mainWindow->show();
}

void UIEngine::initMainWindow(){
    this->mainWindow->setWindowTitle("Cellulut");
}

void UIEngine::changeToMainMenuView(){
    MainMenuView *mainMenuView = new MainMenuView(0,this);
    this->mainWindow->setCentralWidget(mainMenuView);
}

void UIEngine::changeToSimulationView(){
    SimulationViewV2 *simulationView = new SimulationViewV2(0);
    this->mainWindow->setCentralWidget(simulationView);
}

void UIEngine::changeToCreateTemplateView(){
    CreateTemplateView *createTemplateView = new CreateTemplateView(0,this);
    this->mainWindow->setCentralWidget(createTemplateView);
}

void UIEngine::changeToLoadTemplateView(){
    LoadTemplateView *loadTemplateView = new LoadTemplateView(0,this);
    this->mainWindow->setCentralWidget(loadTemplateView);
}
