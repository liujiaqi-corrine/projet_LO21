#include "afficher.h"
#include "Grid.h"
using namespace std;

//couleur possible (string) : 0 blanc, 1 noir, 2 vert, 3 rouge, 4 jaune, 5 orange

void Grid::afficher_1_etat (Grid g){
    QWidget fenetre;
    fenetre.setFixedSize(g.getWidth()*20,g.getLength()*20);

    QPushButton *start = new QPushButton("start");
    QPushButton *pause = new QPushButton("pause");
    QPushButton *fin = new QPushButton("fin");

    QTableWidget* tableWidget=new QTableWidget(g.getLength(),g.getWidth());
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setVisible(false);
    tableWidget->resize(g.getLength(), g.getWidth());

    State* state;
    for(unsigned int i=0;i<g.getLength();i++){
        for(unsigned int j=0;j<g.getWidth();j++){
            state=(g.getlistCells()[i][j].getState());
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
    QVBoxLayout* couche=new QVBoxLayout;
    couche->addWidget(tableWidget);
    QObject::connect(tableWidget,SIGNAL(doubleClicked(const QModelIndex&)),&app,SLOT(cellActivation(const QModelIndex)));
    fenetre.setLayout(couche);
}
/*
void cellActivation(QTableWidget* tableWidget,Grid g){
    for(unsigned int i=0;i<g.getLength();i++){
        for(unsigned int j=0;j<g.getWidth();j++){
            state=(g.getlistCells()[i][j].getState());
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

}
*/
