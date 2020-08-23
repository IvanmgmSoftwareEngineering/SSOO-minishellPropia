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
	struct tcommand *apuntador_arreglo_objetos_tcommand;

	apuntador_objeto_tline = &objeto_tline;
	apuntador_objeto_tcommand = &objeto_tcommand;
	apuntador_arreglo_objetos_tcommand = arreglo_tcommand;





	// Primero obtenemos el numero de mandatos.
	//Recordar que los mandatos están separados por el símbolo '|'
	char *aux_str;
	int contadorMandatos;


	aux_str = str;
	contadorMandatos = 1;

	while (*aux_str != '\0'){
		if(*aux_str++ == '|'){
			contadorMandatos++;
		}
	}


	objeto_tline.ncommands = contadorMandatos;
/*
	objeto_tcommand.filename = str;
	arreglo_tcommand[0]=objeto_tcommand;
	objeto_tline.commands = arreglo_tcommand;

*/
	int i;
	char *aux_str3;

	aux_str3 = str;

	for (i = 1; i <= contadorMandatos; i++){
		aux_str = my_strchr2(str,'|');

		if(aux_str == NULL){//solo hay un comando en la linea

			objeto_tcommand.filename = str;
			arreglo_tcommand[i-1]=objeto_tcommand;
			objeto_tline.commands = arreglo_tcommand;

		}else{ //hay dos comandos


			*aux_str='\0';
			aux_str++;

			objeto_tcommand.filename = aux_str3;
			arreglo_tcommand[i-1]=objeto_tcommand;

			objeto_tline.commands = arreglo_tcommand;

			str = aux_str;
			aux_str3 = aux_str;
		}

	}





	return apuntador_objeto_tline;

}
