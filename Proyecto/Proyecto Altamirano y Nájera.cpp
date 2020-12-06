#include <stdio.h>
#include <conio.h> //ayuda a movimiento
#include <stdlib.h> //Es la libreria estandra
#include <String.h> //ayuda a que las cadenas esten en donde tienen que estar
#include <fstream> //ayuda a leer y escribir los archivos del disco duro y en la ejecucion del ofstream y el ifstream
#include <windows.h> //para poner los colores en la consola utilizamos la libreria de windows.h

//Utilizamos struct y en el desarrollo del cuerpo del programa se mandan llamar las funciones de las variables globlales en el main cuando se ejecuta el programa
// Profe tiene que tener antes el archivo de mascotas.txt si no lo descargo o no lo ha creado no va  a correr adecuadamente el programa gracias

using namespace std; //dar acceso al espacio de nombres (namespace) std, donde se encuentra encerrada toda la librería estándar.
// Declara el struct

struct Mascotas
{
	int clave;
	char nombre[31];
	char sexo[15];
	int existencia;
};
// Al struct le indicas un arreglo y de cuanto
Mascotas arr[1000];
// Va a ayudar a manejar los movimientos que hay (modificaciones, eliminacion, etc)
int no_registros=0,existe=0,aux_producto, actual;


void error(int er)
{
	if (er==1)printf("\nError, opcion fuera de rango entre 1 y 8 ...\n");
	if (er==2)printf("\nError, Numero de producto se duplica en base de datos ...\n");
	if (er==3)printf("\nError, Numero de producto inexistente en base de datos ...\n");
	if (er==4)printf("\nError, El monto debe ser mayor a cero ...\n");
	if (er==5)printf("\nError, Mascotas insuficientes para la adopcion ...\n");
	if (er==20)printf("\n Pausa [ENTER] para continuar\n");
	getche(); //ayuda a guardar correctamente los datos del teclado para mostrarlos posteriormente
}
// Esta funcion va ayudar a saber si la mascota esta o no en la base de datos.
void pide_valida_mascota()
{
	system("cls");
	printf("Dame la clave de la mascota:  ");
	scanf("%d",&aux_producto);

	existe=0;
	for(int i=0;i<no_registros;i++)
		if(aux_producto==arr[i].clave)
		{
			actual=i;
			existe=1;
			break;
		}
}

void altas()
{
	pide_valida_mascota();
	if(existe==1)error(2);
	else
	{
		arr[no_registros].clave=aux_producto;
		printf("\nDame la raza de la mascota: ");gets(arr[no_registros].nombre);gets(arr[no_registros].nombre);
		printf("\nDame el sexo de la mascota: ");gets(arr[no_registros].sexo);
		printf("\nDame el numero de mascotas que hay: ");scanf("%d",&arr[no_registros].existencia);
		no_registros++;
	}//Termina la validacion de mascota duplicada
}

void modificaciones()
{
	pide_valida_mascota();
	if(existe==0) error(3);
	else
	{
		arr[actual].clave=aux_producto;
		printf("\nDame la raza de la mascota: ");gets(arr[actual].nombre);gets(arr[actual].nombre);
		printf("\nDame el sexo de la mascota: ");gets(arr[actual].sexo);
	}//Termina
}

void bajas()
{
	char sino;
	pide_valida_mascota();
	if(existe==0)error(3);
	else
	{
		printf("El nombre es: %s\n",arr[actual].nombre);
		printf("?Seguro de eliminar?[s/n]: ");sino=getche();
		if(sino=='s')
		{
			arr[actual].clave=-1;
			printf("\n *El registro ha sido eliminado*");
			error(20);
		}
	}
}
/*
[operaciones]

	[int dor]: Indicara si se sumara o se restara existencias en las adopciones
			   3 -> Aumentar
			   4 -> Reducir
*/
void operaciones(int dor)
{
	float monto;
	pide_valida_mascota();
	if(existe==0) error(3);
	else
	{
		printf("Dame el numero de mascotas rescatadas : "); scanf("%f",&monto);
		if (monto<=0) error(4);
		if (dor==3) arr[actual].existencia = arr[actual].existencia+monto;
		else
			if ( monto > arr[actual].existencia) error(5);
			else arr[actual].existencia = arr[actual].existencia-monto;
	}
}
// De forma general
void listado()
{
	system("cls");
	for(int i=0;i<no_registros;i++)
		if(arr[i].clave!=-1)
		printf("Clave: %3d   Raza:%s   Sexo: %3s   Disponibilidad: %3d\n",arr[i].clave,arr[i].nombre,arr[i].sexo,arr[i].existencia);
	error(20);
}

void busquedaId()
{
	system("cls");
	pide_valida_mascota();
	if(existe==0) error(3);
	else
	{
		printf("Clave: %3d   Nombre:%s   Sexo: %3s   Existencia: %3d\n",arr[actual].clave,arr[actual].nombre,arr[actual].sexo,arr[actual].existencia);
	}

	error(20);
}
// Escribe todo lo que se hizo y cada modificacion realizada ya aparecera en el txt
void descargar()
{
	ofstream arch;
		arch.open("mascotas.txt",ios::out);
		for(int i=0;i<no_registros;i++)
			if (arr[i].clave!=-1)
				arch <<arr[i].clave <<" " <<arr[i].nombre <<" " <<arr[i].sexo <<" " <<arr[i].existencia <<"\n";
			arch.close();
}
// el ofstream sirve para modificar y buscar el archiv de mascotas.txt
// Carga al sistema el txt ya creado y se trabaja con la informacion con la que habian trabajado antes
void carga()
{
	ifstream arch;
	arch.open("mascotas.txt",ios::in);
	while(!arch.eof())
	{
		arch >>arr[no_registros].clave >>arr[no_registros].nombre >>arr[no_registros].sexo >>arr[no_registros].existencia;
		if (!arch.eof()) no_registros++;
	}
	arch.close();
}

void menu()
{
	int op=0;
	while(op!=8)
	{
	    //el system limpia la consola para que ya no se muestre el menu cuando compila la opcion seleccionada y se vea organido y limpio

		system("cls");
		printf("\033[1;35m"); // los colores son los printf con números en especificos prints
		printf("Base de datos del Refugio ZOAN\n");
		printf("\033[1;34m");
		printf("1)Rescates de mascotas\n");
		printf("2)Adopcion de mascotas\n");
		printf("3)Registro de entradas de mascotas\n");
		printf("4)Registro de salidas de mascotas\n");
		printf("5)Listado de mascotas\n");
		printf("6)Modificacion de maacotas\n");
		printf("7)Busqueda por ID\n");
		printf("8)Terminar\n");
		printf("\n Indica la opcion:  \n");
		scanf("%d",&op);
        printf("Hasta pronto, termina mi progrma\033[1;32m");//plus despedida
		if((op<1)||(op>8))error(1);
		else
		{
			if(op==1) altas();
			if(op==2) bajas();
			if((op==3) || (op==4))  operaciones(op);  //para no usar el siwtch usamos ifs
			if(op==5) listado();
			if(op==6) modificaciones();
			if(op==7) busquedaId();
		}
	}
}


main()
{
// Carga primero el archivo  de mascotas.txt para tener el listado
	carga();
	menu();
	descargar();
// guarda las modificaciones en el txt
}
