/*
 * libreria.h
 *
 *  Created on: Aug 21, 2020
 *      Author: IvanMGM
 */

#ifndef LIBRERIA_H_
#define LIBRERIA_H_

struct tcommand{
	char *filename;
	int argc;
	char ** argv;
};

struct tline{
	int ncommands;
	struct tcommand *commands;
	char *redirect_input;
	char *redirect_output;
	char *redirect_error;
	int background; //activado a 1 si el mandato se ejecuta o 0 en caso contrario
};

struct tline *tokenize(char *str);


#endif /* LIBRERIA_H_ */
