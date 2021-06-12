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
        Surrounding(unsigned int _id, string _name, unsigned int _radius = 1);
    public :
        ~Surrounding();

        unsigned int getId_Surrounding() const;
        string getName() const;
        unsigned int getRadius() const;
        vector<bool>* getInteraction() const;

        void setName(string _name);
        void setRadius(unsigned int _radius);
        void setInteraction(vector<bool>* _interaction);

        void addInteraction(vector<bool> _interactionLine);

        friend class Library;
};


#endif // SURROUNDING_H
