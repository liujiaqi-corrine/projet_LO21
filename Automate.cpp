#include "Automate.h"
#include <windows.h>

Automate::Automate() : QWidget()
{
    added = 0; //les deux added seront unissables apres, la maintenant flemme
    ran = 0;
    total_ran = 0;


    b_library = new QPushButton("Bibliothèque",this);
    b_voisinage = new QPushButton("Afficher Voisinage",this);
    b_surrounding = new QPushButton("Choisir Voisinage",this);
    b_rules = new QPushButton("Definir règles",this);
    b_next = new QPushButton("Grille suivante",this);
    b_reset = new QPushButton("Reset",this);
    b_run = new QSpinBox();
        b_run->setMinimum(1);
    b_number = new QLCDNumber();
    b_config = new QPushButton("Ajouter Config");
    b_intension = new QPushButton("Ajouter Intension");
    b_random = new QPushButton("Grille aléatoire");

    lib = new Library;
    grille = new Grid(10,10,this);

    drawInterface();

}


void Automate::generateRandomGrid(){

    Cell*** nextCells = new Cell**[grille->rowCount()];
    for (int i=0; i<grille->rowCount(); i++){
        nextCells[i] = new Cell*[grille->columnCount()];
        for (int j=0; j<grille->columnCount(); j++){
            nextCells[i][j] = new Cell(i,j);
            nextCells[i][j]->setState(lib->getCurrentModel()->getListStates()[QRandomGenerator::global()->bounded(0,lib->getCurrentModel()->getNbState())]);
        }
    }

    grille->updateGrid(nextCells);

}

void Automate::drawInterface(){

    setMinimumSize(600,600);
    setWindowTitle("Automate en Y");

    QHBoxLayout *run = new QHBoxLayout;
        run->addWidget(b_next);
        run->addWidget(b_run);

    QVBoxLayout *principal = new QVBoxLayout;
        principal->addWidget(b_library);
        principal->addWidget(b_surrounding);
        principal->addWidget(b_voisinage);
        principal->addWidget(b_rules);
        principal->addWidget(b_intension);
        principal->addWidget(b_config);
        principal->addWidget(b_reset);
        principal->addLayout(run);
        principal->addWidget(b_number);
        principal->addWidget(b_random);
        principal->addWidget(grille);

    setLayout(principal);

    QObject::connect(b_library,&QPushButton::clicked,this,&Automate::chooseModel);
    QObject::connect(b_voisinage,&QPushButton::clicked,this,&Automate::displaySurrounding);
    QObject::connect(b_surrounding,&QPushButton::clicked,this,&Automate::chooseSurrounding);
    //QObject::connect(b_rules,&QPushButton::clicked,this,&Automate::chooseRules);
    QObject::connect(b_next,&QPushButton::clicked,this,&Automate::run);
    QObject::connect(b_reset,&QPushButton::clicked,this,&Automate::reset);
    QObject::connect(b_config,&QPushButton::clicked,this,&Automate::drawConfig);
    QObject::connect(b_intension,&QPushButton::clicked,this,&Automate::defineRuleIntension);
    QObject::connect(b_random,&QPushButton::clicked,this,&Automate::generateRandomGrid);


}


