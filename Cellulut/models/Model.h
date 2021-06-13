#ifndef MODEL_H
#define MODEL_H

#include "main.h"
#include "models/Rule.h"
#include "models/State.h"
#include "models/Surrounding.h"

/*!
 *  \file Model.h
 *  This file contains the Model class
 */


/*!
 * \brief The Model class
 */

class Model
{
    protected :
        unsigned int id_model;
        string title;
        string description;
        string author;
        string date_creation;
        vector<State*>* listStates;
        Surrounding* surrounding;
        vector<Rule_int*>* rule_int;
        vector<Rule_ext*>* rule_ext;
        Model(unsigned int _id, string _title, string _description, string _author, string _date);

    public :
        ~Model() = default;
        unsigned int getId_Model() const;
        string getTitle() const;
        string getDescription() const;
        string getAuthor() const;
        string getDate() const;
        vector<State*>* getListStates() const;
        Surrounding* getSurrounding() const;
        vector<Rule_int*>* getRule_int() const;
        vector<Rule_ext*>* getRule_ext() const;

        void setTitle(string _title);
        void setDescription(string _title);
        void setAuthor(string _title);
        void setDate(string _title);
        void setListStates(vector<State*>* _listStates);
        void setSurrounding(Surrounding* _surrounding);
        void setRule_int(vector<Rule_int*>* _rule_int);
        void setRule_ext(vector<Rule_ext*>* _rule_ext);

        State* get_State(unsigned int _index);
        void add_State(State* new_state);
        void del_State(State* _state);

        void add_Rule_int(Rule_int* new_rule_int);
        void add_Rule_ext(Rule_ext* new_rule_ext);

        QString getTitleAsQString() const{return QString::fromStdString(this->title);}
        QString getDescriptionAsQString() const{return QString::fromStdString(this->description);}
        QString getAuthorAsQString() const{return QString::fromStdString(this->author);}
        QString getDateAsQString() const{return QString::fromStdString(this->date_creation);}

        friend class Library;
};


#endif // MODEL_H
