#ifndef VENTANA_H
#define VENTANA_H

#include <QDialog>
#include "arbolavl.h"
#include "matriz.h"
#include "listarelaciones.h"
#include "listadoble.h"
#include "ArbolBinarioCompleto.h" // Incluye el archivo de cabecera del árbol binario completo

namespace Ui {
class ventana;
}

class ventana : public QDialog
{
    Q_OBJECT

public:
    explicit ventana(QWidget *parent = nullptr, ArbolAVL* arbol = nullptr, const QString& currentUserEmail = "", MatrizDispersa* matriz = nullptr, ListaRelaciones* listaRelaciones = nullptr, ListaDoble* listaDoble = nullptr, ArbolBinarioCompleto* arbolBinarioCompleto = nullptr);
    ~ventana();

private slots:
    void on_ButtonRegresar_clicked();

    void on_ButtonCrear_clicked();

    void on_ButtonSelecionar_clicked();

    void on_pushButton_clicked();

    void on_Buttonpubli_clicked();

    void on_ButtonComen_clicked();

    void on_ButtonOrden_clicked();

    void on_ButtonPreorden_clicked();

    void on_ButtonPostorden_clicked();

    void on_ButtonTop_clicked();

    void on_ButtonGraficar_clicked();

    void on_ButtonMostrarTopPublicaciones_clicked();

private:
    Ui::ventana *ui;
    ArbolAVL* arbol;
    QString currentUserEmail;
    MatrizDispersa* matriz;
    ListaRelaciones* listaRelaciones;
    ListaDoble* listaDoble;
    QString pathImagenSeleccionada;
    ArbolBinarioCompleto* arbolBinarioCompleto; // Referencia al árbol binario completo

};

#endif // VENTANA_H
