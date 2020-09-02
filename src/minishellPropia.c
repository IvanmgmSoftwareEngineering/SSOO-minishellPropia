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
#include <signal.h>

#include "error_mandatos.h"
#include "libreria.h"
#include "my_libreria.h"

void catch1(int sig);

int foo = 1;
int signal2 = 0;

int main(void) {


	struct tline *apuntador_objeto_tline;
	char entrada_usuario [100];
	char *apuntador;
	int control_error;



	signal (SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
	signal (SIGTSTP, catch1);

		//char c;
		//while((c = getchar()) != '\n' && c != EOF);


	while(foo){
			imprime_el_prompt();
			//Lee ordenes desde teclado
			apuntador=fgets(entrada_usuario,100,stdin);
			limpia(apuntador);
			if(entrada_usuario[0]!='\0'){//La orden no esta vacia
				//Analizar, ordenar y diferenciar los campos de la linea
				//analiza_objeto_tline(apuntador_objeto_tline);
				apuntador_objeto_tline =  tokenize(entrada_usuario);


				//Reviso los mandatos que componen la linea en busca de errores del tipo:
				//- Alguno de los mandatos no existe ==> Se imprime: "mandato: No se encuentra el mandato"
				//- Algun parametro de alguno de los mandatos no existe  ==> Se imprime: "mandato: No se encuentra el mandato"
				//- Las redireccciones no son correctas ==> “fichero: Error. Descripción del error”
				control_error = analiza_en_busca_errores_mandatos_linea(apuntador_objeto_tline);


			}else{//la orden esta vacia

			}
	}

	//liberamos la memoria antes de salir del programa
	for(int i = 0; i<apuntador_objeto_tline->ncommands;i++){
		free(apuntador_objeto_tline->commands[i].filename);
	}
	free(apuntador_objeto_tline->commands);
	free(apuntador_objeto_tline->redirect_input);
	free(apuntador_objeto_tline->redirect_output);
	free(apuntador_objeto_tline->redirect_error);


		imprime_adios();
		return EXIT_SUCCESS;
}

void catch1(int sig){

	//signal(SIGINT, catch1);
	printf("\nSeñal: %i atrapada!\n", sig);
	foo = 0;


	//char c;
	//while((c = getchar()) != '\n' && c != EOF);

}

