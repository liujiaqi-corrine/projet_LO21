#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include "Model.h"
#include <vector>
using namespace std;

class Library
{
    protected :
        static Library *singleton;  //Pointer to singleton
        Library() = default;  //Private constructor
        vector<Model*>* listModels = new vector<Model*>;
    public :
        static Library* getInstance() noexcept {return singleton;}

        ~Library() = default;
        Library(const Library&) = delete;
        Library& operator=(const Library&) = delete;

        vector<Model*>* getListModels();

        void add_Model(Model* new_model);
        void del_Model(Model* _model);
};


#endif // LIBRARY_H_INCLUDED
