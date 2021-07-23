/*
Desarrollar un programa veterinario:
Mascota: nombre, edad, especie(perro,gato,conejo), sexo, celular de contacto
Operaciones: registrar y modificar
Reportes:
1.dato un celular mostrar datos de la mascota
2.dada una especie listar las mascotas registradas
3.estadisticas de mascotas registradas: cantidad por especie, cantidad por sexo
Adicional:
Validad q el nombre no se repita

*/

#include "basicas.CPP"

#define MAXNUM 10
#define DELTA 2

class Mascota{
  private:
	char nombre[MAX];
   	int edad;
   	char especie;
   	char sexo;
   	char celular[MAXNUM];

  public:
	Mascota()
	{
   		this->nombre[0] = NULL;
   		this->edad = 0;
      	this->especie = NULL;
		this->sexo = NULL;
      	this->celular[0] = NULL;
	}

   	void leer()
	{
   		cout << "Edad : "; 
		cin >> this->edad;
      	this->especie = leeCaracter(" P: Perro"," G: Gato"," C: Conejo",'P','G','C',"Especie : ");
      	this->sexo = leeCaracter(" H: Hembra"," M: Macho","\0",'H','M','\0',"Sexo : ");
      	do
		{
      		cout << "Celular de contacto(9 digitos) : "; 
			cin >> this->celular;
      	}while(!(strlen(celular)==MAXNUM-1));
   	}

   	void getDescripcionSexo(char *sexo)
	{
   		if(this->sexo=='H')
		{
      		strcpy(sexo,"Hembra");
      	}
      	if(this->sexo=='M')
		{
       		strcpy(sexo,"Macho");
      	}
   	}

   	void getDescripcionEspecie(char *especie)
   	{
   		if(this->especie=='P')
		{
      		strcpy(especie,"Perro");
      	}
      	if(this->especie=='G')
		{
       		strcpy(especie,"Gato");
      	}
      	if(this->especie=='C')
		{
       		strcpy(especie,"Conejo");
      	}
   	}

   	char *getNombre()
	{
   		return this->nombre;
   	}

   	void *getNombre(char *auxNombre)
	{
   		strcpy(auxNombre,this->nombre);
   	}

   	void setNombre(char *auxNombre)
	{
   		strcpy(this->nombre,auxNombre);
   	}

   	int getEdad()
	{
   		return this->edad;
   	}

   	void *getCelular(char *auxCelular)
	{
   		strcpy(auxCelular,this->celular);
   	}

   	char getEspecie()
	{
   		return this->especie;
   	}

   	char getSexo()
	{
   		return this->sexo;
   	}

   	char *getCelular()
	{
   		return this->celular;
   	}
};

class ListaMascotas{
  private:
	int n;
   	int max;
   	Mascota *data;

  public :
	ListaMascotas()
	{
   		this->n = 0;
      	this->max = 0;
      	this->data = NULL;
   	}

   	~ListaMascotas()
	{
   		if(this->max > 0)
	   	{
      		delete []this->data;
      	}
      	this->max = 0;
   		this->n = 0;
      	this->data = 0;
   	}

   	int getN()
	{
   		return this->n;
   	}

   	Mascota *get( int pos)
	{
  		return (this->data + pos);
   	}

	void agregar(Mascota &mascota)
	{
   		if( this->n == this->max)
		{
      		this->crecer();
      	}

      	this->data[this->n] = mascota;
		this->n++;
   	}

   	Mascota *buscarModificar(char *nombre)
	{
   		Mascota *temp;
		char aux[MAX];

      	for(int i=0;i<this->n;i++)
		{
      		temp=this->get(i);
      		temp->getNombre(aux);
      		if(strcmpi(nombre,aux)==0)
			{
         		return temp;
      		}
      	}
      	return NULL;
   	}

	int buscarNombre(char *buscarNombre)
	{
	  	Mascota *temp;
		char nombre[MAX];
	
		for(int i=0;i<this->n;i++)
		{
	     	temp=this->get(i);
			temp->getNombre(nombre);
	  		if(stricmp(buscarNombre,nombre)==0)
			{
	  			return i;
	  		}
		}
		return -1;
	}

