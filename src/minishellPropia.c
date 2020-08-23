/*
 ============================================================================
 Name        : minishellPropia.c
 Author      : IMG
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libreria.h"

struct tcommand objeto_tcommand;
struct tline objeto_tline;

int main(void) {

	printf("Empieza el main\n ");

	//char *apuntador_entrada_usuario;
	//struct tcommand *apuntador_objeto_tcommand;
	struct tline *apuntador_objeto_tline;



	//char c;
	//while ((c = getchar()) != '\n' && c != EOF);



	while(1){

		printf("Empieza el bucle while\n ");
		char entradaUsuario[100];
		char *apuntador_entradaUsuario = NULL;

		printf("msh> ");

		apuntador_entradaUsuario = fgets (entradaUsuario,100,stdin);
		strtok(entradaUsuario, "\n"); //Elminia el salto de linea de la cadena entradaUsusario
		//Quitamos
		//fgets (entradaUsuario, 100, stdin);

		printf("\n");//Dejar aqui porque sino la consola se vuelve loca


		//strcmp(apuntador_entrada_usuario,"\n")==0
		if(apuntador_entradaUsuario==NULL) {
			//ERROR en fgets(): Si entra aqui significa que: fgets no ha almacenado ninguno (error o carácter fin-de-fichero, CTRL+Z) devuelve un puntero NULL.
			printf("\n");
			printf("Entra en 1\n");


		}else{
			printf("\n");
			printf("Entra en 2\n");


			if(strcmp(entradaUsuario,"\n")==0){
				printf("\n");
				printf("-- El ususario no introdujo ningún mandato, directamente pulsó la tecla ENTER: %s\n",entradaUsuario);

			}else{

				printf("\n");
				printf("--El comando introducido por el usuario es: : %s\n",entradaUsuario);

				apuntador_objeto_tline =  tokenize(apuntador_entradaUsuario);
				printf("-- Analizamos el mandato\n");

				int numComandosRecibidos;
				numComandosRecibidos = apuntador_objeto_tline->ncommands;

				printf("---- Número comandos recibidos en la linea es: %d \n", apuntador_objeto_tline->ncommands);
				int i =1;

				while(i<=numComandosRecibidos){

					printf("---- El mandato %i que contiene la linea es: %s\n",i,apuntador_objeto_tline->commands[i-1].filename);
					i++;
				}



			}



		}
		//while(getchar()!= '\n');


	}

	return EXIT_SUCCESS;
}
