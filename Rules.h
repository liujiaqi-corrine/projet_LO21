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

class Rules {

    protected:
        QString nom;
        Model* parent;

    public:
        Rules(QString _nom ,Model* _parent) {nom = _nom; parent = _parent;}
        Model* getParent() const {return parent;}
        virtual void setVoisins(int indice, int min, int max) = 0; //permet d'utiliser la bonne fonction des classes filles
        virtual std::vector<int> getVoisinsMin(int indice) = 0;
        virtual std::vector<int> getVoisinsMax(int indice) = 0;

};

class Rule_Intension : public Rules {

    private :
        struct nb_voisins{
            std::vector<int> min;
            std::vector<int> max;
        } typedef nb_voisins;
        nb_voisins* state_rules;



    public :
        Rule_Intension(QString _nom ,Model* _parent, int nb) : Rules(_nom, _parent) {state_rules = new nb_voisins[nb];}
        virtual void setVoisins(int indice, int min, int max) {state_rules[indice].min.push_back(min); state_rules[indice].max.push_back(max);}
        virtual std::vector<int> getVoisinsMin(int indice) {return state_rules[indice].min;}
        virtual std::vector<int> getVoisinsMax(int indice) {return state_rules[indice].max;}

};

class Rule_Extension : public Rules {

    private:
        std::vector<Config*> configs;

    public:
        Rule_Extension(QString _nom ,Model* _parent) : Rules(_nom, _parent) {}
        //void setConfigs() {configs.push_back(new Config());}


};












#endif // RULES_H
