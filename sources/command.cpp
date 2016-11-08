#include "command.h"
#include "computer.h"

/**
 * @brief Command::loadRegister - загрузка внутреннего регистра
 * @param COMP - указатель на объект компьютер
 *
 * Загружает внутренний регистр из адреса по абсолютной или относительной адресации.
 * Функция вызывается только из потомков Command.
 */
void Command::loadRegister(Computer *COMP)
{
    unsigned int ptr;
    if(COMP->CMD.B == 0) //Абсолютная адресация
        ptr = COMP->CMD.Addr;
    else //Относительная адресация
        ptr = COMP->CMD.Addr + COMP->RA;
    COMP->debug("Загрузка регистра из адреса " + QString::number(ptr));

    COMP->R1.b1 = COMP->MEM[ptr++];
    COMP->R1.b2 = COMP->MEM[ptr++];
    COMP->R1.b3 = COMP->MEM[ptr++];
    COMP->R1.b4 = COMP->MEM[ptr++];    
}

/**
 * @brief cSTOP::operator ()
 * @return 0
 *
 * Завершает работу программы
 */
int cSTOP::operator()(Computer *)
{
    return 0;
}

/**
 * @brief cIadd::operator () - Целочисленное сложение
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает внутренний регистр по адресу.
 * Складывает сумматор с внутренним регистром.
 * Ставит флаги операции.
 */
int cIadd::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.I += COMP->R1.I;
    COMP->flagI(); //Установка флага результата

    COMP->debug("Целочисленное сложение. Сумматор = " + QString::number(COMP->RS.I));
    return 1;
}

/**
 * @brief cIsub::operator () - Целочисленная разность
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает внутренний регистр по адресу.
 * Вичитает из сумматора значение внутреннего регистра.
 * Ставит флаги операции.
 */
int cIsub::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.I -= COMP->R1.I;
    COMP->flagI(); //Установка флага результата

    COMP->debug("Целочисленное вычитание. Сумматор = " + QString::number(COMP->RS.I));
    return 1;
}

/**
 * @brief cImul::operator () - Целочисленное произведение
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает внутренний регистр по адресу.
 * Умножает сумматор на внутренний регистр
 * Ставит флаги операции.
 */
int cImul::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.I *= COMP->R1.I;
    COMP->flagI(); //Установка флага результата

    COMP->debug("Целочисленное умножение. Сумматор = " + QString::number(COMP->RS.I));
    return 1;
}

/**
 * @brief cIdiv::operator () - Целочисленное деление
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает внутренний регистр по адресу.
 * Делит сумматор на значение внутреннего регистра.
 * Ставит флаги операции.
 */
int cIdiv::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.I /= COMP->R1.I;
    COMP->flagI(); //Установка флага результата

    COMP->debug("Целочисленное деление. Сумматор = " + QString::number(COMP->RS.I));
    return 1;
}

/**
 * @brief cImod::operator () - Целочисленный остаток от деления
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает внутренний регистр по адресу.
 * Записывает в сумматор остаток от деления сумматоран на значение внутреннего регистра.
 * Ставит флаги операции.
 */
int cImod::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.I %= COMP->R1.I;
    COMP->flagI(); //Установка флага результата

    COMP->debug("Целочисленный остаток от деления. Сумматор = " + QString::number(COMP->RS.I));
    return 1;
}

/**
 * @brief cRadd::operator () - Вещественная сумма
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает внутренний регистр по адресу.
 * Складывает сумматор с внутренним регистром.
 * Ставит флаги операции.
 */
int cRadd::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.R += COMP->R1.R;
    COMP->flagR(); //Установка флага результата

    COMP->debug("Вещественное сложение. Сумматор = " + QString::number(COMP->RS.R));
    return 1;
}

/**
 * @brief cRsub::operator () - Вещественная разность
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает внутренний регистр по адресу.
 * Вичитает из сумматора значение внутреннего регистра.
 * Ставит флаги операции.
 */
int cRsub::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.R -= COMP->R1.R;
    COMP->flagR(); //Установка флага результата

    COMP->debug("Вещественное вычитание. Сумматор = " + QString::number(COMP->RS.R));
    return 1;
}

/**
 * @brief cRmul::operator () - Вещественное произведение
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает внутренний регистр по адресу.
 * Умножает сумматор на внутренний регистр
 * Ставит флаги операции.
 */
int cRmul::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.R *= COMP->R1.R;
    COMP->flagR(); //Установка флага результата

    COMP->debug("Вещественное умножение. Сумматор = " + QString::number(COMP->RS.R));
    return 1;
}

/**
 * @brief cRdiv::operator () - вещественное деление
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает внутренний регистр по адресу.
 * Делит сумматор на значение внутреннего регистра.
 * Ставит флаги операции.
 */
