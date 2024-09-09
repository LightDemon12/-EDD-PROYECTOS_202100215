#include "registro.h"
#include "ui_registro.h"
#include "mainview.h"
#include <QMessageBox>
#include <QDebug>

Registro::Registro(QWidget *parent, ArbolAVL* arbol, MainView* mainView, MatrizDispersa* matriz)
    : QWidget(parent)
    , ui(new Ui::Registro)
    , arbol(arbol)
    , mainView(mainView)
    , matriz(matriz)
    , contadorNodos(0) // Inicializar el contador de nodos
{
    ui->setupUi(this);
    qDebug() << "Registro window created";
}

Registro::~Registro()
{
    delete ui;
}

void Registro::on_ButtonRegistro_clicked()
{
    qDebug() << "ButtonRegistro clicked";

    // Obtener los datos de los QLineEdit y QDateEdit
    QString nombre = ui->lineNombre->text();
    QString apellido = ui->lineApellido->text();
    QString correo = ui->lineCorreo->text();
    QString contrasena = ui->lineContra->text();
    QString fechaNacimiento = ui->dateFecha->date().toString("dd/MM/yyyy");

    // Verificar si algún campo está vacío
    if (nombre.isEmpty() || apellido.isEmpty() || correo.isEmpty() || contrasena.isEmpty() || fechaNacimiento.isEmpty()) {
        QMessageBox::warning(this, "Error", "Todos los campos deben estar llenos.");
        return;
    }

    // Verificar si el correo ya está registrado
    if (arbol->buscar(correo.toStdString())) {
        QMessageBox::warning(this, "Error", "El correo ya está registrado.");
        return;
    }

    // Crear un nuevo usuario
    Usuario* nuevoUsuario = new Usuario(nombre.toStdString(), apellido.toStdString(), fechaNacimiento.toStdString(), correo.toStdString(), contrasena.toStdString());

    // Insertar el usuario en el árbol AVL
    arbol->insertar(nuevoUsuario);

    // Determinar la posición en la matriz dispersa
    matriz->setValor(contadorNodos, contadorNodos, correo.toStdString());
    contadorNodos++; // Incrementar el contador de nodos

    // Mostrar el recorrido en preorden del árbol AVL
    qDebug() << "Usuarios en el árbol AVL (enOrden):";
    arbol->enOrden(arbol->getRaiz());
}

void Registro::on_ButtonSalir_clicked()
{
    // Mostrar la ventana principal
    if (mainView) {
        mainView->show();
    }

    // Cerrar la ventana de registro
    this->close();
}
