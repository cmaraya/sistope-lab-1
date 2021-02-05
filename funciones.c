//Funciones
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

//Lee el archivo y rescata todos los datos 
//Entrada: entra un archivo de nombre ejemplo.txt, el cual contendra los datos de entrada una cadena de ADN
//Salida: un puntero a char el cual contiene los caracteres presentes en el archivo de entrada 

char* leerArchivo(char* nombreArchivo)
{
    //Se declara un archivo
    FILE *archivo;
    //Se declar auna variable caracter que contendra los caracteres que ingresaran a la lista
    char caracter;
    //Se inicializa una variabe para darle espacio a la lista
    int i=1;
    //Se inical9
    char *listaCaracteres=(char*)malloc(sizeof(char)*i);
    //Se abre el archivo en modo lectura
    archivo = fopen(nombreArchivo,"r");
    //Se comprueba que el archivo no este vario o corrupto de se asi se le informa al usuario
    if (archivo == NULL)
    {
        //Se le informa al usuario el fallo
        printf("\nEl archivo %s no pudo ser leido. \n\n",nombreArchivo);
        //En caso de fallo se retorna esto , pues no esta en la lista de caracteres validos
        listaCaracteres[0]='N';
    }
    //Si esta correcto se sigue con esta parte
    else{
        //Se entra en un ciclo que no se detiene hasta encontrar el End Of File, es decir el final del archivo
        while((caracter = fgetc(archivo)) != EOF)   
        {
        	//Si se encuentra con un espacio o un salto de linea , no los escribe en el arreglo, de no ser estos caracteres se continua
            if((caracter=='A')||(caracter=='T')||(caracter=='G')||(caracter=='C'))
            {
            	//Se agregan en forma normal
	            listaCaracteres[i-1]=caracter;
	            //Se aumenta el contador
	            i++;
	            //Se cambia el tamaño
	            listaCaracteres=realloc(listaCaracteres,sizeof(char)*i);
	         }
        }
    }
    //Se cierra el archivo
    fclose(archivo);
    //Caracter que se inserta al final de la lista para determinar que esta llego a su fin
    listaCaracteres[i]='F';
    //Se retorna una lista de caracteres scon espacios
    return listaCaracteres;
}

//Devuelve la longitud de la cadena sin tomar en cuenta el caracter de final de cadena.
//Entrada: char puntero, el cual contiene todos los cacteres del archivo
//Salida: entero con el numero total de caracteres en el archivo
int largo( char* listaArchivo){
	int i=0;
	while(listaArchivo[i]!='F')
	{
		i++;
	}
	return i;	
}


//Funcion que entrega una lista de lista en donde cada lista interna representa una secion del codigo del ADN  y cada elemento en la mismoa es un nucleotico
//Entrada: listaArchivo Array de char con saltos de lineas, los dos enteros sirven para dar el largo y ancho del resultado de salida
//Salida: char estatido de 2 dimensiones en donde se separa por lineas y caracteres respectivmaente en las direrentes dimensiones
void ordenarLista(char* listaArchivo, int cantidadCaracteres,int l, char secuencia[l][cantidadCaracteres])
{
	//Se genreran 2 contadores para designar memoria
	int contadorCaracteres=0;
	int contadorSecuencias=0;
	//Se inicializa un contador para poder avanzar en 
	int i=0;
	//Se leen todos los caracteres hasta antes de la letra F
	while (i < largo(listaArchivo))
	{
	
		if(contadorCaracteres<cantidadCaracteres)
		{
			secuencia[contadorSecuencias][contadorCaracteres]=listaArchivo[i];
			contadorCaracteres= contadorCaracteres+1;
			
		}
		else{
			
			contadorCaracteres=0;
			contadorSecuencias=contadorSecuencias+1;
			secuencia[contadorSecuencias][contadorCaracteres]=listaArchivo[i];
			contadorCaracteres=1;
		}
		++i;
	}

	//return secuencia;
	
}

