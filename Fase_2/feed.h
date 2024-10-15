#ifndef FEED_H
#define FEED_H

#include <QDialog>
#include "arbolavl.h" // Incluir la cabecera del árbol AVL
#include "pila.h"
#include "listaenviados.h"
#include "matriz.h"
#include "listarelaciones.h" // Incluir la cabecera de ListaRelaciones
#include "listadoble.h"
#include "ventana.h" // Incluir la cabecera de la nueva ventana
#include "ArbolBinarioCompleto.h" // Incluye el archivo de cabecera del árbol binario completo
#include "Grafo.h"
#include <QWheelEvent>
#include <QGraphicsScene>


namespace Ui {
class Feed;
}

class Feed : public QDialog
{
    Q_OBJECT

public:
    explicit Feed(QWidget *parent, ArbolAVL* arbol, const QString& currentUserEmail, MatrizDispersa* matriz, ListaRelaciones* listaRelaciones, ListaDoble* listaDoble,ArbolBinarioCompleto* arbolBinarioCompleto = nullptr, Grafo* grafo = nullptr);
    ~Feed();
    void setCurrentUserEmail(const QString& email); // Declarar el método para actualizar el correo electrónico del usuario actual
protected:
    void wheelEvent(QWheelEvent* event) override;

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

    void on_ButtonPublicaciones_clicked();

    void on_ButtonSugerenias_clicked();

    void on_Mostrar_clicked();

    void on_Actualizar_clicked();

private:
    Ui::Feed *ui;
    ArbolAVL* arbol; // Puntero al árbol AVL
    MatrizDispersa* matriz; // Declarar el puntero a MatrizDispersa
    QString currentUserEmail; // Variable para almacenar el correo electrónico del usuario actual
    Pila pila; // Agregar la pila
    ListaEnviados listaEnviados; // Agregar la lista enlazada
    ListaRelaciones* listaRelaciones; // Cambiar a puntero
    ListaDoble* listaDoble; // Puntero a ListaDoble
    ventana *ventana; // Declarar un puntero a la nueva ventana
    ArbolBinarioCompleto* arbolBinarioCompleto; // Referencia al árbol binario completo
    Grafo* grafo;
    QGraphicsScene* scene; // Agregar la escena gráfica


};

#endif // FEED_H
