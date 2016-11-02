#include "command.h"

void Command::loadRegister(Computer *COMP)
{
    unsigned int ptr;
    if(COMP->CMD.B == 0) //Абсолютная адресация
        ptr = COMP->CMD.Addr;
    else //Относит адресация
        ptr = COMP->CMD.Addr + COMP->RA;
    COMP->debug("Загрузка регистра из адреса " + QString::number(ptr));

    COMP->R1.b1 = COMP->MEM[ptr++];
    COMP->R1.b2 = COMP->MEM[ptr++];
    COMP->R1.b3 = COMP->MEM[ptr++];
    COMP->R1.b4 = COMP->MEM[ptr++];    
}

int cSTOP::operator()(Computer *)
{
    return 0;
}

int cIadd::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.I += COMP->R1.I;
    COMP->flagI(); //Установка флага результата

    COMP->debug("Целочисленное сложение. Сумматор = " + QString::number(COMP->RS.I));
    return 1;
}

int cIsub::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.I -= COMP->R1.I;
    COMP->flagI(); //Установка флага результата

    COMP->debug("Целочисленное вычитание. Сумматор = " + QString::number(COMP->RS.I));
    return 1;
}

int cImul::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.I *= COMP->R1.I;
    COMP->flagI(); //Установка флага результата

    COMP->debug("Целочисленное умножение. Сумматор = " + QString::number(COMP->RS.I));
    return 1;
}

int cIdiv::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.I /= COMP->R1.I;
    COMP->flagI(); //Установка флага результата

    COMP->debug("Целочисленное деление. Сумматор = " + QString::number(COMP->RS.I));
    return 1;
}

int cImod::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.I %= COMP->R1.I;
    COMP->flagI(); //Установка флага результата

    COMP->debug("Целочисленный остаток от деления. Сумматор = " + QString::number(COMP->RS.I));
    return 1;
}

int cRadd::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.R += COMP->R1.R;
    COMP->flagR(); //Установка флага результата

    COMP->debug("Вещественное сложение. Сумматор = " + QString::number(COMP->RS.R));
    return 1;
}

int cRsub::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.R -= COMP->R1.R;
    COMP->flagR(); //Установка флага результата

    COMP->debug("Вещественное вычитание. Сумматор = " + QString::number(COMP->RS.R));
    return 1;
}

int cRmul::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.R *= COMP->R1.R;
    COMP->flagR(); //Установка флага результата

    COMP->debug("Вещественное умножение. Сумматор = " + QString::number(COMP->RS.R));
    return 1;
}

int cRdiv::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.R /= COMP->R1.R;
    COMP->flagR(); //Установка флага результата

    COMP->debug("Вещественное деление. Сумматор = " + QString::number(COMP->RS.R));
    return 1;
}

//Загрузка сумматора из ОЗУ
int cLoad::operator()(Computer *COMP)
{
    address ptr;
    if(COMP->CMD.B == 0) //Абсолютная адресация
        ptr =  COMP->CMD.Addr;
    else //Относит адресация
        ptr = COMP->CMD.Addr + COMP->RA;

    COMP->debug("Загрузка сумматора из адреса " + QString::number(ptr));

    COMP->RS.b1 = COMP->MEM[ptr++];
    COMP->RS.b2 = COMP->MEM[ptr++];
    COMP->RS.b3 = COMP->MEM[ptr++];
    COMP->RS.b4 = COMP->MEM[ptr];

    return 1;
}

//Выгрузка сумматора в ОЗУ
int cStore::operator()(Computer *COMP)
{
    address ptr;
    if(COMP->CMD.B == 0) //Абсолютная адресация
        ptr =  COMP->CMD.Addr;
    else //Относит адресация
        ptr = COMP->CMD.Addr + COMP->RA;

    COMP->debug("Выгрузка сумматора по адресу " + QString::number(ptr));

    COMP->MEM[ptr++] = COMP->RS.b1;
    COMP->MEM[ptr++] = COMP->RS.b2;
    COMP->MEM[ptr++] = COMP->RS.b3;
    COMP->MEM[ptr] = COMP->RS.b4;

    return 1;
}

