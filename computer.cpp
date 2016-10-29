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

    //Дробная арифметика
    pCMD[Radd]  =   new cRadd();
    pCMD[Rsub]  =   new cRsub();
    pCMD[Rmul]  =   new cRmul();
    pCMD[Rdiv]  =   new cRdiv();

    //Операции с сумматором
    pCMD[Load]  =   new cLoad();    //Загрузка сумматора
    pCMD[Store] =   new cStore();   //Сохранение сумматора
}

Computer::~Computer()
{
    for( int i = 0 ; i < 128 ; i++ ) {
        delete pCMD[i];
    }
    delete[] &pCMD;

    delete[] &MEM;
}
//Загрузка программы в массив ОЗУ
void Computer::load(QString path)
{
//    QByteArray barr;
//    QFile file(path);
//    if(file.open(QIODevice::ReadOnly)){
//        barr = file.readAll();
//        memcpy(MEM,barr,barr.length());
//    }else {
//        QMessageBox b;
//        b.setText("Файл программы не загружен");
//        b.exec();
//    }
//    file.close();

    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        while(!file.atEnd()){
            QStringList strline = QString(file.readLine()).split(" ");
            if(!strline.isEmpty()){
                CMD.CODE.COM = (char)strline[0].toInt();
                CMD.addr = (address)strline[1].toInt();
            }
        }

    }else {
        QMessageBox b;
        b.setText("Файл программы не загружен");
        b.exec();
    }
    file.close();

}

void Computer::start()
{
    PSW.IP = 0x0000;
    RA = 0x0000;
}

void Computer::run()
{
//    while(true)
//    {
//        //Загрузка команды в структуру
//        if(MEM[PSW.IP]&1<<7){       //Проверяем флаг типа адреса CMD.b
//            MEM[PSW.IP]&=~(1<<7);
//            CMD.b = 1;              //Принудительно очищаем код от флага
//        }
//        CMD.code = MEM[ PSW.IP ];   //Записываем код операции
//        address tmp;//К битовому полу нельзя получить адрес, поэтому нужна переменная
//        memcpy(&tmp,&MEM[ PSW.IP + 1 ],2);
//        CMD.addr = tmp;
//        //*************************************

//        if( pCMD[ CMD.code ]->operator ()(this) == 0){
//            QMessageBox b; b.setText("Программ завершилась с кодом 0"); b.exec();
//            break;
//        }
//        else {
//            QMessageBox b; b.setText(QString::number(CMD.code)); b.exec(); //Временно, выводит текущий ОПкод в 10сч.
//        }
//        PSW.IP += 3; //Переход на сл команду
//    }
}

void Computer::flagI()
{
    PSW.ZF = 0;
    PSW.SF = 0;
    if(RS.I == 0) PSW.ZF = 1;
    else if(RS.I < 0) PSW.SF = 1;
}

void Computer::flagR()
{
    PSW.ZF = 0;
    PSW.SF = 0;
    if(RS.R == 0) PSW.ZF = 1;
    else if(RS.R < 0) PSW.SF = 1;
}

//Установка флага результата


void Computer::test()
{
    //this->start();
    //this->run();



    QString s;

    for(int j = 0 ; j<8 ; j++)
    {
        if(CMD.CODE.b[j] == 1)
            s.append("1");
        else s.append("0");
    }

    {QMessageBox b; b.setText(s); b.exec();}

}
