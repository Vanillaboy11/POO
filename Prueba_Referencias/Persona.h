#pragma once
class Persona
{

protected:
	int edad=18;
	//char nombre[30]="Juan";
	char* nombre; //el nombre lo manejaremos en memoria dinamica
	void Reir() const;  //Un metodo const no puede modificar atributos
	void Comer()const;
public:
	//Constructores
	Persona();
	Persona(const char* el_nombre, int la_edad);
	//Destructor
	~Persona();
	void HacerReir(int motivo) const;
	//Existen metodos para modificar y acceder atributos que
	//estan protegidos del mundo exterior.
	//Estos metodos se llama setter, para modificar,
	//y getter para acceder.
	//El nombre de los metodos usualmente comienzan con Get o
	//Set, seguido del nombre del atributo.
	char* GetNombre() const;
	void SetNombre(const char* nuevo_nombre);
	//Las funciones pueden ser implementadas al momento de
	//ser declaradas. Este tipo de implementación se llama
	//implementacion inline. Si se utiliza se recomienda que
	//sea con funciones que tengan poco codigo.
	int GetEdad() const { return edad; };
	void SetEdad(int nueva_edad)
	{
		edad = (nueva_edad > 0) ? nueva_edad : edad;
	}
	
	void Saludar() const;
	void Liberar();
};

