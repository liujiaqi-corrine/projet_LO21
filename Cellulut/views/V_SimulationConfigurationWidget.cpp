#include "V_SimulationConfigurationWidget.h"
#include "ui_v_simulationconfigurationwidget.h"

V_SimulationConfigurationWidget::V_SimulationConfigurationWidget(QWidget *parent, Cellulut *app) :
    QWidget(parent),
    ui(new Ui::V_SimulationConfigurationWidget), app(app)
{
    ui->setupUi(this);

    this->comboBoxModel = new QStringListModel(this);

    // Build combo box with list of models from app
    QStringList listOfModelsView;
    for(unsigned int i = 0; i < this->app->getListOfModels()->size(); i++){
        listOfModelsView << this->app->getListOfModels()->at(i)->getTitleAsQString();
    }

    this->comboBoxModel->setStringList(listOfModelsView);
    this->ui->comboBox->setModel(this->comboBoxModel);
}

V_SimulationConfigurationWidget::~V_SimulationConfigurationWidget()
{
    delete ui;
}

void V_SimulationConfigurationWidget::on_comboBox_currentIndexChanged(int index)
{
    if(this->statesTableModel != nullptr){
        delete this->statesTableModel;
    }

    Model *model = this->app->getListOfModels()->at(index);
    vector<State*> *listOfStates = model->getListStates();
    unsigned int statesTableRowCount = listOfStates->size();

    this->statesTableModel = new QStandardItemModel(statesTableRowCount, 3, this);
    this->statesTableModel->setHorizontalHeaderLabels(this->statesTableHeaders.split(","));
    for(unsigned int row = 0; row < statesTableRowCount; row++){
        State *state = listOfStates->at(row);
        QModelIndex iIndex = this->statesTableModel->index(row, 0, QModelIndex());
        QModelIndex iColor = this->statesTableModel->index(row, 1, QModelIndex());
        QModelIndex iLabel = this->statesTableModel->index(row, 2, QModelIndex());
        this->statesTableModel->setData(iIndex, state->getIndex());
        this->statesTableModel->setData(iColor, state->getColorAsQString());
        this->statesTableModel->setData(iLabel, state->getLabelAsQString());
    }
    this->ui->statesTable->setModel(this->statesTableModel);
}

