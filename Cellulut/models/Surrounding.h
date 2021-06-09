#ifndef SURROUNDING_H
#define SURROUNDING_H

#include "main.h"

class Surrounding
{
    protected :
        unsigned int id_surrounding;
        string name;
        unsigned int radius;
        vector<bool>* interaction;
    public :
        Surrounding(unsigned int _id_surrounding = 0, string _name = "", unsigned int _radius = 1);
        ~Surrounding();

        unsigned int getId_Surrounding() const;
        string getName() const;
        unsigned int getRadius() const;
        vector<bool>* getInteraction() const;

        void setName(string _name);
        void setRadius(unsigned int _radius);
        void setInteraction(vector<bool>* _interaction);

        void afficher_surround();
        void addInteraction(vector<bool> _interactionLine);
};


#endif // SURROUNDING_H
