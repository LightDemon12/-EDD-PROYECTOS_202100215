#ifndef NODOB_H
#define NODOB_H

#include <string>

class NodoB {
public:
    static const int T = 5; // Orden del árbol B

    NodoB(bool esHoja);

    // Atributos del nodo
    std::string correos[2 * T - 1]; // Lista de correos
    std::string contenidos[2 * T - 1]; // Lista de contenidos
    std::string fechas[2 * T - 1]; // Lista de fechas
    std::string horas[2 * T - 1]; // Lista de horas

    // Punteros a los hijos
    NodoB* hijos[2 * T];

    // Indica si el nodo es una hoja
    bool esHoja;

    // Número actual de claves en el nodo
    int numClaves;

    // Métodos para manejar el nodo
    void insertarNoLleno(const std::string& correo, const std::string& contenido, const std::string& fecha, const std::string& hora);
    void dividirHijo(int i, NodoB* y);
    // Método auxiliar para comparar fecha y hora
    bool esMenor(const std::string& fecha1, const std::string& hora1, const std::string& fecha2, const std::string& hora2);
private:

};

#endif // NODOB_H
