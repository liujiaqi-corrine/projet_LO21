#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include <QWidget>
#include "ui/UIEngine.h"

namespace Ui {
class MainMenuView;
}

class UIEngine;

class MainMenuView : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuView(QWidget *parent = nullptr, UIEngine *uiEngine = 0);
    ~MainMenuView();

private slots:

    void on_actionLoadTemplate_clicked();

    void on_actionCreateTemplate_clicked();

private:
    Ui::MainMenuView *ui;
    UIEngine *uiEngine;
};

#endif // MAINMENUVIEW_H
