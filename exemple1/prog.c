#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parsearg.h"
struct info program = {"version:1.0","zoeurk@gmail.com"};
struct parser_option options[] =	{
					{ "test", 't', OPTION_ARG_OPTIONAL, "X", "test file"},
					{ "out", 'o', 0 , "STD", "test file2"},
					{ "retest", 'r', 0, NULL, "grr"},
					{ "retest2", '2', OPTION_ALIAS, NULL, "grr2"},
					{ "putaincesttroplong", 'L', 0, NULL, "c'est vraiment tres long"},
					{0}
				};
int arguments(int key, char *arg, struct parser_state *state){
	if(arg)
		printf("[=>ok:%c:%s\n",key, arg);
	else	printf("[+>ok:%c\n",key);
	return 0;
}
struct parser args = {options, arguments, "prog", "salut", "Exemple de programme", &program, NULL};
struct arguments{
	int i;
	char buffer[1024];
};
int main(int argc, char **argv){
	struct arguments _args_;
	parser_parse(&args, argc, argv/*, 0, 0*/, &_args_);
	args.state = NULL;
	parser_usage(&args);
	return 0;
}
