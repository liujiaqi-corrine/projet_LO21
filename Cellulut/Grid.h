#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "Cell.h"
#include "Model.h"
#include <QTableWidget>
#include <QtWidgets>

class Grid : public QTableWidget
{
    protected :
        unsigned int length;
        unsigned int width;
        Cell** listCells;
        Model* model;
    public :
        Grid(unsigned int _length = 0, unsigned int _width = 0);
        Grid(QWidget *parent) : QTableWidget(parent) {}
        Grid(int rows, int columns, QWidget *parent);
        ~Grid() = default;

        unsigned int getLength() const;
        unsigned int getWidth() const;
        Cell** getlistCells() const;

        void setModele(Model* _modele);

        void setlistCells(Cell** _listCells);
        void setLength(unsigned int _length);
        void setWidth(unsigned int _width);

    public slots:
        void changeState(int columns, int rows);
        //void deblockCells();
};

#endif // GRID_H_INCLUDED
