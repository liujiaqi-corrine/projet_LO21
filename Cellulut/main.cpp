#include <iostream>
#include "Cellulut.h"

using namespace std;

int main()
{
    cout<<"Bienvenue dans l'application Cellulut !\n\n";
    Model *model = new Model();
    model->init_Grid(3,5);

    model->add_State("mort","noir");
    model->getGrid()->getlistCells()[1][3].setState(model->getListStates()->at(1));

    for(int i = 0; i< model->getGrid()->getWidth(); i++)
    {
        for(int j = 0; j< model->getGrid()->getLength(); j++)
        {
            cout<<model->getGrid()->getlistCells()[i][j].getState()->getLabel()<<" ";
        }
        cout<<"\n";
    }
    //system("pause");
    //cout << "Hello world!" << endl;
    return 0;
}
