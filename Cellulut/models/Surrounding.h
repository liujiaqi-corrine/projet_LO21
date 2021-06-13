#ifndef SURROUNDING_H
#define SURROUNDING_H

#include "main.h"

/*!
 *  \file Surrounding.h
 *  This file contains the Surrounding class
 */


/*!
 * \brief The Surrounding class
 */

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

        void afficher_surround();
        void addInteraction(vector<bool> _interactionLine);

        QString getNameAsQString() const{return QString::fromStdString(this->name);}

        friend class Library;
};


#endif // SURROUNDING_H
