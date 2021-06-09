#include "MainMenuView.h"
#include "ui_MainMenuView.h"

MainMenuView::MainMenuView(QWidget *parent, UIEngine *_uiEngine) :
    QWidget(parent),
    ui(new Ui::MainMenuView),
    uiEngine(_uiEngine)
{
    ui->setupUi(this);
    qInfo() << "MainMenuView::MainMenuView - constructor";
}

MainMenuView::~MainMenuView()
{
    delete ui;
    qInfo() << "MainMenuView::~MainMenuView - destructor";
}


void MainMenuView::on_actionLoadTemplate_clicked()
{
    this->uiEngine->changeToLoadTemplateView();
}


void MainMenuView::on_actionCreateTemplate_clicked()
{
    this->uiEngine->changeToCreateTemplateView();
}

