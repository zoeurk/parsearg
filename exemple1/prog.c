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
void arguments(int key, char *arg, struct parser_state *state){
	if(arg)
		printf("[=>ok:%i:%c:arg:%s\n",key, key, arg);
	else	printf("[+>ok:%i:%c:no arg\n",key, key);
	/*return 0;*/
}
struct parser args = {options, arguments, "[OPTIONS]", "salut", "Exemple de programme", &program, NULL};
struct arguments{
	int i;
	char buffer[1024];
};
void bye(void){
	free(args.state);
}
int main(int argc, char **argv){
	struct arguments _args_;
	atexit(bye);
	if((args.state = calloc(1,sizeof(struct parser_state))) == NULL){
		perror("calloc()");
		exit(EXIT_FAILURE);
	}
	args.state->argv = argv;
	args.state->argc = argc;
	args.state->name = argv[0];
	args.state->out_stream = stdout;
	args.state->err_stream = stderr;
	args.state->arg_colonne = 35;
	parser_parse(&args, argc, argv, &_args_);
	parser_usage(&args);
	return 0;
}
