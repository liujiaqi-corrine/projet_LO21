#include "SimulationView.h"
#include "ui_SimulationView.h"

SimulationView::SimulationView(QWidget *parent, UIEngine *_uiEngine) :
    QWidget(parent),
    ui(new Ui::SimulationView),
    uiEngine(_uiEngine),
    board(new SimulationBoard)
{
    ui->setupUi(this);
    //ui->slider_size->setMinimum(MIN_GRID_SIZE);
    //ui->slider_size->setMaximum(MAX_GRID_SIZE);
    //ui->input_size->setText(QString::number(MIN_GRID_SIZE));

    qInfo() << "SimulationView::SimulationView - constructor";
}

SimulationView::~SimulationView()
{
    delete ui;
    qInfo() << "SimulationView::~SimulationView - destructor";
}

void SimulationView::on_slider_size_valueChanged(int value)
{
    if(value%2!=0){
     //ui->input_size->setText(QString::number(value));
    }
}

