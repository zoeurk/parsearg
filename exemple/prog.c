#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "parsearg.h"
struct info program = {"version: 1.0","zoeurk@gmail.com"};
struct parser_option options[] =	{
					{ "test", 't', OPTION_ARG_OPTIONAL, "X", "test file"},
					{ "out", 'o', 0 , "STD", "test file2"},
					{ "retest", 'r', 0, NULL, "grr"},
					{ "retest2", '2', OPTION_ALIAS, NULL, "grr2"},
					{ "putaincesttroplong", 'L', 0, "euh", "c'est vraiment tres long"},
					{ "option-totalement-null", 1, 0, "cool", "cette option est null"},
					{ "option-de-merde-alors-putain", 2, 0,"yes", "putain mais la c'est vraiment la merde"},
					{0}
				};
struct arguments{
	char *buffer;
};
void arguments(int key, char *arg, struct parser_state *state){
	struct arguments *arguments = (struct arguments *)state->input;
	switch(key){
		case 't':
			if(arg)
				printf("test:%s\n",arg);
			else
				printf("test: no args\n");
			break;
		case 'o': printf("out:%s\n", arg);
			break;
		case 'r':
		case '2':
			printf("retest\n");
			break;
		case 'L':
			printf("putaincesttroplong:%s\n", arg);
			break;
		case 1:printf("option-totalement-null:%s\n", arg);
			break;
		case 2:printf("option-de-merde-alors-putain:%s\n", arg);
			break;
		default:
			/*printf("%s\n", arg);*/
			if(arguments->buffer == NULL && arg != NULL){
				if((arguments->buffer = calloc(strlen(arg)+1, sizeof(char))) == NULL){
					perror("calloc()");
					exit(EXIT_FAILURE);
				}
				strcpy(arguments->buffer,arg);
			}else{
				if(arg == NULL){
					fprintf(stderr,"Erreur: argument manquant\n");
					exit(EXIT_FAILURE);
				}
				if(arguments->buffer != NULL && arg != NULL){
					fprintf(stderr,"Erreur: trop d'argmument:%s\n",arg);
					exit(EXIT_FAILURE);
				}
			}
	}
}
struct parser args = {options, arguments, "[OPTIONS]", "string", "Exemple de programme", &program, NULL};
int main(int argc, char **argv){
	struct arguments _args_ = {NULL};
	if((args.state = calloc(1,sizeof(struct parser_state))) == NULL){
		perror("calloc()");
		exit(EXIT_FAILURE);
	}
	args.state->argv = argv;
	args.state->argc = argc;
	args.state->name = argv[0];
	args.state->out_stream = stdout;
	args.state->err_stream = stderr;
	args.state->arg_colonne = 45;
	parser_parse(&args, argc, argv, &_args_);
	if(_args_.buffer != NULL){
		printf("arguments: %s\n", _args_.buffer);
		free(_args_.buffer);
	}else{ fprintf(stderr, "Erreur: argument  manquant\n");
	}
	if(args.state)
		free(args.state);
	return 0;
}
