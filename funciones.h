#ifndef FUNCIONES_H
#define FUNCIONES_H

//----------------------------Funciones Cordinador--------------------------

char* leerArchivo(char* nombreArchivo);

int largo( char* listaArchivo);

void ordenarLista(char* listaArchivo, int cantidadCaracteres,int l, char secuencia[l][cantidadCaracteres]);

void archivoSalidaCoordinador(char* nombreCadena, int procesos, int flag, int lista[procesos][2]);

void recibirArgumentos(int argc, char *argv[],char **nombre, int *n,int *c,char **cadena, int *flag);

void ordenarFilas(int procesos,int secuencia,int dos, int filas[procesos][dos]);

//----------------------------Funciones Comparador--------------------------

void entregar(int inicio,int final,int numC,int lineas,char matriz[lineas][numC],char seccion[final-inicio+1][numC]);

void inicializarResultados(int sec,int resultados[sec]);

void encontrarCadena(int sec,int caract,char scADN[sec][caract],int resultados[sec],char cadena[4],int proceso);

#endif