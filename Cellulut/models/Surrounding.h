#ifndef SURROUNDING_H
#define SURROUNDING_H

#include "main.h"

class Surrounding
{
    protected :
        string name;
        unsigned int diameter;
        bool** interaction;
    public :
        Surrounding(string _name = "", unsigned int _diameter = 0, bool** _interaction = nullptr);
        ~Surrounding() = default;

        string getName() const;
        unsigned int getDiameter() const;
        bool** getInteraction() const;

        void setName(string _name);
        void setDiameter(unsigned int _diameter);
        void setInteraction(bool** _interaction);
};


#endif // SURROUNDING_H
