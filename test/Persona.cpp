#include<iostream>
#include"Persona.h"
using std::cout;
using std::endl;

void Persona::Reir() {
	cout << "Jajajajaja..." << endl;
}

void Persona::Comer() {
	cout << "Nom, nom, nom..." << endl;
}

void Persona::Saludar() {
	cout << "Hola, soy " << nombre;
	cout << "y tengo" << edad << "anios" << endl;
}

int Persona::HacerReir(int motivo) {
	if ((motivo % 3) == 0) {
		Reir();
	}
	else {
		cout << ":|" << endl;
	}
}