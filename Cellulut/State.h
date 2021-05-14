#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <QString>

class State
{
    protected :
        QString label;
        QString color;
        int index;
    public :
        State(QString _label="" , QString _color="" , int _index=0);
        ~State() = default;

        QString getLabel() const;
        QString getColor() const;
        int getIndex() const;

        void setIndex(int _index);
};

#endif // STATE_H_INCLUDED
