#include "UIEngine.h"

UIEngine::UIEngine(QApplication* _app) : qapp(_app)
{
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

void UIEngine::changeToSimulationView(){
    SimulationView *simulationView = new SimulationView(0, this);
    this->mainWindow->setCentralWidget(simulationView);
}

void UIEngine::changeToMainMenuView(){
    MainMenuView *mainMenuView = new MainMenuView(0, this);
    this->mainWindow->setCentralWidget(mainMenuView);
}

void UIEngine::changeToLoadModelFormView(){
    LoadModelFormView *loadModelFormView = new LoadModelFormView(0, this);
    this->mainWindow->setCentralWidget(loadModelFormView);
}

void UIEngine::changeToCreateSurroundingFormView(){
    SurroundingFormView *surroundingFormView = new SurroundingFormView(0, this);
    this->mainWindow->setCentralWidget(surroundingFormView);
}

void UIEngine::changeToLibraryView(){
    LibraryView *libraryView = new LibraryView(0, this);
    this->mainWindow->setCentralWidget(libraryView);
}
