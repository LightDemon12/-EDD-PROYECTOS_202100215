#include "ventana.h"
#include "ui_ventana.h"
#include "mainview.h"
#include <QDateTime>
#include <QFileDialog>
#include <QPixmap>
#include <cstdlib> // Para std::system

ventana::ventana(QWidget *parent, ArbolAVL* arbol, const QString& currentUserEmail, MatrizDispersa* matriz, ListaRelaciones* listaRelaciones, ListaDoble* listaDoble, ArbolBinarioCompleto* arbolBinarioCompleto) :
    QDialog(parent),
    ui(new Ui::ventana),
    arbol(arbol),
    currentUserEmail(currentUserEmail),
    matriz(matriz),
    listaRelaciones(listaRelaciones),
    listaDoble(listaDoble),
    arbolBinarioCompleto(arbolBinarioCompleto), // Inicializa el árbol binario completo
    pathImagenSeleccionada("") // Inicializa el path de la imagen seleccionada

{
    ui->setupUi(this);
    // Configurar la tabla para mostrar el árbol binario
    ui->tablepubli->setColumnCount(6);
    QStringList headers = {"Índice", "Correo", "Contenido", "Fecha", "Hora", "Path Imagen"};
    ui->tablepubli->setHorizontalHeaderLabels(headers);
    // Configurar la tabla para mostrar los comentarios
    ui->tablecomen->setColumnCount(1);
    QStringList commentHeaders = {"Comentario"};
    ui->tablecomen->setHorizontalHeaderLabels(commentHeaders);
}


ventana::~ventana()
{
    delete ui;
}


void ventana::on_ButtonRegresar_clicked()
{
    // Llamar al método eliminarTodosLosNodos de ArbolBinarioCompleto
    arbolBinarioCompleto->eliminarTodosLosNodos();
    this->close();
}

void ventana::on_ButtonCrear_clicked()
{
    QString contenido = ui->ContenidoTxt->toPlainText();
    QString correo = currentUserEmail;
    QString fecha = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString hora = QDateTime::currentDateTime().toString("HH:mm");

    listaDoble->insertar(correo.toStdString(), contenido.toStdString(), fecha.toStdString(), hora.toStdString(), pathImagenSeleccionada.toStdString());

    qDebug() << "Publicación creada - Correo:" << correo << ", Contenido:" << contenido << ", Fecha:" << fecha << ", Hora:" << hora << ", Imagen:" << pathImagenSeleccionada;

    // Limpiar el contenido del QTextEdit
    ui->ContenidoTxt->clear();
}

void ventana::on_ButtonSelecionar_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Seleccionar Imagen"), "", tr("Imágenes (*.png *.xpm *.jpg *.jpeg *.bmp)"));
    if (!fileName.isEmpty()) {
        pathImagenSeleccionada = fileName;
        QPixmap pixmap(fileName);
        QPixmap scaledPixmap = pixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->labelimagen->setPixmap(scaledPixmap);
        qDebug() << "Imagen seleccionada:" << fileName;
    }
}

void ventana::on_pushButton_clicked()
{
    // Obtener la fecha del QDateEdit
    QDate fecha = ui->dateEdit->date();
    QString fechaStr = fecha.toString("yyyy-MM-dd");

    // Limpiar el árbol binario antes de insertar nuevas publicaciones
    arbolBinarioCompleto->eliminarTodosLosNodos();

    // Pasar las publicaciones de la fecha específica al árbol binario
    listaDoble->pasarAlArbolBinarioPorFecha(*arbolBinarioCompleto, fechaStr.toStdString());

    // Mostrar las publicaciones en la QTableWidget
    arbolBinarioCompleto->mostrarEnTabla(ui->tablepubli);
}

void ventana::on_Buttonpubli_clicked()
{
    // Obtener el índice de la publicación desde el QLineEdit
    bool ok;
    int indice = ui->linepubli->text().toInt(&ok);
    if (!ok) {
        qDebug() << "Índice no válido";
        return;
    }

    // Buscar la publicación por índice en el árbol binario
    NodoBinarioCompleto* nodo = arbolBinarioCompleto->buscarPorIndice(indice);
    if (nodo == nullptr) {
        qDebug() << "Publicación no encontrada";
        return;
    }

    // Mostrar el contenido de la publicación en PubliTxt
    ui->PubliTxt->setPlainText(QString::fromStdString(nodo->contenido));

    // Mostrar la imagen si existe
    if (!nodo->pathimagen.empty()) {
        QPixmap pixmap(QString::fromStdString(nodo->pathimagen));
        QPixmap scaledPixmap = pixmap.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->labelpubli->setPixmap(scaledPixmap);
    } else {
        ui->labelpubli->clear();
    }

    // Buscar la publicación en la ListaDoble
    NodoLista* nodoLista = listaDoble->buscar(nodo->correo, nodo->contenido, nodo->fecha, nodo->hora);
    if (nodoLista == nullptr) {
        qDebug() << "Publicación no encontrada en la ListaDoble";
        return;
    }

    // Mostrar los comentarios en la QTableWidget
    ui->tablecomen->setRowCount(0); // Limpiar la tabla de comentarios
    nodoLista->comentarios.mostrarEnTabla(ui->tablecomen);
}

