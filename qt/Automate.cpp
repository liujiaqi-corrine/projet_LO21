#include "Automate.h"
#include <windows.h>

Automate::Automate() : QWidget()
{
    added = 0; //les deux added seront unissables apres, la maintenant flemme
    added_rules = 0;
    added_states=0;
    ran = 0;
    total_ran = 0;

    strt=false;

    b_library = new QPushButton("Bibliothèque",this);
    b_voisinage = new QPushButton("Afficher Voisinage",this);
    b_rules = new QPushButton("Definir règles",this);
    b_next = new QPushButton("Grille suivante",this);
    b_reset = new QPushButton("Reset",this);
    b_run = new QSpinBox();
        b_run->setMinimum(1);
    b_number = new QLCDNumber();
    b_config = new QPushButton("Ajouter Config");
    b_random = new QPushButton("Grille aléatoire");

    b_start = new QPushButton("commence",this);
    b_stop = new QPushButton("arrête",this);

    lib = new Library;
    grille = new Grid(5,5,this);


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
        principal->addWidget(b_voisinage);
        principal->addWidget(b_rules);
        principal->addWidget(b_config);
        principal->addWidget(b_reset);
        principal->addLayout(run);

        principal->addWidget(b_start);
        principal->addWidget(b_stop);

        principal->addWidget(b_number);
        principal->addWidget(b_random);




        principal->addWidget(grille);


    setLayout(principal);

    QObject::connect(b_library,&QPushButton::clicked,this,&Automate::chooseModel);
    QObject::connect(b_voisinage,&QPushButton::clicked,this,&Automate::displaySurrounding);
    QObject::connect(b_rules,&QPushButton::clicked,this,&Automate::chooseRules);
    QObject::connect(b_next,&QPushButton::clicked,this,&Automate::run);
    QObject::connect(b_reset,&QPushButton::clicked,this,&Automate::reset);
    QObject::connect(b_config,&QPushButton::clicked,this,&Automate::drawConfig);
    QObject::connect(b_random,&QPushButton::clicked,this,&Automate::generateRandomGrid);

    QObject::connect(b_start,&QPushButton::clicked,this,&Automate::run_auto);
    QObject::connect(b_stop,&QPushButton::clicked,this,&Automate::stop_auto);


}


