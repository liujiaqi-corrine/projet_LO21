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
        vector<Model*>* listModels = new vector<Model*>;
        vector<Surrounding*>* listSurroundings = new vector<Surrounding*>;
    public :
        static Library* getLibrary() noexcept {return singleton;}

        ~Library() = default;
        Library(const Library&) = delete;
        Library& operator=(const Library&) = delete;

        vector<Model*>* getListModels();
        vector<Surrounding*>* getListSurroundginds();

        void add_Model(Model* new_model);
        Model* get_Model(unsigned int model_id);
        void del_Model(Model* _model);
};


#endif // LIBRARY_H