void Automate::run(){

    if (!lib->getCurrentModel()->getVoisinage()){
        QMessageBox::critical(this, "Avertissement", "Vous n'avez pas defini de voisinage pour le modele" + lib->getCurrentModel()->getName());
        return;
    }

    if (!lib->getCurrentModel()->getRule() && !lib->getCurrentModel()->getRuleExtension()){
        QMessageBox::critical(this, "Avertissement", "Vous n'avez aucune règle pour le modele" + lib->getCurrentModel()->getName());
        return;
    }

    if (ran <  b_run->value()){

       b_number->setDisabled(true);
       qDebug("run");
       total_ran++;
       b_number->display(total_ran);
       ran++;

       //Allocation Memoire
       Cell*** nextCells = new Cell**[grille->rowCount()];  //on garce Cell*** pour rester coherant avec grid.h
       for (int i=0; i<grille->rowCount(); i++){
           nextCells[i] = new Cell*[grille->columnCount()];
           for (int j=0; j<grille->columnCount(); j++)
               nextCells[i][j] = new Cell(i,j); // New Cells pour l'history
       }

       State* state = nullptr;
       for (int i=0; i<grille->rowCount(); i++){ //pour chaque cellule de la grille
           for(int j=0; j<grille->columnCount(); j++){
               if ((state = nextIntension(i,j))) nextCells[i][j]->setState(state);
                else if ((state = nextConfig(i,j))) nextCells[i][j]->setState(state);
                        else nextCells[i][j]->setState(grille->getlistCells()[i][j]->getState());
           }
       }

       grille->updateGrid(nextCells);
       QTimer::singleShot(1000, this, &Automate::run);

    } else {
        b_number->setDisabled(false);
        ran = 0;
    }


}

State* Automate::nextIntension(int i, int j){

    if (!lib->getCurrentModel()->getRule()) return nullptr;

    qDebug("nextIntension");

    int rayon = lib->getCurrentModel()->getVoisinage()->getDiametre()/2;
    int diametre = lib->getCurrentModel()->getVoisinage()->getDiametre();
    int* compteur = new int[lib->getCurrentModel()->getNbState()];

            //Remise à 0 du compteur
            for(int y=0; y<lib->getCurrentModel()->getNbState(); y++) compteur[y]=0;

            bool verif = false;


            int k=((grille->rowCount() + ((i-rayon) % grille->rowCount())) % grille->rowCount());
            int cptk = 0;
            do
            {
                int cptl =0;
                int l=((grille->columnCount() + ((j-rayon) % grille->columnCount())) % grille->columnCount());
                do{
                    //Si fait partie du voisinage + compte le nombre de voisins/etats
                    if (lib->getCurrentModel()->getVoisinage()->getInteractable()[diametre*cptk+cptl])
                        compteur[grille->getlistCells()[k][l]->getState()->getIndex()]++;

                    l++;
                    l = l%grille->columnCount();
                    cptl++;

                } while (cptl<diametre);
                k++;
                k = k%grille->rowCount();
                cptk++;
            } while (cptk<diametre);

            //on connait maintenant les voisins de la cellule [i,j]
            //Verification correspondances des Regles
            for (int z=0; z<lib->getCurrentModel()->getNbState(); z++){ //pour chaque etat
                for (int a=0; a< (int) lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->size(); a++){ // on recupere le nombre de conditions de z, si 0 pas de boucle
                    if (compteur[lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).index_comptant] <= lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).max)
                    if (compteur[lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).index_comptant] >= lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).min)
                    {  return lib->getCurrentModel()->getListStates()[z];
                        verif = true;
                        break;}

                }
                if (verif) break;
            }
            if (!verif) return nullptr;

}

State* Automate::nextConfig(int i, int j){

    if (!lib->getCurrentModel()->getRuleExtension()) return nullptr;

    qDebug("nextConfig");
    int rayon = lib->getCurrentModel()->getVoisinage()->getDiametre()/2;
    int diametre = lib->getCurrentModel()->getVoisinage()->getDiametre();


            bool verif2 = false; //si il a aucune config
            for(int z=0; z< (int) lib->getCurrentModel()->getRuleExtension()->getConfigs(grille->getlistCells()[i][j]->getState()->getIndex()).size(); z++){ //pour chaque config de l'etat de la cellule
                verif2 = true;

                // On verifie pour tous les voisins si les positions correspondent à la configuration
                int k=((grille->rowCount() + ((i-rayon) % grille->rowCount())) % grille->rowCount());
                int cptk = 0;
                do
                { //pour chaque voisin
                    int cptl =0;
                    int l=((grille->columnCount() + ((j-rayon) % grille->columnCount())) % grille->columnCount());
                    do{

                        if (lib->getCurrentModel()->getVoisinage()->getInteractable()[diametre*cptk+cptl]) //Le voisin est concerné != 0
                        if (lib->getCurrentModel()->getRuleExtension()->getConfigs(grille->getlistCells()[i][j]->getState()->getIndex()).operator[](z).getEnvironment()[diametre*cptk+cptl] != grille->getlistCells()[k][l]->getState()->getIndex()){
                            verif2 = false;
                        }

                        l++;
                        l = l%grille->columnCount();
                        cptl++;

                    } while (cptl<diametre);
                    k++;
                    k = k%grille->rowCount();
                    cptk++;
                } while (cptk<diametre);
                if (verif2) { // si tous les voisins correspondent à la config
                    return lib->getCurrentModel()->getListStates()[lib->getCurrentModel()->getRuleExtension()->getConfigs(grille->getlistCells()[i][j]->getState()->getIndex()).operator[](z).getCentral()];
                }

            }
            if (!verif2) return nullptr;
}