void Automate::run(){
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

void Automate::run_auto(){
    if(strt==true){
        b_number->setDisabled(true);
        qDebug("run");
        total_ran++;
        b_number->display(total_ran);
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

        QObject::connect(b_stop,&QPushButton::clicked,this,&Automate::stop_auto);
        QTimer::singleShot(1000, this, &Automate::run_auto);
    }
    else{
        strt=true;
    }
}

void Automate::stop_auto(){
    strt=false;
}



State* Automate::nextIntension(int i, int j){

    qDebug("Lunchinh of next()");
    /*total_ran++;
    b_number->display(total_ran);
    ran++;
    //Allocation memoire
    Cell*** nextCells = new Cell**[grille->rowCount()];  //on garce Cell*** pour rester coherant avec grid.h
    for (int i=0; i<grille->rowCount(); i++){
        nextCells[i] = new Cell*[grille->columnCount()];
        for (int j=0; j<grille->columnCount(); j++)
            nextCells[i][j] = new Cell(i,j); // New Cells pour l'history
    }*/
    qDebug("nextIntension");
    int rayon = lib->getCurrentModel()->getVoisinage()->getDiametre()/2;
    int diametre = lib->getCurrentModel()->getVoisinage()->getDiametre();
    int* compteur = new int[lib->getCurrentModel()->getNbState()];

    //Calcul //Modulo retourne un negatif si on entre un négatif
    //for (int i=0; i<grille->rowCount(); i++){ //pour chaque cellule de la grille

        //for(int j=0; j<grille->columnCount(); j++){

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

                    //qDebug("%d : %d - %d : %d",i,j,k,l); detection + verif du voisinage OK !
                    //Si fait partie du voisinage + compte le nombre de voisins/etats
                    //qDebug("    Position Voisinage : %d - %d",cptk,cptl);
                    if (lib->getCurrentModel()->getVoisinage()->getInteractable()[diametre*cptk+cptl])
                        //Compter cb de voisins/etat la cellule possede
                        compteur[grille->getlistCells()[k][l]->getState()->getIndex()]++;

                    l++;
                    l = l%grille->columnCount();
                    cptl++;

                } while (cptl<diametre);
                k++;
                k = k%grille->rowCount();
                cptk++;
            } while (cptk<diametre);

            //for(int y=0; y<lib->getCurrentModel()->getNbState(); y++) qDebug("%d : %d - %d : %d",i,j,y,compteur[y]);

            //on connait maintenant les voisins de la cellule [i,j]
            //Verification correspondances des Regles

            for (int z=0; z<lib->getCurrentModel()->getNbState(); z++){ //pour chaque etat
                //qDebug("destination z :%d",z);
                //qDebug("Nombre de regle pour z : %d",(int) lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->size());
                for (int a=0; a< (int) lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->size(); a++){ // on recupere le nombre de conditions de z, si 0 pas de boucle
                    //qDebug("regle en cours d'examen a: %d",a);
                    //qDebug("%d:%d - Regle pour %d - min : %d - max : %d",i,j,lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).index_comptant,lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).min,lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).max);
                    //qDebug("        %d : %d",lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).index_comptant,compteur[lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).index_comptant]);
                    if (compteur[lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).index_comptant] <= lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).max)
                    if (compteur[lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).index_comptant] >= lib->getCurrentModel()->getRule()->getConditions(grille->getlistCells()[i][j]->getState()->getIndex(),z)->operator[](a).min)
                    {   //nextCells[i][j]->setState(lib->getCurrentModel()->getListStates()[z]);
                        return lib->getCurrentModel()->getListStates()[z];
                        verif = true;
                        //qDebug("changement %d:%d",i,j);
                        break;}

                }
                if (verif) break;
            }
            if (!verif) {//nextCells[i][j]->setState(grille->getlistCells()[i][j]->getState());
                        return nullptr;
                        /*qDebug("conservation %d:%d",i,j);*/}
        //}
    //}

    //grille->updateGrid(nextCells);

}

