#include "Automate.h"



Automate::Automate() : QWidget()
{
    added = 0;

    b_library = new QPushButton("Bibliothèque",this);
    b_voisinage = new QPushButton("Afficher Voisinage",this);

    lib = new Library;
    grille = new Grid(10,10,this);

    drawInterface();

}

void Automate::drawInterface(){

    setMinimumSize(600,600);
    setWindowTitle("Automate en Y");

    QVBoxLayout *principal = new QVBoxLayout;
        principal->addWidget(b_library);
        principal->addWidget(b_voisinage);
        principal->addWidget(grille);

    setLayout(principal);

    QObject::connect(b_library,&QPushButton::clicked,this,&Automate::chooseModel);
    QObject::connect(b_voisinage,&QPushButton::clicked,this,&Automate::displaySurrounding);

}

void Automate::chooseModel(){

    QLCDNumber* nombre = new QLCDNumber ;
    nombre->display((int) lib->getListModels().size());

    list = new QComboBox;
    for (unsigned long long i=0;i<lib->getListModels().size();i++) list->addItem(lib->getListModels()[i]->getName());


    QPushButton *annuler = new QPushButton("Annuler");
    QPushButton *valider = new QPushButton("Valider");
    QPushButton *creer = new QPushButton("Créer");

    QHBoxLayout *boutons = new QHBoxLayout;
        boutons->addWidget(annuler);
        boutons->addWidget(valider);

    QFormLayout *form = new QFormLayout;
        form->addRow("Nombre de modele:", nombre);
        form->addRow("Choix du Modele:", list);
        form->addRow("Ajout d'un modele:", creer);

    QVBoxLayout *vertical = new QVBoxLayout;
        vertical->addLayout(form);
        vertical->addLayout(boutons);

    infos = new QDialog(this);
        infos->setWindowTitle("Choix d'un Modele");
        infos->setModal(true);
        infos->setLayout(vertical);
        infos->show();

    QObject::connect(valider,&QPushButton::clicked,this,&Automate::applyModel);
    QObject::connect(valider,&QPushButton::clicked,infos,&QDialog::close);
    QObject::connect(creer,&QPushButton::clicked,this,&Automate::defineModel);
    QObject::connect(creer,&QPushButton::clicked,infos,&QDialog::close);
    QObject::connect(annuler,&QPushButton::clicked,infos,&QDialog::close);
    QObject::connect(annuler,&QPushButton::clicked,this,&Automate::liberateDialog);



}

void Automate::applyModel(){

    lib->setCurrentModel(list->currentIndex());
    grille->resetGrid();

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
    QObject::connect(suivant,&QPushButton::clicked,infos,&QDialog::close);
    QObject::connect(annuler,&QPushButton::clicked,infos,&QDialog::close);
    QObject::connect(annuler,&QPushButton::clicked,this,&Automate::liberateDialog);

}


void Automate::defineStates(){

    //Creation du Modele selon les infos récupérés dans defineState
    if(added==0) {
        lib->addModel(nom->text(),nb->value()); //Le modele est ajouté à la fin de la liste
        //model = new Model(nom->text(),nb->value());
        //lib->addModel(model);
        //grille->setModele(model);
    }

    //Ajout de l'Etat récupérés dans l'appel à defineStates précedent
    if(added>0) lib->getListModels()[lib->getListModels().size()-1]->getListStates()[added-1] = new State(added-1,QColor(*couleur),label->text());

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
    QObject::connect(suivant,&QPushButton::clicked,infos,&QDialog::close);
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
        nb->setMaximum(4);
        nb->setMinimum(2);

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


    lib->getListModels()[lib->getListModels().size()-1]->setVoisinage(nb->value()*2-1);

    QGroupBox* texte = new QGroupBox("Definissez le voisinage de la cellule centrale :");
    QPushButton *valider = new QPushButton("Valider");

    Grid* voisins = new Grid(nb->value()*2-1,texte);
    //voisins->setModele(new Model());
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
   QObject::connect(voisins,&Grid::cellClicked,lib->getListModels()[lib->getListModels().size()-1]->getVoisinage(),&Surrounding::setInteractable);
   //QObject::connect(voisins,&Grid::cellClicked,this,&Automate::displaySurrounding);
   QObject::connect(valider,&QPushButton::clicked,this,&Automate::chooseModel);
   //QObject::connect(valider,&QPushButton::clicked,this,&Automate::liberateDialog);

}

void Automate::displaySurrounding(){

    QPushButton *terminer = new QPushButton("Terminer");

    //Grid* voisins = new Grid(grille->getParent()->getLib()->getCurrentModel()->getVoisinage()->getDiametre(),grille->getParent()->getLib()->getCurrentModel()->getVoisinage()->getDiametre(),this);
    //voisins->setModele(new Model());
    Grid* voisins = new Grid(grille->getParent()->getLib()->getCurrentModel()->getVoisinage()->getDiametre(),this);
    for (int i=0; i<voisins->rowCount(); i++){
        for (int j=0; j<voisins->columnCount(); j++){
            if (grille->getParent()->getLib()->getCurrentModel()->getVoisinage()->getInteractable()[voisins->rowCount()*i+j] == true )
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

void Automate::liberateDialog(){

    //added=0; ajouter apres pour pouvoir recreer un modele

    delete infos;
    delete nom;
    delete nb;
    delete color;
    delete couleur;
    delete label;
    //delete list;



}