//Загрузка адресного регистра
int cRadr::operator()(Computer *COMP)
{
    if(COMP->CMD.B == 0) //Абсолютная адресация
        COMP->RA = COMP->CMD.Addr;
    else //Относит адресация
        COMP->RA += COMP->CMD.Addr;

    COMP->debug("Установка адресного регистра на " + QString::number(COMP->RA));
    return 1;
}

//Сравнение целых
int cIcmp::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->DATA.I = COMP->RS.I;
    COMP->RS.I -= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    COMP->RS.I = COMP->DATA.I;

    COMP->debug("Целочисленное сравнение");
    return 1;
}

//Сравнение вещественных
int cRcmp::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->DATA.R = COMP->RS.R;
    COMP->RS.R -= COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    COMP->RS.R = COMP->DATA.R;

    COMP->debug("Вещественное сравнение");
    return 1;
}

//Безусловный переход
int cJmp::operator()(Computer *COMP)
{
    if(COMP->CMD.B == 0) //Абсолютная адресация
        COMP->PSW.IP = COMP->CMD.Addr;
    else //Относит адресация
        COMP->PSW.IP += COMP->CMD.Addr;

    COMP->debug("Безусловный переход по адресу " + QString::number(COMP->PSW.IP));
    return 1;
}
//переход, если равно
int cJZ::operator()(Computer *COMP)
{
    if(COMP->PSW.ZF != 1) return 1;
    if(COMP->CMD.B == 0) //Абсолютная адресация
        COMP->PSW.IP = COMP->CMD.Addr;
    else //Относит адресация
        COMP->PSW.IP += COMP->CMD.Addr;

    COMP->debug("Операнды равны. Переход по адресу " + QString::number(COMP->PSW.IP));
    return 1;
}
//переход, если больше
int cJG::operator()(Computer *COMP)
{
    if(COMP->PSW.SF != 1) return 1;
    if(COMP->CMD.B == 0) //Абсолютная адресация
        COMP->PSW.IP = COMP->CMD.Addr;
    else //Относит адресация
        COMP->PSW.IP += COMP->CMD.Addr;

    COMP->debug("Сумматор больше. Переход по адресу " + QString::number(COMP->PSW.IP));
    return 1;
}
//переход, если меньше
int cJL::operator()(Computer *COMP)
{
    if(COMP->PSW.SF != 0) return 1;
    if(COMP->CMD.B == 0) //Абсолютная адресация
        COMP->PSW.IP = COMP->CMD.Addr;
    else //Относит адресация
        COMP->PSW.IP += COMP->CMD.Addr;

    COMP->debug("Сумматор меньше. Переход по адресу " + QString::number(COMP->PSW.IP));
    return 1;
}

//Ввод целого числа
int cIin::operator()(Computer *COMP)
{
    COMP->interrupt(hIin);
    COMP->RS.I = COMP->DATA.I;

    COMP->debug("Ввод целого числа " + QString::number(COMP->RS.I));
    return 1;
}

//Ввод вещественного числа
int cRin::operator()(Computer *COMP)
{
    COMP->interrupt(hRin);
    COMP->RS.R = COMP->DATA.R;

    COMP->debug("Ввод вещественного числа " + QString::number(COMP->RS.R));
    return 1;
}

//Вывод целого числа
int cIout::operator()(Computer *COMP)
{
    COMP->debug("Вывод целого числа " + QString::number(COMP->RS.I));
    COMP->interrupt(hIout);
    return 1;
}

//Вывод вещественного числа
int cRout::operator()(Computer *COMP)
{
    COMP->debug("Вывод вещественного числа " + QString::number(COMP->RS.R));
    COMP->interrupt(hRout);
    return 1;
}
