#include "computer.h"

Computer::Computer()
{
    //Целая арифметика
    pCMD[STOP]  =   new cSTOP();
    pCMD[Iadd]  =   new cIadd();
    pCMD[Isub]  =   new cIsub();
    pCMD[Imul]  =   new cImul();
    pCMD[Idiv]  =   new cIdiv();
    pCMD[Imod]  =   new cImod();

    //Операции с сумматором
    pCMD[Load]  =   new cLoad();    //Загрузка сумматора
    pCMD[Store] =   new cStore();   //Сохранение сумматора
}

Computer::~Computer()
{

}

void Computer::start()
{
    PSW.IP = 0x01;
}

void Computer::run()
{
    while(true)
    {
        if( pCMD[ MEM[PSW.IP] ]->operator ()(this) == 0)        {
            QMessageBox b;
            b.setText("Программа завершилась с кодом 0");
            b.exec();
        }
    }
}

void Computer::test()
{


    int i = 0x42F17FB3;
    MEM[0] = 0;
    MEM[1] = 0x28;
    MEM[2] = 0x03;
    memcpy(&MEM[3],&i,4);
    MEM[7] = 0x00;



    CMD.code = MEM[1];
    CMD.addr = MEM[2];

    memcpy(&RS.I,&MEM[CMD.addr],4);

    //pCMD[CMD.code]->operator ()(this);




}
