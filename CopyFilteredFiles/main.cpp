#include "getcppsrcfiles.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GetCppSrcFiles w;
    w.show();
    return a.exec();
}
