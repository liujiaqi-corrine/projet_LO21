#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <QString>
#include <QColor>

class State
{
    protected :
        int index;
        QString label;
        QColor color;
    public :
        State(int _index, QColor _color, QString _label="" );
        ~State() = default;

        QString getLabel() const;
        QColor getColor() const;
        int getIndex() const;

        void setIndex(int _index);
};

#endif // STATE_H_INCLUDED
