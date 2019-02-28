#include "editor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Editor w(argc, argv);

    return a.exec();
}
