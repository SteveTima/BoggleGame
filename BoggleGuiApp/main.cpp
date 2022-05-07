#include "boggleguiapp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BoggleGuiApp w;
    w.show();
    return a.exec();
}
