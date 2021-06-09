#include "main.h"
#include "models/Library.h"

Library* Library::singleton = new Library;

vector<Surrounding*>* Library::getListSurroundings() const{return this->listSurroundings;}

vector<Model*>* Library::getListModels() const{return this->listModels;}


void Library::add_Surrounding(Surrounding* new_surrounding)
{
    for(unsigned int i = 0; i < listSurroundings->size(); i++)
    {
        if(listSurroundings->at(i)->getId_Surrounding() == new_surrounding->getId_Surrounding())
        {
            //throw invalid_argument("Surrounding index already exists, index : " + to_string(new_surrounding->getId_Surrounding()));
            cout<<"Surrounding index already exists"<<endl;
            return;
        }
    }
    this->listSurroundings->push_back(new_surrounding);
    cout<<"Surrounding added"<<endl;
    return;
}

Surrounding* Library::get_Surrounding(unsigned int surrounding_id)
{
    for(unsigned int i = 0; i < listSurroundings->size(); i++)
    {
        if(listSurroundings->at(i)->getId_Surrounding() == surrounding_id)
        {
            return listSurroundings->at(i);
        }
    }
    cout<<"This surrounding doesn't exists";
    return nullptr;
}

void Library::del_Surrounding(Surrounding* _surrounding)
{
    for(unsigned int i = 0; i < listSurroundings->size(); i++)
    {
        if(listSurroundings->at(i) == _surrounding)
        {
            listSurroundings->erase(listSurroundings->begin()+i);
            cout<<"Surrounding deleted"<<endl;
            return;
        }
    }
    cout<<"This surrounding doesn't exists";
    return;
}


void Library::add_Model(Model* new_model)
{
    for(unsigned int i = 0; i < listModels->size(); i++)
    {
        if(listModels->at(i)->getId_Model() == new_model->getId_Model())
        {
            //throw invalid_argument("Model index already exists, index : " + to_string(new_model->getId_Model()));
            cout<<"Model index already exists"<<endl;
            return;
        }
    }
    this->listModels->push_back(new_model);
    cout<<"Model added"<<endl;
    return;
}

Model* Library::get_Model(unsigned int model_id)
{
    for(unsigned int i = 0; i < listModels->size(); i++)
    {
        if(listModels->at(i)->getId_Model() == model_id)
        {
            return listModels->at(i);
        }
    }
    cout<<"This model doesn't exists";
    return nullptr;
}

void Library::del_Model(Model* _model)
{
    for(unsigned int i = 0; i < listModels->size(); i++)
    {
        if(listModels->at(i) == _model)
        {
            listModels->erase(listModels->begin()+i);
            cout<<"Model deleted"<<endl;
            return;
        }
    }
    cout<<"This model doesn't exists";
    return;
}
