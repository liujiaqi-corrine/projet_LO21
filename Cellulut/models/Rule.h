#ifndef RULE_H
#define RULE_H

#include "main.h"

// Rule_int = (A, B, C, D)
// Si la cellule est dans l'état A, qu'elle a B voisins dans l'état C, alors elle devient D
class Rule_int
{
    protected :
        unsigned int* list;
    public :
        Rule_int(unsigned int _A = 0, unsigned int _B = 0, unsigned int _C = 0, unsigned int _D = 0);
        ~Rule_int() = default;

        unsigned int getRule_current_state() const;
        unsigned int getRule_nb_nearby() const;
        unsigned int getRule_state_nearby() const;
        unsigned int getRule_next_state() const;

        void setRule_current_state(unsigned int _current_state);
        void setRule_nb_nearby(unsigned int _nb_nearby);
        void setRule_state_nearby(unsigned int _state_nearby);
        void setRule_next_state(unsigned int _next_state);
};

class Rule_ext
{
    protected :
        vector<int>* current_config;
        unsigned int next_state_index;
        unsigned int radius;
    public :
        Rule_ext(unsigned int _index = 0, unsigned int radius = 1);
        ~Rule_ext() = default;

        vector<int>* getCurrent_config() const;
        unsigned int getNext_state_index() const;
        unsigned int getRadius() const;

        void setCurrent_config(vector<int>* _config);
        void setNext_state_index(unsigned int _index);
        void setRadius(unsigned int _radius);

        void afficher_rule_ext();
        void addConfigLine(vector<int> _configLine);
};



#endif // RULE_H
