#ifndef GRID_H
#define GRID_H

#include "main.h"
#include "models/Cell.h"

#include <QTableWidget>

class Grid : public QTableWidget
{
    protected :
        Cell** listCells;
    public :
        Grid(int rows = 0,int columns = 0);
        ~Grid() = default;

        //int rowCount() const; // Héritage
        //int columnCount() const; // Héritage
        Cell** getlistCells() const;

        void setlistCells(Cell** _listCells);
        //void setRowCount(int rows); // Héritage
        //void setColumnCount(int columns); // Héritage
};


#endif // GRID_H
