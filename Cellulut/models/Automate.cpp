#include "main.h"
#include "models/Automate.h"

Automate::Automate()
{
    model = new Model();
    grid = new Grid();
    historic = new vector<int**>;
}


Model* Automate::getModel() const{return model;}

Grid* Automate::getGrid() const{return grid;}


void Automate::setModel(Model* _model){this->model = _model;}

void Automate::setGrid(Grid* _grid){this->grid = _grid;}


/*void Automate::init_Grid()
{
    grid->setRowCount(width);
    grid->setColumnCount(length);
    grid->setlistCells(new Cell*[width]);
    for (int i=0; i < width; i++)
    {
        grid->getlistCells()[i] = new Cell[length];
    }
    for (int i=0; i < width; i++)
    {
        for (int j=0; j < length; j++)
        {
            grid->getlistCells()[i][j].setX(i);
            grid->getlistCells()[i][j].setY(j);
            //grid->getlistCells()[i][j].setState(getModel()->getListStates()->at(0));
        }
    }
    return;
}*/
