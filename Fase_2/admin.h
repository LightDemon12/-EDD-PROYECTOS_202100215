#ifndef ADMIN_H
#define ADMIN_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "arbolavl.h"
#include "matriz.h"
#include "cargamasivausuarios.h"
#include "cargamasivasolicitudes.h"
#include "listarelaciones.h"
#include "listadoble.h"
#include "cargamasivapublicaciones.h"
#include "ArbolBinarioCompleto.h" // Incluye el archivo de cabecera del árbol binario completo
#include "Grafo.h" // Incluir la clase Grafo


namespace Ui {
class Admin;
}

class Admin : public QDialog
{
    Q_OBJECT

public:
    explicit Admin(QWidget *parent = nullptr, ArbolAVL* arbol = nullptr, MatrizDispersa* matriz = nullptr, ListaRelaciones* listaRelaciones = nullptr, ListaDoble* listaDoble = nullptr, ArbolBinarioCompleto* arbolBinarioCompleto = nullptr, Grafo* grafo = nullptr);
    ~Admin();
protected:
    void wheelEvent(QWheelEvent* event) override; // Sobrescribir el evento de la rueda del ratón

private slots:
    void on_ButtonCU_clicked();
    void on_ButtonCS_clicked();

    void on_pushButton_clicked();

    void on_ButtonCPlu_clicked();

    void on_ButtonCerrar_clicked();

    void on_ButtonAVL_clicked();

    void on_ButtonAVL_2_clicked();

    void on_ButtonenOrden_clicked();

    void on_ButtonpostOrden_clicked();

    void on_ButtonpreOrden_clicked();

    void on_Buttonmostrar_clicked();

    void on_ButonBuscar_clicked();

    void on_ButtonGrafo_clicked();

    void on_ButtonLista_clicked();

    void on_pushButton1_clicked();

private:
    Ui::Admin *ui;
    ArbolAVL* arbol;
    MatrizDispersa* matriz;
    CargaMasivaUsuarios* cargaMasivaUsuarios;
    CargaMasivaSolicitudes* cargaMasivaSolicitudes;
    ListaRelaciones* listaRelaciones; // Agregar puntero a ListaRelaciones
    ListaDoble* listaDoble; // Agregar puntero a ListaDoble
    CargaMasivaPublicaciones* cargaMasivaPublicaciones; // Agregar puntero a CargaMasivaPublicaciones
    ArbolBinarioCompleto* arbolBinarioCompleto; // Agregar puntero a ArbolBinarioCompleto
    Grafo* grafo; // Agregar el grafo
    QGraphicsScene* scene; // Agregar la escena gráfica
    QGraphicsPixmapItem* pixmapItem; // Agregar el item del pixmap

};

#endif // ADMIN_H
