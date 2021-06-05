#include "main.h"
#include "models/Library.h"

Library* Library::singleton = new Library;

vector<Model*>* Library::getListModels(){return listModels;}

void Library::add_Model(Model* new_model)
{
    for(unsigned int i = 0; i < listModels->size(); i++)
    {
        if(listModels->at(i) == new_model)
        {
            //throw invalid_argument("This model already exists \n");
        }
    }
    this->listModels->push_back(new_model);
    //cout<<"Model added"<<endl;
    return;
}

Model* Library::get_Model(unsigned int model_id)
{
    for(unsigned int i = 0; i < listModels->size(); i++)
    {
        if(listModels->at(i)->getId() == model_id)
        {
            return listModels->at(i);
        }
    }
    //cout<<"This model doesn't exists"
    return nullptr;
}

void Library::del_Model(Model* _model)
{
    for(unsigned int i = 0; i < listModels->size(); i++)
    {
        if(listModels->at(i) == _model)
        {
            listModels->erase(listModels->begin()+i);
            //cout<<"Model deleted"<<endl;
            return;
        }
    }
    //cout<<"This model doesn't exists"
    return;
}
