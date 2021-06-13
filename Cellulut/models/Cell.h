#ifndef CELL_H
#define CELL_H

#include "main.h"
#include "models/State.h"

/*!
 *  \file Cell.h
 *  This file contains the Cell class
 */


/*!
 * \brief The Cell class
 */

class Cell
{
    protected :
        int x;
        int y;
        State* state;
    public :
        Cell() = default;
        ~Cell() = default;
        Cell(int X, int Y): x(X), y(Y), state(nullptr){};

        int getX() const;
        int getY() const;
        State* getState() const;

        void setX(int _x);
        void setY(int _y);
        void setState(State* _state);

        string getHash() const;
        static string getHashFromPos(int posX, int posY);
};


#endif // CELL_H
