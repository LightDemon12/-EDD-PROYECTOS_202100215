#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include "arbolavl.h"
#include "matriz.h"
#include <QMessageBox>
#include "feed.h" // Incluir la cabecera de la nueva ventana Feed

// Forward declaration
class Registro;

QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    MainView(QWidget *parent = nullptr);
    ~MainView();

private slots:
    void on_Registro_clicked();

    void on_Inicio_clicked();

private:
    Ui::MainView *ui;
    Registro *registro;
    Feed *feed; // Declarar un puntero a la ventana Feed
    ArbolAVL arbol;
    MatrizDispersa matriz;

};

#endif // MAINVIEW_H
