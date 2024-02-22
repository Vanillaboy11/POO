// Referencias.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Persona.h"
using std::cout;
using std::endl;

const double PI = 3.1416;

void UsarPersona(Persona &persona) {
    cout << "----- Utilizando persona ------" << endl;
    persona.Saludar();
    persona.HacerReir(rand());
    cout << "--- Persona utilizada -----" << endl;
}


// cuando se recibe un parametro por referencia, existe la
// posibilidad de uqe la funcion modifique el parametro
// afectando a la variable que utilizamos al invocar la funcion.

void usarPersona2(const Persona& persona)
{
    cout << "--- usando otra vez a persona: " << persona.GetNombre();
    cout << "----------------" << endl;
    persona.Saludar();

    // si recibimos un parametro como const, no se pueden
    // invocar metodos que no sean const.
    
    // persona.SetNombre("Tilin");
    //persona.SetEdad(-20);
    persona.HacerReir(rand());
    cout << "------------------------------" << endl;

}

int main()
{
    
    
    srand(time(0));
    Persona persona1("Sempronio", 20);
    Persona persona2("AMLO", 72);
    Persona* persona3= new Persona("Abundio", 23);
    //persona3 = &persona1;
    persona1.Saludar();
    UsarPersona(persona2);
    UsarPersona(*persona3);

    usarPersona2(persona1);

    persona1.Saludar();


    cout << "Adios..." << endl;
    delete persona3;
}

