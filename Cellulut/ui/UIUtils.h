#ifndef UIUTILS_H
#define UIUTILS_H

#include "main.h"

/*!
 *  \file UIUtils.h
 *  This file contains the UIUtils class
 */

/*!
 * \brief The UIUtils class
 */

class UIUtils
{
    public:
        UIUtils();
        static QLabel* createLabel(const QString &text, int fontSize,bool isBold = false, bool isItalic = false, QFont::Capitalization cap = QFont::Capitalization::MixedCase);
        static QPushButton *createButton(const QString &text, int fontSize = 15, bool isBold =true, bool isItalic = false, QFont::Capitalization cap = QFont::Capitalization::AllUppercase);
        static QFont getFont(int fontSize = 12,bool isBold = false, bool isItalic = false, QFont::Capitalization cap = QFont::Capitalization::MixedCase);
};

#endif // UIUTILS_H