int cRdiv::operator()(Computer *COMP)
{
    loadRegister(COMP);
    COMP->RS.R /= COMP->R1.R;
    COMP->flagR(); //Установка флага результата

    COMP->debug("Вещественное деление. Сумматор = " + QString::number(COMP->RS.R));
    return 1;
}

/**
 * @brief cLoad::operator () - Загрузка сумматора
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает сумматор из ОЗУ.
 * Размер загрузки 4 байта
 */
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

/**
 * @brief cStore::operator () - Выгрузка сумматора
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Выгружает сумматор в оперативную память.
 * Размер выгрузки 4 байта.
 */
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

/**
 * @brief cRadr::operator () - Загрузка адресного регистра
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает в адресный регистр константу.
 * Константа либо абсолютный адрес в ОЗУ, либо отступ от текущего значения адресного регистра.
 */
int cRadr::operator()(Computer *COMP)
{
    if(COMP->CMD.B == 0) //Абсолютная адресация
        COMP->RA = COMP->CMD.Addr;
    else //Относит адресация
        COMP->RA += COMP->CMD.Addr;

    COMP->debug("Установка адресного регистра на " + QString::number(COMP->RA));
    return 1;
}

/**
 * @brief cIcmp::operator () - Сравнение целых чисел
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает внутренний регистр из памяти.
 * Сравнивает целочисленное значение сумматора с целочисленныйм значением внутреннего регистра.
 * Результаты записываются в флаги PSW.
 * Значение сумматора не изменяется.
 */
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

/**
 * @brief cRcmp::operator () - Сравнение вещественных чисел
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Загружает внутренний регистр из памяти.
 * Сравнивает вещественное значение сумматора с вещественным значением внутреннего регистра.
 * Результаты записываются в флаги PSW.
 * Значение сумматора не изменяется.
 */
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

/**
 * @brief cJmp::operator () - Безусловный переход
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Изменяет значение указателя на инструкцию по абсолютному значению адреса ОЗУ, либо отступа от текущего значения.
 */
int cJmp::operator()(Computer *COMP)
{
    if(COMP->CMD.B == 0) //Абсолютная адресация
        COMP->PSW.IP = COMP->CMD.Addr;
    else //Относит адресация
        COMP->PSW.IP += COMP->CMD.Addr;

    COMP->debug("Безусловный переход по адресу " + QString::number(COMP->PSW.IP));
    return 1;
}

/**
 * @brief cJZ::operator () - Переход если равно
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Если по результатам сравнения Icmp или Rcmp операнды были равны,
 * изменяет значение указателя на инструкцию по абсолютному значению адреса ОЗУ, либо отступа от текущего значения.
 */
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

/**
 * @brief cJG::operator () - Переход если больше
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Если по результатам сравнения Icmp или Rcmp сумматор был больше адресного регистра,
 * изменяет значение указателя на инструкцию по абсолютному значению адреса ОЗУ, либо отступа от текущего значения.
 */
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

/**
 * @brief cJL::operator () - Переход если меньше
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Если по результатам сравнения Icmp или Rcmp сумматор был меньше адресного регистра,
 * изменяет значение указателя на инструкцию по абсолютному значению адреса ОЗУ, либо отступа от текущего значения.
 */
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

/**
 * @brief cIin::operator () - Прерывание: ввод вещественного значения
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Вызывает прерывание для ввода целочисленного значения от пользователя и загружает его в сумматор
 */
int cIin::operator()(Computer *COMP)
{
    COMP->interrupt(hIin);
    COMP->RS.I = COMP->DATA.I;

    COMP->debug("Ввод целого числа " + QString::number(COMP->RS.I));
    return 1;
}

/**
 * @brief cRin::operator () - Прерывание: ввод вещественного значения
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Вызывает прерывание для ввода Вещественного значения от пользователя и загружает его в сумматор
 */
int cRin::operator()(Computer *COMP)
{
    COMP->interrupt(hRin);
    COMP->RS.R = COMP->DATA.R;

    COMP->debug("Ввод вещественного числа " + QString::number(COMP->RS.R));
    return 1;
}

/**
 * @brief cIout::operator () - Прерывание: вывод целого значения
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Вызывает прерывание для вывода целочисленного значения на экран из сумматора
 */
int cIout::operator()(Computer *COMP)
{
    COMP->debug("Вывод целого числа " + QString::number(COMP->RS.I));
    COMP->interrupt(hIout);
    return 1;
}

/**
 * @brief cRout::operator () - Прерывание: вывод вещественного значения из сумматора
 * @param COMP - указатель на объект компьютер
 * @return 1
 *
 * Вызывает прерывание для вывода вещественного значения на экран
 */
int cRout::operator()(Computer *COMP)
{
    COMP->debug("Вывод вещественного числа " + QString::number(COMP->RS.R));
    COMP->interrupt(hRout);
    return 1;
}
