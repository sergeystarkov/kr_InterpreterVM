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
//Загрузка программы в массив ОЗУ
void Computer::load(QString path)
{
    QByteArray barr;
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        barr = file.readAll();
        memcpy(MEM,barr,barr.length());
    }else {
        QMessageBox b;
        b.setText("Файл программы не загружен");
        b.exec();
    }
    file.close();
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
            break;
        }
    }
}

void Computer::test()
{
    CMD.addr = 0x05;
    CMD.b = 0;

    this->start();

    this->run();




    QMessageBox b;
    b.setText(QString::number(RS.I));
    b.exec();

    //pCMD[CMD.code]->operator ()(this);




}
