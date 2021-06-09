#ifndef LIBRARY_H
#define LIBRARY_H

#include "main.h"
#include "models/Model.h"
#include "models/Surrounding.h"

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

        void add_Surrounding(Surrounding* new_surrounding);
        Surrounding* get_Surrounding(unsigned int surrounding_id);
        void del_Surrounding(Surrounding* _surrounding);

        void add_Model(Model* new_model);
        Model* get_Model(unsigned int model_id);
        void del_Model(Model* _model);
};


#endif // LIBRARY_H