State* Automate::nextConfig(int i, int j){

    if (lib->getCurrentModel()->getRuleExtension()==nullptr) return nullptr;
    /*//Allocation memoire
    Cell*** nextCells = new Cell**[grille->rowCount()];  //on garce Cell*** pour rester coherant avec grid.h
    for (int i=0; i<grille->rowCount(); i++){
        nextCells[i] = new Cell*[grille->columnCount()];
        for (int j=0; j<grille->columnCount(); j++)
            nextCells[i][j] = new Cell(i,j); // New Cells pour l'history
    }*/
    qDebug("nextConfig");
    int rayon = lib->getCurrentModel()->getVoisinage()->getDiametre()/2;
    int diametre = lib->getCurrentModel()->getVoisinage()->getDiametre();

    //Calcul //Attention :Modulo retourne un negatif si on entre un négatif
    /*for (int i=0; i<grille->rowCount(); i++){ //pour chaque cellule de la grille
        for(int j=0; j<grille->columnCount(); j++){*/

            bool verif2 = false; //si il a aucune config
            qDebug("%d-%d -> z %d",i,j,(int) lib->getCurrentModel()->getRuleExtension()->getConfigs(grille->getlistCells()[i][j]->getState()->getIndex()).size());
            for(int z=0; z< (int) lib->getCurrentModel()->getRuleExtension()->getConfigs(grille->getlistCells()[i][j]->getState()->getIndex()).size(); z++){ //pour chaque config de l'etat de la cellule
                qDebug("z %d",z);
                verif2 = true;

                // On verifie pour tous les voisins si les positions correspondent à la configuration
                int k=((grille->rowCount() + ((i-rayon) % grille->rowCount())) % grille->rowCount());
                int cptk = 0;
                do
                { //pour chaque voisin
                    int cptl =0;
                    int l=((grille->columnCount() + ((j-rayon) % grille->columnCount())) % grille->columnCount());
                    do{

                        if (lib->getCurrentModel()->getVoisinage()->getInteractable()[diametre*cptk+cptl]){//qDebug("voisin teste"); //Le voisin est concerné != 0
                        if (lib->getCurrentModel()->getRuleExtension()->getConfigs(grille->getlistCells()[i][j]->getState()->getIndex()).operator[](z).getEnvironment()[diametre*cptk+cptl] != grille->getlistCells()[k][l]->getState()->getIndex()){
                            verif2 = false;
                            //qDebug("%d-%d -> Voisin %d:%d non --> false",i,j,k,l);
                            //break;
                        }}

                        //if (!verif2) break;

                        l++;
                        l = l%grille->columnCount();
                        cptl++;

                    } while (cptl<diametre);
                    //if (!verif2) break;
                    k++;
                    k = k%grille->rowCount();
                    cptk++;
                } while (cptk<diametre);
                if (verif2) { // si tous les voisins correspondent à la config
                    qDebug("%d-%d en %d premier ",i,j,lib->getCurrentModel()->getRuleExtension()->getConfigs(grille->getlistCells()[i][j]->getState()->getIndex()).operator[](z).getCentral());
                    //nextCells[i][j]->setState(lib->getCurrentModel()->getListStates()[lib->getCurrentModel()->getRuleExtension()->getConfigs(grille->getlistCells()[i][j]->getState()->getIndex()).operator[](z).getCentral()]);
                    return lib->getCurrentModel()->getListStates()[lib->getCurrentModel()->getRuleExtension()->getConfigs(grille->getlistCells()[i][j]->getState()->getIndex()).operator[](z).getCentral()];
                    //break;
                } /*else // si la config ne correspondant pas et que c'est la derniere
                if (z < (int) lib->getCurrentModel()->getRuleExtension()->getConfigs(grille->getlistCells()[i][j]->getState()->getIndex()).size()) {nextCells[i][j]->setState(grille->getlistCells()[i][j]->getState());
                    qDebug("%d-%d en %d second",i,j,grille->getlistCells()[i][j]->getState()->getIndex());}*/

            }
            if (!verif2) {/*nextCells[i][j]->setState(grille->getlistCells()[i][j]->getState());qDebug("%d-%d en %d tres",i,j,grille->getlistCells()[i][j]->getState()->getIndex());*/
                            return nullptr;}
        //}
    //}

    //grille->updateGrid(nextCells);
}

void Automate::addConfig(){

    list = new QComboBox;
    for (int i=0;i<lib->getCurrentModel()->getNbState();i++) list->addItem(lib->getCurrentModel()->getListStates()[i]->getLabel());


    QPushButton *annuler = new QPushButton("Annuler");
    QPushButton *valider = new QPushButton("Valider");

    QHBoxLayout *boutons = new QHBoxLayout;
        boutons->addWidget(annuler);
        boutons->addWidget(valider);

    QFormLayout *form = new QFormLayout;
        form->addRow("Ajouter config pour :", list);

    QVBoxLayout *vertical = new QVBoxLayout;
        vertical->addLayout(form);
        vertical->addLayout(boutons);

    infos = new QDialog(this);
        infos->setWindowTitle("Choix d'un Modele");
        infos->setModal(true);
        infos->setLayout(vertical);
        infos->show();

   QObject::connect(valider,&QPushButton::clicked,this,&Automate::defineConfig);
   QObject::connect(valider,&QPushButton::clicked,infos,&QDialog::close);
   QObject::connect(annuler,&QPushButton::clicked,infos,&QDialog::close);

}

