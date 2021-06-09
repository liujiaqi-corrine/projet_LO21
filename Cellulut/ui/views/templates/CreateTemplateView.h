#ifndef CREATETEMPLATEVIEW_H
#define CREATETEMPLATEVIEW_H

#include <QWidget>
#include "ui/UIEngine.h"

namespace Ui {
class CreateTemplateView;
}

class CreateTemplateView : public QWidget
{
    Q_OBJECT

public:
    explicit CreateTemplateView(QWidget *parent = nullptr, UIEngine *uiEngine = 0);
    ~CreateTemplateView();

private:
    Ui::CreateTemplateView *ui;
    UIEngine *uiEngine;
};

#endif // CREATETEMPLATEVIEW_H
