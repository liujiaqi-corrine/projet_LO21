#include "Automate.h"

Automate::Automate() : QWidget()
{
    setMinimumSize(600,600);
    setWindowTitle("Automate en Y");

    added = 0;

    b_modele = new QPushButton("Modele",this);
    b_voisinage = new QPushButton("Afficher Voisinage",this);

    grille = new Grid(10,10,this);

    QVBoxLayout *principal = new QVBoxLayout;
        principal->addWidget(b_modele);
        principal->addWidget(b_voisinage);
        principal->addWidget(grille);

    setLayout(principal);

    QObject::connect(b_modele,&QPushButton::clicked,this,&Automate::defineModel);
    QObject::connect(b_voisinage,&QPushButton::clicked,this,&Automate::displaySurrounding);

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

    //Creation du Modele selon les infos récupérés dans defineState
    if(added==0) {
        model = new Model(nom->text(),nb->value());
        grille->setModele(model);
    }

    //Ajout de l'Etat récupérés dans l'appel à defineStates précedent
    if(added>0) model->getListStates()[added-1] = new State(added-1,*couleur,label->text());

    if (added==nb->value()) {
        this->defineSurrounding();
        return;
    }


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


void Automate::defineSurrounding(){

    //added=0; pour pouvoir recreer un modele
    nom = new QLineEdit;
    nb = new QSpinBox;
        nb->setMaximum(5);
        nb->setMinimum(3);

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
       infos->setWindowTitle("Définition du Voisinage");
       infos->setModal(true);
       infos->setLayout(vertical);
       infos->show();

   QObject::connect(suivant,&QPushButton::clicked,this,&Automate::drawSurrounding);
   QObject::connect(suivant,&QPushButton::clicked,infos,&QDialog::close);
   QObject::connect(annuler,&QPushButton::clicked,infos,&QDialog::close);

}

void Automate::drawSurrounding(){


    model->setVoisinage(nb->value()*2-1);

    QGroupBox* texte = new QGroupBox("Definissez le voisinage de la cellule centrale :");
    QPushButton *valider = new QPushButton("Valider");

    Grid* voisins = new Grid(model->getVoisinage()->getDiametre(),model->getVoisinage()->getDiametre(),texte);
    voisins->setModele(new Model());
    //voisins->item(nb->value()/2+1, nb->value()/2+1)->setBackground(QBrush(QColor(Qt::black)));

    QHBoxLayout *boutons = new QHBoxLayout;
        boutons->addWidget(valider);

   QVBoxLayout *vertical = new QVBoxLayout;
      vertical->addWidget(texte);
      vertical->addWidget(voisins);
      vertical->addLayout(boutons);

   infos = new QDialog(this);
       infos->setWindowTitle("Définition du Voisinage");
       infos->setModal(true);
       infos->setLayout(vertical);
       infos->show();

   QObject::connect(valider,&QPushButton::clicked,infos,&QDialog::close);
   QObject::connect(voisins,&Grid::cellClicked,model->getVoisinage(),&Surrounding::setInteractable);
   QObject::connect(voisins,&Grid::cellClicked,this,&Automate::displaySurrounding);

}

void Automate::displaySurrounding(){

    QPushButton *terminer = new QPushButton("Terminer");

    Grid* voisins = new Grid(grille->getModel()->getVoisinage()->getDiametre(),grille->getModel()->getVoisinage()->getDiametre(),this);
    voisins->setModele(new Model());
    for (int i=0; i<voisins->rowCount(); i++){
        for (int j=0; j<voisins->columnCount(); j++){
            if (grille->getModel()->getVoisinage()->getInteractable()[voisins->rowCount()*i+j] == true )
                voisins->getlistCells()[i][j]->setBackground(QBrush(QColor(Qt::black)));
        }
    }

    QHBoxLayout *boutons = new QHBoxLayout;
        boutons->addWidget(terminer);

   QVBoxLayout *vertical = new QVBoxLayout;
      vertical->addWidget(voisins);
      vertical->addLayout(boutons);

   infos = new QDialog(this);
       infos->setWindowTitle("Affichage du Voisinage");
       infos->setModal(true);
       infos->setLayout(vertical);
       infos->show();

   QObject::connect(terminer,&QPushButton::clicked,infos,&QDialog::close);

}


