#include "main.h"
#include "models/Library.h"

Library* Library::singleton = new Library;

vector<Surrounding*>* Library::getListSurroundings() const{return this->listSurroundings;}

vector<Model*>* Library::getListModels() const{return this->listModels;}


Surrounding* Library::create_Surrounding(string _name)
{
    Surrounding* new_surrounding = new Surrounding(this->listSurroundings->size(), _name);
    this->listSurroundings->push_back(new_surrounding);
    cout<<"Create Surrounding '"<<new_surrounding->getName()<<"' with index "<<new_surrounding->getId_Surrounding()<<endl;

    return new_surrounding;
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
    qInfo() <<"This surrounding doesn't exist";
    return nullptr;
}

void Library::del_Surrounding(unsigned int surrounding_id)
{
    if (surrounding_id > Library::getLibrary()->getListSurroundings()->size() - 1)
    {
        cout<<"This surrounding doesn't exist"<<endl;
    }
    else if (surrounding_id == 0 or surrounding_id == 1)
    {
        cout<<"You can't delete pre-existing surrounding"<<endl;
    }
    else {
        for(unsigned int i=surrounding_id; i < getLibrary()->getListSurroundings()->size(); i++)
        {
            this->getListSurroundings()->at(i)->id_surrounding--;
        }
        cout<<"Surrounding '"<<this->getListSurroundings()->at(surrounding_id)->getName()<<"' deleted"<<endl;
        this->listSurroundings->erase(this->listSurroundings->begin()+surrounding_id);
    }
    return;
}


void Library::create_Model(string _title, string _description, string _author, string _date)
{
    Model* new_model = new Model(this->listModels->size(), _title, _description, _author, _date);
    this->listModels->push_back(new_model);
    cout<<"Create Model '"<<new_model->getTitle()<<"' with index "<<new_model->getId_Model()<<endl;
}

Model* Library::get_Model(unsigned int model_id)
{
    if (model_id > this->listModels->size()){
        cout<<"This model doesn't exists";
        return nullptr;
    }
    return this->listModels->at(model_id);
}

void Library::del_Model(unsigned int model_id)
{
    if (model_id > Library::getLibrary()->getListModels()->size() - 1)
    {
        cout<<"This model doesn't exist"<<endl;
    }
    else if (model_id == 0 or model_id == 1 or model_id == 2)
    {
        cout<<"You can't delete pre-existing model"<<endl;
    }
    else {
        for(unsigned int i=model_id; i < getLibrary()->getListModels()->size(); i++)
        {
            this->getListModels()->at(i)->id_model--;
        }
        cout<<"Model '"<<this->getListModels()->at(model_id)->getTitle()<<"' deleted"<<endl;
        this->listModels->erase(this->listModels->begin()+model_id);
    }
    return;
}
