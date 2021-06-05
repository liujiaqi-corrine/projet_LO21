#ifndef CONFIG_H
#define CONFIG_H

#include "State.h"
#include <vector>
#include <QTableWidgetItem>

class Config {

    private:
        State* central;
        std::vector<int*> listSets;

    public:
        Config(State* _central) {central = _central;}
        void addSet(int diametre);

    public slots:
        void setSet(QTableWidgetItem* item);








};




#endif // CONFIG_H
