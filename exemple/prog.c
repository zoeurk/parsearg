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
					{ "putaincesttroplong", 'L', 0, NULL, "c'est vraiment tres long"},
					{ "option-totalement-null", 1, 0, "cool", "cette option est null"},
					{ "option-de-merde-alors-putain", 2, 0,NULL, "putain mais la c'est vraiment la merde"},
					{0}
				};
struct arguments{
	int i;
	int pad;
	char *buffer;
};
void arguments(int key, char *arg, struct parser_state *state){
	struct arguments *arguments = (struct arguments *)state->input;
	if(arg){
		arguments->buffer = arg;
		printf("[=>ok:%i:%c:arg:%s\n",key, key, arg);
	}else	printf("[+>ok:%i:%c:no arg\n",key, key);
	/*return 0;*/
}
struct parser args = {options, arguments, "[OPTIONS]", "string", "Exemple de programme", &program, NULL};
int main(int argc, char **argv){
	struct parser_state ps = {NULL, NULL, 0, 0, 0, 0, 0, 35, 75, 75, NULL, NULL, NULL, NULL};;
	struct arguments _args_ = {0, 0, NULL};
	args.state = &ps;
	args.state->argv = argv;
	args.state->argc = argc;
	args.state->name = argv[0];
	args.state->out_stream = stdout;
	args.state->err_stream = stderr;
	parser_parse(&args, argc, argv, &_args_);
	if(_args_.buffer == NULL){
		fprintf(stderr, "%s take one arguments.",argv[0]);
		fprintf(stderr, "Try %s -?|--usage\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("arguments: %s\n", _args_.buffer);
	/*if((args.state = calloc(1,sizeof(struct parser_state))) == NULL){
		perror("calloc()");
		exit(EXIT_FAILURE);
	}*/
	//memset(&ps,0, sizeof(struct parser_state));
	//args.state->arg_colonne = 75;
	//parser_usage(&args);
	return 0;
}
