#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "main.h"
#include "models/Model.h"
#include "models/Grid.h"

class Automate
{
    protected :
        Model* model;
        Grid* grid;
        vector<int**>* historic;
    public :
        Automate();
        ~Automate() = default;

        Model* getModel() const;
        Grid* getGrid() const;

        void setModel(Model* _model);
        void setGrid(Grid* grid);

        void init_Grid();
};

#endif // AUTOMATE_H
