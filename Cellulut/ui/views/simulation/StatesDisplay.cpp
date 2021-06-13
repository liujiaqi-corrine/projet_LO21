#include "StatesDisplay.h"

StatesDisplay::StatesDisplay(QWidget *parent) :QWidget(parent)
{
    vector<State*>* listOfStates = Automate::getAutomate()->getModel()->getListStates();

    this->mapOfColors = new map<int,QWidget*>();
    this->mapOfLabels = new map<int,QLabel*>();
    this->mapOfCounts = new map<int,QLCDNumber*>();
    this->layout = new QGridLayout;

    for(unsigned int i =0; i < listOfStates->size(); i++){
        State *state = listOfStates->at(i);

        // State Color
        QString stateColor(tr(state->getColor().c_str()));
        QWidget *colorWidget = new QWidget();
        colorWidget->setStyleSheet("QWidget{background-color:"+stateColor+"}");
        colorWidget->setFixedHeight(50);
        colorWidget->setFixedWidth(50);
        this->mapOfColors->insert({i,colorWidget});
        this->layout->addWidget(colorWidget,i,0);

        // State Label
        QString stateLabel(tr(state->getLabel().c_str()));
        QLabel *labelWidget = new QLabel(stateLabel);
        this->mapOfLabels->insert({i,labelWidget});
        this->layout->addWidget(labelWidget,i,1);

        // State count
        QLCDNumber *stateCount = new QLCDNumber(5);
        stateCount->setSegmentStyle(QLCDNumber::Filled);
        this->mapOfCounts->insert({i,stateCount});
        this->layout->addWidget(stateCount,i,2);
    }

    this->setLayout(this->layout);
}
StatesDisplay::~StatesDisplay()
{
    delete this->layout;
}

void StatesDisplay::refreshCounters(){
    std::map<int,int> mapNbCellsPerState = Grid::getGrid()->countNbCellsPerState();
    for(std::map<int, QLCDNumber*>::iterator itr = this->mapOfCounts->begin(); itr != this->mapOfCounts->end(); itr++)
    {
        int stateIndex = itr->first;
        int nbOfStates = mapNbCellsPerState.count(stateIndex) == 0 ? 0 : mapNbCellsPerState.at(stateIndex);
        itr->second->display(QString::number(nbOfStates));
    }
}
