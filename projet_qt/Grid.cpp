#include "main.h"
#include "Grid.h"


Grid::Grid(QWidget* parent):QWidget(parent){
    /*
    QPushButton *start = new QPushButton("start");
    QPushButton *pause = new QPushButton("pause");
    QPushButton *fin = new QPushButton("fin");
    */
    tableWidget=new QTableWidget(length,width);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setVisible(false);
    //tableWidget->resize(length, width);

    State* state;
    for(unsigned int i=0;i<length;i++){
        for(unsigned int j=0;j<width;j++){
            state=(listCells[i][j].getState());
            switch (state->getIndex()) {
                case 0 :
                    tableWidget->setItem(i,j,new QTableWidgetItem(""));
                    tableWidget->item(i,j)->setBackgroundColor("white");
                    tableWidget->item(i,j)->setTextColor("white");
                    break;
                case 1 :
                    tableWidget->setItem(i,j,new QTableWidgetItem(""));
                    tableWidget->item(i,j)->setBackgroundColor("black");
                    tableWidget->item(i,j)->setTextColor("black");
                    break;
                case 2 :
                    tableWidget->setItem(i,j,new QTableWidgetItem(""));
                    tableWidget->item(i,j)->setBackgroundColor("green");
                    tableWidget->item(i,j)->setTextColor("green");
                    break;
                case 3 :
                    tableWidget->setItem(i,j,new QTableWidgetItem(""));
                    tableWidget->item(i,j)->setBackgroundColor("red");
                    tableWidget->item(i,j)->setTextColor("red");
                    break;
                case 4 :
                    tableWidget->setItem(i,j,new QTableWidgetItem(""));
                    tableWidget->item(i,j)->setBackgroundColor("yellow");
                    tableWidget->item(i,j)->setTextColor("yellow");
                    break;
                case 5 :
                    tableWidget->setItem(i,j,new QTableWidgetItem(""));
                    tableWidget->item(i,j)->setBackgroundColor("orange");
                    tableWidget->item(i,j)->setTextColor("orange");
                    break;
                default:
                    break;
            }
        }
    }
    couche=new QVBoxLayout;
    couche->addWidget(tableWidget);
    /*
    couche->addWidget(start);
    couche->addWidget(pause);
    couche->addWidget(fin);
    */
    setLayout(couche);
}











unsigned int Grid::getLength() const{return length;}

unsigned int Grid::getWidth() const{return width;}

Cell** Grid::getlistCells() const{return listCells;}

void Grid::setlistCells(Cell** _listCells) {listCells = _listCells;}

void Grid::setLength(unsigned int _length) {length = _length;}

void Grid::setWidth(unsigned int _width) {width = _width;}
