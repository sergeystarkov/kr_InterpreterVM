#include "interpreter.h"

interpreter::interpreter(QString PATH)
{
    ProgramPath = PATH;
}

interpreter::~interpreter()
{
    delete VM;
}

void interpreter::startVM()
{
     VM = new Computer(ProgramPath,this);
     emit debugMSG("Запуск программы " + ProgramPath);
     int result = VM->execute();
     emit debugMSG("Программа завершилась с кодом " + QString::number(result));
     delete this;
}

QString interpreter::inputDialog(QString text)
{
    bool bOk;
    QString str = QInputDialog::getText( 0,
                                         text,
                                         "Значение",
                                         QLineEdit::Normal,
                                         "",
                                         &bOk
                                        );
    if (bOk) {
        return str;
    }else return str;
}

void interpreter::outputDialog(QString str)
{
    QMessageBox message;
    message.setWindowTitle("Сообщение");
    message.setText(str);
    message.exec();
}

void interpreter::debug(QString  msg)
{
    emit debugMSG("Программа#: " + msg);
}

