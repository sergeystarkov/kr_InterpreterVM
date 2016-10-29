#include "command.h"




int cSTOP::operator()(Computer *)
{
    return 0;
}

int cIadd::operator()(Computer *COMP)
{
//    if(COMP->CMD.b = 0)
//        memcpy(&COMP->R1.I,&COMP->MEM[COMP->CMD.addr],4);
//    //else Относит адресация
//    COMP->RS.I += COMP->R1.I;
//    COMP->flagI(); //Установка флага результата
    return 1;
}

int cIsub::operator()(Computer *COMP)
{
//    if(COMP->CMD.b = 0)
//        memcpy(&COMP->R1.I,&COMP->MEM[COMP->CMD.addr],4);
//    //else Относит адресация
//    COMP->RS.I -= COMP->R1.I;
//    COMP->flagI(); //Установка флага результата
    return 1;
}

int cImul::operator()(Computer *COMP)
{
//    if(COMP->CMD.b = 0)
//        memcpy(&COMP->R1.I,&COMP->MEM[COMP->CMD.addr],4);
//    //else Относит адресация
//    COMP->RS.I *= COMP->R1.I;
//    COMP->flagI(); //Установка флага результата
    return 1;
}

int cIdiv::operator()(Computer *COMP)
{
//    if(COMP->CMD.b = 0)
//        memcpy(&COMP->R1.I,&COMP->MEM[COMP->CMD.addr],4);
//    //else Относит адресация
//    COMP->RS.I /= COMP->R1.I;
//    COMP->flagI(); //Установка флага результата
    return 1;
}

int cImod::operator()(Computer *COMP)
{
//    if(COMP->CMD.b = 0)
//        memcpy(&COMP->R1.I,&COMP->MEM[COMP->CMD.addr],4);
//    //else Относит адресация
//    COMP->RS.I %= COMP->R1.I;
//    COMP->flagI(); //Установка флага результата
    return 1;
}

int cRadd::operator()(Computer *COMP)
{
//    if(COMP->CMD.b = 0)
//        memcpy(&COMP->R1.R,&COMP->MEM[COMP->CMD.addr],4);
//    //else Относит адресация
//    COMP->RS.R += COMP->R1.R;
//    COMP->flagR(); //Установка флага результата
    return 1;
}

int cRsub::operator()(Computer *COMP)
{
//    if(COMP->CMD.b = 0)
//        memcpy(&COMP->R1.R,&COMP->MEM[COMP->CMD.addr],4);
//    //else Относит адресация
//    COMP->RS.R -= COMP->R1.R;
//    COMP->flagR(); //Установка флага результата
    return 1;
}

int cRmul::operator()(Computer *COMP)
{
//    if(COMP->CMD.b = 0)
//        memcpy(&COMP->R1.R,&COMP->MEM[COMP->CMD.addr],4);
//    //else Относит адресация
//    COMP->RS.R *= COMP->R1.R;
//    COMP->flagR(); //Установка флага результата
    return 1;
}

int cRdiv::operator()(Computer *COMP)
{
//    if(COMP->CMD.b = 0)
//        memcpy(&COMP->R1.R,&COMP->MEM[COMP->CMD.addr],4);
//    //else Относит адресация
//    COMP->RS.R /= COMP->R1.R;
//    COMP->flagR(); //Установка флага результата
    return 1;
}

//Загрузка сумматора из ОЗУ
int cLoad::operator()(Computer *COMP)
{
//    if(COMP->CMD.b == 0){//При абсолютной адресации
//        memcpy( &COMP->RS.I , &COMP->MEM[COMP->CMD.addr] , 4 );
//    }else{//Доработать!!!
//        //memcpy( &COMP->RS.I , &COMP->MEM[ COMP->RA + COMP->CMD.addr ] , 4 );
//    }
    return 1;
}

//Выгрузка сумматора в ОЗУ
int cStore::operator()(Computer *COMP)
{
//    if(COMP->CMD.b == 0){//При абсолютной адресации
//        memcpy( &COMP->MEM[COMP->CMD.addr] , &COMP->RS.I , 4 );
//    }else{//ДОРАБОТАТЬ!!!
//        //memcpy( &COMP->MEM[ COMP->RA + COMP->CMD.addr ] , &COMP->RS.I , 4 );
//    }
    return 1;
}

int cRadr::operator()(Computer *COMP)
{
//    if(COMP->CMD.b == 0){//При абсолютной адресации
//        COMP->RA = COMP->CMD.addr;
//    }else{//При относительно адресации
//        COMP->RA += COMP->CMD.addr;
//    }
    return 1;
}

//Безусловный переход
int cJmp::operator()(Computer *COMP)
{
//    if(COMP->CMD.b == 0){//При абсолютной адресации
//        COMP->PSW.IP = COMP->CMD.addr;
//    }else{//При относительно адресации
//        COMP->PSW.IP = COMP->RA + COMP->CMD.addr;
//    }
    return 1;
}
