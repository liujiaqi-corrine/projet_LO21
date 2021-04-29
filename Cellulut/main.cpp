#include <iostream>
#include "Cellulut.h"

using namespace std;

int main()
{
    cout<<"Welcome to Cellulut !\n\n";

    /*//Manipulation de la bibliothèque
    Model* model1 = new Model("model1"); //Initialisation de 3 modèles
    Model* model2 = new Model("model2");
    Model* model3 = new Model("model3");
    Library::getInstance()->add_Model(model1); //Ajout des 3 modèles à la bibliothèque
    Library::getInstance()->add_Model(model2);
    Library::getInstance()->add_Model(model3);
    Library::getInstance()->add_Model(model1); //Ajout redondant
    cout<<Library::getInstance()->getListModels()->size()<<"\n";             //Taille de la biblio
    cout<<Library::getInstance()->getListModels()->at(2)->getName()<<"\n";  //Nom du troisieme modele
    Library::getInstance()->del_Model(model1);                             //Suppression du modele 1
    cout<<Library::getInstance()->getListModels()->at(0)->getName()<<"\n";//Nom du premier modele
    */

    /*//Initaliser un modèle avec une grille 3x5 et ajout de l'état "dead"
    Model* model = new Model();
    model->init_Grid(3,5);

    State* dead = new State("dead","black");
    model->add_State(dead);
    model->getGrid()->getlistCells()[1][3].setState(model->getListStates()->at(1));

    for(int i = 0; i< model->getGrid()->getWidth(); i++)
    {
        for(int j = 0; j< model->getGrid()->getLength(); j++)
        {
            cout<<model->getGrid()->getlistCells()[i][j].getState()->getLabel()<<" ";
        }
        cout<<"\n";
    }*/


    cout<<"\n Done \n";
    //system("pause");
    return 0;
}