//Funcion que crea un archivo de salida que reune los resultados de los procesos comparadores en orden de numero de proceso
//Entrada: nombre d eal cadena buscar, la cantdad d eprocesos realizados y la lista con el largo de proceso con el cual sabremos
//si se debe leer el archivo de dicho proceso
//Salida: archivo que contiene todos los resultados de archivos del coodirnador
void archivoSalidaCoordinador(char* nombreCadena, int procesos, int flag, int lista[procesos][2])
{
	FILE *archivo;
	//Char que contiene el inicio del nombre del archivo de salida
    char inicioCoordinador[]="rc_";
	//
	char inicio[]="rp_";
	//Char que contiene el tipo de texto
	char tipo[]=".txt";
	//Se declar auna variable caracter que contendra los caracteres que ingresaran a la lista
    char caracter;
	//Char que contendra el nombre del archivo de salida
    int k;
	int salto=0;
	//************************PROCESOS***************************
	int j=1;
	char *listaCaracteres=(char*)malloc(sizeof(char)*j);
	int largoEnteroProceso=1;
	FILE* salida;
	//Char que contendra el nombre del archivo de salida
	char nombreSalida[11];
	//char nombreSalida[11];
	//Funciones de la libreira string que concatena ditintos strings
	sprintf( nombreSalida,"%s%c%c%c%c%s", inicioCoordinador,  nombreCadena[0], nombreCadena[1], nombreCadena[2], nombreCadena[3],tipo);
	//Se abre en modo write par asobreescribir
	salida=fopen(nombreSalida,"w");
	fclose(salida);
	for (int i = 0; i < procesos; i++)
	{
		if (lista[i][0]!=-1)
		{
			largoEnteroProceso=1;
			// Se ve ek tamaño necesario para utilizar el proceso comi char
			while (0>i+1/(10*largoEnteroProceso))
			{			
				largoEnteroProceso=largoEnteroProceso+1;
			}
			char numeroDeJuego[largoEnteroProceso];
			//Se trasforma de int a char la variable juego y se guarda numeroDeJuego
			sprintf(numeroDeJuego,"%d",i+1);
			//Se guarda memoria para el nombre
			char nombreSalidaProceso[7+largoEnteroProceso];
			//Funciones de la libreira string que concatena ditintos strings
			sprintf( nombreSalidaProceso,"%s%c%c%c%c""_""%s%s", inicio, nombreCadena[0], nombreCadena[1], nombreCadena[2], nombreCadena[3],numeroDeJuego ,tipo);
			//
			j=1;
			//Se inical9
			listaCaracteres=(char*)malloc(sizeof(char)*j);
			//Se abre el archivo en modo lectura
			archivo = fopen(nombreSalidaProceso,"r");
			//Se comprueba que el archivo no este vario o corrupto de se asi se le informa al usuario
			if (archivo == NULL)
			{
				//Se le informa al usuario el fallo
				printf("\nEl archivo %s no pudo ser leido. \n\n",nombreSalidaProceso);
				//En caso de fallo se retorna esto , pues no esta en la lista de caracteres validos
				listaCaracteres[0]='N';
			}
			//Si esta correcto se sigue con esta parte
			else{
				//Se entra en un ciclo que no se detiene hasta encontrar el End Of File, es decir el final del archivo
				while((caracter = fgetc(archivo)) != EOF)   
				{
					listaCaracteres[j-1]=caracter;
					//Se aumenta el contador
					j++;
					//Se cambia el tamaño
					listaCaracteres=realloc(listaCaracteres,sizeof(char)*j);
				}
			}
			//
			fclose(archivo);
			//
			salida=fopen(nombreSalida,"a+");
			for(k=0;k <j-1;k++)
			{
				//Se agrega la seccion de ADN que se esta revisando
				fprintf(salida,"%c",listaCaracteres[k]);
				if(flag==1){
					printf("%c",listaCaracteres[k]);
				}
			}
		}else{
			if (salto==0)
			{
				printf("\n");
				salto++;
			}
			
			printf("Para el proceso Nº: %d no existen textos\n",i+1);
		}
		//Se cierra el archivo
    }
	fclose(salida);
    //Se cierra el archivo
}

