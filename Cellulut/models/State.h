#ifndef STATE_H
#define STATE_H

#include "main.h"

class State
{
protected :
    unsigned int index;
    string color;
    string label;
public :
    State(unsigned int index = 0,  string color = "",  string label = "");
    ~State() = default;

    unsigned int getIndex() const;
    string getColor() const;
    string getLabel() const;

    void setIndex(unsigned int _index);
    void setColor(string _color);
    void setLabel(string _label);

    QString getColorAsQString() const;
    QString getLabelAsQString() const;
};

#endif // STATE_H
