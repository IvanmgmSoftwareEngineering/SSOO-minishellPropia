/*
 * my_libreria.h
 *
 *  Created on: Aug 21, 2020
 *      Author: IvanMGM
 */
#include "libreria.h"
#ifndef MY_LIBRERIA_H_
#define MY_LIBRERIA_H_

void imprime_el_prompt(void);
void limpia(const char *cadena);
int my_strchr1(const char *fuente1, const char caracterBuscado);
char *my_strchr2(const char *fuente1, int caracterBuscado);
char *mi_strcpy2 (const char *fuente, char *destino);
char *mi_strcpy1 (const char *fuente, char *destino);
int mi_lenght (const char *arreglo);
void analiza_objeto_tline (const struct tline *apuntador_objeto_tline);
void imprime_adios(void);

#endif /* MY_LIBRERIA_H_ */
