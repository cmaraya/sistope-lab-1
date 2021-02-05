#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "funciones.h"

#define LECTURA 0
#define ESCRITURA 1


int main(int argc, char *argv[]){
	
	int secuencias, cantidadCaracteres, proceso, inicio, final;
	char enterror[128];
	
	read(STDIN_FILENO,enterror,128);
	secuencias= atoi(enterror);
	read(STDIN_FILENO,enterror,128);
	cantidadCaracteres= atoi(enterror);
	read(STDIN_FILENO,enterror,128);
	proceso= atoi(enterror);
	read(STDIN_FILENO,enterror,128);
	inicio= atoi(enterror);
	read(STDIN_FILENO,enterror,128);
	final= atoi(enterror);
	char cadena[4];
	read(STDIN_FILENO,enterror,128);
	cadena[0]=enterror[0];
	cadena[1]=enterror[1];
	cadena[2]=enterror[2];
	cadena[3]=enterror[3];

	char matrizADN[secuencias][cantidadCaracteres];
	for(int i=0;i<secuencias;i++){
		for(int j=0;j<cantidadCaracteres;j++){
			read(STDIN_FILENO,enterror,128);
			matrizADN[i][j]=enterror[0];
		}
	}

	if (final!=-1)
	{
		//se obtiene la seccion del ADN que se debe leer y utilizar
		//Se pide memoria para guardar una seccion de la matriz de ADN
		int calculosLineas=final-inicio+1;
		char seccion[calculosLineas][cantidadCaracteres];
		int resultados[secuencias];
		entregar(inicio,final,cantidadCaracteres,secuencias,matrizADN,seccion);
		//Se incializa la lista resultados
		inicializarResultados(secuencias,resultados); 
		//Se encuentra y crear los archivos por proceso
		encontrarCadena(calculosLineas,cantidadCaracteres,seccion,resultados,cadena, proceso);
	}
	return 0;
}