void Automate::defineRuleIntension(){ //Pour l'instant on crée les regles pour le modele courant

        QPushButton *suivant = new QPushButton("Autre Regle");
        QPushButton *terminer = new QPushButton("Terminer");

        nb = new QSpinBox;
            nb->setMinimum(-1); // -1 pour ne pas prendre en compte un etat particulier
            nb->setMaximum(lib->getCurrentModel()->getVoisinage()->getDiametre()*lib->getCurrentModel()->getVoisinage()->getDiametre()-1);
            nb->setValue(0);

        nb1 = new QSpinBox;
            nb1->setMinimum(-1); // -1 pour ne pas prendre en compte un etat particulier
            nb1->setMaximum(lib->getCurrentModel()->getVoisinage()->getDiametre()*lib->getCurrentModel()->getVoisinage()->getDiametre()-1);
            nb1->setValue(nb1->maximum());

        list = new QComboBox;
        for (int i=0;i<lib->getCurrentModel()->getNbState();i++) list->addItem(lib->getCurrentModel()->getListStates()[i]->getLabel());

        list1 = new QComboBox;
        for (int i=0;i<lib->getCurrentModel()->getNbState();i++) list1->addItem(lib->getCurrentModel()->getListStates()[i]->getLabel());

        list2 = new QComboBox;
        for (int i=0;i<lib->getCurrentModel()->getNbState();i++) list2->addItem(lib->getCurrentModel()->getListStates()[i]->getLabel());

        QFormLayout *form = new QFormLayout;
            form->addRow("La Cellule:",list);
            form->addRow("Se transformera en:",list1);
            form->addRow("Min :",nb);
            form->addRow("Max :",nb1);
            form->addRow("de cellules:",list2);

        QVBoxLayout *vertical = new QVBoxLayout;
            vertical->addLayout(form);
            vertical->addWidget(suivant);
            vertical->addWidget(terminer);

        infos = new QDialog(this);
            infos->setWindowTitle("Définition de regle Intension pour "+lib->getCurrentModel()->getName());
            infos->setModal(true);
            infos->setLayout(vertical);
            infos->show();

        QObject::connect(suivant,&QPushButton::clicked,infos,&QDialog::close);
        QObject::connect(suivant,&QPushButton::clicked,this,&Automate::validateRuleIntension);
        QObject::connect(suivant,&QPushButton::clicked,this,&Automate::defineRuleIntension);
        QObject::connect(terminer,&QPushButton::clicked,infos,&QDialog::close);
        QObject::connect(terminer,&QPushButton::clicked,this,&Automate::validateRuleIntension);

}

void Automate::validateRuleIntension(){

    if (!lib->getCurrentModel()->getRule())
            lib->getCurrentModel()->setRule(new Rule_Intension(nom->text(),lib->getCurrentModel(),lib->getCurrentModel()->getNbState()));

    lib->getCurrentModel()->getRule()->setVoisins(list->currentIndex(),list1->currentIndex(),list2->currentIndex(),nb->value(),nb1->value()) ; //;

}


