#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "Cell.h"
#include "Model.h"
#include <QTableWidget>
#include <QtWidgets>

class Grid : public QTableWidget
{
    protected :
        //int length;
        //int width;
        Cell*** listCells;
        Model* model;
    public :
        //Grid(unsigned int _length = 0, unsigned int _width = 0);
        Grid(QWidget *parent) : QTableWidget(parent) {}
        Grid(int rows, int columns, QWidget *parent);
        ~Grid() = default;

        int getLength() const;
        int getWidth() const;
        Cell*** getlistCells() const;
        Model* getModel() const {return model;}

        void setModele(Model* _modele);

        void setlistCells(Cell*** _listCells);
        void setLength(unsigned int _length);
        void setWidth(unsigned int _width);

    public slots:
        void changeState(int row, int rows);
        //void deblockCells();
};

#endif // GRID_H_INCLUDED
