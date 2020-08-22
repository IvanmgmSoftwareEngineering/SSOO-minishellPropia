/*
 * libreria.c
 *
 *  Created on: Aug 21, 2020
 *      Author: IvanMGM
 */

#include <stdio.h>
#include <string.h>
#include "libreria.h"
#include "my_libreria.h"

struct tline objeto_tline;
struct tcommand objeto_tcommand;
struct tcommand arreglo_tcommand[20];



struct tline *tokenize(char *str){

	struct tline *apuntador_objeto_tline;
	struct tcommand *apuntador_objeto_tcommand;

	apuntador_objeto_tline = &objeto_tline;
	objeto_tline.commands = arreglo_tcommand;
	apuntador_objeto_tcommand = objeto_tline.commands;

	// Primero obtenemos el numero de mandatos.
	//Recordar que los mandatos están separados por el símbolo '|'
	char *aux_str;
	int contadorMandatos;


	aux_str = str;
	contadorMandatos = 1;

	while (*str != '\0'){
		if(*str++ == '|'){
			contadorMandatos++;
		}
	}


	int i;

	for (i = 1; i <= contadorMandatos; i++){
		aux_str = my_strchr2(str,'|');
		if(aux_str == NULL){

			apuntador_objeto_tcommand[i-1].filename = str;

		}else{

		}
	}

	objeto_tline.ncommands = contadorMandatos;

	return apuntador_objeto_tline;






}
