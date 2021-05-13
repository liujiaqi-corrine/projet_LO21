#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

class Grid
{
    protected :
        unsigned int length;
        unsigned int width;
        Cell** listCells;
    public :
        Grid(unsigned int _length = 0, unsigned int _width = 0);
        ~Grid() = default;

        unsigned int getLength() const;
        unsigned int getWidth() const;
        Cell** getlistCells() const;

        void setlistCells(Cell** _listCells);
        void setLength(unsigned int _length);
        void setWidth(unsigned int _width);
};

#endif // GRID_H_INCLUDED
