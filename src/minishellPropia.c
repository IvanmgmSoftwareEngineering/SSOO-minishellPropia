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
int foo;

int main(void) {


	struct tline *apuntador_objeto_tline;
	char entrada_usuario [100];
	char *apuntador;
	int i;
	int control_error;





	signal (SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
	signal (SIGTSTP, catch1);

		//char c;
		//while((c = getchar()) != '\n' && c != EOF);

	foo = 1;
	while(foo){
			imprime_el_prompt();
			//Lee ordenes desde teclado
			apuntador=fgets(entrada_usuario,100,stdin);
			limpia(apuntador);


			if(entrada_usuario[0]!='\0'){//La orden no esta vacia
				//Analizar, ordenar y diferenciar los campos de la linea
				//analiza_objeto_tline(apuntador_objeto_tline);
				apuntador_objeto_tline =  tokenize(entrada_usuario);

				//Compruebo si ha habido algún error de sintaxis en alguno de los mandatos de la línea asociado a las redirecciones;
				//en caso de haberlo se muestra el mensaje mandato: No se encuentra el mandato
				//en caso contrario se llama a la funcion 'analiza_en_busca_errores_mandatos_linea' para hacer un estudio mas detallado de la sintaxis de los mandatos que componen la línea
				if(apuntador_objeto_tline->commands[apuntador_objeto_tline->ncommands-1].filename != NULL && apuntador_objeto_tline->commands[0].filename != NULL){

					//Reviso los mandatos que componen la linea en busca de errores del tipo:
					//1- Alguno de los mandatos no existe ==> Se imprime: "mandato: No se encuentra el mandato"
					//2- Algun parametro de alguno de los mandatos no existe  ==> Se imprime: "mandato: No se encuentra el mandato"
					//3- Hay problemas en los nombres de los ficheros de Las redireccciones no son correctas ==> “fichero: Error. Descripción del error”
						//*redirec_input: el fichero debe existir previamente y tener permiso de lectura
						//*redirec_output: el fichero no debe porque existir previamente, pero si existe debe tener pemriso de escritura
						//*redirec_error: el fichero no debe porque existir previamente, pero si existe debe tener pemriso de escritura
					// NOTA: por lo que dice el enunciado con respecto a *filename cito: "si el mandato existe se almacena la ruta completa del mandato, en caso contrario apunta a NULL".
					// (sigue NOTA) quizás los puntos 1 y 2 van dentro de la función tokenize: en este caso como esta función nos la dan implementada solo debo analizar que pone a NULL dicha función.
					control_error = analiza_en_busca_errores_mandatos_linea(apuntador_objeto_tline);


				}else{

					printf("mandato: No se encuentra el mandato\n");
				}

				if(control_error == 0){ //Darse cuenta que si control_error != 0 ya se han impreso los mensajes de error desde dentro de la funcion analiza_en_busca_errores_mandatos_linea.
					//Si se mete aqui es que toda la sintaxis es correcta, es decir:
						//1)La sintaxis de la redirección es correcta, es decir: (ESTA COMPROBACION SE HACE EN libreria.c)
							// ... > nombre_fichero para la salida estandar
							// ... 1> nombre_fichero para la salida estandar
							// ... 2> nombre_fichero para la salida error
							// ... < nombre_fichero para la entrada estandar
							// ... 0< nombre_fichero para la salida estandar
							// Considerando que la redirección de salida estandar o la salida de error afectá solo al ultimo mandato de la linea
							// Se considera que la redirecion de entrada estandar afecta solo al primer mandato de la línea
							//Por lo dicho anteriormente:
							//Si hay un error sintáctico en la redireccion de salida se considerará que el último mandato de la linea tiene un error sintáctico y como consecuencia *filename = NULL de dicho mandato
								//Ejemplo: ... 5> nombre_fichero.txt
							//Si hay un error sintáctico en la redireccion de entrada se considerará que el primer mandato de la linea tiene un error sintáctico y como consecuencia *filename = NULL de dicho mandato
								// Ejemplo: ... 3< nombre_fichero.txt
						//2)Cada uno de los mandatos, junto con sus parámetros, que componen la línea son correctos sintácticamente (ESTA COMPROBACION SE HACE EN error_mandato.c)
							//El mandato junto con sus parametros no existe
							//Ejemplo: ... 52> nombre_fichero.txt. En este caso, el paso 1 tomará como correcta la redirecion de salida, pero el ultimo mandato contendrá en su última posicion el caracter '5', lo que deberia provocar
							//(sigue ejemplo) que el ultimo mandato de error ¿Que sucede si el mandato acepta como paerametro el '5'?
						//3)en caso de haber redirecciones, el nombre de los ficheros asociados a las redirecciones cunmplen con lo que deben de cumplir, es decir:
							//*redirec_input: el fichero debe existir previamente y tener permiso de lectura
							//*redirec_output: el fichero no debe porque existir previamente, pero si existe debe tener pemriso de escritura
							//*redirec_error: el fichero no debe porque existir previamente, pero si existe debe tener pemriso de escritura


				}



			}else{
				//la orden esta vacia, entonces no se hace y se vuelve al principio del bucle while
			}
	}

	//liberamos la memoria antes de salir del programa
	for(i = 0; i<apuntador_objeto_tline->ncommands;i++){
		free(apuntador_objeto_tline->commands[i].filename);
		free(apuntador_objeto_tline->commands[i].argv);
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

