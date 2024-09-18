#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QLineEdit>
#include "arbolavl.h"
#include "matriz.h"
#include <QMessageBox>
#include "feed.h" // Incluir la cabecera de la nueva ventana Feed
#include "admin.h" // Incluir la cabecera de Admin
#include "listarelaciones.h"
#include "listadoble.h"
#include "ArbolBinarioCompleto.h" // Incluye el archivo de cabecera del árbol binario completo

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
    void insertarUsuario(Usuario* usuario);

private slots:
    void on_Registro_clicked();

    void on_Inicio_clicked();

private:
    Ui::MainView *ui;
    Registro *registro;
    Admin *adminWindow; // Puntero a la ventana Admin
    Feed *feed; // Declarar un puntero a la ventana Feed
    ArbolAVL arbol;
    MatrizDispersa matriz;
    ListaRelaciones listaRelaciones; // Declarar listaRelaciones
    QString currentUserEmail; // Variable para almacenar el correo electrónico del usuario actual
    ListaDoble listaDoble; // Declarar la lista doblemente enlazada
    ArbolBinarioCompleto arbolBinarioCompleto; // Inicializa el árbol binario completo

};

#endif // MAINVIEW_H
