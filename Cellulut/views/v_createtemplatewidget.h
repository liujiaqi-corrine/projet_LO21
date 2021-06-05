#ifndef V_CREATETEMPLATEWIDGET_H
#define V_CREATETEMPLATEWIDGET_H

#include <QWidget>

namespace Ui {
class V_CreateTemplateWidget;
}

class V_CreateTemplateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit V_CreateTemplateWidget(QWidget *parent = nullptr);
    ~V_CreateTemplateWidget();

private:
    Ui::V_CreateTemplateWidget *ui;
};

#endif // V_CREATETEMPLATEWIDGET_H