//Funcionamiento: Funcion que obtiene los parametros de entrada necesarios para el funciojnamiento del programa
//Entrada: parametros ingresados por el usuario siguiendo el sgiguiente patron:
//-i: nombre del archivo de entrada
//-n: numero de procesos
//-c: cantidad de caracteres por linea en el archivo
//-p: cadena a buscar
//-d: bandera que indica al programa si debemos mostrar por pantalla el resultado
//Salida: No posee retorno, ya que es una función void, pero entrega por puntero los parametros de entreo, char*, entero, char y enetero
void recibirArgumentos(int argc, char *argv[],char **nombre, int *n,int *c,char **cadena, int *flag){
	int flags, opt;
	char *aux2;
	char *aux3;
	aux2 = malloc(10*sizeof(char));
	aux3 = malloc(10*sizeof(char)); 

	if(argc <9){//si se ingresa un numero de argumentos menor a 9, se finaliza la ejecucion del programa
		printf("Se ingreso un numero incorrecto de argumentos\n");
		fprintf(stderr, "Uso correcto: %s [-i archivo de entrada] [-n numero de procesos] [-c cantidad de caracteres del archivo] [-p cadena a buscar] [-d]\n",
				   argv[0]);
         
		   exit(EXIT_FAILURE);
		}
	int N = -1;
	int C = -1;
	flags = 0;
	while((opt = getopt(argc, argv, "i:n:c:p:d")) != -1) 
    { 
	   //opt recibe el argumento leido (se hace de forma secuencial) y se ingresa a un switch
	   //En caso de que opt sea -1, se dejaran de buscar entradas y por lo tanto se podrá salir del while

	   switch(opt) 
       {
            case 'd':
                flags = 1;
            break;
                
            case 'i':
              	(*nombre)=optarg; 

            break;
            
	 		case 'n': 
                N = strtol(optarg, &aux2, 10);
                if(optarg!=0 && N==0){
                    fprintf(stderr, "Uso correcto: %s [-i archivo de entrada] [-n numero de procesos] [-c cantidad de caracteres del archivo] [-p cadena a buscar] [-d]\n",
                        argv[0]); 
                        exit(EXIT_FAILURE);
                }
         
            break;

            case 'c': 
                C = strtol(optarg, &aux3, 10);
                if(optarg!=0 && C==0){
                    fprintf(stderr, "Uso correcto: %s [-i archivo de entrada] [-n numero de procesos] [-c cantidad de caracteres del archivo] [-p cadena a buscar] [-d]\n",
                        argv[0]); 
                        exit(EXIT_FAILURE);
                }               
            break;

            case 'p':
			(*cadena)=optarg;
            break;

            default:
                printf("opcions default\n");
                fprintf(stderr, "Uso correcto: %s [-i archivo de entrada] [-n numero de procesos] [-c cantidad de caracteres del archivo] [-p cadena a buscar] [-d]\n",
                        argv[0]); 
                exit(EXIT_FAILURE);
        }
	}
	if(flags==1)
    {
		(*flag) = 1;
    }	
	(*n) = N; 
	(*c) = C;	
	if(N<=0 || C<=0){
		printf("El valor que acompaña a -c y -n deben ser mayores a 0\n");
		fprintf(stderr, "Uso correcto: %s [-i archivo de entrada] [-n numero de procesos] [-c cantidad de caracteres del archivo] [-p cadena a buscar] [-d]\n",
				   argv[0]); 
		exit(EXIT_FAILURE);
		}
}

//Funciomanieto: Se encarga de ordenarr los datos y dejarlos prepados para su uso a lo largo del rpograma , pues lo deja en forma de 
//matriz 
//Entrada: char de caracteres
//Salida : matriz cuyo largo serà igual a la lineas presentes en el archivo, y su ancho seran la cantidad de caracteres por linea
void ordenarFilas(int procesos,int secuencia,int dos, int filas[procesos][dos])
{
	int probarDiv=secuencia/procesos;
	int probarmod=secuencia%procesos;
	int j=0;
	int residuo=1;
	if((secuencia/procesos>0))
	{
		if(secuencia%procesos!=0)
		{
			for (int i = 0; i < procesos; i++)
			{
				if(residuo<=probarmod)
				{
					if (i==0)
					{
						filas[i][0]=0;
						filas[i][1]=probarDiv;
						residuo=residuo+1;
					}else{
						filas[i][0]=filas[i-1][1]+1;
						filas[i][1]=filas[i-1][1]+probarDiv+1;
						residuo=residuo+1;
					}
				}else
				{
					if (i==0)
					{
						
						filas[i][0]=0;
						filas[i][1]=probarDiv;
						
					}else{
						filas[i][0]=filas[i-1][1]+1;
						filas[i][1]=filas[i-1][1]+probarDiv;
					}	
				}
			}
		}else{
			while (j<procesos)
			{
				if(j==0){
					filas[j][0]=j;
					filas[j][1]=(secuencia-1)/procesos;
				}else{
					filas[j][0]=filas[j-1][1]+1;
					filas[j][1]=filas[j-1][1]+secuencia/procesos;
				}
				j++;
			}
		}
	//opcion si los procesos son más que lineas disponibles o iguales 
	}else{
		
		while (j<procesos)
		{
			if (j<secuencia)
			{
				filas[j][0]=j;
				filas[j][1]=j;
				
			}else{
				filas[j][0]=-1;
				filas[j][1]=-1;
			}
			j++;	
		}
	}
}

