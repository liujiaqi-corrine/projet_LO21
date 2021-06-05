#include "v_createtemplatewidget.h"
#include "ui_v_createtemplatewidget.h"

V_CreateTemplateWidget::V_CreateTemplateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::V_CreateTemplateWidget)
{
    ui->setupUi(this);
}

V_CreateTemplateWidget::~V_CreateTemplateWidget()
{
    delete ui;
}
