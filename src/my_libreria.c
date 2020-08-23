/*
 * my_libreria.c
 *
 *  Created on: Aug 21, 2020
 *      Author: IvanMGM
 */

#include <stdio.h>
#include <string.h>
#include "my_libreria.h"


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
		*posicion++;
	}

	if (encontrado == 0){
		posicion_encontrado = NULL;
		return posicion_encontrado;

	}else{
		return posicion_encontrado;
	}
}
