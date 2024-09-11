#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "listaenviados.h"
#include "pila.h"

class Usuario {
private:
    std::string nombres;
    std::string apellidos;
    std::string fechaNacimiento;
    std::string correoElectronico;
    std::string contrasena;
    ListaEnviados listaEnviados; // Agregar la lista enlazada
    Pila pila; // Agregar la pila

public:
    // Constructor
    Usuario(const std::string& nombres, const std::string& apellidos, const std::string& fechaNacimiento, const std::string& correoElectronico, const std::string& contrasena);

    // Getters
    std::string getNombres() const;
    std::string getApellidos() const;
    std::string getFechaNacimiento() const;
    std::string getCorreoElectronico() const;
    std::string getContrasena() const;

    // Setters
    void setNombres(const std::string& nombres);
    void setApellidos(const std::string& apellidos);
    void setFechaNacimiento(const std::string& fechaNacimiento);
    void setCorreoElectronico(const std::string& correoElectronico);
    void setContrasena(const std::string& contrasena);

    // Métodos para acceder a las estructuras de datos
    ListaEnviados& getListaEnviados();
    Pila& getPila();
};

#endif // USUARIO_H
