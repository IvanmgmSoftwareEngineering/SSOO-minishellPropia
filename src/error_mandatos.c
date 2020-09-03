/*
 * ejecutar.c
 *
 *  Created on: Aug 31, 2020
 *      Author: IvanMGM
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "libreria.h"
#include "my_libreria.h"




int resultado;



int analiza_en_busca_errores_mandatos_linea(struct tline *apuntador_estructura_tline){
/*
	printf("\n");
	printf("-----------------------------------------------\n");
	printf("ENTRO FUNCIÓN void ejecuta(struct tline *apuntador_objeto_tline)\n");
	printf("\n");
*/
	// ZONA DE DECLARACION DE VARIABLES
	typedef char Comando [100];
	Comando *arreglo_comandos;
	typedef char Nombres_ficheros_salida[100];
	Nombres_ficheros_salida *ficheros_salida;
	typedef char Nombres_ficheros_error[100];
	Nombres_ficheros_error *ficheros_error;
	FILE *fichero;
	FILE *aux_fichero;
	char redireccion[50];
	char nombre_fichero[100];
	char letra;
	int *comando_existe;
	int resultado;
	int i,j,k,m;
	int todos_mandatos_y_parametros_de_la_linea_estan_bien;
	int redireccion_entrada_correcta; //0 = CORRECTA, != INCORRECTA
	int redireccion_salida_correcta; //0 = CORRECTA, != INCORRECTA
	int redireccion_error_correcta; //0 = CORRECTA, != INCORRECTA
	int encontrado; //0=encontrado, -1=No encontrado
	// FIN ZONA DE DECLARACION DE VARIABLES


	//Comprobamos que los mandatos exixten
	resultado = 0;
	ficheros_salida =  malloc(apuntador_estructura_tline->ncommands*100 * sizeof(char));

	if (ficheros_salida == NULL){ //manejo de errores de malloc
		printf("Ha habido un problema con la función malloc()");
		exit(0);
	}

	k =0;
	m =0;
	while(k<apuntador_estructura_tline->ncommands){
		while(m<100){
			ficheros_salida[k][m]='\0';
			m++;
		}
		k++;
		m=0;
	}



	k =0;

	while (k<apuntador_estructura_tline->ncommands){
		sprintf(ficheros_salida[k], "redirect_output_%i.txt",k);
		//printf("ficheros_salida[%i] = %s\n",k,ficheros_salida[k]);
		k++;

	}

	ficheros_error = malloc(apuntador_estructura_tline->ncommands * 100* sizeof(char));

	if (ficheros_error == NULL){ //manejo de errores de malloc
		printf("Ha habido un problema con la función malloc()");
		exit(0);
	}

	k =0;
	m =0;
	while(k<apuntador_estructura_tline->ncommands){
		while(m<100){
			ficheros_error[k][m]='\0';
			m++;
		}
		k++;
		m=0;
	}


	k =0;

	while (k<apuntador_estructura_tline->ncommands){
		sprintf(ficheros_error[k], "redirect_error_%i.txt",k);
		//printf("ficheros_error[%i] = %s\n",k,ficheros_error[k]);
		k++;

	}





	comando_existe= (int*) malloc(apuntador_estructura_tline->ncommands * sizeof(int));



	while (k<apuntador_estructura_tline->ncommands){
		comando_existe[k] = -1;
		k++;
	}



	arreglo_comandos = (Comando*)malloc(apuntador_estructura_tline->ncommands * 100* sizeof(char));
	k =0;
	m =0;
	while (k<apuntador_estructura_tline->ncommands){
		while(m<100){
			arreglo_comandos[k][m]='\0';
			m++;
		}
		k++;

	}





	for(i=0;i<apuntador_estructura_tline->ncommands;i++){

		for(j=0;j<mi_lenght(apuntador_estructura_tline->commands[i].filename);j++){
			arreglo_comandos[i][j]=apuntador_estructura_tline->commands[i].filename[j];
		}
		//printf("--Analizando comando %i: %s\n",i,arreglo_comandos[i]);
		//edirigimos la salida estandar y la salida de error a ficheros para que no los muestre por pantalla
		//printf("Redirigimos la salida estandar y la salida de error\n");

		//printf("redirección = %s\n",redireccion);


		sprintf(redireccion , " 2> redirect_error_%i.txt 1> redirect_output_%i.txt",i,i);


		//printf("redirección = %s\n",redireccion);

		for(int j=0;j<49;j++){
			arreglo_comandos[i][j+mi_lenght(apuntador_estructura_tline->commands[i].filename) ]= redireccion[j];
		}
		//printf("--El comando con redireccion es: %s\n",arreglo_comandos[i]);

		comando_existe[i]  = system (arreglo_comandos[i]);
		//printf("comando_existe[%i] = %i",i,comando_existe[i]);
		/*
		if(comando_existe[i] == 0){
			printf("  => SI EXISTE\n");

		}else{
			printf("  => NO EXISTE\n");
		}
		*/



		//borramos ficheros salida

	}

	//printf("Durmiento: aprovecha y prueba Ctrl+C:");
	//sleep(10);
	todos_mandatos_y_parametros_de_la_linea_estan_bien = 0; //0 todo esta bien, -1 alguo esta mal

	for (k=0;k<apuntador_estructura_tline->ncommands;k++){
		if(comando_existe[k] != 0){
			todos_mandatos_y_parametros_de_la_linea_estan_bien = -1;

		}
	}
	if(todos_mandatos_y_parametros_de_la_linea_estan_bien == -1){
		resultado = todos_mandatos_y_parametros_de_la_linea_estan_bien;
		printf("mandato: No se encuentra el mandato\n");
	}

	for (k=0;k<apuntador_estructura_tline->ncommands;k++){
		if(remove(ficheros_salida[k])!=0){
			printf("Hubo algun problema borrando fichero %s\n",ficheros_salida[k]);
		}else{

		}

		if(remove(ficheros_error[k])!=0){
			printf("Hubo algun problema borrando fichero %s\n",ficheros_error[k]);
		}else{

		}
	}

	//comprobamos si se produce error al abrir el fichero de redireccion.
	//redireccion entrada: el fichero debe existir previamente y tener permiso de lectura
	//redireccion salida: el fichero no debe porque existir previamente, pero si existe deber tener pemriso de escritura
	//redirreción error: el fichero no debe porque existir previamente, pero si existe deber tener pemriso de escritura
	//Si los mandatos y los parametros de cada uno de los mandatos son correctos, entonces continuamos.

	redireccion_entrada_correcta = 0; //0 = CORRECTA, != INCORRECTA
	redireccion_salida_correcta = 0; //0 = CORRECTA, != INCORRECTA
	redireccion_error_correcta = 0; //0 = CORRECTA, != INCORRECTA

	if(todos_mandatos_y_parametros_de_la_linea_estan_bien == 0){

		//comprobamos si hay redireccion de entrada; en caso de haberla comprobamos que el fichero existe
		if(apuntador_estructura_tline->redirect_input !=NULL){

			fichero = fopen(apuntador_estructura_tline->redirect_input,"rt");
			if(fichero == NULL){
				//Debemos comprobar el motivo por el que el fichero no se ha abierto
				//Motivo1: El fichero existe pero no tiene permiso de lectura
				//Motivo 2:el fichero no existe
				redireccion_entrada_correcta = -1;
				system("ls 1>comprobacion.txt");



				aux_fichero = fopen("comprobacion.txt","r");
				if (aux_fichero == NULL) {
						printf( "No se puede abrir el fichero comprobacion.txt.\n" );
						exit( 1 );
				}


				k=0;
				while (k<100){
					nombre_fichero[k]='\0';
					k++;
				}

				encontrado = -1; //0=encontrado, -1=No encontrado
				k=0;
				letra = getc(aux_fichero);
				while (letra != EOF && encontrado !=0) {
					while(letra != '\n' && letra != EOF){
						nombre_fichero[k] = letra;
						k++;
						letra = getc(aux_fichero);
					}

					encontrado = strcmp(nombre_fichero,apuntador_estructura_tline->redirect_input);



					if(letra != EOF && encontrado != 0){
						letra = getc(aux_fichero);//Almacena el primer caracter de la siguiente linea
						k=0;//Borramos todo lo que hay en nombre_fichero
						while (k<100){
							nombre_fichero[k]='\0';
							k++;
						}
						k=0;
					}
				}

				if(encontrado ==0){
					printf("fichero: Error. El fichero %s existe pero no tiene permiso de lectura\n",apuntador_estructura_tline->redirect_input);
				}else{
					printf("fichero: Error. El fichero %s no esixte\n",apuntador_estructura_tline->redirect_input);
				}

				if(remove("comprobacion.txt")!=0){
					printf("Hubo algun problema borrando fichero comprobacion.txt\n");
				}

			}
		}else if (apuntador_estructura_tline->redirect_output !=NULL){
			FILE *fichero;
			fichero = fopen(apuntador_estructura_tline->redirect_output,"wt");
			if(fichero == NULL){
				//Debemos comprobar el motivo por el que el fichero no se ha abierto
				//Motivo :el fichero no existe
				redireccion_salida_correcta = -1;
				system("ls 1>comprobacion.txt");

				FILE *aux_fichero;
				char letra;

				aux_fichero = fopen("comprobacion.txt","r");
				if (aux_fichero == NULL) {
					printf( "No se puede abrir el fichero comprobacion.txt.\n" );
					exit( 1 );
				}
				char nombre_fichero[100];

				int k;

				k=0;
				while (k<100){
					nombre_fichero[k]='\0';
					k++;
				}

				int encontrado = -1; //0=encontrado, -1=No encontrado
				k=0;
				letra = getc(aux_fichero);
				while (letra != EOF && encontrado !=0) {
					while(letra != '\n' && letra != EOF){
						nombre_fichero[k] = letra;
						k++;
						letra = getc(aux_fichero);
					}

					encontrado = strcmp(nombre_fichero,apuntador_estructura_tline->redirect_output);



					if(letra != EOF && encontrado != 0){
						letra = getc(aux_fichero);//Almacena el primer caracter de la siguiente linea
						k=0;//Borramos todo lo que hay en nombre_fichero
						while (k<100){
							nombre_fichero[k]='\0';
							k++;
						}
						k=0;
					}
				}
				if(encontrado ==0){
					printf("fichero: Error. El fichero %s existe pero no tiene permiso de escritura\n",apuntador_estructura_tline->redirect_output);
				}

				if(remove("comprobacion.txt")!=0){
					printf("Hubo algun problema borrando fichero comprobacion.txt\n");
				}

			}


		}else if (apuntador_estructura_tline->redirect_error !=NULL){


			fichero = fopen(apuntador_estructura_tline->redirect_output,"wt");
			if(fichero == NULL){
				//Debemos comprobar el motivo por el que el fichero no se ha abierto
				//Motivo :el fichero no existe
				redireccion_error_correcta = -1;
				system("ls 1>comprobacion.txt");



				aux_fichero = fopen("comprobacion.txt","r");
				if (aux_fichero == NULL) {
					printf( "No se puede abrir el fichero comprobacion.txt.\n" );
					exit( 1 );
				}


				k=0;
				while (k<100){
					nombre_fichero[k]='\0';
					k++;
				}

				encontrado = -1; //0=encontrado, -1=No encontrado
				k=0;
				letra = getc(aux_fichero);
				while (letra != EOF && encontrado !=0) {
					while(letra != '\n' && letra != EOF){
						nombre_fichero[k] = letra;
						k++;
						letra = getc(aux_fichero);
					}

					encontrado = strcmp(nombre_fichero,apuntador_estructura_tline->redirect_output);



					if(letra != EOF && encontrado != 0){
						letra = getc(aux_fichero);//Almacena el primer caracter de la siguiente linea
						k=0;//Borramos todo lo que hay en nombre_fichero
						while (k<100){
							nombre_fichero[k]='\0';
							k++;
						}
						k=0;
					}
				}
				if(encontrado ==0){
					printf("fichero: Error. El fichero %s existe pero no tiene permiso de escritura\n",apuntador_estructura_tline->redirect_output);
				}

				if(remove("comprobacion.txt")!=0){
					printf("Hubo algun problema borrando fichero comprobacion.txt\n");
				}

			}
		}

	}



/*
	printf("\n");
	printf("SALGO FUNCIÓN void ejecuta(struct tline *apuntador_objeto_tline)\n");
	printf("-----------------------------------------------");
	printf("\n");

*/
	if(todos_mandatos_y_parametros_de_la_linea_estan_bien != 0){
		resultado = -1;

	}else if(redireccion_entrada_correcta != 0){
		resultado = -1;
	}else if(redireccion_salida_correcta != 0){
		resultado = -1;
	}else if(redireccion_error_correcta != 0){
		resultado = -1;
	}
	return resultado;
}
