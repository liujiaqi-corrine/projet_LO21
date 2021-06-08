#ifndef SURROUNDING_H
#define SURROUNDING_H

#include "main.h"

class Surrounding
{
    protected :
        string name;
        unsigned int radius;
        vector<bool> *interaction;
    public :
        Surrounding(string _name = "", unsigned int _radius = 1);
        ~Surrounding();

        string getName() const;
        unsigned int getRadius() const;
        vector<bool>* getInteraction() const;

        void setName(string _name);
        void setRadius(unsigned int _radius);
        void setInteraction(vector<bool> *_interaction);

        void afficher_surround();
        void addInteraction(vector<bool> _interactionLine);
};


#endif // SURROUNDING_H
