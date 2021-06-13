#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main.h"
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

    private:
        UIEngine* uiEngine;
        QAction *mainMenuAct;
        QAction *loadModelAct;
        QAction *simulationAct;
        void keyPressEvent(QKeyEvent* event);
};

#endif // MAINWINDOW_H
