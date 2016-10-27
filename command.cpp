#include "command.h"




int CPU::STOP(Computer * COMP)
{
    return 1;
}

int CPU::IADD(Computer *COMP)
{
    if(COMP->CMD.b = 0)
        memcpy(&COMP->R1.I,&COMP->MEM[COMP->CMD.addr],4);
    //else Относит адресация
    COMP->RS.I += COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int CPU::ISUB(Computer *COMP)
{
    if(COMP->CMD.b = 0)
        memcpy(&COMP->R1.I,&COMP->MEM[COMP->CMD.addr],4);
    //else Относит адресация
    COMP->RS.I -= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int CPU::IMUL(Computer *COMP)
{
    if(COMP->CMD.b = 0)
        memcpy(&COMP->R1.I,&COMP->MEM[COMP->CMD.addr],4);
    //else Относит адресация
    COMP->RS.I *= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int CPU::IDIV(Computer *COMP)
{
    if(COMP->CMD.b = 0)
        memcpy(&COMP->R1.I,&COMP->MEM[COMP->CMD.addr],4);
    //else Относит адресация
    COMP->RS.I /= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int CPU::IMOD(Computer *COMP)
{
    if(COMP->CMD.b = 0)
        memcpy(&COMP->R1.I,&COMP->MEM[COMP->CMD.addr],4);
    //else Относит адресация
    COMP->RS.I %= COMP->R1.I;
    COMP->flagI(); //Установка флага результата
    return 1;
}

int CPU::RADD(Computer *COMP)
{
    if(COMP->CMD.b = 0)
        memcpy(&COMP->R1.R,&COMP->MEM[COMP->CMD.addr],4);
    //else Относит адресация
    COMP->RS.R += COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    return 1;
}

int CPU::RSUB(Computer *COMP)
{
    if(COMP->CMD.b = 0)
        memcpy(&COMP->R1.R,&COMP->MEM[COMP->CMD.addr],4);
    //else Относит адресация
    COMP->RS.R -= COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    return 1;
}

int CPU::RMUL(Computer *COMP)
{
    if(COMP->CMD.b = 0)
        memcpy(&COMP->R1.R,&COMP->MEM[COMP->CMD.addr],4);
    //else Относит адресация
    COMP->RS.R *= COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    return 1;
}

int CPU::RDIV(Computer *COMP)
{
    if(COMP->CMD.b = 0)
        memcpy(&COMP->R1.R,&COMP->MEM[COMP->CMD.addr],4);
    //else Относит адресация
    COMP->RS.R /= COMP->R1.R;
    COMP->flagR(); //Установка флага результата
    return 1;
}

//Загрузка сумматора из ОЗУ
int CPU::LOAD(Computer *COMP)
{
    if(COMP->CMD.b == 0){//При абсолютной адресации
        memcpy( &COMP->RS.I , &COMP->MEM[COMP->CMD.addr] , 4 );
    }else{//Доработать!!!
        //memcpy( &COMP->RS.I , &COMP->MEM[ COMP->RA + COMP->CMD.addr ] , 4 );
    }
    return 1;
}

//Выгрузка сумматора в ОЗУ
int CPU::STORE(Computer *COMP)
{
    if(COMP->CMD.b == 0){//При абсолютной адресации
        memcpy( &COMP->MEM[COMP->CMD.addr] , &COMP->RS.I , 4 );
    }else{//ДОРАБОТАТЬ!!!
        //memcpy( &COMP->MEM[ COMP->RA + COMP->CMD.addr ] , &COMP->RS.I , 4 );
    }
    return 1;
}

int CPU::RADR(Computer * COMP)
{
    if(COMP->CMD.b == 0){//При абсолютной адресации
        COMP->RA = COMP->CMD.addr;
    }else{//При относительно адресации
        COMP->RA += COMP->CMD.addr;
    }
    return 1;
}

//Безусловный переход
int CPU::JMP(Computer *COMP)
{
    if(COMP->CMD.b == 0){//При абсолютной адресации
        COMP->PSW.IP = COMP->CMD.addr;
    }else{//При относительно адресации
        COMP->PSW.IP = COMP->RA + COMP->CMD.addr;
    }
    return 1;
}
