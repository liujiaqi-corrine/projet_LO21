#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

#include <QString>
#include "State.h"
#include "Surrounding.h"
#include "Rules.h"

class Rules;
class Rule_Extension;

class Model
{
    protected :
        QString name;
        State** listStates;
        Surrounding* voisinage;
        int nbState;
        Rules* rule;
        Rule_Extension* extension;
    public :
        Model(QString _name, int _nbState);
        Model();
        ~Model() = default;

        QString getName() const;
        State** getListStates() const;
        Surrounding* getVoisinage() const {return voisinage;}
        Rules* getRule() const {return rule;}
        Rule_Extension* getRuleExtension() const {return extension;}
        int getNbState() const;


        void setVoisinage(int _diametre) {voisinage = new Surrounding(_diametre);}
        void setName(QString _name);
        void setRule(Rules* _rule) {rule = _rule;}
        void setRuleExtension(Rule_Extension* _rule) {if (!_rule) qDebug("this null Model.h");extension = _rule;}
        //void setRuleExtension(Rule_Extension* _rule) {if (!_rule) qDebug("this null Model.h");extension = _rule;}


        //void init_Grid(int width, int length);
        //void add_State(State* new_state);
        //void del_State(State* _state);
};

#endif // MODEL_H_INCLUDED