void Automate::defineConfig(){

    //lib->getCurrentModel()->setRuleExtension(new Rule_Extension(/*"Nom",lib->getCurrentModel(),*/lib->getCurrentModel()->getNbState()));
    lib->getCurrentModel()->setRuleExtension(new Rule_Extension(/*"Nom",lib->getCurrentModel(),*/lib->getCurrentModel()->getNbState()));

    QPushButton *valider = new QPushButton("Valider");

    Grid* voisins = new Grid(nb->value()*2-1,this);

    QVBoxLayout *vertical = new QVBoxLayout;
        vertical->addWidget(voisins);
        vertical->addWidget(valider);

    infos = new QDialog(this);
        infos->setWindowTitle("Définition du Voisinage");
        infos->setModal(true);
        infos->setLayout(vertical);
        infos->show();

    QObject::connect(valider,&QPushButton::clicked,infos,&QDialog::close);
    //QObject::connect(voisins,&Grid::cellClicked,this,&Automate::setEntourage);
    QObject::connect(valider,&QPushButton::clicked,this,&Automate::chooseModel);

}

/*void Automate::setEntourage(int row, int column){

    lib->getCurrentModel()->getRuleExtension()->getConfigs(list->currentIndex()).operator[](z).getEnvironment()[diametre*k+l];


}*/

void Automate::chooseRules(){


    QPushButton *suivant = new QPushButton("Suivant");
    QPushButton *annuler = new QPushButton("Annuler");

    nom = new QLineEdit;

    r_intension = new QRadioButton("En Intension",this);
    r_extension = new QRadioButton("En Extension",this);

    /*Grid* voisins = new Grid(grille->getParent()->getLib()->getCurrentModel()->getVoisinage()->getDiametre(),this);
    for (int i=0; i<voisins->rowCount(); i++){
        for (int j=0; j<voisins->columnCount(); j++){
            if (grille->getParent()->getLib()->getCurrentModel()->getVoisinage()->getInteractable()[voisins->rowCount()*i+j] == true)
                voisins->getlistCells()[i][j]->setBackground(QBrush(QColor(Qt::black)));
        }
    }*/

    QFormLayout *name = new QFormLayout;
        name->addWidget(nom);

    QVBoxLayout *radio = new QVBoxLayout;
        radio->addWidget(r_intension);
        radio->addWidget(r_extension);

    QHBoxLayout *boutons = new QHBoxLayout;
        boutons->addWidget(annuler);
        boutons->addWidget(suivant);

    QVBoxLayout *vertical = new QVBoxLayout;
        vertical->addLayout(name);
        vertical->addLayout(radio);
        //vertical->addWidget(voisins);
        vertical->addLayout(boutons);

   infos = new QDialog(this);
       infos->setWindowTitle("Définition de la règle");
       infos->setModal(true);
       infos->setLayout(vertical);
       infos->show();


   QObject::connect(suivant,&QPushButton::clicked,this,&Automate::defineRulesStates);
   QObject::connect(suivant,&QPushButton::clicked,infos,&QDialog::close);
   QObject::connect(annuler,&QPushButton::clicked,infos,&QDialog::close);

}


void Automate::defineRules(){

    added_states=0;
    if (r_intension->isChecked() == true){

        // Creation de la regle
        lib->getCurrentModel()->setRule(new Rule_Intension(nom->text(),lib->getCurrentModel(),lib->getCurrentModel()->getNbState()));

        this->setWindowTitle(QString::number(lib->getCurrentModel()->getNbState()));

        for (int i =0; i<lib->getCurrentModel()->getNbState();i++){
            defineRulesStates();
            added_states++;


        }

    }

    /*else
       if (r_extension->isChecked() == true){
           lib->getCurrentModel()->setRule(new Rule_Extension(nom->text(),lib->getCurrentModel()));
           Rules* regle = lib->getCurrentModel()->getRule() ;


       }*/

}

