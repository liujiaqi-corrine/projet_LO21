#ifndef SIMULATIONVIEWV2_H
#define SIMULATIONVIEWV2_H

#include <QWidget>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QCoreApplication>
#include <QSlider>
#include <QLineEdit>
#include <QSizePolicy>
#include "ui/views/grid/SimulationBoard.h"

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE
class SimulationBoard;

class SimulationViewV2 : public QWidget
{
    Q_OBJECT
public:
    SimulationViewV2(QWidget *parent = nullptr);
private:
    QLabel *createLabel(const QString &text);

    SimulationBoard *board;
    QLCDNumber *levelLcd;
    QPushButton *startButton;
    QLineEdit *inputSize;
    QSlider *sliderSize;

    void initEvents();
    void updateInputSizeValueFromInt(int newValue);
    void updateInputSizeValueFromString(QString newValue);
};

#endif // SIMULATIONVIEWV2_H
