#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent, UIEngine *_uiEngine) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    uiEngine(_uiEngine)
{
    ui->setupUi(this);
    qInfo() << "MainWindow::MainWindow - constructor";
}

MainWindow::~MainWindow()
{
    delete ui;
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


void MainWindow::on_actionGoToSimulation_triggered()
{
    qInfo() << "MainWindow::on_actionGoToSimulation_triggered";
    this->uiEngine->changeToSimulationView();
}


void MainWindow::on_actionGoToMainMenu_triggered()
{
    qInfo() << "MainWindow::on_actionGoToMainMenu_triggered";
    this->uiEngine->changeToMainMenuView();
}


void MainWindow::on_actionGoToCreateTemplate_triggered()
{
    qInfo() << "MainWindow::on_actionGoToCreateTemplate_triggered";
    this->uiEngine->changeToCreateTemplateView();
}

void MainWindow::on_actionGoToLoadTemplate_triggered()
{
    qInfo() << "MainWindow::on_actionGoToLoadTemplate_triggered";
    this->uiEngine->changeToLoadTemplateView();
}