   	int buscarCelular(char *buscarCelular)
   	{
      	Mascota *temp;
		char celular[MAXNUM];

   		for(int i=0;i<this->n;i++)
		{
         	temp=this->get(i);
   			temp->getCelular(celular);
      		if(strcmpi(buscarCelular,celular)==0)
			{
      			return i;
      		}
   		}
   		return -1;
	}

  private:
	void crecer()
	{
   		Mascota *temp;

      	this->max += DELTA;
      	temp = new Mascota[this->max];

      	for( int i=0; i<this->n; i++)
		{
      		temp[i] = this->data[i];
      	}
      	if( this->n > 0)
		{
      		delete []this->data;
      	}
      	this->data = temp;
   	}

};

ListaMascotas mascotas;

int leerOpcion()
{
	char *opciones[] = {"Registrar mascota", "Modificar mascota",
        "Reportes","Salir"};
   	int op;

	cout << " - MENU PRINCIPAL -" << endl;
   	for( int i=0; i<4; i++)
	{
   		cout << (i+1) << ".- " << opciones[i] << endl;
   	}

   	op = leeEntero(" Opcion : ", 1, 4, "Opcion no valida");

   	return op;
}

void registrarMascota()
{
  	Mascota mascota;
   	char auxNombre[MAX];
   	int pos;

   	do
	{
   		cout << "\n";
      	cout << "Nombre : ";
      	cin >> auxNombre;
      	pos=mascotas.buscarNombre(auxNombre);
      	if(pos==-1)
		{
      		mascota.setNombre(auxNombre);
         	mascota.leer();
      	}
		else
		{
      		cout<<"\t* El Nombre ingresado ya ha sido registrado"<<endl;
      	}
   	}while(pos>-1);

   	mascotas.agregar(mascota);
   	cout << "\t* Mascota registrada exitosamente*" << endl;
   	getch();
}

void modificarMascota()
{
	char nombre[MAX];
   	Mascota *mascota;

   	cout << "\nNombre de la mascota a modificar: ";
   	cin >> nombre;
   	mascota=mascotas.buscarModificar(nombre);
   	if(nombre!=NULL)
	{
   		mascota->leer();
      	cout << "\t* Mascota modificado exitosamente*" << endl;
   	}
	else
	{
   		cout << "\t* Mascota no encontrada" << endl;
   	}
   	getch();
}

int leerReporte()
{
	char *reportes[]={"Listado de Mascotas",
		"Dado un celular mostrar datos de la mascota",
      	"Dada una especie listar las mascotas registradas",
      	"Estadistica de mascotas registradas: cantidad por especie y cantidad por sexo",
      	"Salir"};
   	int op;

	cout << " - REPORTES -" << endl;
   	for(int i=0;i<5;i++)
	{
   		cout << (i+1) << "." << reportes[i] << endl;
   	}

   	op=leeEntero(" Opcion : ",1,5,"Opcion no valida");

   	return op;
}

//REPORTE N 01 - Listado de Mascotas
void presentarLista()
{
   	char descripcionEspecie[10],descripcionSexo[10];

   	cout << "\n";
   	cout << "LISTADO DE MASCOTAS" << endl;
	for(int i=0;i<mascotas.getN();i++)
	{
   		mascotas.get(i)->getDescripcionEspecie(descripcionEspecie);
      	mascotas.get(i)->getDescripcionSexo(descripcionSexo);
      
      	cout << "\n";
      	cout << " " << (i+1) << ".- " << mascotas.get(i)->getNombre() << " - " << descripcionEspecie
      		<< " - " << descripcionSexo << "(" << mascotas.get(i)->getEdad()
         	<< ")" << endl;
   	}
   	cout << "=================================================" <<endl;
	getch();
}

//REPORTE N 02

