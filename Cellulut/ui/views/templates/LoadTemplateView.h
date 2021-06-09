#ifndef LOADTEMPLATEVIEW_H
#define LOADTEMPLATEVIEW_H

#include <QWidget>
#include "ui/UIEngine.h"

namespace Ui {
class LoadTemplateView;
}

class LoadTemplateView : public QWidget
{
    Q_OBJECT

public:
    explicit LoadTemplateView(QWidget *parent = nullptr, UIEngine *uiEngine = 0);
    ~LoadTemplateView();

private:
    Ui::LoadTemplateView *ui;
    UIEngine *uiEngine;
};

#endif // LOADTEMPLATEVIEW_H
