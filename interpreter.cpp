#include "interpreter.h"

interpreter::interpreter(QString PATH)
{
    ProgramPath = PATH;
}

int interpreter::startVM()
{
     VM = new Computer(ProgramPath);
     int result = VM->execute();
     delete VM;
     return result;
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

