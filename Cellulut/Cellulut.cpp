#include "Cellulut.h"

Model::Model(){
    name = "";
    groupState = new State*[8];
    nb_state = 0;
    voisinage = nullptr;
    addState("defaut","blanc");
}

