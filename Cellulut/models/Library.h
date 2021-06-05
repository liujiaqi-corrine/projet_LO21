#ifndef LIBRARY_H
#define LIBRARY_H

#include "main.h"
#include "models/Model.h"

class Library
{
    protected :
        static Library* singleton;  // Pointer to singleton
        Library() = default;  // Private constructor
        vector<Model*>* listModels = new vector<Model*>;
    public :
        static Library* getInstance() noexcept {return singleton;}

        ~Library() = default;
        Library(const Library&) = delete;
        Library& operator=(const Library&) = delete;

        vector<Model*>* getListModels();

        void add_Model(Model* new_model);
        Model* get_Model(unsigned int model_id);
        void del_Model(Model* _model);
};


#endif // LIBRARY_H
