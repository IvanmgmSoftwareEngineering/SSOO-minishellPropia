/*
 * libreria.c
 *
 *  Created on: Aug 21, 2020
 *      Author: IvanMGM
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libreria.h"
#include "my_libreria.h"


struct tline objeto_tline;


struct tline *tokenize(char *str){

/*
	printf("\n");
	printf("-----------------------------------------------\n");
	printf("ENTRO FUNCIÓN struct tline *tokenize(char *str)\n");
	printf("\n");
*/

	// ZONA DE DECLARACION DE VARIABLES
	struct tline *apuntador_objeto_tline;
	struct tcommand *commands;
	typedef char AregloMandatos[100];
	AregloMandatos *mandatos;
	char **parametros;
	char *copia_str;
	int *posiciones;
	int *numero_parametros_cada_mandato;
	int contador_tamaño_mandato;
	int tamaño_str;
	int contadorMandatos;
	int exixte_redireccion_salida_mandato;//SI =1 , NO = 0
	int posicion_redireccion_salida_mandato;
	int exixte_redireccion_entrada_mandato;//SI =1 , NO = 0
	int posicion_redireccion_entrada_mandato;
	int longitud_nombre_fichero_redireccion;
	int encontrado;
	int contador;
	int background;
	int i,j,k,r,m;
	// FIN ZONA DE DECLARACION DE VARIABLES


	apuntador_objeto_tline = &objeto_tline;


	// Primero obtenemos el numero de mandatos.
	//Recordar que los mandatos están separados por el símbolo '|'

	//printf("Paso 1) Extraemos el número de mandatos que hay en la línea.\n");



	i = 0;
	contadorMandatos = 1;

	while (str[i] != '\0'){
		if(str[i] == '|'){
			contadorMandatos++;
		}
		i++;
	}


	objeto_tline.ncommands = contadorMandatos;

	//NOTAR QUE: en este punto el apuntador STR sigue apuntando al principio de la ccadena, mientras que el apuntador apuntador_1_arreglo_str apunta al final de la cadena STR

	//CONTROL DE LO QUE VAMOS HACIENDO
	//printf("-----------El valor de la variable ncommands del objeto tline es: %i \n",objeto_tline.ncommands);
	//FIN  CONTROL DE LO QUE VAMOS HACIENDO

	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	//------------------------------------------------------------------------

	// Segundo separamos cada comando de la linea por el operador | y lo almacenamos en la valiable *filename de la estructura tcommand.


	//printf("Paso 2) Extraemos cada uno de los mandatos que hay en la línea y los almacenamos en la matriz commands \n");




	tamaño_str = mi_lenght(str);
	copia_str = (char *)malloc(tamaño_str * sizeof(char));
	posiciones = (int *)malloc(contadorMandatos * sizeof(int));
	mandatos = malloc(contadorMandatos * 100 * sizeof(char));
	commands = malloc(contadorMandatos * sizeof(struct tcommand ));




	if (copia_str == NULL){ //manejo de errores de malloc
		printf("Ha habido un problema con la función malloc()");
		exit(0);
	}

	if (posiciones == NULL){ //manejo de errores de malloc
			printf("Ha habido un problema con la función malloc()");
			exit(0);
	}

	if (mandatos == NULL){ //manejo de errores de malloc
			printf("Ha habido un problema con la función malloc()");
			exit(0);
	}






	k = 0;
	while (str[k] != '\0'){
		copia_str[k] = str[k];
		k++;
	}


	k = 0;
	while (k < contadorMandatos){
			posiciones[k] = -1;
			k++;
	}

	contador_tamaño_mandato = 0;
	k = 0;
	j = 0;
	for (k = 0; k< mi_lenght(copia_str) ; k++){
		if(copia_str[k]=='|'){
			posiciones[j]= contador_tamaño_mandato;
			//printf("posiciones[%i] = %i\n",j,posiciones[j]);
			contador_tamaño_mandato = 0;
			j++;
		}else{
			contador_tamaño_mandato++;
		}
	}

	posiciones[j]= contador_tamaño_mandato;
	//printf("posiciones[%i] = %i\n",j,posiciones[j]);

	int contador_posicion;

	contador_posicion = 0;
	for (k=0;k < contadorMandatos ;k++){
		for(j= contador_posicion; j < posiciones[k]+contador_posicion;j++){
			mandatos[k][j-contador_posicion]= copia_str[j];
			//printf("mandatos[%i][%i] = %c\n",k,j-contador_posicion, mandatos[k][j-contador_posicion]);
		}
		//mandatos[k][posiciones[k]]='\0';


		contador_posicion = contador_posicion + posiciones[k]+1;
	}



	//Ahora guardo los mandatos en la variable commmands del objeto tline

	//struct tcommand commands[contadorMandatos];
	objeto_tline.commands = commands;



	for (k=0;k < contadorMandatos ;k++){
		objeto_tline.commands[k].filename = (char *)malloc(100 * sizeof(char));
		if (objeto_tline.commands[k].filename == NULL){ //manejo de errores de malloc
			printf("Ha habido un problema con la función malloc()");
			exit(0);
		}
		for (j=0;j <= posiciones[k] ;j++){
			objeto_tline.commands[k].filename[j]= mandatos[k][j];
			//printf("El contenido de filename en commands[%i] es: %s\n", k,objeto_tline.commands[k].filename );
		}
		objeto_tline.commands[k].filename[posiciones[k]+1]= '\0';
	}


	k=0;
	while(k<contadorMandatos){
		//printf("-----------El valor de la variable objeto_tline.commands[%i].filename es: %s \n",k,objeto_tline.commands[k].filename);
		k++;
	}

	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	//------------------------------------------------------------------------

	//Analizamos redirecciones
	//printf("Paso 3) Buscamos redirección y en el caso de haberla limpiamos el último mandato.\n");


	exixte_redireccion_salida_mandato = 0 ;//SI =1 , NO = 0
	posicion_redireccion_salida_mandato  = 0 ;
	exixte_redireccion_entrada_mandato  = 0 ;//SI =1 , NO = 0
	posicion_redireccion_entrada_mandato = 0 ;







	for (j=0;j < mi_lenght(str) ;j++){
		if(str[j] == '>'){
			exixte_redireccion_salida_mandato = 1;
			posicion_redireccion_salida_mandato = j;

		} else if(str[j] ==  '<'){
			exixte_redireccion_entrada_mandato = 1;
			posicion_redireccion_entrada_mandato = j;
		}
	}

	longitud_nombre_fichero_redireccion = 0;
	if(exixte_redireccion_salida_mandato == 1){

		if(str[posicion_redireccion_salida_mandato-1]==' ' ||str[posicion_redireccion_salida_mandato-1]=='1'){
			longitud_nombre_fichero_redireccion = mi_lenght(str)- 1 - posicion_redireccion_salida_mandato +2;;
			objeto_tline.redirect_output = (char *)malloc(longitud_nombre_fichero_redireccion * sizeof(char));
			if (objeto_tline.redirect_output  == NULL){ //manejo de errores de malloc
				printf("Ha habido un problema con la función malloc()");
				exit(0);
			}
			for (j = 0; j < longitud_nombre_fichero_redireccion; j++){
				objeto_tline.redirect_output[j] = str[j+posicion_redireccion_salida_mandato + 2];
			}
			if(str[posicion_redireccion_salida_mandato-1]==' '){
				encontrado = 0;
				for (i=0;i<mi_lenght(objeto_tline.commands[contadorMandatos-1].filename);i++){
					if(objeto_tline.commands[contadorMandatos-1].filename[i] == '>'){
						encontrado = 1;
					}
					if(encontrado ==1){
						objeto_tline.commands[contadorMandatos-1].filename[i] ='\0';
					}
				}
				//objeto_tline.commands[contadorMandatos-1].filename[mi_lenght(objeto_tline.commands[contadorMandatos-1].filename)-1] ='\0';
			}else{
				int encontrado = 0;
				for (i=0;i<mi_lenght(objeto_tline.commands[contadorMandatos-1].filename);i++){
					if(objeto_tline.commands[contadorMandatos-1].filename[i] == '>'){
						encontrado = 1;
					}
					if(encontrado ==1){
						objeto_tline.commands[contadorMandatos-1].filename[i-2] ='\0';
					}
				}
				//objeto_tline.commands[contadorMandatos-1].filename[mi_lenght(objeto_tline.commands[contadorMandatos-1].filename)-1] ='\0';

			}
			objeto_tline.redirect_input = NULL;
			objeto_tline.redirect_error = NULL;

		}else if (str[posicion_redireccion_salida_mandato-1]=='2'){
			longitud_nombre_fichero_redireccion = mi_lenght(str)- 1 - posicion_redireccion_salida_mandato +2;;
			objeto_tline.redirect_error = (char *)malloc(longitud_nombre_fichero_redireccion * sizeof(char));
			if (objeto_tline.redirect_error  == NULL){ //manejo de errores de malloc
				printf("Ha habido un problema con la función malloc()");
				exit(0);
			}
			for (j = 0; j < longitud_nombre_fichero_redireccion; j++){
				objeto_tline.redirect_error[j] = str[j+posicion_redireccion_salida_mandato + 2];
			}

			encontrado = 0;
			for (i=0;i<mi_lenght(objeto_tline.commands[contadorMandatos-1].filename);i++){
				if(objeto_tline.commands[contadorMandatos-1].filename[i] == '>'){
					encontrado = 1;
				}
				if(encontrado ==1){
					objeto_tline.commands[contadorMandatos-1].filename[i-2] ='\0';
				}
			}
			//objeto_tline.commands[contadorMandatos-1].filename[mi_lenght(objeto_tline.commands[contadorMandatos-1].filename)-1] ='\0';

			objeto_tline.redirect_input = NULL;
			objeto_tline.redirect_output = NULL;
		}else{

			objeto_tline.commands[contadorMandatos-1].filename = NULL;

			objeto_tline.redirect_input = NULL;
			objeto_tline.redirect_output = NULL;
			objeto_tline.redirect_error = NULL;

		}


	}else if (exixte_redireccion_entrada_mandato == 1){
		longitud_nombre_fichero_redireccion = mi_lenght(str) -1 - posicion_redireccion_entrada_mandato + 2;;
		objeto_tline.redirect_input = (char *)malloc(longitud_nombre_fichero_redireccion * sizeof(char));
		if (objeto_tline.redirect_input  == NULL){ //manejo de errores de malloc
			printf("Ha habido un problema con la función malloc()");
			exit(0);
		}
		for (j = 0 ; j < longitud_nombre_fichero_redireccion; j++){

			objeto_tline.redirect_input[j] = str[j + posicion_redireccion_entrada_mandato + 2];
		}
		if(str[posicion_redireccion_entrada_mandato-1]==' ' ){

			encontrado = 0;
			for (i=0;i<mi_lenght(objeto_tline.commands[contadorMandatos-1].filename);i++){
				if(objeto_tline.commands[contadorMandatos-1].filename[i] == '<'){
					encontrado = 1;
				}
				if(encontrado ==1){
					objeto_tline.commands[contadorMandatos-1].filename[i] ='\0';

				}
			}

		}else if (str[posicion_redireccion_entrada_mandato-1]=='0'){
			encontrado = 0;
			for (i=0;i<mi_lenght(objeto_tline.commands[contadorMandatos-1].filename);i++){
				if(objeto_tline.commands[contadorMandatos-1].filename[i] == '<'){
					encontrado = 1;
				}
				if(encontrado ==1){
					objeto_tline.commands[contadorMandatos-1].filename[i-2] ='\0';

				}
			}
			//objeto_tline.commands[contadorMandatos-1].filename[mi_lenght(objeto_tline.commands[contadorMandatos-1].filename)-1] ='\0';

		}else{
			objeto_tline.commands[0].filename = NULL;

			objeto_tline.redirect_input = NULL;

		}

		objeto_tline.redirect_output = NULL;
		objeto_tline.redirect_error = NULL;



	}else{
		objeto_tline.redirect_input = NULL;
		objeto_tline.redirect_output = NULL;
		objeto_tline.redirect_error = NULL;

	}


	//printf("-----------El valor de objeto_tline.redirect_input es:   %s\n ", objeto_tline.redirect_input);
	//printf("-----------El valor de objeto_tline.redirect_output es: %s\n ", objeto_tline.redirect_output);
	//printf("-----------El valor de objeto_tline.redirect_error es:   %s\n ", objeto_tline.redirect_error);


	//k=0;
	//while(k<contadorMandatos){
		//printf("-----------El valor de la variable objeto_tline.commands[%i].filename es: %s \n",k,objeto_tline.commands[k].filename);
		//k++;
	//}




	//En este punto comprobamos si la linea contiene algun error debido a una mala sintaxis en la parte de la redireccion
	//En concreto si se ha utilizado algo direferente a lo siguiente se detectará como un error:
	// ... > nombre_fichero para la salida estandar
	// ... 1> nombre_fichero para la salida estandar
	// ... 2> nombre_fichero para la salida error
	// ... < nombre_fichero para la entrada estandar
	// ... 0< nombre_fichero para la salida estandar
	// Considerando que la redirección de salida estandar o la salida de error afectá solo al ultimo mandato de la linea
	// Se considera que la redirecion de entrada estandar afecta solo al primer mandato de la línea
	//Por lo dicho anteriormente:
	//Si hay un error sintáctico en la redireccion de salida se considerará que el último mandato de la linea tiene un error sintáctico y como consecuencia *filename = NULL de dicho mandato
	//Si hay un error sintáctico en la redireccion de entrada se considerará que el primer mandato de la linea tiene un error sintáctico y como consecuencia *filename = NULL de dicho mandato
