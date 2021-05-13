#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <string>
using namespace std;

class State
{
    protected :
        string label;
        string color;
        int index;
    public :
        State(string _label = "", string _color = "", int _index = 0);
        ~State() = default;

        string getLabel() const;
        string getColor() const;
        int getIndex() const;

        void setIndex(int _index);
};

#endif // STATE_H_INCLUDED
