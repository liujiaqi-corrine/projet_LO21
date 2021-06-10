#include "main.h"
#include "models/Model.h"

Model::Model(unsigned int _id_model, string _title, string _description, string _author, string _date) : id_model(_id_model), title(_title), description(_description), author(_author), date_creation(_date)
{
    this->listStates = new vector<State*>;
    this->surrounding = nullptr;
    this->rule_int = new vector<Rule_int*>;
    this->rule_ext = new vector<Rule_ext*>;
}


unsigned int Model::getId_Model() const{return this->id_model;}

string Model::getTitle() const{return this->title;}

string Model::getDescription() const{return this->title;}

string Model::getAuthor() const{return this->title;}

string Model::getDate() const{return this->title;}

vector<State*>* Model::getListStates() const{return this->listStates;}

Surrounding* Model::getSurrounding() const{return this->surrounding;}

vector<Rule_int*>* Model::getRule_int() const{return this->rule_int;}

vector<Rule_ext*>* Model::getRule_ext() const{return this->rule_ext;}


void Model::setTitle(string _title){this->title = _title;}

void Model::setDescription(string _description){this->description = _description;}

void Model::setAuthor(string _author){this->author = _author;}

void Model::setDate(string _date){this->date_creation = _date;}

void Model::setListStates(vector<State*>* _listStates){this->listStates = _listStates;}

void Model::setSurrounding(Surrounding* _surrounding){this->surrounding = _surrounding;}

void Model::setRule_int(vector<Rule_int*>* _rule_int){this->rule_int = _rule_int;}

void Model::setRule_ext(vector<Rule_ext*>* _rule_ext){this->rule_ext = _rule_ext;}


State* Model::get_State(unsigned int _index)
{
    for (unsigned int i =0; i < listStates->size(); i++)
    {
        if(listStates->at(i)->getIndex() == _index)
        {
            return listStates->at(i);
        }
    }
    cout<<"This state index doesn't exist"<<endl;
    return nullptr;
}

void Model::add_State(State* new_state)
{
    if(listStates->size() >= MAX_STATE)
    {
        //throw out_of_range("Maximum number of states reached");
    }
    for (unsigned int i =0; i < listStates->size(); i++)
    {
        if(listStates->at(i)->getIndex() == new_state->getIndex())
        {
            //throw invalid_argument("State index already exists, index : " + to_string(new_state->getIndex()));
            cout<<"State index already exists"<<endl;
            return;
        }
    }
    this->listStates->push_back(new_state);
    cout<<"State '"<<new_state->getLabel()<<"' added to '"<<this->getTitle()<<"'"<<endl;
    return;
}

void Model::del_State(State* _state)
{
    if (this->listStates->size() == 1)
    {
        cout<<"At least 1 state needed"<<endl;
        return;
    }
    for(unsigned int i = 0; i < listStates->size(); i++)
    {
        if(listStates->at(i) == _state)
        {
            listStates->erase(listStates->begin()+i);
            cout<<"State '"<<_state->getLabel()<<"' deleted"<<endl;
            return;
        }
    }
    cout<<"This state doesn't exist";
    return;
}

void Model::add_Rule_int(Rule_int* new_rule_int)
{
    this->rule_int->push_back(new_rule_int);
    return;
}

void Model::add_Rule_ext(Rule_ext* new_rule_ext)
{
    this->rule_ext->push_back(new_rule_ext);
    return;
}

