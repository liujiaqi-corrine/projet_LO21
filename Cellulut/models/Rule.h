#ifndef RULE_H
#define RULE_H

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
    public :
        Rule_ext() = default;
        ~Rule_ext() = default;
};



#endif // RULE_H
