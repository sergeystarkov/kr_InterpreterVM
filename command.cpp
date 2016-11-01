#include "command.h"

void Command::loadIntegerRegister(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->R1.I = COMP->MEM[COMP->CMD.Addr];
    else //Относит адресация
        COMP->R1.I = COMP->MEM[COMP->CMD.Addr + COMP->RA];
}

void Command::loadRealRegister(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->R1.R = COMP->MEM[COMP->CMD.Addr];
    else //Относит адресация
        COMP->R1.R = COMP->MEM[COMP->CMD.Addr + COMP->RA];
}


int cSTOP::operator()(Computer *)
{
    return 0;
}

int cIadd::operator()(Computer *COMP)
{
    loadIntegerRegister(COMP);
    COMP->RS.I += COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int cIsub::operator()(Computer *COMP)
{
    loadIntegerRegister(COMP);
    COMP->RS.I -= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int cImul::operator()(Computer *COMP)
{
    loadIntegerRegister(COMP);
    COMP->RS.I *= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int cIdiv::operator()(Computer *COMP)
{
    loadIntegerRegister(COMP);
    COMP->RS.I /= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int cImod::operator()(Computer *COMP)
{
    loadIntegerRegister(COMP);
    COMP->RS.I %= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int cRadd::operator()(Computer *COMP)
{
    loadRealRegister(COMP);
    COMP->RS.R += COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    return 1;
}

int cRsub::operator()(Computer *COMP)
{
    loadRealRegister(COMP);
    COMP->RS.R -= COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    return 1;
}

int cRmul::operator()(Computer *COMP)
{
    loadRealRegister(COMP);
    COMP->RS.R *= COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    return 1;
}

int cRdiv::operator()(Computer *COMP)
{
    loadRealRegister(COMP);
    COMP->RS.R /= COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    return 1;
}

//Загрузка сумматора из ОЗУ
int cLoad::operator()(Computer *COMP)
{
    unsigned int ptr;
    if(COMP->CMD.B = 0) //Абсолютная адресация
        ptr =  COMP->CMD.Addr;
    else //Относит адресация
        ptr = COMP->CMD.Addr + COMP->RA;

    COMP->RS.b1 = COMP->MEM[ptr++];
    COMP->RS.b2 = COMP->MEM[ptr++];
    COMP->RS.b3 = COMP->MEM[ptr++];
    COMP->RS.b4 = COMP->MEM[ptr];

    return 1;
}

//Выгрузка сумматора в ОЗУ
int cStore::operator()(Computer *COMP)
{
    unsigned int ptr;
    if(COMP->CMD.B = 0) //Абсолютная адресация
        ptr =  COMP->CMD.Addr;
    else //Относит адресация
        ptr = COMP->CMD.Addr + COMP->RA;

    COMP->MEM[ptr++] = COMP->RS.b1;
    COMP->MEM[ptr++] = COMP->RS.b2;
    COMP->MEM[ptr++] = COMP->RS.b3;
    COMP->MEM[ptr] = COMP->RS.b4;

    return 1;
}

//Загрузка адресного регистра
int cRadr::operator()(Computer *COMP)
{
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->RA = COMP->CMD.Addr;
    else //Относит адресация
        COMP->RA += COMP->CMD.Addr;
    return 1;
}

//Сравнение целых
int cIcmp::operator()(Computer *COMP)
{
    loadIntegerRegister(COMP);
    COMP->DATA.I = COMP->RS.I;
    COMP->RS.I -= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    COMP->RS.I = COMP->DATA.I;
    return 1;
}

//Сравнение вещественных
int cRcmp::operator()(Computer *COMP)
{
    loadIntegerRegister(COMP);
    COMP->DATA.R = COMP->RS.R;
    COMP->RS.R -= COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    COMP->RS.R = COMP->DATA.R;
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
//переход, если равно
int cJZ::operator()(Computer *COMP)
{
    if(COMP->PSW.ZF != 1) return 0;
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->PSW.IP = COMP->CMD.Addr;
    else //Относит адресация
        COMP->PSW.IP += COMP->CMD.Addr;
    return 1;
}
//переход, если больше
int cJG::operator()(Computer *COMP)
{
    if(COMP->PSW.SF != 1) return 0;
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->PSW.IP = COMP->CMD.Addr;
    else //Относит адресация
        COMP->PSW.IP += COMP->CMD.Addr;
    return 1;
}
//переход, если меньше
int cJL::operator()(Computer *COMP)
{
    if(COMP->PSW.SF != 0) return 0;
    if(COMP->CMD.B = 0) //Абсолютная адресация
        COMP->PSW.IP = COMP->CMD.Addr;
    else //Относит адресация
        COMP->PSW.IP += COMP->CMD.Addr;
    return 1;
}

int cIin::operator()(Computer *COMP)
{
    COMP->handle(hIin);
    COMP->RS.I = COMP->DATA.I;
    return 1;
}

int cRin::operator()(Computer *COMP)
{
    COMP->handle(hRin);
    COMP->RS.R = COMP->DATA.R;
    return 1;
}

int cIout::operator()(Computer *COMP)
{
    COMP->handle(hIout);
    return 1;
}

int cRout::operator()(Computer *COMP)
{
    COMP->handle(hRout);
    return 1;
}
