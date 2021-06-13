#ifndef AUTOMATE_H
#define AUTOMATE_H

#include "main.h"
#include "models/Model.h"
#include "models/Grid.h"

class Automate // Singleton
{
    protected :
        static Automate* singleton; // Pointer to singleton
        Automate(); // Private constructor
        Model* model = nullptr; //current_model
        vector<unsigned int**>* historic = new vector<unsigned int**>;
    public :
        ~Automate() = default;

        Model* getModel() const;
        vector<unsigned int**>* getHistoric() const;

        void setModel(Model* _model);

        static Automate* getAutomate() noexcept {return singleton;}
        void init_Grid(unsigned int size_grid);

        void save_current_config();

        State* random_state();

        void random_init();

        unsigned int count_nearby_state(unsigned int x, unsigned int y, unsigned int state_index);

        unsigned int check_rule_int(unsigned int x, unsigned int y, unsigned int rule_int_index);

        unsigned int check_rule_ext(unsigned int x, unsigned int y, unsigned int rule_ext_index);

        unsigned int check_stability();

        void afficher_historique(int x);

        void next_generation();

        unsigned int back_generation();
};

#endif // AUTOMATE_H
