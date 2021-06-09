#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "ui/UIEngine.h"

namespace Ui {
class MainWindow;
}

class UIEngine;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, UIEngine *uiEngine = 0);
    ~MainWindow();

private slots:

    void on_actionGoToMainMenu_triggered();

    void on_actionGoToSimulation_triggered();

    void on_actionGoToCreateTemplate_triggered();

    void on_actionGoToLoadTemplate_triggered();

private:
    Ui::MainWindow *ui;
    UIEngine* uiEngine;
    void keyPressEvent(QKeyEvent* event);
};

#endif // MAINWINDOW_H
