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
#include <sys/wait.h>

#include "error_mandatos.h"
#include "libreria.h"
#include "my_libreria.h"

void mycd ();
void catch1(int sig);
struct tline *apuntador_objeto_tline;
int foo;
int count;

int main(void) {


	struct tline *apuntador_objeto_tline;
	char entrada_usuario [100];
	char mandato[100];
	char *apuntador;
	int **tuberias;
	int i,k,j;
	int estado_hijo;	/* Estado de salida */
	int pids;
	int status;
	int resultado_analiza_en_busca_errores_mandatos_linea;






	signal (SIGINT, SIG_IGN);
	signal (SIGQUIT, SIG_IGN);
	signal (SIGTSTP, catch1);

		//char c;
		//while((c = getchar()) != '\n' && c != EOF);
	resultado_analiza_en_busca_errores_mandatos_linea =-1;
	foo = 1;
	while(foo){



				signal(SIGINT , SIG_IGN);
				signal(SIGQUIT, SIG_IGN);

				imprime_el_prompt();
				//Lee ordenes desde teclado
				apuntador=fgets(entrada_usuario,100,stdin);
				limpia(apuntador);


				if(entrada_usuario[0]!='\0'){//La orden no esta vacia
					//Analizar, ordenar y diferenciar los campos de la linea

					apuntador_objeto_tline =  tokenize(entrada_usuario);

					//imprime por pantalla lo que contiene el objeto tline devuelto por la funcion tokenize
					analiza_objeto_tline(apuntador_objeto_tline);

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
						resultado_analiza_en_busca_errores_mandatos_linea = analiza_en_busca_errores_mandatos_linea(apuntador_objeto_tline);


					}else{

						printf("mandato: No se encuentra el mandato\n");
					}

					if(resultado_analiza_en_busca_errores_mandatos_linea == 0){ //Darse cuenta que si control_error != 0 ya se han impreso los mensajes de error desde dentro de la funcion analiza_en_busca_errores_mandatos_linea.
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

						switch (fork()){

							case -1:
								printf("Error: el proceso hijo no ha sido creado mediante la funcion fork()");
								break;

							case 0:
								//Codigo del proceso hijo

								if(resultado_analiza_en_busca_errores_mandatos_linea ==0){
									//Alcaceno el mandato, sus argumentos y redirecciones en cao de haberlas en la variable mandato[100]

									k=0;
									while(k<100){
										mandato[k]='\0';
										k++;
									}

									k=0;
									while(k<mi_lenght(apuntador_objeto_tline->commands[0].filename)){
										mandato[k]=apuntador_objeto_tline->commands[0].filename[k];
										k++;
									}

									//almaceno redireción en caso de existir
									if(apuntador_objeto_tline->redirect_input != NULL){
										mandato[k]=' ';
										k++;
										mandato[k]='<';
										k++;
										mandato[k]=' ';
										k++;
										j=0;
										while(j<mi_lenght(apuntador_objeto_tline->redirect_input)){
											mandato[k]=apuntador_objeto_tline->redirect_input[j];
											k++;
											j++;
										}

									}else if (apuntador_objeto_tline->redirect_output != NULL){
										mandato[k]=' ';
										k++;
										mandato[k]='>';
										k++;
										mandato[k]=' ';
										k++;
										j=0;
										while(j<mi_lenght(apuntador_objeto_tline->redirect_output)){
											mandato[k]=apuntador_objeto_tline->redirect_output[j];
											k++;
											j++;
										}

									}else if (apuntador_objeto_tline->redirect_error != NULL){
										mandato[k]=' ';
										k++;
										mandato[k]='2';
										k++;
										mandato[k]='>';
										k++;
										mandato[k]=' ';
										k++;
										j=0;
										while(j<mi_lenght(apuntador_objeto_tline->redirect_error)){
											mandato[k]=apuntador_objeto_tline->redirect_error[j];
											k++;
											j++;
										}
									}



									printf("El mandato completo que se va a ejecutar es: %s\n ",mandato);

									system(mandato);
									printf("\n");
									exit(0);

								}else{
									exit(0);
								}

								break;

							default:
								//Codigo del proceso padre
								wait(&estado_hijo);
								//printf("%i\n",estado_hijo);

						}



					}else{

						//Hay algun error en el mandato, pero aqui no hacemos nada ya que ya hemos impreso los mensajes de error por pantalla desde otra sitio

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
	//count++;
}

//char c;
	//while((c = getchar()) != '\n' && c != EOF);

void mycd (){

	char *dir; // Variable de directorios
	char buffer[512];
	int errno;
	FILE *stderr;

	if(apuntador_objeto_tline->commands[0].argc > 2) // No puedo hacer un cd a 2 directorios
		{
		  fprintf(stderr,"Uso: %s directorio\n", apuntador_objeto_tline->commands[0].argv[0]);
		}
	if (apuntador_objeto_tline->commands[0].argc == 1) // Si vale 1 , no me pasan nada, osea nombre del programa.
	{
		dir = getenv("HOME");
		if(dir == NULL)
		{
			fprintf(stderr,"No existe la variable $HOME\n");
		}
	}else {
		dir = apuntador_objeto_tline->commands[0].argv[1];
	}

	// Comprobar si es un directorio.
	if (chdir(dir) != 0) { // Sino es distinto de 0 lo hace normal el chdir
		fprintf(stderr,"Error al cambiar de directorio: %s\n", strerror(errno)); // Los errores a llamada al sistema siempre se guardan en errno, y strerror explica el porque de errno.
	}
	printf( "El directorio actual es: %s\n", getcwd(buffer,-1));
}

