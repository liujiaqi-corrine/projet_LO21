#include "v_startmenu.h"
#include "ui_v_startmenu.h"

v_startmenu::v_startmenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::v_startmenu)
{
    ui->setupUi(this);
}

v_startmenu::~v_startmenu()
{
    delete ui;
}
