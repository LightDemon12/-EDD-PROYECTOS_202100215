#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Usuario {
private:
    std::string nombres;
    std::string apellidos;
    std::string fechaNacimiento;
    std::string correoElectronico;
    std::string contrasena;

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

    // Métodos para agregar las estructuras de datos más adelante
    // void agregarListaEnlazadaSimple();
    // void agregarPila();
};

#endif // USUARIO_H
