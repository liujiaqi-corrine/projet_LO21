#ifndef MODEL_H
#define MODEL_H

#include "main.h"
#include "models/Rule_int.h"
#include "models/Rule_ext.h"
#include "models/State.h"
#include "models/Surrounding.h"

class Model
{
    protected :
        unsigned int id;
        string title;
        string description;
        string author;
        string date_creation;
        vector<State*>* listStates;
        Surrounding* surrounding;
        vector<Rule_int>* rule_int;
        vector<Rule_ext>* rule_ext;
    public :
        Model() = default;
        Model(unsigned int id, string title, string description, string author, string dateOfCreation);
        ~Model() = default;

        unsigned int getId() const;
        string getTitle() const;
        string getDescription() const;
        string getAuthor() const;
        string getDate() const;
        vector<State*>* getListStates() const;

        void setId(unsigned int _id);
        void setTitle(string _title);
        void setDescription(string _title);
        void setAuthor(string _title);
        void setDate(string _title);
        void setListStates(vector<State*>* _listStates);

        State* get_State(unsigned int _index);
        void add_State(State* new_state);
        void del_State(State* _state);

        QString getTitleAsQString() const{return QString::fromUtf8(this->title.c_str());}
};


#endif // MODEL_H