//Entrada: fila de inicio y final que le corresponde al proceso actual, numero de lineas (int) y caracteres por linea (int)
//del archivo ingresado, matriz representante del archivo ingresado (char), lista de lineas que el proceso debera leer.
//Función: entrega la seccion de lineas (del archivo ), que el proceso actual debera leer (char array)
//Salida: matriz de datos tipos char.
void entregar(int inicio,int final,int numC,int lineas,char matriz[lineas][numC],char seccion[final-inicio+1][numC]){
	for(int i=inicio;i<=final;i++){
		for(int j=0;j<numC;j++){
			seccion[i-inicio][j]=matriz[i][j];
		}
	}
}
//Funcion que busca una cadena en cada una de las secuancias de ADN entregadas
//Entrada: secuencias de ADN (matriz tipo char), lista inicial de resultados (lista tipo int), cadenas a buscar (array tipo char)
//Salida: resultados de busqueda ingresados (array tipo int) , donde 1 representa haber hallado la cadena y 0 es no haberla hallado dentro de la secuancia
void encontrarCadena(int sec,int caract,char scADN[sec][caract],int resultados[sec],char cadena[4],int proceso)
{	
	//Se crea el archivo y sobreescribe cualquier dato en un archivo del mismo nombre
	FILE* salida;
	//Char que contiene el inicio del nombre del archivo de salida
    char inicio[]="rp_";
	//Char que contiene el tipo de texto
	char tipo[]=".txt";
	//
	char guion[]="_";
	//
	char no[]="NO";
	//
	char si[]="SI";
	// char que alvbergara la cantidad de procesos 
	int largoEnteroProceso=1;
	// Se ve ek tamaño necesario para utilizar el proceso comi char
	while (0>proceso/(10*largoEnteroProceso))
	{
		largoEnteroProceso=largoEnteroProceso+1;
	}
	char numeroDeJuego[largoEnteroProceso+0];
	//Se trasforma de int a char la variable juego y se guarda numeroDeJuego
	sprintf(numeroDeJuego,"%d",proceso);
	//Se guarda memoria para el nombre
    char nombreSalida[7+largoEnteroProceso];
	//Funciones de la libreira string que concatena ditintos strings
	sprintf( nombreSalida,"%s%c%c%c%c%s%s%s", inicio, cadena[0], cadena[1], cadena[2], cadena[3],guion,numeroDeJuego ,tipo);
	//Se abre en modo write par asobreescribir
	salida=fopen(nombreSalida,"w");
	//Se cierra el archivo
	fclose(salida);
	//
	for(int i=0; i <= sec-1 ; i++){
		for(int j=0 ; j <= (caract-3) ; j++){
 			if(scADN[i][j]==cadena[0] && scADN[i][j+1]==cadena[1] && scADN[i][j+2]==cadena[2] && scADN[i][j+3]==cadena[3] ){
 					resultados[i]=1;
 					j=caract; //deja de buscar
 			}
		}
		
		//Se termina la lectura de un linea
		salida=fopen(nombreSalida,"a+");

		for(int k=0;k <caract;k++)
		{
			//Se agrega la seccion de ADN que se esta revisando
			fprintf(salida,"%c",scADN[i][k]);
		}
		if(resultados[i]==1)
		{
			fprintf(salida," %s\n",si);	
		}else{
			fprintf(salida," %s\n",no);	
		}
		//Se cierra el archivo
		fclose(salida);
	}
}

//Funcion que inicializar array de resultados (valores en 0).
//Entrada: numero de secuencias y array de reultados creados.
void inicializarResultados(int sec,int resultados[sec])
{
	for(int r = 0; r < sec;r++){
		resultados[r]=0;
	}
}
