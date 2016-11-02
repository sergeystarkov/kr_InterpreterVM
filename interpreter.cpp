#include "interpreter.h"

interpreter::~interpreter()
{
    delete VM;
}

//Запуск интерпретатора
void interpreter::startVM()
{
     VM = new Computer(ProgramPath,this);
     emit debugMSG("Запуск программы " + ProgramPath);
     int result = VM->execute();

     emit debugMSG("Программа завершилась с кодом " +
                   QString::number(result) + "\n\n");
     delete this;
}

//Диалог ввода
QString interpreter::inputDialog(QString text)
{
    bool bOk;
    QString str = QInputDialog::getText( 0, text, "Значение",
                                         QLineEdit::Normal,
                                         "", &bOk );
    if (bOk) {
        return str;
    }else return inputDialog(text);
}

//Диалог вывода
void interpreter::outputDialog(QString str)
{
    QMessageBox message;
    message.setWindowTitle("Сообщение");
    message.setText(str);
    message.exec();
}

//Лог
void interpreter::debug(QString  msg)
{
    emit debugMSG("Программа#: " + msg);
}

