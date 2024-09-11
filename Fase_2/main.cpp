#include <QApplication>
#include "mainview.h"
#include "usuario.h" // Incluir la cabecera de Usuario

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Crear instancia de MainView
    MainView w;

    // Crear algunos usuarios y agregarlos al árbol AVL
    Usuario* usuario1 = new Usuario("Juan", "Perez", "01/01/1990", "b", "b");
    Usuario* usuario2 = new Usuario("Maria", "Gomez", "02/02/1985", "maria.gomez@example.com", "password456");
    Usuario* usuario3 = new Usuario("Carlos", "Lopez", "03/03/1975", "a", "a");

    w.insertarUsuario(usuario1);
    w.insertarUsuario(usuario2);
    w.insertarUsuario(usuario3);

    // Mostrar la ventana principal
    w.show();

    return a.exec();
}
