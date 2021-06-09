#include "LoadTemplateView.h"
#include "ui_LoadTemplateView.h"

LoadTemplateView::LoadTemplateView(QWidget *parent, UIEngine *_uiEngine) :
    QWidget(parent),
    ui(new Ui::LoadTemplateView),
    uiEngine(_uiEngine)
{
    ui->setupUi(this);
    qInfo() << "LoadTemplateView::LoadTemplateView - constructor";
}

LoadTemplateView::~LoadTemplateView()
{
    delete ui;
    qInfo() << "LoadTemplateView::~LoadTemplateView - destructor";
}
