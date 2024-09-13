#ifndef FEED_H
#define FEED_H

#include <QDialog>
#include "arbolavl.h" // Incluir la cabecera del árbol AVL
#include "pila.h"
#include "listaenviados.h"
#include "matriz.h"
#include "listarelaciones.h" // Incluir la cabecera de ListaRelaciones
#include "listadoble.h"


namespace Ui {
class Feed;
}

class Feed : public QDialog
{
    Q_OBJECT

public:
    explicit Feed(QWidget *parent, ArbolAVL* arbol, const QString& currentUserEmail, MatrizDispersa* matriz, ListaRelaciones* listaRelaciones, ListaDoble* listaDoble);
    ~Feed();
    void setCurrentUserEmail(const QString& email); // Declarar el método para actualizar el correo electrónico del usuario actual

private slots:
    void on_ButtonBuscar_clicked();

    void on_ButtonMostrar_clicked();

    void on_ButtonEliminar_clicked();

    void on_ButtonCerrar_clicked();

    void on_Buttonmostrar_clicked();

    void on_Buttonlista_clicked();

    void on_ButtonEnviar_clicked();

    void on_ButtonActualizar_clicked();

    void on_ButtonPila_clicked();

    void on_ButtonCancelar_clicked();

    void on_ButtonRechazar_clicked();

    void on_ButtonAceptar_clicked();

private:
    Ui::Feed *ui;
    ArbolAVL* arbol; // Puntero al árbol AVL
    MatrizDispersa* matriz; // Declarar el puntero a MatrizDispersa
    QString currentUserEmail; // Variable para almacenar el correo electrónico del usuario actual
    Pila pila; // Agregar la pila
    ListaEnviados listaEnviados; // Agregar la lista enlazada
    ListaRelaciones* listaRelaciones; // Cambiar a puntero
    ListaDoble* listaDoble; // Puntero a ListaDoble


};

#endif // FEED_H