void Automate::defineRulesStates(){ //Pour l'instant on crée les regles pour le modele courant

    /*if (r_intension->isChecked() == true){
        lib->getCurrentModel()->setRule(new Rule_Intension(nom->text(),lib->getCurrentModel(),lib->getCurrentModel()->getNbState()));


        //Ajout à la fin du vector, dans l'ordre de la listStates
        if (added_rules>0)
            lib->getCurrentModel()->getRule()->setVoisins(added_states,nb->value(),nb1->value());

        added_rules++;

        if (added_rules>lib->getCurrentModel()->getNbState()){
            added_rules = 0;
            added_states++;
            if (added_states>=lib->getCurrentModel()->getNbState()){
                    added_states = 0;
                    return;
            }else{
                defineRulesStates();
                return;}
        }


        //Case correspondante à un etat
        QTableWidget* carre = new QTableWidget(1,1,this);
        carre->horizontalHeader()->setVisible(false);
        carre->verticalHeader()->setVisible(false);
        carre->setSelectionMode(QAbstractItemView::SingleSelection);
        carre->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        carre->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        carre->resizeColumnsToContents();
        carre->resizeRowsToContents();
        carre->setItem(0,0, new QTableWidgetItem());
        carre->item(0,0)->setFlags(Qt::NoItemFlags);
        carre->item(0,0)->setBackground(lib->getCurrentModel()->getListStates()[added_rules-1]->getColor());

        QPushButton *suivant = new QPushButton("Suivant");

        nb = new QSpinBox;
            nb->setMinimum(-1); // -1 pour ne pas prendre en compte un etat particulier
            nb->setMaximum(lib->getCurrentModel()->getVoisinage()->getDiametre()*lib->getCurrentModel()->getVoisinage()->getDiametre()-1);
            nb->setValue(0);


        nb1 = new QSpinBox;
            nb1->setMinimum(-1); // -1 pour ne pas prendre en compte un etat particulier
            nb1->setMaximum(lib->getCurrentModel()->getVoisinage()->getDiametre()*lib->getCurrentModel()->getVoisinage()->getDiametre()-1);
            nb1->setValue(nb1->maximum());

        QFormLayout *form = new QFormLayout;
            form->addRow("Min :",nb);
            form->addRow("Max :",nb1);

        QVBoxLayout *vertical = new QVBoxLayout;
            vertical->addWidget(carre);
            vertical->addLayout(form);
            vertical->addWidget(suivant);

        infos = new QDialog(this);
            infos->setWindowTitle("Définition de la règle " + lib->getCurrentModel()->getListStates()[added_states]->getLabel() );
            infos->setModal(true);
            infos->setLayout(vertical);
            infos->show();

        QObject::connect(suivant,&QPushButton::clicked,infos,&QDialog::close);
        QObject::connect(suivant,&QPushButton::clicked,this,&Automate::defineRulesStates);
    }*/
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
    //QObject::connect(annuler,&QPushButton::clicked,this,&Automate::liberateDialog);

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
        //added=0; //pour rajouter d'autre modele apres
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

void Automate::drawSurrounding(){

    QGroupBox* texte = new QGroupBox("Definissez le voisinage de la cellule centrale :");
    QPushButton *valider = new QPushButton("Valider");

    /*Grid**/ voisins = new Grid(nb->value()*2-1,this);
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
   //QObject::connect(valider,&QPushButton::clicked,this,&Automate::defineRules);
   //QObject::connect(voisins,&Grid::cellClicked,this,&Automate::cellToStateMethod);
   //QObject::connect(this,&Automate::cellToState,lib->getCurrentModel()->getVoisinage(),&Surrounding::setInteractable);
   QObject::connect(valider,&QPushButton::clicked,this,&Automate::chooseModel);
   QObject::connect(valider,&QPushButton::clicked,this,&Automate::validateSurrounding);
   //QObject::connect(valider,&QPushButton::clicked,this,&Automate::liberateDialog);
}

void Automate::validateSurrounding(){

    lib->getCurrentModel()->setVoisinage(lib->getCurrentModel()->getVoisinage()->getDiametre());

    for (int i=0; i<lib->getCurrentModel()->getVoisinage()->getDiametre(); i++)
        for (int j=0; j<lib->getCurrentModel()->getVoisinage()->getDiametre(); j++)
            lib->getCurrentModel()->getVoisinage()->setInteractable(i,j,voisins->getlistCells()[i][j]->getState()->getIndex());
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




/*void Automate::liberateDialog(){


    //Qt libere automatique à la fin des fonctions

    //added=0; ajouter apres pour pouvoir recreer un modele

    delete infos;
    delete nom;
    delete nb;
    delete color;
    delete couleur;
    delete label;
    //delete list;



}*/

