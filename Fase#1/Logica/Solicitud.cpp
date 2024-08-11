//
// Created by LightDemon12 on 10/08/2024.
//
#include "../Headers/Solicitud.h"

// Constructor para inicializar los atributos del nodo
Solicitud::Solicitud(string dest, string emi, string est) : destinatario(dest), emisor(emi), estado(est), siguiente(nullptr) {}