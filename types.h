#ifndef TYPES_H
#define TYPES_H

//Типы данных

typedef signed char Byte;
typedef unsigned char uByte;
typedef short Short;
typedef unsigned short uShort;
typedef int Word;
typedef unsigned int uWord;
typedef long long Long;
typedef unsigned long long uLong;
typedef float Float;
typedef double Double;

typedef unsigned int address;

struct Registers
{
    // регистры общего назначения
    union POH
    {
        Byte    b[256]; // байтовые знаковые целые
        uByte   ub[256]; // байтовые беззнаковые целые
        Short   s[128]; // двухбайтовые знаковые целые
        uShort  us[128]; // двухбайтовые беззнаковые целые
        Word    w[64]; // четырехбайтовые знаковые целые
        uWord   uw[64]; // четырехбайтовые беззнаковые целые
        Float   f[64]; // короткие вещественные
        Long    l[32]; // восьмибайтовые знаковые целые
        uLong   ul[32]; // восьмибайтовые беззнаковые целые
        Double  d[32]; // длинные вещественные
    };

    //Системные регистры
    address PC; // счетчик адреса команды;
    address SP; // указатель стека;
    address RI; // регистр адреса таблицы прерываний.

    //PSW (Cостояние процессора)
    struct bits
    {
        unsigned int IP:16; //Instruction Pointer
        unsigned int CF:1; // бит переноса
        unsigned int OF:1; // переполнение знаковое целое
        unsigned int OV:1; // переполнение плавающей арифметики
        unsigned int UV:1; // антипереполнение плавающей арифметики
        unsigned int TF:1; // флаг трассировки
        unsigned int:11; // пока не используется
    } PSW;
};









#endif // TYPES_H
