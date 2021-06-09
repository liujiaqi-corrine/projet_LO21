#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "Cell.h"
#include "Model.h"
#include "Automate.h"
#include <QTableWidget>
#include <QtWidgets>

class Automate; //forward declaration

class Grid : public QTableWidget
{
    protected :
        //int length;
        //int width;
        Cell*** listCells;
        Automate* parent;
    public :
        //Grid(unsigned int _length = 0, unsigned int _width = 0);
        Grid(QWidget *parent) : QTableWidget(parent) {}
        Grid(int rows, int columns, QWidget *parent);
        Grid(int size, QWidget *parent);
        ~Grid() = default;


        //virtual class Automate* parent() {return this->parent()->parent();}

        int getLength() const;
        int getWidth() const;
        Cell*** getlistCells() const;
        Automate* getParent() const {return parent;}
        //Model* getModel() const {return model;}

        void resetGrid();
        void updateGrid(Cell*** newCells);

        //void setModele(Model* _modele);

        void setlistCells(Cell*** _listCells);
        void setLength(unsigned int _length);
        void setWidth(unsigned int _width);

    public slots:
        void changeState(int row, int rows);
        void changeStateSurrounding(int row, int column);
        //void deblockCells();
};

#endif // GRID_H_INCLUDED
