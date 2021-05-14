#include <QApplication>

#include "Cell.h"
#include "Grid.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget fenetre;
    fenetre.setMinimumSize(600,600);

    Grid *grille = new Grid(10,10,&fenetre); //pourquoi il faut la lier à la fenetre pour l'afficher en plus du layout?

    QPushButton *modele = new QPushButton;
    modele->setText("Modele");

    QVBoxLayout *principal = new QVBoxLayout;
    principal->addWidget(modele);
    principal->addWidget(grille);

    fenetre.setLayout(principal);

    fenetre.show();

    return a.exec();
}
