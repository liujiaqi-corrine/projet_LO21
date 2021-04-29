#include "Cellulut.h"

Library* Library::singleton = new Library;

vector<Model*>* Library::getListModels(){return listModels;}

Model* Library::getModel()
{

}

void Library::add_Model(Model* new_model)
{
    for(int i = 0; i < listModels->size(); i++)
    {
        if(listModels->at(i) == new_model)
        {
            cout<<"This model already exist \n"; //Gestion d'exception à faire
            return;
        }
    }
    this->listModels->push_back(new_model);
}

void Library::del_Model(Model* _model)
{
    for(int i = 0; i < listModels->size(); i++)
    {
        if(listModels->at(i) == _model)
        {
            listModels->erase(listModels->begin()+i);
            cout<<"Model deleted \n";
            return;
        }
    }
}
