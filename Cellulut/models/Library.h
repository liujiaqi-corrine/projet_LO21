#ifndef LIBRARY_H
#define LIBRARY_H

#include "main.h"
#include "models/Model.h"
#include "models/Surrounding.h"

/*!
 *  \file Library.h
 *  This file contains the Library class
 */


/*!
 * \brief The Library class
 */

class Library // Singleton
{
    protected :
        static Library* singleton;  // Pointer to singleton
        Library() = default;  // Private constructor
        vector<Surrounding*>* listSurroundings = new vector<Surrounding*>;
        vector<Model*>* listModels = new vector<Model*>;
    public :
        static Library* getLibrary() noexcept {return singleton;}

        ~Library() = default;
        Library(const Library&) = delete;
        Library& operator=(const Library&) = delete;

        vector<Surrounding*>* getListSurroundings() const;
        vector<Model*>* getListModels() const;

        Surrounding* create_Surrounding(string _name);
        Surrounding* get_Surrounding(unsigned int surrounding_id);
        void del_Surrounding(unsigned int surrounding_id);

        void create_Model(string _title, string _description = "", string _author = "", string _date = "");
        Model* get_Model(unsigned int model_id);
        void del_Model(unsigned int model_id);
};


#endif // LIBRARY_H
