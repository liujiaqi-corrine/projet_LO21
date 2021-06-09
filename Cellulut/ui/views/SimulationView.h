#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include <QWidget>
#include "ui/UIEngine.h"
#include "ui/views/grid/SimulationBoard.h"

namespace Ui {
class SimulationView;
}

class UIEngine;

class SimulationView : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationView(QWidget *parent = nullptr, UIEngine *uiEngine = 0);
    ~SimulationView();

private slots:
    void on_slider_size_valueChanged(int value);

private:
    Ui::SimulationView *ui;
    UIEngine *uiEngine;
    SimulationBoard *board;
};

#endif // SIMULATIONVIEW_H
