/*
 * my_libreria.c
 *
 *  Created on: Aug 21, 2020
 *      Author: IvanMGM
 */

#include <stdio.h>
#include <string.h>
#include "my_libreria.h"
#include "libreria.h"



void imprime_el_prompt(void){
	printf("msh> ");
}

void imprime_adios(void){
	printf("msh> logout ");
}
void limpia (const char *cadena){
	 char *p;
	  p = strchr (cadena, '\n');
	  if (p != NULL){
		  *p = '\0';
	  }
}

int my_strchr1(const char *fuente1, const char caracterBuscado){

	int posicion = -1;
	int contador = 0;


	while(*fuente1 != '\0'){
		if(*fuente1 == caracterBuscado){
			posicion = contador;
			return posicion;
		}
		contador++;
		fuente1++;
		}


		return posicion;
}


char *my_strchr2(const char *fuente1, int caracterBuscado){

	char *posicion;
	char *posicion_encontrado;
	int contador = 0;
	int encontrado = 0;
	posicion = fuente1;


	while(*posicion != '\0'){
		if(*posicion == (char)caracterBuscado && encontrado ==0){
			encontrado = 1;
			posicion_encontrado = posicion;
		}
		contador++;
		posicion++;
	}

	if (encontrado == 0){
		posicion_encontrado = NULL;
		return posicion_encontrado;

	}else{
		return posicion_encontrado;
	}
}

char *mi_strcpy2 (const char *fuente, char *destino){

	int i = 1;
	while (*fuente != '\0'){
		*destino++ = *fuente++;
		i++;
	}
	*destino = '\0';
	return destino;
}

char *mi_strcpy1 (const char *fuente, char *destino){

	int i = 1;
	char *p = destino;
	while (*fuente != '\0'){
		*p++ = *fuente++;
		i++;
	}
	*p = '\0';
	return destino;
}

int mi_lenght (const char *arreglo){
	int contador;

	contador = 0;

	while (*(arreglo + contador) != '\0'){
		contador++;
	}
	return contador;
}

void analiza_objeto_tline (const struct tline *apuntador_objeto_tline){
	printf("---- Analizamos objeto tfile devuelto por la funcion tokenize en MAIN ----\n");
	printf("\n");

	int numComandosRecibidos;
	numComandosRecibidos = apuntador_objeto_tline->ncommands;

	printf("-------- Número comandos recibidos en la linea (variable int ncommads) es: %d \n", apuntador_objeto_tline->ncommands);
	printf("\n");
	printf("-------- Analizamos arreglo de objetos tcommads (variable *commands) \n");
	printf("\n");

	for(int i=0;i<numComandosRecibidos;i++){
		printf("------------ Objeto tcommand %i almacenado en *commands\n",i);
		int numArgumentosRecibidos;
		numArgumentosRecibidos = apuntador_objeto_tline->commands[i].argc;
		printf("---------------- Mandato completo (variable char *filename) es: %s\n",apuntador_objeto_tline->commands[i].filename);
		printf("---------------- Número de argumentos (variable int argc) es:   %i\n", numArgumentosRecibidos);
		printf("---------------- Argumentos (variable char **argv)\n");

		for(int j=0;j<numArgumentosRecibidos;j++){


			printf("-------------------- Argumento %i es: %s \n",j,apuntador_objeto_tline->commands[i].argv[j]);

		}
		printf("\n");
	}
	printf("\n");
	printf("-------- Redirección entrada (variable char *redirect_input) es: %s \n", apuntador_objeto_tline->redirect_input);
	printf("\n");
	printf("-------- Redirección salida (variable char *redirect_output) es: %s \n", apuntador_objeto_tline->redirect_output);
	printf("\n");
	printf("-------- Redirección error (variable char *redirect_error) es: %s \n", apuntador_objeto_tline->redirect_error);
	printf("\n");
	printf("-------- Activado background (activado = 1, desactivado = 0) (variable int background) es: %i \n", apuntador_objeto_tline->background);
	printf("\n");


}

