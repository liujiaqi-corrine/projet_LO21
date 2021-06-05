#ifndef V_MAINWINDOW_H
#define V_MAINWINDOW_H

#include <QMainWindow>
#include "../controllers/c_mainwindow.h"

namespace Ui {
class V_MainWindow;
}

class C_MainWindow;

class V_MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::V_MainWindow *ui;
    C_MainWindow *controller;

public:
    explicit V_MainWindow(QWidget *parent = 0, C_MainWindow *c = 0);
    ~V_MainWindow();

    Ui::V_MainWindow* getUi() const {return this->ui;}

private slots:
    void on_actionLancer_une_simulation_triggered();
};

#endif // V_MAINWINDOW_H