void Automate::reset(){

    total_ran = 0;
    b_number->display(total_ran);
    grille->resetGrid();

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
    //QObject::connect(annuler,&QPushButton::clicked,this,&Automate::liberateDialog);



}

void Automate::applyModel(){

    lib->setCurrentModel(list->currentIndex());
    reset();

}

void Automate::applySurrounding(){
    lib->getCurrentModel()->setVoisinage(lib->getListSurrounding()[list->currentIndex()]);
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

}


void Automate::defineStates(){

    //Creation du Modele selon les infos récupérés dans defineState
    if(added==0)
        lib->addModel(nom->text(),nb->value()); //Le modele est ajouté à la fin de la liste


    //Ajout de l'Etat récupérés dans l'appel à defineStates précedent
    if(added>0) lib->getListModels()[lib->getListModels().size()-1]->getListStates()[added-1] = new State(added-1,QColor(*couleur),label->text());

    if (added==nb->value())
        return;



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

    label->setText(QString::number(added-1));
    couleur = new QColor(Qt::white);

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

void Automate::drawConfig(){

    QGroupBox* texte = new QGroupBox("se transformera en cellule central");
    QPushButton *valider = new QPushButton("Valider");
    QPushButton *annuler = new QPushButton("Annuler");

    list = new QComboBox;
    for (int i=0; i<lib->getCurrentModel()->getNbState();i++) list->addItem(lib->getCurrentModel()->getListStates()[i]->getLabel());


    voisins = new Grid(lib->getCurrentModel()->getVoisinage()->getDiametre(),this);

    QHBoxLayout *boutons = new QHBoxLayout;
        boutons->addWidget(annuler);
        boutons->addWidget(valider);


   QVBoxLayout *vertical = new QVBoxLayout;
      vertical->addWidget(list);
      vertical->addWidget(texte);
      vertical->addWidget(voisins);
      vertical->addLayout(boutons);

   infos = new QDialog(this);
       infos->setWindowTitle("Définition d'une ");
       infos->setModal(true);
       infos->setLayout(vertical);
       infos->show();

   QObject::connect(valider,&QPushButton::clicked,infos,&QDialog::close);
   QObject::connect(valider,&QPushButton::clicked,this,&Automate::validateConfig);
   QObject::connect(annuler,&QPushButton::clicked,infos,&QDialog::close);
}

void Automate::validateConfig(){

    if (!lib->getCurrentModel()->getRuleExtension()){
        qDebug("ValidateConfig creation ruleExtension");
        lib->getCurrentModel()->setRuleExtension(new Rule_Extension(lib->getCurrentModel()->getNbState()));}

    Config* conf = new Config(lib->getCurrentModel()->getVoisinage()->getDiametre());

    for (int i=0; i<lib->getCurrentModel()->getVoisinage()->getDiametre(); i++)
        for (int j=0; j<lib->getCurrentModel()->getVoisinage()->getDiametre(); j++){
            conf->setEnvironment(i,j,voisins->getlistCells()[i][j]->getState()->getIndex());
            qDebug("%d %d -> %d",i,j,voisins->getlistCells()[i][j]->getState()->getIndex());
            qDebug("diametre/2 : %d",lib->getCurrentModel()->getVoisinage()->getDiametre()/2);
            qDebug("Central : %d",conf->getCentral());
        }

    lib->getCurrentModel()->getRuleExtension()->addConfig(list->currentIndex(),conf);
}


void Automate::chooseSurrounding(){

    added=0; //pour pouvoir recreer un modele

    QLCDNumber* nombre = new QLCDNumber ;
    nombre->display((int) lib->getListSurrounding().size());

    list = new QComboBox;
    for (unsigned long long i=0;i<lib->getListSurrounding().size();i++) list->addItem(lib->getListSurrounding()[i]->getName());

    QPushButton *annuler = new QPushButton("Annuler");
    QPushButton *valider = new QPushButton("Valider");
    QPushButton *creer = new QPushButton("Créer");

    QHBoxLayout *boutons = new QHBoxLayout;
        boutons->addWidget(annuler);
        boutons->addWidget(valider);

    QFormLayout *form = new QFormLayout;
        form->addRow("Nombre de Voisinage:", nombre);
        form->addRow("Choix du Voisinage:", list);
        form->addRow("Ajout d'un Voisinage:", creer);

    QVBoxLayout *vertical = new QVBoxLayout;
        vertical->addLayout(form);
        vertical->addLayout(boutons);

    infos = new QDialog(this);
        infos->setWindowTitle("Choix d'un Voisinage pour "+lib->getCurrentModel()->getName());
        infos->setModal(true);
        infos->setLayout(vertical);
        infos->show();

    QObject::connect(valider,&QPushButton::clicked,this,&Automate::applySurrounding);
    //QObject::connect(valider,&QPushButton::clicked,this,&Automate::chooseRules);
    QObject::connect(valider,&QPushButton::clicked,infos,&QDialog::close);
    QObject::connect(creer,&QPushButton::clicked,this,&Automate::defineSurrounding);
    QObject::connect(creer,&QPushButton::clicked,infos,&QDialog::close);
    QObject::connect(annuler,&QPushButton::clicked,infos,&QDialog::close);

}

void Automate::drawSurrounding(){

    QGroupBox* texte = new QGroupBox("Definissez le voisinage de la cellule centrale :");
    QPushButton *valider = new QPushButton("Valider");

    voisins = new Grid(nb->value(),this);

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
   //QObject::connect(valider,&QPushButton::clicked,this,&Automate::defineRules);
   //QObject::connect(voisins,&Grid::cellClicked,this,&Automate::cellToStateMethod);
   //QObject::connect(this,&Automate::cellToState,lib->getCurrentModel()->getVoisinage(),&Surrounding::setInteractable);
   //QObject::connect(valider,&QPushButton::clicked,this,&Automate::chooseSurrounding);
   QObject::connect(valider,&QPushButton::clicked,this,&Automate::validateSurrounding);
   //QObject::connect(valider,&QPushButton::clicked,this,&Automate::liberateDialog);
}

void Automate::validateSurrounding(){

    lib->addSurrounding(nb->value(),nom->text());

    for (int i=0; i<lib->getListSurrounding()[lib->getListSurrounding().size()-1]->getDiametre(); i++)
        for (int j=0; j<lib->getListSurrounding()[lib->getListSurrounding().size()-1]->getDiametre(); j++)
            lib->getListSurrounding()[lib->getListSurrounding().size()-1]->setInteractable(i,j,voisins->getlistCells()[i][j]->getState()->getIndex());

    chooseSurrounding();

}

void Automate::displaySurrounding(){

    QPushButton *terminer = new QPushButton("Terminer");

    //Grid* voisins = new Grid(grille->getParent()->getLib()->getCurrentModel()->getVoisinage()->getDiametre(),grille->getParent()->getLib()->getCurrentModel()->getVoisinage()->getDiametre(),this);
    //voisins->setModele(new Model());
    Grid* voisins = new Grid(lib->getCurrentModel()->getVoisinage()->getDiametre(),this);
    for (int i=0; i<voisins->rowCount(); i++){
        for (int j=0; j<voisins->columnCount(); j++){
                qDebug("%d",lib->getCurrentModel()->getVoisinage()->getInteractable()[lib->getCurrentModel()->getVoisinage()->getDiametre()*i+j]);
                voisins->getlistCells()[i][j]->setBackground(QBrush(lib->getCurrentModel()->getListStates()[lib->getCurrentModel()->getVoisinage()->getInteractable()[lib->getCurrentModel()->getVoisinage()->getDiametre()*i+j]]->getColor()));
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

void Automate::cellToStateMethod(int row, int column){

    //Necessite verificate pour savoir si il envoie la cellule modifie pour la cellule initial
    emit cellToState(row,column,grille->getlistCells()[row][column]->getState()->getIndex()%lib->getCurrentModel()->getNbState());

}


