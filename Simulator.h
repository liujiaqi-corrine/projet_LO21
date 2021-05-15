//
//  simulator.hpp
//  lo21projetxcode
//
//  Created by Manqing WEI on 2021/5/13.
//

#ifndef simulator_hpp
#define simulator_hpp

#include <iostream>
#include "Model.h"
#include "Grid.h"

using namespace std;

class SimulatorException { //出错时throw
public:
    SimulatorException(const string& message):info(message) {}
    string getInfo() const { return info; }
private:
    string info;
};

class Simulator {
private:
    Model* model;
    const Grid* start;
    Grid** history;
    int rank; // 变的次数
    int nbMax; //可储存的最多
    int flag; // 0->mode automate; 1->mode pas à pas
    
    Simulator(const Simulateur& s)=delete;
    Simulator& operator=(const Simulateur& s)=delete;
    
    void build(int c);
public:
    Simulator(const Model& m, const Grid& sta, int n):model(m), start(sta), history(NULL), rank(0), nbMax(n), flag(0){}
    ~Simulator = default; 
    
    Model* getModel() const;
    const Grid* getGridStart() const;
    Grid** getGridHistory() const;
    int getRank() const;
    int getNbMax() const;
    
    void setStart(const Grid* g);
    void next();
    void run();
    void reset();
    void changeMode();
};

#endif /* simulator_hpp */
