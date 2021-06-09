#ifndef GRID_H
#define GRID_H

#include "main.h"
#include "models/Cell.h"

class Grid // Singleton
{
    protected :
        static Grid* singleton; // Pointer to singleton
        Grid() = default; // Private constructor
        unsigned int rows;
        unsigned int columns;
        Cell** listCells;
    public :
        static Grid* getGrid() noexcept {return singleton;}
        ~Grid() = default;

        unsigned int getRows() const;
        unsigned int getColumns() const;
        Cell** getlistCells() const;

        void setRows(unsigned int _rows);
        void setColumns(unsigned int _columns);
        void setlistCells(Cell** _listCells);
};


#endif // GRID_H
