#include "CreateTemplateView.h"
#include "ui_CreateTemplateView.h"

CreateTemplateView::CreateTemplateView(QWidget *parent, UIEngine *_uiEngine) :
    QWidget(parent),
    ui(new Ui::CreateTemplateView),
    uiEngine(_uiEngine)
{
    ui->setupUi(this);
    qInfo() << "CreateTemplateView::CreateTemplateView - constructor";
}

CreateTemplateView::~CreateTemplateView()
{
    delete ui;
    qInfo() << "CreateTemplateView::~CreateTemplateView - destructor";
}
