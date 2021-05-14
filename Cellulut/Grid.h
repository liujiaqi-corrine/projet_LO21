#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "Cell.h"
#include <QtWidgets>
#include <QTableWidget>

class Grid : public QTableWidget
{
    protected :
        unsigned int length;
        unsigned int width;
        Cell** listCells;
    public :
        Grid(unsigned int _length = 0, unsigned int _width = 0);
        Grid(QWidget *parent) : QTableWidget(parent) {}
        Grid(int rows, int columns, QWidget *parent);
        ~Grid() = default;

        unsigned int getLength() const;
        unsigned int getWidth() const;
        Cell** getlistCells() const;

        void setlistCells(Cell** _listCells);
        void setLength(unsigned int _length);
        void setWidth(unsigned int _width);

    signals:
        void clicked();

    public slots:
        void faire(int columns, int rows);
};

#endif // GRID_H_INCLUDED
