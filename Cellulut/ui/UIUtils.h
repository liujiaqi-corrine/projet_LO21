#ifndef UIUTILS_H
#define UIUTILS_H

#include "main.h"

class UIUtils
{
    public:
        UIUtils();
        static QLabel* createLabel(const QString &text, int fontSize,bool isBold = false, bool isItalic = false, QFont::Capitalization cap = QFont::Capitalization::MixedCase);
        static QFont getFont(int fontSize = 12,bool isBold = false, bool isItalic = false, QFont::Capitalization cap = QFont::Capitalization::MixedCase);
};

#endif // UIUTILS_H
