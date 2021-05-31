#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <QString>
//#include "Grid.h"
#include "State.h"

class Model
{
    protected :
        QString name;
        State** listStates;
        int nbState;
        //Grid* grid;
    public :
        Model(QString _name, int _nbState);
        Model();
        ~Model() = default;

        QString getName() const;
        State** getListStates() const;
        //Grid* getGrid() const;
        int getNbState() const;

        void setName(QString _name);

        //void init_Grid(int width, int length);
        //void add_State(State* new_state);
        //void del_State(State* _state);
};

#endif // MODEL_H_INCLUDED
