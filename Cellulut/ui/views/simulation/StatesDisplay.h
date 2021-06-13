#ifndef STATESDISPLAY_H
#define STATESDISPLAY_H

#include "main.h"
#include "models/State.h"
#include "models/Automate.h"
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLCDNumber>

class StatesDisplay : public QWidget
{
    Q_OBJECT
public:
    StatesDisplay(QWidget *parent = nullptr);
    ~StatesDisplay();

public slots:
    void refreshCounters();

private:
    QGridLayout *layout;

    map<int, QWidget*> *mapOfColors;
    map<int, QLabel*> *mapOfLabels;
    map<int, QLCDNumber*> *mapOfCounts;
};

#endif // STATESDISPLAY_H
