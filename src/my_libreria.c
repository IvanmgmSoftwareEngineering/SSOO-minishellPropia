/*
 * my_libreria.c
 *
 *  Created on: Aug 21, 2020
 *      Author: IvanMGM
 */

#include <stdio.h>
#include <string.h>
#include "my_libreria.h"


const char *my_strchr2(const char *fuente1, int caracterBuscado){

	char *posicion = NULL;
	int contador = 0;
	posicion = fuente1;


	while(*posicion != '\0'){
		if(*posicion == (char)caracterBuscado){
		return posicion;
		}
		contador++;
		*posicion++;
	}
	return posicion;
}
