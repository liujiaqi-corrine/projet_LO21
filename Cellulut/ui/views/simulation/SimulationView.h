#ifndef SIMULATIONVIEW_H
#define SIMULATIONVIEW_H

#include "models/Model.h"
#include "models/Automate.h"
#include "SimulationBoard.h"
#include "StatesDisplay.h"
#include "SimulationButtonsBar.h"
#include "ui/UIEngine.h"

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class SimulationBoard;

class SimulationView : public QWidget
{
    Q_OBJECT
public:
    SimulationView(QWidget *parent = nullptr, UIEngine *uiEngine = nullptr);
    ~SimulationView();
private:
    UIEngine *uiEngine;
    SimulationBoard *board;
    Model *modelForSimulation;

    QLabel *modelTitle;
    QLabel *modelDescription;
    QLabel *modelAuthor;
    QLabel *modelDate;

    QLineEdit *inputSize;
    QSlider *sliderSize;
    QWidget *sizeDisplay;
    StatesDisplay *statesDisplay;
    SimulationButtonsBar *simulationButtonsBar;
    QPushButton *randomConfigurationButton;

    QGridLayout *gridLayout;
    QHBoxLayout *simulationButtonsLayout;

    QLabel *createLabel(const QString &text, const QString &objectName, int fontSize, bool isBold, bool isItalic);

    void setupGridLayout();
    void setupLabelsForModel();
    void initEvents();
    void updateInputSizeValueFromInt(int newValue);
    void updateInputSizeValueFromString(QString newValue);
    void onClickStepForward();
    void onClickRandomConfiguration();
    void changeGridSize(int newValue);

    const char *styleSheet =
            "";
};

#endif // SIMULATIONVIEW_H
