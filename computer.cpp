#include "computer.h"

Computer::Computer()
{
    //Целая арифметика
    pCMD[STOP] = new cSTOP();
    pCMD[Iadd] = new cIadd();
    pCMD[Isub] = new cIsub();
    pCMD[Imul] = new cImul();
    pCMD[Idiv] = new cIdiv();
    pCMD[Imod] = new cImod();
}

Computer::~Computer()
{

}

void Computer::test()
{
    //pCMD[OP_1]->operator ()(this);

    double i;
    int k = sizeof(i);

    QMessageBox b;
    b.setText(QString::number(k));
    b.exec();


}
