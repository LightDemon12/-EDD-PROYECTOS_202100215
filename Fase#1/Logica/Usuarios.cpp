// Usuarios.cpp
#include "../Headers/Usuarios.h"
#include <iostream>
using namespace std;

// Constructor para inicializar un nodo de usuario
Usuario::Usuario(int id, string nom, string ape, string fechaNac, string correo, string contra)
    : id(id), nombres(nom), apellidos(ape), fechaNacimiento(fechaNac), correoElectronico(correo), contrasena(contra), siguiente(nullptr) {}

// Función para imprimir la información de un usuario
void imprimirUsuario(const Usuario& usuario) {
    std::cout << "*******************************" << std::endl;
    cout << "ID: " << usuario.id << endl;
    cout << "Nombres: " << usuario.nombres << endl;
    cout << "Apellidos: " << usuario.apellidos << endl;
    cout << "Fecha de Nacimiento: " << usuario.fechaNacimiento << endl;
    cout << "Correo Electrónico: " << usuario.correoElectronico << endl;
    cout << "Contraseña: " << usuario.contrasena << endl;
    std::cout << "*******************************" << std::endl;

    // Imprimir elementos de la pila personal del usuario
    cout << "Elementos en la pila personal: ";
    Pila pila = usuario.pilaPersonal;
    while (!pila.empty()) {
        cout << pila.top() << " ";
        pila.pop();
    }
    cout << endl;

    // Imprimir solicitudes de amistad del usuario
    cout << "Solicitudes de amistad: " << endl;
    usuario.listaSolicitudes.mostrarSolicitudes();
}

void Usuario::agregarSolicitud(const std::string& receptor, const std::string& emisor, const std::string& estado) {
    listaSolicitudes.agregarSolicitud(receptor, emisor, estado);
    std::cout << "*******************************" << std::endl;
    std::cout << "Solicitud agregada: Receptor=" << receptor << ", Emisor=" << emisor << ", Estado=" << estado << std::endl; // Mensaje de depuración
    std::cout << "*******************************" << std::endl;
}

void Usuario::agregarRechazo(const std::string& emisor, const std::string& receptor) {
    listaRechazos.agregarRechazo(receptor, emisor);
    std::cout << "*******************************" << std::endl;
    std::cout << "Rechazo agregado: Emisor=" << emisor << ", Receptor=" << receptor << std::endl; // Mensaje de depuración
    std::cout << "*******************************" << std::endl;
}
void Usuario::generarReporteListaSolicitud(const std::string& nombreArchivo) const {
    listaSolicitudes.generarReporteListaSolicitud(correoElectronico, nombreArchivo);
}