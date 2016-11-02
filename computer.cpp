#include "computer.h"
#include "interpreter.h"

Computer::Computer(QString PATH,interpreter *INTER):programPath(PATH),Interpreter(INTER)
{
    pCMD[STOP]  =   new cSTOP();    //Остановка

    //Целая арифметика
    pCMD[Iadd]  =   new cIadd();    //Целочисленное сложение
    pCMD[Isub]  =   new cIsub();    //Целочисленное вычитание
    pCMD[Imul]  =   new cImul();    //Целочисленное умножение
    pCMD[Idiv]  =   new cIdiv();    //Целочисленное деление
    pCMD[Imod]  =   new cImod();    //Целочисл. остаток от деления
    pCMD[Iin]   =   new cIin();     //Ввод целого числа
    pCMD[Iout]  =   new cIout();    //Вывод целого числа

    //Дробная арифметика
    pCMD[Radd]  =   new cRadd();    //Вещественное сложение
    pCMD[Rsub]  =   new cRsub();    //Вещественное вычитание
    pCMD[Rmul]  =   new cRmul();    //Вещественное умножение
    pCMD[Rdiv]  =   new cRdiv();    //Вещественное деление
    pCMD[Rin]   =   new cRin();     //Ввод вещественного числа
    pCMD[Rout]  =   new cRout();    //Вывод вещественного числа

    //Операции с сумматором
    pCMD[Load]  =   new cLoad();    //Загрузка сумматора
    pCMD[Store] =   new cStore();   //Сохранение сумматора

    //прыжки
    pCMD[Jmp]   =   new cJmp();     //Безусловный переход
    pCMD[JZ]    =   new cJZ();      // ==
    pCMD[JG]    =   new cJG();      // >
    pCMD[JL]    =   new cJL();      // <

    //сравнение cIcmp
    pCMD[Icmp]  =   new cIcmp();    //Целочисленное сравнение
    pCMD[Rcmp]  =   new cRcmp();    //Вещественное сравнение
}

//Деструктор
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
            if(curByte >= 0xfffd) break; //Защита от переполнения ОЗУ
            QStringList strline = QString(file.readLine()).split(" ");
            if(!strline[0].isEmpty()){
                CMD.Cmd = (byte)strline[0].toUInt();
                if(!strline[1].isEmpty())
                    CMD.Addr = (address)strline[1].toUInt();
                //Загрузка программы в ОЗУ
                MEM[curByte++] = CMD.Cmd;
                MEM[curByte++] = CMD.H_Addr;
                MEM[curByte++] = CMD.L_Addr;
            }
        }
        RA += curByte; //Адресный регистр для данных после программы
    }else {
        return false;
    }
    if(file.isOpen()) file.close();
    return true;
}

//Сброс регистров
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

//Цикл процессора
int Computer::run()
{
    while(true)
    {
        if(PSW.IP >= 0xFFFC) return 2;
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

//Установка флага результата
void Computer::flagI()
{
    PSW.ZF = 0;
    PSW.SF = 0;
    if(RS.I == 0) PSW.ZF = 1;
    else if(RS.I > 0) PSW.SF = 1;
}
//Установка флага результата
void Computer::flagR()
{
    PSW.ZF = 0;
    PSW.SF = 0;
    if(RS.R == 0) PSW.ZF = 1;
    else if(RS.R > 0) PSW.SF = 1;
}

//запуск выполнения программы
int Computer::execute()
{
    this->reset();
    if(!this->load())
    {
        return 2;
    }
    return this->run();
}


//Обработчик прерываний
void Computer::interrupt(int interruptCode)
{
    switch (interruptCode){
    case hIin: {//Ввод целого значения сумматора
        DATA.I = interpreter::inputDialog("Введите целое число").toInt();
        break;
    }
    case hRin: {//Ввод вещественного значения сумматора
        DATA.R = interpreter::inputDialog("Введите вещественное число").toFloat();
        break;
    }
    case hIout:{//Вывод целого значения сумматора на экран
        QString str = QString::number(RS.I);
        interpreter::outputDialog(str);
        break;
    }
    case hRout: {//Вывод вещественного значения сумматора на экран
        QString str = QString::number(RS.R,'f',2);
        interpreter::outputDialog(str);
        break;
    }
    }
}

//Вывод отладочного сообщения
void Computer::debug(QString msg)
{
    Interpreter->debug(msg);
}
