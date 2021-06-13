#ifndef GRID_H
#define GRID_H

#include "main.h"
#include "models/Cell.h"

/*!
 *  \file Grid.h
 *  This file contains the Grid class
 */


/*!
 * \brief The Grid class
 */

class Grid // Singleton
{
    protected :
        static Grid* singleton; // Pointer to singleton
        Grid(); // Private constructor
        unsigned int size;
        map<string, Cell*> *mapCells;
    public :
        static Grid* getGrid() noexcept {return singleton;}
        ~Grid() = default;

        unsigned int getSize() const;
        map<string, Cell*>* getCells() const;

        void setSize(unsigned int _size);
        void setCells(map<string, Cell*>* _cells);

        void removeAllCells();
        map<int,int> countNbCellsPerState();
};


#endif // GRID_H
