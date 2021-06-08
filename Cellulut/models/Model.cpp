#include "main.h"
#include "models/Model.h"

Model::Model(unsigned int _id, string _title, string _description, string _author, string _date) : id(_id), title(_title), description(_description), author(_author), date_creation(_date)
{
    this->listStates = new vector<State*>;
    State* default_state = new State(0,"default","grey");
    this->add_State(default_state);

    this->surrounding = nullptr;
    this->rule_int = new vector<Rule_int*>;
    this->rule_ext = new vector<Rule_ext*>;
}


unsigned int Model::getId() const{return this->id;}

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
    cout<<"This state index doesn't exists"<<endl;
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
        }
    }
    this->listStates->push_back(new_state);
    cout<<"State added"<<endl;
    return;
}

void Model::del_State(State* _state)
{
    if (!_state->getIndex()){
        cout<<"You can't delete default state"<<endl;
        return;
    }
    for(unsigned int i = 0; i < listStates->size(); i++)
    {
        if(listStates->at(i) == _state)
        {
            listStates->erase(listStates->begin()+i);
            cout<<"State deleted"<<endl;
            return;
        }
    }
}

void Model::add_Rule_int(Rule_int* new_rule_int)
{
    this->rule_int->push_back(new_rule_int);
    return;
}

