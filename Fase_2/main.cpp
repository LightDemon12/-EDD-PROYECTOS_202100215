#include <QApplication>
#include <QDebug>
#include "mainview.h"
#include "usuario.h"


#include <ctime> // Para obtener la fecha y hora actual

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Crear instancia de MainView
    MainView w;


    // Mostrar la ventana principal
    w.show();

    return a.exec();
}
