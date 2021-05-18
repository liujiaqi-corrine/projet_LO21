#ifndef CELL_H_INCLUDED
#define CELL_H_INCLUDED

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
};

#endif // CELL_H_INCLUDED
