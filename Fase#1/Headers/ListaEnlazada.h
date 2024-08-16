//
// Created by LightDemon12 on 08/08/2024.
//
#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H

#include "Usuarios.h"
#include "MatrizDispersa.h"
#include "ListaSolicitud.h"
#include <string>


class MatrizDispersa;
class ListaEnlazada {
private:
    Usuario* cabeza;
    MatrizDispersa* matrizUsuarios;
    ListaSolicitud listaSolicitudes; // Instancia de ListaSolicitud

public:
    ListaEnlazada();
    ~ListaEnlazada();
    void agregarNodo(Usuario* nuevoUsuario);
    void eliminarNodo(const std::string& correoElectronico);
    void imprimirLista() const;
    Usuario* buscarUsuario(const std::string& correoElectronico, const std::string& contrasena = "") const;
    int obtenerTamano() const;
    Usuario* getCabeza() const;
    void imprimirCorreosYNombres(const std::string& correoLogueado) const;
    void agregarObjetoAPila(const std::string& correo, const NodoPila& nodo); // Nuevo método
    bool existeEmisorEnPila(const std::string& correo, const std::string& emisor);
    void imprimirUsuarios() const;
    void crearRelacion(const std::string& correo1, const std::string& correo2); // Añadir esta línea
    bool existeRelacion(const std::string& correo1, const std::string& correo2); // Añadir esta línea
    // Nuevos métodos para manejar rechazos
    void agregarRechazo(const std::string& correoUsuario, const std::string& destinatario, const std::string& emisor);
    bool eliminarRechazo(const std::string& correoUsuario, const std::string& destinatario, const std::string& emisor);
    Solicitud* buscarRechazo(const std::string& correoUsuario, const std::string& destinatario, const std::string& emisor) const;
    void mostrarRechazos(const std::string& correoUsuario) const;
    void generarReporteRelacionesAmistad(const std::string& nombreArchivo) const;
    void generarReporteListaEnlazada(const std::string& nombreArchivo) const;
    void generarTopMenosAmigos(int topN) const;
    void generarReporteAmigosUsuario(const std::string& correo, const std::string& nombreArchivo) const;
    void generarReportePilaUsuario(const std::string& correo, const std::string& nombreArchivo) const; // Declaración de la función
    void generarReporteListaSolicitudes(const std::string& correo, const std::string& nombreArchivo) const; // Modificar la firma de la función
    void eliminarObjetosDePilaPorCorreoEmisor(const std::string& correoUsuario, const std::string& correoEmisor);



};

#endif // LISTAENLAZADA_H