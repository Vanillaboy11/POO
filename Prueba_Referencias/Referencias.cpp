// Referencias.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Persona.h"
using std::cout;
using std::endl;



void UsarPersona(Persona &persona) {
    cout << "----- Utilizando persona ------" << endl;
    
    persona.Saludar();
    persona.HacerReir(rand());
    cout << "--- Persona utilizada -----" << endl;
}

//Cuando se recibe un parametro por referencia, existe la
//posibilidad de que la funcion modifique el parametro
//afectando a la variable que utilizamos al invocar la funcion.

void UsarPersona2(const Persona& persona) {
    cout << "---- usando otra vez a persona: " << persona.GetNombre();
    cout << "----------------" << endl;
    persona.Saludar();
   //Si recibimos un parametro como const, no se pueden
   // invocar metodos que no sean const.
   // persona.SetNombre("Ifigenia");
   // persona.SetEdad(-20);
    persona.HacerReir(rand());
    cout << "------------------------------------------" << endl;
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

    UsarPersona2(persona1);

    persona1.Saludar();


    cout << "Adios..." << endl;
    delete persona3;
}

