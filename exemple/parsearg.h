#ifndef PARSEARG
#define PARSEARG

enum FLAGS{
	OPTION_ARG_OPTIONAL = 1,
	OPTION_ALIAS = 2
};
struct parser_option{
	char *longoption;
	int shortoption;
	int flags; /*partially understand*/
	char *args;
/*	char *doc;*/
	char *explain;
	/*unsigned long int group;*/
};
struct info{
	const char *program_version;
	const char *program_bug_address;
};
/*extern struct info program;*/
extern struct parser_option options[];
struct parser_state{
	struct parser *parser;
	char **argv;
	int argc;
	int next;
	unsigned int flags;
	unsigned int arg_num;
	unsigned long int quoted;
	unsigned long int arg_colonne;
	unsigned long int explain_colonne;
	unsigned long int short_usage;
/*	int ___;*/
	void *input;
/*	void **child_input;*/
/*	void *hook;*/
	char *name;
	FILE *err_stream;
	FILE *out_stream;
/*	void *pstate;*/
};
struct parser{
	struct parser_option *options;
	void (*parse_opt)(int key,char *arg,struct parser_state *state);
	const char *doc;
	const char *args_doc;
	const char *about;
	struct info *program;
	struct parser_state *state;
};
/*struct parser args = { options, arguments, NULL, NULL};*/
size_t _strlen(const char *str);
int _strcmp(const char *src, const char *dst);
int _strncmp(const char *src, const char *dst, const size_t len);
char *_strchr(char *str, const char c);
void _memcpy(void *dst, const void *src, const size_t len);
void _memset(void *dst, const char c, const size_t len);
extern void parser_short_usage(struct parser *parser);
extern void parser_usage(struct parser *parser);
extern void parser_version(struct parser *parser);
extern void parser_parse(struct parser *parser, int argc, char **argv, /*unsigned int flags, unsigned int index,*/ void *input);
#endif
