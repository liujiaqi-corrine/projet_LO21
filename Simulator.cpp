//
//  simulator.cpp
//  lo21projetxcode
//
//  Created by Manqing WEI on 2021/5/13.
//

#include "Simulator.h"

void Simulator::build(int c){
    if (c > nbMax) {
        throw SimulatorException("Not enough space");
    }
    if (history[c] == NULL) {
        history[c] = new Grid;
    }
}

Model* Simulator::getModel() const {return model;}

const Grid* Simulator::getGridStart() const {return start;}

Grid** Simulator::getGridHistory() const {return history;}

int Simulator::getRank() const {return rank;}

int Simulator::getNbMax() const {return nbMax;}

void Simulator::setStart(const Grid* g){
    start=g;
    reset();
}
void Simulator::next(){
    if (start==NULL) {
        throw SimulatorException("State of start not define");
    }
    rank++;
    build(rank%nbMax);
    /*------------- the functions for iteration-------------*/
}
void Simulator::run(){
    for (int i=0; i<nbMax; i++) {
        next();
    }
}
void Simulator::reset(){
    if (start==NULL) {
        throw SimulatorException("State of start not define");
    }
    build(0);
    *history[0]=*start;
    rank=0;
}
void Simulator::changeMode(){
    if (flag==0) flag=1;
    else flag=0;
}
