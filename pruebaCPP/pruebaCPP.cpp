// PruebaCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Persona.h"
using std::cout;
using std::endl;

void Foo() {
    Persona persona_local("Jilvherto", 15);
    persona_local.Saludar();
    if (true) {
        Persona otra("Juaquin", 45);
        otra.HacerReir(rand());
    }
}

int main()
{
    srand(time(0));

    Foo();
   //Creamos objetos de clase Persona.
    //LOs objetos se pueden crear de 2 formas: estatica y dinamica
    //En la forma estatica, se declara como cualquier variable
    //en la cual el tipo es la clase
    Persona la_persona("Sosimo",19);
    //la_persona es un objeto de tipo Persona, tiene nombre,
    //edad y el comportamiento declarado para una persona.
    //La segunda forma es la forma dinamica, el objeto
    //se debe crear en memoria dinamica por medio del
    //operador new.
    //new devuelve la direccion de memoria del objeto recien
    //creado en el heap. Necesitamos un apuntador para almacenar
    //la direccion y poder acceder al objeto
    Persona* otra_persona;
    //Todavia no existe objeto nuevo en este punto
    otra_persona=new Persona("Nicanor",25);

    //La principal diferencia entre los objetos en memoria estatica
    //y los objetos en memoria dinamica es que los objetos estaticos
    //se eliminan automaticamente de memoria una vez que finaliza
    //el bloque de codigo en el cual fueron creados (igual que
    //las variables locales), los objetos en memoria dinamica
    //se tienen que eliminar explicitamente con el operador delete


    //Para utilizar el objeto, podemos acceder a sus miembros
    //(variables o funciones) por medio de los mismos operadores
    //que utilizamos en las estructuras.
    // . cuando es estatico
    // -> cuando es apuntador
    la_persona.Saludar();
    la_persona.HacerReir(rand());

    otra_persona->Saludar();

    Persona tercer_persona("Maria Espergencia de la Luz del ninio Jesus McGregor",28);

    tercer_persona.Saludar();
    
    
    
    delete otra_persona;//elimina de memoria el objeto
}

