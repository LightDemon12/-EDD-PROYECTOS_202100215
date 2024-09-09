#ifndef REGISTRO_H
#define REGISTRO_H

#include <QWidget>
#include "arbolavl.h"
#include "matriz.h"

// Forward declaration
class MainView;

namespace Ui {
class Registro;
}

class Registro : public QWidget
{
    Q_OBJECT

public:
    explicit Registro(QWidget *parent = nullptr, ArbolAVL* arbol = nullptr, MainView* mainView = nullptr, MatrizDispersa* matriz = nullptr);
    ~Registro();

private slots:
    void on_ButtonRegistro_clicked();
    void on_ButtonSalir_clicked();

private:
    Ui::Registro *ui;
    ArbolAVL* arbol;
    MainView* mainView;
    MatrizDispersa* matriz;
    int contadorNodos; // Contador de nodos
};

#endif // REGISTRO_H