void ventana::on_ButtonComen_clicked()
{
    // Obtener el comentario del QLineEdit
    QString comentario = ui->Comentar->text();
    if (comentario.isEmpty()) {
        qDebug() << "Comentario vacío";
        return;
    }

    // Obtener el índice de la publicación desde el QLineEdit
    bool ok;
    int indice = ui->linepubli->text().toInt(&ok);
    if (!ok) {
        qDebug() << "Índice no válido";
        return;
    }

    // Buscar la publicación por índice en el árbol binario
    NodoBinarioCompleto* nodo = arbolBinarioCompleto->buscarPorIndice(indice);
    if (nodo == nullptr) {
        qDebug() << "Publicación no encontrada";
        return;
    }

    // Buscar la publicación en la ListaDoble
    NodoLista* nodoLista = listaDoble->buscar(nodo->correo, nodo->contenido, nodo->fecha, nodo->hora);
    if (nodoLista == nullptr) {
        qDebug() << "Publicación no encontrada en la ListaDoble";
        return;
    }

    // Insertar el comentario en el árbol B de la publicación
    nodoLista->comentarios.insertar(nodo->correo, comentario.toStdString(), nodo->fecha, nodo->hora);

    // Mostrar los comentarios actualizados en la QTableWidget
    ui->tablecomen->setRowCount(0); // Limpiar la tabla de comentarios
    nodoLista->comentarios.mostrarEnTabla(ui->tablecomen);

    // Ajustar el tamaño de las columnas al contenido
    ui->tablecomen->resizeColumnsToContents();

    // Limpiar el QLineEdit de comentario
    ui->Comentar->clear();
}

void ventana::on_ButtonOrden_clicked()
{
    int limite = ui->lineEditLimite->text().toInt();
    arbolBinarioCompleto->mostrarInordenLimitado(ui->tablepubli, limite);
    ui->tablepubli->resizeColumnsToContents();
}


void ventana::on_ButtonPreorden_clicked()
{
    int limite = ui->lineEditLimite->text().toInt();
    arbolBinarioCompleto->mostrarPreordenLimitado(ui->tablepubli, limite);
    ui->tablepubli->resizeColumnsToContents();
}


void ventana::on_ButtonPostorden_clicked()
{
    int limite = ui->lineEditLimite->text().toInt();
    arbolBinarioCompleto->mostrarPostordenLimitado(ui->tablepubli, limite);
    ui->tablepubli->resizeColumnsToContents();
}


void ventana::on_ButtonTop_clicked()
{
    if (listaDoble == nullptr) {
        QMessageBox::warning(this, "Error", "La lista doblemente enlazada no está inicializada.");
        return;
    }

    int topN = 5; // Número de fechas a mostrar
    auto topFechas = listaDoble->obtenerTopFechasConMasPublicaciones(topN);

    QString mensaje = "Top " + QString::number(topN) + " fechas con más publicaciones:\n";
    for (const auto& fecha : topFechas) {
        mensaje += QString::fromStdString(fecha.first) + ": " + QString::number(fecha.second) + " publicaciones\n";
    }

    QMessageBox::information(this, "Top Fechas", mensaje);

}


void ventana::on_ButtonGraficar_clicked()
{
    if (arbolBinarioCompleto == nullptr) {
        QMessageBox::warning(this, "Error", "El árbol binario no está inicializado.");
        return;
    }

    try {
        std::string nombreArchivo = "arbol.dot";
        arbolBinarioCompleto->graficarArbol(nombreArchivo);

        // Comando para generar la imagen del gráfico usando Graphviz
        std::string comando = "dot -Tpng " + nombreArchivo + " -o arbol.png";
        int resultado = std::system(comando.c_str());

        if (resultado == 0) {
            // Cargar la imagen en un QPixmap
            QPixmap pixmap("arbol.png");
            if (!pixmap.isNull()) {
                // Establecer el QPixmap en el QLabel
                ui->labelGrafico->setPixmap(pixmap);
                ui->labelGrafico->setScaledContents(true); // Escalar la imagen para que se ajuste al QLabel
                QMessageBox::information(this, "Éxito", "El árbol binario ha sido graficado exitosamente en arbol.png.");
            } else {
                QMessageBox::warning(this, "Error", "No se pudo cargar la imagen generada.");
            }
        } else {
            QMessageBox::warning(this, "Error", "Hubo un error al intentar graficar el árbol binario.");
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

void ventana::on_ButtonMostrarTopPublicaciones_clicked()
{
    if (listaDoble == nullptr) {
        QMessageBox::warning(this, "Error", "La lista doblemente enlazada no está inicializada.");
        return;
    }

    int topN = 3; // Número de publicaciones a mostrar
    auto topPublicaciones = listaDoble->obtenerTopPublicacionesConMasComentarios(topN);

    QString mensaje = "Top " + QString::number(topN) + " publicaciones con más comentarios:\n";
    for (const auto& publicacion : topPublicaciones) {
        mensaje += "Correo: " + QString::fromStdString(publicacion->correo) + ", Contenido: " + QString::fromStdString(publicacion->contenido) + ", Fecha: " + QString::fromStdString(publicacion->fecha) + ", Hora: " + QString::fromStdString(publicacion->hora) + ", Comentarios: " + QString::number(publicacion->comentarios.contarComentarios()) + "\n";
    }

    QMessageBox::information(this, "Top Publicaciones", mensaje);
}

