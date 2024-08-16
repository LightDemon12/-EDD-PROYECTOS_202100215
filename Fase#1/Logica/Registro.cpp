#include "../Headers/Registro.h"
#include <iostream>
#include <sstream> // Incluir para std::istringstream
#include <limits>  // Incluir para std::numeric_limits

using namespace std;

// Función para registrar un nuevo usuario
void registrarUsuario(ListaEnlazada& lista) {
    string nombres, apellidos, fechaNacimiento, correo, contrasena;

    // Solicitar los datos del usuario
    std::cout << "*******************************" << std::endl;
    cout << "Ingrese sus nombres: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer de entrada
    getline(cin, nombres);
    cout << "Ingrese sus apellidos: ";
    getline(cin, apellidos);
    cout << "Ingrese su fecha de nacimiento (YYYY/MM/DD): ";
    getline(cin, fechaNacimiento);
    cout << "Ingrese su correo electrónico: ";
    getline(cin, correo);
    cout << "Ingrese su contraseña: ";
    getline(cin, contrasena);
    std::cout << "*******************************" << std::endl;
    // Verificar si el correo ya existe en la lista
    Usuario* usuarioExistente = lista.buscarUsuario(correo, "");
    if (usuarioExistente != nullptr) {
        cout << "El correo electrónico ya está registrado." << endl;
        return;
    }

    // Validar la fecha de nacimiento
    int anio, mes, dia;
    char sep1, sep2;
    istringstream fechaStream(fechaNacimiento);
    if (!(fechaStream >> anio >> sep1 >> mes >> sep2 >> dia) || sep1 != '/' || sep2 != '/' || fechaStream.fail()) {
        cout << "Formato de fecha de nacimiento inválido. Use el formato YYYY/MM/DD." << endl;
        return;
    }

    if (anio < 1900 || anio > 2024) {
        cout << "El año de nacimiento debe estar entre 1900 y 2024." << endl;
        return;
    }

    if (mes < 1 || mes > 12) {
        cout << "El mes de nacimiento debe estar entre 1 y 12." << endl;
        return;
    }

    if (dia < 1 || dia > 31) {
        cout << "El día de nacimiento debe estar entre 1 y 31." << endl;
        return;
    }

    // Validar la contraseña (ejemplo: al menos 6 caracteres)
    if (contrasena.length() < 0) {
        cout << "La contraseña debe tener al menos 6 caracteres." << endl;
        return;
    }

    // Asignar un nuevo ID basado en el tamaño de la lista
    int nuevoId = lista.obtenerTamano() + 1;

    // Crear un nuevo usuario y agregarlo a la lista
    Usuario* nuevoUsuario = new Usuario(nuevoId, nombres, apellidos, fechaNacimiento, correo, contrasena);
    lista.agregarNodo(nuevoUsuario);
    cout << "Usuario registrado exitosamente." << endl;
}