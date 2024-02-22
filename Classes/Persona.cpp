#define _CRT_SECURE_NO_WARNINGS
#include "Persona.h"
#include<iostream>
#include<string.h>
using std::cout;
using std::endl;

void Persona::Reir() {
	cout << "Jajajaja" << endl;
}

void Persona::Comer()
{
	cout << "Nom, nom, nom...." << endl;
}

Persona::Persona()
{
	// los constructores se utilizan para inicializar
	//atributos y reservar recursos que pudiera
	//utilizar el objeto.
	edad = 20;
	//Necesitamos reservar memoria para el nombre
	nombre = (char *)malloc(7);
	strncpy(nombre, "Sosimo",6);
	nombre[6] = 0;
}

Persona::Persona(const char* el_nombre, int la_edad)
{
	edad = la_edad;
	//Necesitamos reservar memoria para el nombre
	nombre = (char*)malloc(strlen(el_nombre)+1);
	strncpy(nombre,  el_nombre, strlen(el_nombre));
	nombre[strlen(el_nombre)] = 0;
}

void Persona::HacerReir(int motivo)
{
	if ((motivo % 3) == 0) {
		Reir();
    }
	else
		cout << ":|" << endl;
}

char* Persona::GetNombre() const
{
	return nombre;
}

void Persona::SetNombre(const char* nuevo_nombre)
{
	free(nombre);
	nombre = (char*)malloc(strlen(nuevo_nombre) + 1);
	strncpy(nombre, nuevo_nombre, strlen(nuevo_nombre));
	nombre[strlen(nuevo_nombre)] = 0;
}

void Persona::Saludar() const
{
	cout << "Hola, yo soy " << nombre;
	cout << " y tengo " << edad << " anios"<<endl;
}

void Persona::Liberar()
{
	free(nombre);
	nombre = nullptr;
}

Persona::~Persona() const
{
	if (nombre != nullptr) {

		cout << "Ejecutando destructor de " << nombre << "..." << endl;
		free(nombre);
	}
}


