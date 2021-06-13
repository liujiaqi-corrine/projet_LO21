#ifndef STATE_H
#define STATE_H

#include "main.h"

/*!
 *  \file State.h
 *  This file contains the State class
 */


/*!
 * \brief The State class
 */

class State
{
protected :
    unsigned int index;
    string label;
    string color;
public :
    State(unsigned int index = 0,  string _label = "",  string _color = "");
    ~State() = default;

    unsigned int getIndex() const;
    string getLabel() const;
    string getColor() const;

    void setLabel(string _label);
    void setColor(string _color);

    QString getColorAsQString() const;
    QString getLabelAsQString() const;
};

#endif // STATE_H
