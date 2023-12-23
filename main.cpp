#include "mainwindow.h"

#include <QApplication>
#include <calcviewmodel.h>

int main(int argc, char *argv[])
{
    CalcViewModel viewModel;
    QApplication a(argc, argv);
    MainWindow w(nullptr, &viewModel);
    w.setWindowTitle("Калькулятор");
    w.show();
    return a.exec();
}