void dadoCelularDatosMascota()
{
	char descripcionEspecie[10],descripcionSexo[10],auxCelular[MAXNUM];
   	int pos,n=0;

   	do
	{
   		cout << "\nCelular(9 digitos) : ";
   		cin >> auxCelular;
   	}while(!(strlen(auxCelular)==MAXNUM-1));
   	pos=mascotas.buscarCelular(auxCelular);

   	if(pos>=0)
	{
      	cout << "\n";
   		cout << "DATOS DE MASCOTA" << "(" << auxCelular << ")" <<endl;
      	for(int i=0;i<mascotas.getN();i++)
		{
         	mascotas.get(i)->getDescripcionEspecie(descripcionEspecie);
   			mascotas.get(i)->getDescripcionSexo(descripcionSexo);

   			if(strcmpi(mascotas.get(i)->getCelular(),auxCelular)==0)
			{
         		cout << "\n";
      			cout << " " << (n+1) << ".- " << mascotas.get(i)->getNombre() << " - " << descripcionEspecie
      				<< " - " << descripcionSexo << "(" << mascotas.get(pos)->getEdad()
         			<< ")" << endl;
            	n++;
         	}
      	}
   	}
	else
	{
   		cout << "\t* Celular no encontrado" << endl;
   	}
   	cout << "=================================================" <<endl;
	getch();
}

//REPORTE N 03

void dadaEspecieListaMascotas()
{
	char descripcionSexo[10],auxEspecie;
   	int n=0;

   	cout << "\n";
   	auxEspecie=leeCaracter(" P: Perro"," G: Gato"," C: Conejo",'P','G','C',"Especie : ");

   	cout << "\n";
   	cout << "LISTADO DE MASCOTAS" << endl;
	for(int i=0;i<mascotas.getN();i++)
	{
      	mascotas.get(i)->getDescripcionSexo(descripcionSexo);

      	if(mascotas.get(i)->getEspecie()==auxEspecie)
		{
      		cout << "\n";
      		cout << " " << (n+1) << ".- " << mascotas.get(i)->getNombre() << " - " << descripcionSexo
         		<< "(" << mascotas.get(i)->getEdad() << ")" << endl;
         	n++;
      	}
   	}
   	cout << "=================================================" <<endl;
	getch();
}

//REPORTE N 04
void estadisticaMascotas()
{
   	int contPerros=0,contGatos=0,contConejos=0,contHembras=0,contMachos=0;

   	cout << "\n";
	for(int i=0;i<mascotas.getN();i++)
	{
      	if(mascotas.get(i)->getEspecie()=='P')
	  	{
      		contPerros++;
      	}
      	if(mascotas.get(i)->getEspecie()=='G')
	  	{
      		contGatos++;
      	}
      	if(mascotas.get(i)->getEspecie()=='C')
	  	{
      		contConejos++;
      	}
      	if(mascotas.get(i)->getSexo()=='H')
	  	{
      		contHembras++;
      	}
      	if(mascotas.get(i)->getSexo()=='M')
	  	{
      		contMachos++;
      	}
   	}

   	cout << " + Cantidad de mascotas(Especie): " << endl;
   	cout << "\tPerros : " << contPerros << endl;
   	cout << "\tGatos : " << contGatos << endl;
   	cout << "\tConejos : " << contConejos << endl;
   	cout << "\n";
   	cout << " + Cantidad de mascotas(Sexo): " << endl;
   	cout << "\tHembra : " << contHembras << endl;
   	cout << "\tMachos : " << contMachos << endl;
   	cout << "=================================================" <<endl;
	getch();
}

void listaReportes()
{
	int op;

   	do
	{
   		system("cls");
      	op=leerReporte();
      	switch(op)
		{
      		case 1: presentarLista(); break;
         	case 2: dadoCelularDatosMascota(); break;
         	case 3: dadaEspecieListaMascotas(); break;
         	case 4: estadisticaMascotas(); break;
         	case 5: break;
      	}
   	}while(op<5);
}

int main()
{
	int op;

   	do
	{
      	system("cls");
   		op = leerOpcion();
      	switch(op)
		{
      		case 1: registrarMascota(); break;
         	case 2: modificarMascota(); break;
         	case 3: listaReportes(); break;
         	case 4: cout << "OFF"; break;
      	}
  	}while(op < 4);
  	
  	return 1;
}
