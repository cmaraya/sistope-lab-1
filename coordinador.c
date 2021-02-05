//Nombres: Catalina Araya Y Ekaterina Cornejo
//Seccion: B-2
//N° Laboratorio
//Entrega: Viernes 06/12/18

//Librerias para poder usar printf  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>// permite usar fork, pipes entre otros
#include <sys/wait.h>
#include <sys/types.h>
#include "funciones.h"

#define LECTURA 0
#define ESCRITURA 1


int main (int argc, char* argv[]) {
	int proceso = 0;
	int flag = 0;
	int  cantidadCaracteres = 0;
	char *nombre;
	nombre = malloc(10*sizeof(char));
	char *cadena;
	cadena = malloc(4*sizeof(char));
	recibirArgumentos(argc, argv,&nombre, &proceso,&cantidadCaracteres,&cadena,&flag);
	if(flag==1){
		printf("Se utilizo flag -d\n");
		}
	char* archivo=leerArchivo(nombre);
	int secuencias= largo(archivo)/cantidadCaracteres;
	char matrizADN[secuencias][cantidadCaracteres];
	int dos =2;
	int filas[proceso][dos];
	//Se obtiene los paraemtros de incio y fin para la matriz de AND
	//Se crea y separa la matriz de AND
	ordenarLista(archivo,cantidadCaracteres,secuencias,matrizADN);
	//ejecución:
	// se pide memori para los  enteros necesarios en la ejecucion del programa
	int final ;
	int inicio;
	int** pipes = (int**)malloc(sizeof(int*)*proceso);
	for (int l = 0; l < proceso; l++)
	{
		pipes[l] = (int*)malloc(sizeof(int)*proceso);
		pipe(pipes[l]);
	}
	char width_s[127];
	int status;			
	int pid;
	int i=0;
	for (i=0; i<proceso; i++) 
	{
		pid = fork();				// se hace fork()
		if (pid==0) 
		{
			close(pipes[i][ESCRITURA]);
			dup2(pipes[i][LECTURA],STDIN_FILENO);
			char *args[]={(char* )"comparador", NULL};
			execvp("./comparador",args);
		}else if (pid==-1) {			// si hay error, se aborta la operación
			perror("ERROR al hacer fork()");
			exit(1);
			break;
		}	
		else {					// Lógica del Padre   ///Parte 1
			ordenarFilas(proceso,secuencias,dos, filas);
			// esperamos a que todos los hijos terminen 			
			final =filas[i][1];
			inicio= filas[i][0];
			close(pipes[i][LECTURA]);
			sprintf(width_s,"%d",secuencias); 
			write(pipes[i][ESCRITURA],width_s,128);
			sprintf(width_s,"%d",cantidadCaracteres); 
			write(pipes[i][ESCRITURA],width_s,128);
			sprintf(width_s,"%d",i+1); 
			write(pipes[i][ESCRITURA],width_s,128);
			sprintf(width_s,"%d",inicio); 
			write(pipes[i][ESCRITURA],width_s,128);
			sprintf(width_s,"%d",final); 
			write(pipes[i][ESCRITURA],width_s,128);
			char *otro= cadena;
			sprintf(width_s,"%s",otro);
			write(pipes[i][ESCRITURA],width_s,128);
			for (int a = 0; a < secuencias; a++)
			{
				for (int b = 0; b < cantidadCaracteres; b++)
				{
					char prueba[]="";
					strncat(prueba,&matrizADN[a][b],1);
					otro=prueba;
					sprintf(width_s,"%s",otro);
					write(pipes[i][ESCRITURA],width_s,128);
				}	
			}
			for (int d = 0; d < proceso; d++)
			{
				while ((pid=waitpid(-1,&status, 0)!=-1))
				{
				}
			}
		}
	}
	archivoSalidaCoordinador(cadena,proceso, flag, filas);
	return 0;
}