if(objeto_tline.commands[contadorMandatos-1].filename != NULL && objeto_tline.commands[0].filename != NULL){


	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	//------------------------------------------------------------------------

	//Extreamos los parametros de cada mandato

	//printf("Paso 4) Extraemos el numero de parámetros de cada uno de los mandatos.\n");


	numero_parametros_cada_mandato = (int *)malloc(contadorMandatos * sizeof(int));
	if (numero_parametros_cada_mandato  == NULL){ //manejo de errores de malloc
		printf("Ha habido un problema con la función malloc()");
		exit(0);
	}

	k = 0;
	while (k < contadorMandatos){
		numero_parametros_cada_mandato[k] = 0;
		k++;
	}
	contador = 0;
	for (k=0;k < contadorMandatos ;k++){

		for (j=0;j < mi_lenght(objeto_tline.commands[k].filename) ;j++){
			if(objeto_tline.commands[k].filename[j] == ' '){
				contador++;
			}
			objeto_tline.commands[k].filename[j]= mandatos[k][j];
		}
		numero_parametros_cada_mandato[k] = contador+1;

		contador = 0;

	}

	for (k=0;k < contadorMandatos ;k++){
		objeto_tline.commands[k].argc = numero_parametros_cada_mandato[k];
		//printf("-----------El valor de la variable objeto_tline.commands[%i].argc=  %i\n", k,objeto_tline.commands[k].argc );

	}

	//printf("Paso 5) Extraemos los parámetros de cada uno de los mandatos.\n");




	r = 0 ;
	m = 0;
	i = 0;
	for (k=0;k < contadorMandatos ;k++){
		parametros= (char *) malloc (objeto_tline.commands[k].argc * sizeof(char*));

		if (parametros  == NULL){ //manejo de errores de malloc
			printf("Ha habido un problema con la función malloc()");
			exit(0);
		}

		for (r = 0; r<objeto_tline.commands[k].argc;r++){
			parametros[r]=(char *) malloc(100 * sizeof(char*));
			if (parametros[r]  == NULL){ //manejo de errores de malloc
				printf("Ha habido un problema con la función malloc()");
				exit(0);
			}
		}


		objeto_tline.commands[k].argv = parametros;

		j = 0;
		while (j < objeto_tline.commands[k].argc){
			for(m = 0; m<100;m++){
				objeto_tline.commands[k].argv[j][m] = '\0';
			}
			j++;
		}

		i=0;
		m=0;
		for (j=0;j < mi_lenght(objeto_tline.commands[k].filename) ;j++){

			if(objeto_tline.commands[k].filename[j] != ' '){
				parametros[i][m] = objeto_tline.commands[k].filename[j];
				m++;
			}else{
				i++;
				m=0;
			}

		}

	}

	for(k=0;k<contadorMandatos;k++){
		for(j=0;j<objeto_tline.commands[k].argc;j++){
			//printf("-----------El valor de la variable objeto_tline.commands[%i].argv[%i] = %s\n",k,j,objeto_tline.commands[k].argv[j]);
		}

	}

	//------------------------------------------------------------------------
	//------------------------------------------------------------------------
	//------------------------------------------------------------------------

	//Com,probamos si es en foregorund o background

	//printf("Paso 5) Comprobamos si está presente el simbolo & indicando que es en background.\n");

	background = 0 ;//SI =1 , NO = 0

	for(j=0;j<mi_lenght(str);j++){
		if(str[j] == '&'){
			background = 1;
		}
	}
	objeto_tline.background = background;

	//printf("-----------El valor de la variable objeto_tline.backgorund es: %i\n");

	//quito el simbolo & del ultimo mandato: para ello lo quito de la variable *filename del ultimo mandato y elimino el ultimo argumento del ultimo mandato
	if(background==1){
		objeto_tline.commands[objeto_tline.ncommands-1].filename[mi_lenght(objeto_tline.commands[objeto_tline.ncommands-1].filename)-2]='\0';
		objeto_tline.commands[objeto_tline.ncommands-1].filename[mi_lenght(objeto_tline.commands[objeto_tline.ncommands-1].filename)-1]='\0';

		objeto_tline.commands[objeto_tline.ncommands-1].argv[objeto_tline.commands[objeto_tline.ncommands-1].argc-1][0] = '\0';

		objeto_tline.commands[objeto_tline.ncommands-1].argc--;

	}
/*
	printf("\n");
	printf("SALGO FUNCIÓN struct tline *tokenize(char *str)\n");
	printf("-----------------------------------------------\n");
	printf("\n");
*/

}
	return apuntador_objeto_tline;

}
