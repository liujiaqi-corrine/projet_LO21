#ifndef LIBRARYVIEW_H
#define LIBRARYVIEW_H

#include "main.h"
#include "ui/UIEngine.h"

class LibraryView : public QWidget
{
    Q_OBJECT
public:
    LibraryView(QWidget *parent = 0, UIEngine *uiEngine = 0);
    ~LibraryView();
signals:

private:
    UIEngine *uiEngine;
    QGridLayout *gridLayout;
    QLabel *widgetTitle;

    void onViewSurroundingButtonClicked();
    void onDeleteSurroundingButtonClicked();
    void onDeleteModelButtonClicked();
    int getIDFromObjectName(QObject *sender);
};

#endif // LIBRARYVIEW_H
