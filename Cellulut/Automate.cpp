#include "Automate.h"

/*#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>*/


Automate::Automate() : QWidget()
{
    setMinimumSize(600,600);
    setWindowTitle("Automate à l'envers");

    added = 0;

    b_modele = new QPushButton("Modele",this);
    b_voisinage = new QPushButton("Voisinage",this);

    grille = new Grid(10,10,this);

    QVBoxLayout *principal = new QVBoxLayout;
        principal->addWidget(b_modele);
        principal->addWidget(b_voisinage);
        principal->addWidget(grille);

    setLayout(principal);

    QObject::connect(b_modele,&QPushButton::clicked,this,&Automate::defineModel);
    QObject::connect(b_voisinage,&QPushButton::clicked,this,&Automate::defineSurrounding);

}


void Automate::defineSurrounding(){

    nom = new QLineEdit;
    nb = new QSpinBox;
        nb->setMaximum(3);
        nb->setMinimum(1);

    QPushButton *annuler = new QPushButton("Annuler");
    QPushButton *suivant = new QPushButton("Suivant");

    QHBoxLayout *boutons = new QHBoxLayout;
        boutons->addWidget(annuler);
        boutons->addWidget(suivant);

    QFormLayout *form = new QFormLayout;
      form->addRow("Nom:", nom);
      form->addRow("Rayon :", nb);

   QVBoxLayout *vertical = new QVBoxLayout;
      vertical->addLayout(form);
      vertical->addLayout(boutons);

   infos = new QDialog(this);
       infos->setWindowTitle("Ajout d'un Voisinage");
       infos->setModal(true);
       infos->setLayout(vertical);
       infos->show();

   QObject::connect(suivant,&QPushButton::clicked,this,&Automate::drawSurrounding);
   QObject::connect(annuler,&QPushButton::clicked,infos,&QDialog::close);

}

void Automate::drawSurrounding(){

    infos->close();

    QTextEdit texte;
    texte.setText("Definissez le voisinage pour la cellule noire :");


    QPushButton *valider = new QPushButton("Valider");

    Grid* voisins = new Grid(2*nb->value()+1,2*nb->value()+1,this);
    voisins->setModele(new Model());
    voisins->item(nb->value()/2+1, nb->value()/2+1)->setBackground(QBrush(QColor(Qt::black)));
    voisins->item(nb->value()/2+1, nb->value()/2+1)->setFlags(Qt::NoItemFlags);

    QHBoxLayout *boutons = new QHBoxLayout;
        boutons->addWidget(valider);

   QVBoxLayout *vertical = new QVBoxLayout;
      vertical->addWidget(voisins);
      vertical->addLayout(boutons);

   infos = new QDialog(this);
       infos->setWindowTitle("Ajout d'un Voisinage");
       infos->setModal(true);
       infos->setLayout(vertical);
       infos->show();

   QObject::connect(valider,&QPushButton::clicked,infos,&QDialog::close);

}

void Automate::defineModel(){

    nom = new QLineEdit;
    nb = new QSpinBox;
        nb->setMaximum(8);
        nb->setMinimum(2);

    QPushButton *annuler = new QPushButton("Annuler");
    QPushButton *suivant = new QPushButton("Suivant");

    QHBoxLayout *boutons = new QHBoxLayout;
        boutons->addWidget(annuler);
        boutons->addWidget(suivant);

    QFormLayout *form = new QFormLayout;
        form->addRow("Nom du Modele:", nom);
        form->addRow("Nombre d'etats:", nb);

    QVBoxLayout *vertical = new QVBoxLayout;
        vertical->addLayout(form);
        vertical->addLayout(boutons);

    infos = new QDialog(this);
        infos->setWindowTitle("Ajout d'un Modele");
        infos->setModal(true);
        infos->setLayout(vertical);
        infos->show();

    QObject::connect(suivant,&QPushButton::clicked,this,&Automate::defineStates);
    QObject::connect(annuler,&QPushButton::clicked,infos,&QDialog::close);

}


void Automate::defineStates(){

    infos->close();

    if(added==0) {
        model = new Model(nom->text(),nb->value());
        grille->setModele(model);
    }

    if(added>0) model->getListStates()[added-1] = new State(added-1,*couleur,label->text());

    if (added==nb->value()) return;

    added++;

    label = new QLineEdit;
    color = new QPushButton("Couleur");

    QPushButton *suivant = new QPushButton("Suivant");

    QFormLayout *form = new QFormLayout;
        form->addRow("label:", label);
        form->addRow("Couleur:", color);

    QVBoxLayout *vertical = new QVBoxLayout;
        vertical->addLayout(form);
        vertical->addWidget(suivant);

    infos = new QDialog(this);
        QString concat = "Definir Etat n°" + QString::number(added);
        infos->setWindowTitle(concat);
        infos->setModal(true);
        infos->setLayout(vertical);
        infos->show();

    QObject::connect(suivant,&QPushButton::clicked,this,&Automate::defineStates);
    //QObject::connect(suivant,&QPushButton::clicked,grille,&Grid::deblockCells);*
    QObject::connect(color,&QPushButton::clicked,this,&Automate::defineColor);


}

void Automate::defineColor(){

    QColor cou = QColorDialog::getColor(Qt::white, this);
    couleur = new QColor(cou);

    QPalette palette;
    palette.setColor(QPalette::ButtonText, cou);
    color->setPalette(palette);

}
