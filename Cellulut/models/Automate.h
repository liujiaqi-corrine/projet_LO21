#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "main.h"
#include "models/Model.h"
#include "models/Grid.h"

class Automate // Singleton
{
    protected :
        static Automate* singleton; // Pointer to singleton
        Automate() = default; // Private constructor
        Model* model = nullptr;
        vector<unsigned int**>* historic = new vector<unsigned int**>;
    public :
        static Automate* getAutomate() noexcept {return singleton;}
        ~Automate() = default;

        Model* getModel() const;
        vector<unsigned int**>* getHistoric() const;

        void setModel(Model* _model);

        void init_Grid(unsigned int rows, unsigned int columns);

        void save_current_config();

        State* random_state();

        void random_init();

        void manual_init();

        unsigned int count_nearby_state(unsigned int x, unsigned int y, unsigned int state_index);

        unsigned int check_rule_int(unsigned int x, unsigned int y, unsigned int rule_index);

        void next_generation();

        void afficher_historique(int x);

        void afficher_grid();
};

#endif // AUTOMATE_H
