#ifndef V_SIMULATIONCONFIGURATIONWIDGET_H
#define V_SIMULATIONCONFIGURATIONWIDGET_H

#include <QWidget>
#include <QStringListModel>
#include <QStandardItemModel>
#include "models/Cellulut.h"

namespace Ui {
class V_SimulationConfigurationWidget;
}

class V_SimulationConfigurationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit V_SimulationConfigurationWidget(QWidget *parent = nullptr, Cellulut *app = nullptr);
    ~V_SimulationConfigurationWidget();

private slots:
    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::V_SimulationConfigurationWidget *ui;
    Cellulut *app;

    QStringListModel *comboBoxModel;
    QStandardItemModel *statesTableModel;
    QString statesTableHeaders = "Indice,Couleur,Libellé";
};

#endif // V_SIMULATIONCONFIGURATIONWIDGET_H
