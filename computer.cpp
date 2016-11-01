#include "computer.h"

Computer::Computer(QString PATH)
{
    programPath = PATH;

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
    delete[] MEM;
}

//Загрузка программы в массив ОЗУ
bool Computer::load()
{
    QFile file(programPath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        int curByte = 0;
        while(!file.atEnd()){
            if(curByte >= 0xfffb) break; //Защита от переполнения ОЗУ
            QStringList strline = QString(file.readLine()).split(" ");
            if(!strline.isEmpty()){
                CMD.Cmd = (byte)strline[0].toUInt();
                CMD.Addr = (address)strline[1].toUInt();
                //Загрузка программы в ОЗУ
                MEM[curByte] = CMD.Cmd; ++curByte;
                MEM[curByte] = CMD.H_Addr; ++curByte;
                MEM[curByte] = CMD.L_Addr; ++curByte;
            }
        }
        RA += curByte; //Адресный регистр для данных после программы
    }else {
        return false;
    }
    if(file.isOpen()) file.close();
    return true;
}

void Computer::reset()
{
    PSW.IP = 0x0000;
    PSW.OF = 0;
    PSW.SF = 0;
    PSW.ZF = 0;
    RA = 0x0000;
    RS.I = 0;
    R1.I = 0;
}

int Computer::run()
{
    while(true)
    {
        //Загрузка команды в структуру
        CMD.Cmd     =   MEM[ PSW.IP++ ];   //Формируем структуру 3 байта из памяти
        CMD.H_Addr  =   MEM[ PSW.IP++ ];
        CMD.L_Addr  =   MEM[ PSW.IP++ ];
        //*************************************

        int execResult = pCMD[ CMD.OP ]->operator ()(this);     //Выполнение
        if( execResult != 1) return execResult;                 //Результат выполнения
    }
    return 0;
}

void Computer::flagI()
{
    PSW.ZF = 0;
    PSW.SF = 0;
    if(RS.I == 0) PSW.ZF = 1;
    else if(RS.I > 0) PSW.SF = 1;
}

void Computer::flagR()
{
    PSW.ZF = 0;
    PSW.SF = 0;
    if(RS.R == 0) PSW.ZF = 1;
    else if(RS.R > 0) PSW.SF = 1;
}

//Установка флага результата


int Computer::execute()
{
    this->reset();
    if(!this->load())
    {
        return 2;
    }
    return this->run();
}
