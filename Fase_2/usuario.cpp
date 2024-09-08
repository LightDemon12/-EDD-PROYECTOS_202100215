#include "usuario.h"

// Constructor
Usuario::Usuario(const std::string& nombres, const std::string& apellidos, const std::string& fechaNacimiento, const std::string& correoElectronico, const std::string& contrasena)
    : nombres(nombres), apellidos(apellidos), fechaNacimiento(fechaNacimiento), correoElectronico(correoElectronico), contrasena(contrasena) {}

// Getters
std::string Usuario::getNombres() const {
    return nombres;
}

std::string Usuario::getApellidos() const {
    return apellidos;
}

std::string Usuario::getFechaNacimiento() const {
    return fechaNacimiento;
}

std::string Usuario::getCorreoElectronico() const {
    return correoElectronico;
}

std::string Usuario::getContrasena() const {
    return contrasena;
}

// Setters
void Usuario::setNombres(const std::string& nombres) {
    this->nombres = nombres;
}

void Usuario::setApellidos(const std::string& apellidos) {
    this->apellidos = apellidos;
}

void Usuario::setFechaNacimiento(const std::string& fechaNacimiento) {
    this->fechaNacimiento = fechaNacimiento;
}

void Usuario::setCorreoElectronico(const std::string& correoElectronico) {
    this->correoElectronico = correoElectronico;
}

void Usuario::setContrasena(const std::string& contrasena) {
    this->contrasena = contrasena;
}
