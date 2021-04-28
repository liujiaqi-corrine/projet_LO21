#include "Cellulut.h"

Model::Model()
{
    name = "";
    listStates = new vector<State*>;
    voisinage = nullptr;
    addState("defaut","blanc");
}

void Model::addState(string label, string color)
{
    if( listStates->size() < MAX_STATE)
    {
        State* newState = new State(label,color);
        this->listStates->push_back(newState);
    }
}

