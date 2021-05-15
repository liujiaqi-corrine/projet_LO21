#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

#include <main.h>
//#include "State.h"
//#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{
    protected :
        int x;
        int y;
        State* state;
    public :

        Cell(int _x, int _y, int type = Type);
        ~Cell() = default;

        int getX() const;
        int getY() const;
        State* getState() const;

        void setX(int _x);
        void setY(int _y);
        void setState(State* _state);


};

#endif // CELL_H_INCLUDED
