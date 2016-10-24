#ifndef OPERATION_H
#define OPERATION_H

enum Operations {
    //Код команды xyyy, где x=I для целых чисел
    //                      x=R для вещественных чисел
    // yyy - мнемоника

    STOP = 0x00,
    Iadd = 0x01, // – сложение целых чисел
    Isub = 0x02, // – вычитание целых чисел
    Imul = 0x03, // – умножение целых чисел
    Idiv = 0x04, // – деление целых чисел
    Imod = 0x05, // – остаток от деления целых чисел
};

#endif // OPERATION_H
