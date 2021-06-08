#ifndef RULES_H
#define RULES_H

// pour chaque etat, definir les transformations
//creation d'une classe config
// calcul de l'etat suivant en comparant toutes config avec un extrait de la grille avec la cellule centrale - si outer ?

#include "Model.h"
#include "Config.h"
#include <vector>

class Model;
class Rule_Intension;

struct condition{
            int index_comptant;
            int min;
            int max;
        } typedef condition;

class Rules {

    protected:
        QString nom;
        Model* parent;

    public:
        Rules(QString _nom ,Model* _parent) {nom = _nom; parent = _parent;}
        Model* getParent() const {return parent;}
        virtual Rules*  getRue() = 0;
        virtual void setVoisins(int etat,int suivant, int comptant, int min, int max) = 0; //permet d'utiliser la bonne fonction des classes filles
        virtual std::vector<condition>* getConditions(int etat,int suivant) = 0;
        //virtual std::vector<Config> getConfigs(int etat) = 0;

};

class Rule_Intension : public Rules {

    private :
        /*struct condition{
            int index_comptant;
            int min;
            int max;
        } typedef condition;
        struct transfo{
            int index_suivant;
            std::vector<condition> conditions;
        } typedef tranfo;
        transfo*** state_rules;*/

        std::vector<condition>*** states_rules;

    public :
        //Rule_Intension(QString _nom ,Model* _parent, int nb) : Rules(_nom, _parent) {state_rules = new condition*[nb]; for (int i=0; i<nb; i++) state_rules[i] = new condition[nb];}
        Rule_Intension(QString _nom ,Model* _parent, int nb) : Rules(_nom, _parent) {

        states_rules = new std::vector<condition>**[nb]; //pour chaque etat/
        for (int i=0; i<nb; i++) states_rules[i] = new std::vector<condition>*[nb]; // nb transfo possible / etat

        for (int i=0; i<nb; i++) // pour etat destination potentielle
            for (int j=0; j<nb; j++)
                states_rules[i][j] = new std::vector<condition>;

   }
        //virtual void setVoisins(int etat,int indice, int min, int max) {state_rules[etat][indice].min.push_back(min); state_rules[etat][indice].max.push_back(max);}
        virtual void setVoisins(int etat,int suivant, int comptant, int _min, int _max){ condition cond = {comptant, _min, _max};states_rules[etat][suivant]->push_back(cond);}
        virtual std::vector<condition>* getConditions(int etat,int suivant) {return states_rules[etat][suivant];}
        Rule_Intension*  getRue() {return this;}

};

class Rule_Extension /*: public Rules*/ {

    private:
        std::vector<Config>* configs;

    public:
        Rule_Extension(/*QString _nom ,Model* _parent,*/ int nb) /*: Rules(_nom, _parent)*/ {configs = new std::vector<Config>[nb];}
        void addConfig(int etat, Config* conf) {configs[etat].push_back(*conf);}
        //std::vector<Config> getConfigs(int etat) {return configs[etat];}
        std::vector<Config> getConfigs(int etat) {return configs[etat];}


};


#endif // RULES_H
