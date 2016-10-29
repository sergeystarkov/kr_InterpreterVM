#include "command.h"




int cSTOP::operator()(Computer *)
{
    return 0;
}

int cIadd::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->R1.I = COMP->MEM[COMP->CMD.Addr];
    else //Относит адресация
        COMP->R1.I = COMP->MEM[COMP->CMD.Addr + COMP->RA];
    COMP->RS.I += COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int cIsub::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->R1.I = COMP->MEM[COMP->CMD.Addr];
    else //Относит адресация
        COMP->R1.I = COMP->MEM[COMP->CMD.Addr + COMP->RA];
    COMP->RS.I -= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int cImul::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->R1.I = COMP->MEM[COMP->CMD.Addr];
    else //Относит адресация
        COMP->R1.I = COMP->MEM[COMP->CMD.Addr + COMP->RA];
    COMP->RS.I *= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int cIdiv::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->R1.I = COMP->MEM[COMP->CMD.Addr];
    else //Относит адресация
        COMP->R1.I = COMP->MEM[COMP->CMD.Addr + COMP->RA];
    COMP->RS.I /= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int cImod::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->R1.I = COMP->MEM[COMP->CMD.Addr];
    else //Относит адресация
        COMP->R1.I = COMP->MEM[COMP->CMD.Addr + COMP->RA];
    COMP->RS.I %= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int cRadd::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->R1.R = COMP->MEM[COMP->CMD.Addr];
    else //Относит адресация
        COMP->R1.R = COMP->MEM[COMP->CMD.Addr + COMP->RA];
    COMP->RS.R += COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    return 1;
}

int cRsub::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->R1.R = COMP->MEM[COMP->CMD.Addr];
    else //Относит адресация
        COMP->R1.R = COMP->MEM[COMP->CMD.Addr + COMP->RA];
    COMP->RS.R -= COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    return 1;
}

int cRmul::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->R1.R = COMP->MEM[COMP->CMD.Addr];
    else //Относит адресация
        COMP->R1.R = COMP->MEM[COMP->CMD.Addr + COMP->RA];
    COMP->RS.R *= COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    return 1;
}

int cRdiv::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->R1.R = COMP->MEM[COMP->CMD.Addr];
    else //Относит адресация
        COMP->R1.R = COMP->MEM[COMP->CMD.Addr + COMP->RA];
    COMP->RS.R /= COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    return 1;
}

//Загрузка сумматора из ОЗУ
int cLoad::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->RS.I = COMP->MEM[COMP->CMD.Addr];
    else //Относит адресация
        COMP->RS.I = COMP->MEM[COMP->CMD.Addr + COMP->RA];
    return 1;
}

//Выгрузка сумматора в ОЗУ
int cStore::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
         COMP->MEM[COMP->CMD.Addr] = COMP->RS.I;
    else //Относит адресация
        COMP->MEM[COMP->CMD.Addr + COMP->RA] = COMP->RS.I;
    return 1;
}

int cRadr::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->RA = COMP->CMD.Addr;
    else //Относит адресация
        COMP->RA += COMP->CMD.Addr;
    return 1;
}

//Безусловный переход
int cJmp::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->PSW.IP = COMP->CMD.Addr;
    else //Относит адресация
        COMP->PSW.IP += COMP->CMD.Addr;
    return 1;
}
