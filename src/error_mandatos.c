/*
 * ejecutar.c
 *
 *  Created on: Aug 31, 2020
 *      Author: IvanMGM
 */

#include "libreria.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_libreria.h"
#include "error_mandatos.h"

int resultado;

typedef char Comando [100];
Comando *arreglo_comandos;

typedef char Nombres_ficheros_salida[100];
Nombres_ficheros_salida *ficheros_salida;

typedef char Nombres_ficheros_error[100];
Nombres_ficheros_error *ficheros_error;


char redireccion[50];





int analiza_en_busca_errores_mandatos_linea(struct tline *apuntador_estructura_tline){
/*
	printf("\n");
	printf("-----------------------------------------------\n");
	printf("ENTRO FUNCIÓN void ejecuta(struct tline *apuntador_objeto_tline)\n");
	printf("\n");
*/
	//Comprobamos que los mandatos exixten
	int k;
	int m ;
	int *comando_existe;

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





	for(int i=0;i<apuntador_estructura_tline->ncommands;i++){

		for(int j=0;j<mi_lenght(apuntador_estructura_tline->commands[i].filename);j++){
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

	sleep(10);
	int algun_mandato_o_parametro_de_la_linea_no_esta_bien = 0; //0 esta bien, -1 esta mal

	for (k=0;k<apuntador_estructura_tline->ncommands;k++){
		if(comando_existe[k] != 0){
			algun_mandato_o_parametro_de_la_linea_no_esta_bien = -1;

		}
	}
	if(algun_mandato_o_parametro_de_la_linea_no_esta_bien == -1){
		resultado = algun_mandato_o_parametro_de_la_linea_no_esta_bien;
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
	// redireccion entrada: ¿el fichero debe existir previamente?
	//redireccion salida: el fichero no debe porque existir previamente
	//redirreción error: el fichero no debe porque existir previamente
	//Si los mandatos y los parametros de cada uno de elllos son correctos, entonces continuamos.

	if(algun_mandato_o_parametro_de_la_linea_no_esta_bien == 0){

	}



/*
	printf("\n");
	printf("SALGO FUNCIÓN void ejecuta(struct tline *apuntador_objeto_tline)\n");
	printf("-----------------------------------------------");
	printf("\n");

*/
	return resultado;
}
