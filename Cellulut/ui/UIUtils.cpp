#include "UIUtils.h"

UIUtils::UIUtils()
{

}

QLabel* UIUtils::createLabel(const QString &text, int fontSize, bool isBold, bool isItalic, QFont::Capitalization cap){
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    label->setFont(UIUtils::getFont(fontSize, isBold, isItalic, cap));
    return label;
}

QPushButton* UIUtils::createButton(const QString &text, int fontSize, bool isBold, bool isItalic, QFont::Capitalization cap){
    QPushButton *button  = new QPushButton(text);
    button->setFont(UIUtils::getFont(fontSize, isBold, isItalic, cap));
    button->setStyleSheet("background-color : crimson; color: white;");
    return button;
}

QFont UIUtils::getFont(int fontSize, bool isBold, bool isItalic, QFont::Capitalization cap){
    QFont font;
    font.setPointSize(fontSize);
    font.setBold(isBold);
    font.setItalic(isItalic);
    font.setCapitalization(cap);
    font.setFamily("Bahnschrift");
    return font;
}
