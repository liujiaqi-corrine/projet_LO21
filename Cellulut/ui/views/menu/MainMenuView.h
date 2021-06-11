#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include "main.h"
#include "ui/UIEngine.h"

class UIEngine;

class MainMenuView : public QWidget
{
    Q_OBJECT
public:
    MainMenuView(QWidget *parent = 0, UIEngine *uiEngine = 0);
    ~MainMenuView();
signals:
    void createModelClicked();
private:
    UIEngine *uiEngine;
    QLabel *welcomeMessageLabel;
    QPushButton *createModelButton;
    QPushButton *loadModelButton;
    QGridLayout *gridLayout;
};

#endif // MAINMENUVIEW_H
