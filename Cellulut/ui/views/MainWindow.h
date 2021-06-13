#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "main.h"
#include "ui/UIEngine.h"

/*!
 *  \file MainWindow.h
 *  This file contains the MainWindow class
 */

namespace Ui {
class MainWindow;
}

class UIEngine;

/*!
 * \brief The MainWindow class
 */

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
