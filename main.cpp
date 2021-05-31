#include <QApplication>
#include "Automate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Automate simulateur;
    simulateur.show();

    return a.exec();
}
