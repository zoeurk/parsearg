#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
/*#include <argp.h>*/
#include <stdarg.h>
#include <string.h>
#include "parsearg.h"

#define PI 3.141592653589793

/*const char *argp_program_version= "math-0.1";
const char *argp_program_bug_address = "zoeurk@gmail.com";*/
struct info program = { "version 1.0", "zoeurk@gmail.com" };
/*static char doc[] = "Simple program which use some function of 'math.h.'\"(gcc -lm)\"";*/
struct parser_option
options[] = {	{"double",'d', 0, NULL,"uliser une valeur double"},
		{"float",'F', 0,NULL,"utiliser une valeur float"},
		{"dlong",'D', 0, NULL,"utiliser une valeur double long"},
		{"cos",'c',0, "X","cosinus d'un nombre X"},
		{"sin",'s',0, "X","sinus d'un nombre X"},
		{"tan",'t',0, "X","tangente d'un nombre X"},
		{"sqrt",'S',0, "X","carré d'un nombre X"},
		{"exp",'e',0, "X","valeur exponentiel d' un nombre X"},
		{"log",'l',0, "X","logarithme naturel (en base 'e') d'un nombre X"},
		{"log10",'L',0,"X","logarithme naturel (en base 10) d'un nombre X"},
		{"fabs",'f',0, "X","valeur absolue d'un nombre X"},
		{"ceil",'C',0, "X","arrondi un nombre X à un entier plus petit"},
		{"floor",'o',0, "X","arrondi un nombre X à un entier plus grand"},
		{"pow",'p',0, "X=x,Y=y","puissance d'une valeur X élevé à la valeur Y"},
		{"fmod",'m',0, "X=x,Y=y","reste de X/Y"},
		{"virgule",'O',0, "FORMAT","afficher nombre de chiffre après la virgule"},
		{"radian",'R',0, NULL,"afficher le résultat en radian plutôt quand degrès"},
		{"degre",'r',0, NULL,"les entrées sont en degrès plutôt quand radian"},
		{"newline",'N',0, NULL,"affiche le resultat avec un nouvelle ligne: \"result\\n\""},
		/*{"help",'h', NULL, 0, "try -? or \"--usage\""},*/
		{0}

 };
typedef char bool;
enum numbers{
 X,
 Y
}numbers;
char *two_numbers[] = {
 [X] = "X",
 [Y] = "Y"
};
enum functions
{
 INIT	= -1,
 COS	= 0,
 SIN	= 1,
 TAN	= 2,
 SQRT	= 4,
 EXP	= 8,
 LOG	= 16,
 LOG10	= 32,
 FABS	= 64,
 CEIL	= 128,
 FLOOR	= 256,
 POW	= 512,
 FMOD	= 1024

}functions;
enum type
{
 DOUBLE  = 0,
 FLOAT   = 1,
 LDOUBLE = 2,
 IDEGRES = 4,
 ORADIAN = 8,
 NEWLINE = 16
}type;

struct arguments
{
 size_t type,function;
 char *numbers[2];
 char *format;
};
struct comput
{
 size_t type,___pad___;
 char *format;
 size_t formatlen;
 union{
  double      dnumber[2];
  float       fnumber[2];
  long double ldnumber[2];
 }value;
 union{
  union{
   double	(*dfn)(double value);
   double	(*dfn2)(double value1, double value2);
  }d;
  union{
   float	(*ffn)(float value);
   float	(*ffn2)(float value1,float value2);
  }f;
  union{
   long double	(*ldfn)(long double value);
   long double	(*ldfn2)(long double value1,long double value2);
  }l;
 };
 void *________;
 union{
  double      dresult;
  float       fresult;
  long double ldresult;
 }result;
};
int 
comput_two_numbers(struct arguments **args,char *option)
{
 char *subopts = option, *value = NULL;
 while(*subopts != '\0')
 {
  switch(getsubopt(&subopts,two_numbers,&value))
  {
   case X: (*args)->numbers[0] = value;
           break;
   case Y: (*args)->numbers[1] = value;
           break;
   default:fprintf(stderr,"unknow suboption: \"%s\"\n",value);
   	   return -2;
  }
 }
 if((*args)->numbers[0] == NULL || (*args)->numbers[1] == NULL)
 {
  return -1;
 }
 return 0;
}
void
parse_opt(int key, char *arg, struct parser_state *state)
{
 struct arguments *args = state->input;
 switch(key)
 {
  case 'c': args->function = COS;
  	    args->numbers[0] = arg;

  	    break;
  case 's': args->function = SIN;
  	    args->numbers[0] = arg;
  	    break;
  case 't': args->function = TAN;
  	    args->numbers[0] = arg;
  	    break;
  case 'S': args->function = SQRT;
  	    args->numbers[0] = arg;
  	    break;
  case 'e': args->function = EXP;
  	    args->numbers[0] = arg;
  	    break;
  case 'l': args->function = LOG;
  	    args->numbers[0] = arg;
  	    break;
  case 'L': args->function = LOG10;
  	    args->numbers[0] = arg;
  	    break;
  case 'f': args->function = FABS;
  	    args->numbers[0] = arg;
  	    break;
  case 'C': args->function = CEIL;
  	    args->numbers[0] = arg;
  	    break;
  case 'o': args->function = FLOOR;
  	    args->numbers[0] = arg;
  	    break;
  case 'p': args->function = POW;
  	    if(comput_two_numbers(&args,arg) < 0)
	    {
	     fprintf(stderr,"Missing(/Bad) arguments for \"-%c\".\n",key);
	     /*parser_usage(state);*/
	     exit(EXIT_FAILURE);
	    }
  	    break;
  case 'm': args->function = FMOD;
  	    if(comput_two_numbers(&args,arg) < 0)
	    {
	     fprintf(stderr,"Missing(/Bad) arguments for \"-%c\".\n",key);
	     /*parser_usage(state);*/
	     exit(EXIT_FAILURE);
	    }
  	    break;
  case 'F': args->type |= FLOAT;
  	    break;
  case 'd': args->type |= DOUBLE;
  	    break;
  case 'D': args->type |= LDOUBLE;
  	    break;
  case 'r': args->type |= IDEGRES;
  	    break;
  case 'R': args->type |= ORADIAN;
  	    break;
  case 'N': args->type |= NEWLINE;
  	    break;
  case 'O': args->format = arg;
  	/*parser_usage(state->parser);*/
  	    break;
  /*case ARGP_KEY_END:
  	    break;
  case ARGP_KEY_ARG:
  	    if( (arg && strlen(arg) > 0)|| &state->argv[state->next])
	    {
	     argp_usage(state);
	     break;
	    }
  	    state->next = state->argc;
	    break;*/
  default:
  	fprintf(stderr,"Unanderstand parameter: \'%s\'.\nTry --help or --usage for more information.\n", arg);
	exit(EXIT_FAILURE);
 }
 /*return 0;*/
}
const char about[] = "Simple program which use some function of 'math.h.'\"(gcc -lm)\"";
static struct parser argp = { options, parse_opt, "OPTIONS", NULL, \
				about, \
				&program, NULL };
void
check_double_value(int n,char *value,...)
{
  int i;
 va_list ap;
 char *val, *virgule;
 double result;
 for(i = n; i > 0; i--)
 {
  if(i < n)
  {
   val = va_arg(ap, char *);
  }
  else
  {
   va_start(ap,value);
   val = value;
  }
  while((virgule = strchr(val,',')))
  {
   *virgule = '.';
  }
  if(sscanf(val,"%lf",&result) == 0)
  {
   fprintf(stderr,"'%s': Bad value for 'sscanf()'.\n",val);
   exit(EXIT_FAILURE);
  }
 }
 va_end(ap);
}
void 
check_float_value(int n, char *value,...)
{
 int i;
 va_list ap;
 char *val, *virgule;
 float result;
 for(i = n; i > 0; i--)
 {
  if(i < n)
  {
   val = va_arg(ap, char *);
  }
  else
  {
   va_start(ap,value);
   val = value;
  }
  while((virgule = strchr(val,',')))
  {
   *virgule = '.';
  }
  if(sscanf(val,"%f",&result) == 0)
  {
   fprintf(stderr,"%s: Bad value for 'scanf()'.\n",val);
   exit(EXIT_FAILURE);
  }
 }
 va_end(ap);
}
void 
check_long_double_value(int n, char *value,...)
{
 int i;
 va_list ap;
 char *val,*virgule;
 long double result;
 for(i = n; i > 0; i--)
 {
  if(i < n)
  {
   val = va_arg(ap, char *);
  }
  else
  {
   va_start(ap,value);
   val = value;
  }
  while((virgule = strchr(val,',')))
  {
   *virgule = '.';
  }
  if(sscanf(val,"%Lf",&result) == 0)
  {
   fprintf(stderr,"%s: Bad value for 'sscanf()'.\n",val);
   exit(EXIT_FAILURE);
  }
 }
 va_end(ap);
}
int
check_virgule(char *string)
{
 char buffer[1024];
 if(sscanf(string,"%[0-9.,]",buffer) ==0)
 {
  perror("check_vigule:sscanf())");
  return -1;
 }
 return 0;
}
int
main(int argc,char **argv)
{
 struct arguments args = { 0, INIT, { NULL, NULL}, NULL};
 struct comput calcule = {0,0,NULL,0,{{0,0}},{{NULL}},NULL,{0}};
 char
 	*___dprintf___ = "%.6lf",
	*___fprintf___ = "%.12f",
	*___ldprintf___= "%.18Lf",
	*format[3] = {"lf","f","Lf"};
 char *end[2], *format_tmp;
 size_t len,len_;
 int n,i,set;
 bool need_to_be_created = 0;
 parser_parse(&argp, argc, argv, &args);
 if(args.function == INIT)
 {
  fprintf(stderr,"Aucune opération de fournie!!!\n");
  exit(EXIT_FAILURE);
 }
 set = args.type&(DOUBLE|FLOAT|LDOUBLE);
 switch(set)
 {
   case DOUBLE:
    switch(args.function)
    {
     case COS  : calcule.d.dfn = &cos;
	          n = 1;
	          break;
     case SIN  : calcule.d.dfn = &sin;
  	          n = 1;
  	          break;
     case TAN  : calcule.d.dfn = &tan;
	          n = 1;
	          break;
     case SQRT : calcule.d.dfn = &sqrt;
     		 n = 1;
		 break;
     case EXP  : calcule.d.dfn = &exp;
	         n = 1;
	         break;
     case LOG  : calcule.d.dfn = &log;
  	         n = 1;
  	         break;
     case LOG10: calcule.d.dfn = &log10;
  	         n = 1;
  	         break;
     case FABS : calcule.d.dfn = &fabs;
 	          n = 1;
  	          break;
     case CEIL : calcule.d.dfn = &ceil;
  	          n = 1;
  	          break;
     case FLOOR: calcule.d.dfn = &floor;
  	          n = 1;
  	          break;
     case POW  : calcule.d.dfn2 = &pow;
  	          n = 2;
  	          break;
     case FMOD : calcule.d.dfn2 = &fmod;
  	          n = 2;
  	          break;
     }
     break;
   case FLOAT:
    switch(args.function)
    {
     case COS  : calcule.f.ffn = &cosf;
	          n = 1;
	          break;
     case SIN  : calcule.f.ffn = &sinf;
  	          n = 1;
  	          break;
     case TAN  : calcule.f.ffn = &tanf;
	          n = 1;
	          break;
     case SQRT : calcule.f.ffn = &sqrtf;
 	       n = 1;
	       break;
     case EXP  : calcule.f.ffn = &expf;
	          n = 1;
	          break;
     case LOG  : calcule.f.ffn = &logf;
  	          n = 1;
  	          break;
     case LOG10: calcule.f.ffn = &log10f;
  	          n = 1;
  	          break;
     case FABS : calcule.f.ffn = &fabsf;
 	          n = 1;
  	          break;
     case CEIL : calcule.f.ffn = &ceilf;
  	          n = 1;
  	          break;
     case FLOOR: calcule.f.ffn = &floorf;
  	          n = 1;
  	          break;
     case POW  : calcule.f.ffn2 = &powf;
  	          n = 2;
  	          break;
     case FMOD : calcule.f.ffn2 = &fmodf;
  	          n = 2;
  	          break;
    }
    break;
   case LDOUBLE:
    switch(args.function)
    {
     case COS  : calcule.l.ldfn = &cosl;
	          n = 1;
	          break;
     case SIN  : calcule.l.ldfn = &sinl;
  	          n = 1;
  	          break;
     case TAN  : calcule.l.ldfn = &tanl;
	          n = 1;
	          break;
     case SQRT : calcule.l.ldfn = &sqrtl;
 	       n = 1;
	       break;
     case EXP  : calcule.l.ldfn = &expl;
	          n = 1;
	          break;
     case LOG  : calcule.l.ldfn = &logl;
  	          n = 1;
  	          break;
     case LOG10: calcule.l.ldfn = &log10l;
  	          n = 1;
  	          break;
     case FABS : calcule.l.ldfn = &fabsl;
 	          n = 1;
  	          break;
     case CEIL : calcule.l.ldfn = &ceill;
  	          n = 1;
  	          break;
     case FLOOR: calcule.l.ldfn = &floorl;
  	          n = 1;
  	          break;
     case POW  : calcule.l.ldfn2 = &powl;
  	          n = 2;
  	          break;
     case FMOD : calcule.l.ldfn2 = &fmodl;
  	          n = 2;
  	          break;
    }
    break;
   }
 switch(set)
 { 
  case DOUBLE:
   check_double_value(n, args.numbers[0],args.numbers[1]);
   /*Convertion (Degre/Radian)*/
   for(i = 0; i < 2; i++)
   {
    if(args.numbers[i]){
     end[i] = &args.numbers[i][strlen(args.numbers[i])-1];
     calcule.value.dnumber[i] = strtod(args.numbers[i],&end[i]);
    if(!(args.type&ORADIAN) && !(args.type&IDEGRES))
     calcule.value.dnumber[i] = calcule.value.dnumber[i]*PI/180;
    else
     if(((args.type&ORADIAN) && !(args.type&IDEGRES)) || (!(args.type&ORADIAN) && (args.type&IDEGRES)))
      calcule.value.dnumber[i] = calcule.value.dnumber[i];
     else
      if((args.type&ORADIAN) && (args.type&IDEGRES))
       calcule.value.dnumber[i] = calcule.value.dnumber[i]*180/PI;
      /*else
       if(!(args.type&ORADIAN) && (args.type&IDEGRES))
        calcule.value.dnumber[i] = calcule.value.dnumber[i];*/
    }
   }
   format_tmp = (char *)format[set];
   if(!args.format || check_virgule(args.format))
    calcule.format = (char *)___dprintf___;
   else
    /*Prepare to %.'args.format'lf*/
    need_to_be_created = 1;
   break;
  case FLOAT:
   check_float_value(n, args.numbers[0],args.numbers[1]);
    for(i = 0; i < 2; i++)
    {/*Convertion (Degres/Radian)*/
     if(args.numbers[i]){
      end[i] = &args.numbers[i][strlen(args.numbers[i])-1];
      calcule.value.fnumber[i] = strtof(args.numbers[i],&end[i]);
    if(!(args.type&ORADIAN) && !(args.type&IDEGRES))
     calcule.value.dnumber[i] = calcule.value.dnumber[i]*PI/180;
    else
     if(((args.type&ORADIAN) && !(args.type&IDEGRES)) || (!(args.type&ORADIAN) && (args.type&IDEGRES)))
      calcule.value.dnumber[i] = calcule.value.dnumber[i];
     else
      if((args.type&ORADIAN) && (args.type&IDEGRES))
       calcule.value.dnumber[i] = calcule.value.dnumber[i]*180/PI;
      /*else
       if(!(args.type&ORADIAN) && (args.type&IDEGRES))
        calcule.value.dnumber[i] = calcule.value.dnumber[i];*/
    }
   }
   format_tmp = (char *)format[set];
   if(!args.format || check_virgule(args.format))
    calcule.format = (char *)___fprintf___;
   else
    /*Prepare to %0.'args.format'lf*/
    need_to_be_created = 2;
   break;
  case LDOUBLE:
   check_long_double_value(n, args.numbers[0],args.numbers[1]);
   for(i = 0; i < 2; i++)
   {/*Convertion (Degres/Radian)*/
    if(args.numbers[i]){
     end[i] = &args.numbers[i][strlen(args.numbers[i]-1)];
     calcule.value.ldnumber[i] = strtold(args.numbers[i],&end[i]);
    if(!(args.type&ORADIAN) && !(args.type&IDEGRES))
     calcule.value.dnumber[i] = calcule.value.dnumber[i]*PI/180;
    else
     if(((args.type&ORADIAN) && !(args.type&IDEGRES)) || (!(args.type&ORADIAN) && (args.type&IDEGRES)))
      calcule.value.dnumber[i] = calcule.value.dnumber[i];
     else
      if((args.type&ORADIAN) && (args.type&IDEGRES))
       calcule.value.dnumber[i] = calcule.value.dnumber[i]*180/PI;
      /*else
       if(!(args.type&ORADIAN) && (args.type&IDEGRES))
        calcule.value.dnumber[i] = calcule.value.dnumber[i];*/
    }
   }
   format_tmp = (char *)format[set];
   if(!args.format || check_virgule(args.format))
    calcule.format = (char *)___ldprintf___;
   else
    need_to_be_created = 3;
   break;
  }
  format_tmp = format[set];
  if(need_to_be_created)
  { switch(set)
   {
    case FLOAT:
     calcule.formatlen = strlen(args.format) + 5; /*%.f & \0     :4 char*/
     break;
    case DOUBLE: case LDOUBLE:
     calcule.formatlen = strlen(args.format) + 6; /*%.lf/Lf & \0 :5 char*/
     break;
    default: break;
   }
  if((calcule.format = calloc(16+1+calcule.formatlen,sizeof(char))) == NULL) /*16+1: Je ne sais pas pourquoi*/
  {
   perror("malloc()");
   exit(EXIT_FAILURE);
  }
  len = strlen(args.format);
  len_= strlen(format_tmp);
  memcpy(calcule.format,"%.\0",3);
  memcpy(&calcule.format[2],args.format,len);
  memcpy(&calcule.format[2+len],format_tmp,len_);
  memcpy(&calcule.format[2+len+len_],"\0",1);
 }
 switch(args.function)
 {
  case POW: case FMOD:
   switch(set)
   {
    case DOUBLE:  calcule.result.dresult = calcule.d.dfn2(calcule.value.dnumber[0],calcule.value.dnumber[1]);
    		  break;
    case FLOAT:   calcule.result.fresult = calcule.f.ffn2(calcule.value.fnumber[0],calcule.value.fnumber[1]);
    		  break;
    case LDOUBLE: calcule.result.ldresult = calcule.l.ldfn2(calcule.value.ldnumber[0],calcule.value.ldnumber[1]);
    		  break;
   }
   break;
  default:
   switch(set)
   {
    case DOUBLE : calcule.result.dresult = calcule.d.dfn(calcule.value.dnumber[0]);
    		  break;
    case FLOAT  : calcule.result.fresult = calcule.f.ffn(calcule.value.fnumber[0]);
    		  break;
    case LDOUBLE: calcule.result.ldresult = calcule.l.ldfn(calcule.value.ldnumber[0]);
    		  break;
   }
   break;
 }
 /*switch(set)
 { 
  case DOUBLE:
    if(!(args.type&ORADIAN) && !(args.type&IRADIAN))
     calcule.result.dresult = calcule.result.dresult*M_PI/180;
    else
     if((args.type&ORADIAN) && !(args.type&IRADIAN))
      calcule.result.dresult = calcule.result.dresult;
     else
      if((args.type&ORADIAN) && (args.type&IRADIAN))
       calcule.result.dresult = calcule.result.dresult*180/M_PI;
      else
       if(!(args.type&ORADIAN) && (args.type&IRADIAN))
        calcule.result.dresult = calcule.result.dresult;
   break;
  case FLOAT:
      if(!(args.type&ORADIAN) && !(args.type&IRADIAN))
       calcule.result.fresult = calcule.result.fresult;
      else
       if((args.type&ORADIAN) && !(args.type&IRADIAN))
        calcule.result.fresult = calcule.result.fresult*M_PI/180;
       else
        if((args.type&ORADIAN) && (args.type&IRADIAN))
         calcule.result.fresult = calcule.result.fresult;
        else
         if(!(args.type&ORADIAN) && (args.type&IRADIAN))
          calcule.result.fresult = calcule.result.fresult*180/M_PI;
   break;
  case LDOUBLE:
     if(!(args.type&ORADIAN) && !(args.type&IRADIAN))
      calcule.result.ldresult = calcule.result.ldresult;
     else
      if((args.type&ORADIAN) && !(args.type&IRADIAN))
       calcule.result.ldresult = calcule.result.ldresult*M_PI/180;
      else
       if((args.type&ORADIAN) && (args.type&IRADIAN))
        calcule.result.ldresult = calcule.result.ldresult;
       else
        if(!(args.type&ORADIAN) && (args.type&IRADIAN))
         calcule.result.ldresult = calcule.result.ldresult*180/M_PI;
   break;
  }*/
 switch(set)
 {
  case DOUBLE:  printf(calcule.format,calcule.result.dresult);
  	        break;
  case FLOAT :  printf(calcule.format,calcule.result.fresult);
  	        break;
  case LDOUBLE: printf(calcule.format,calcule.result.ldresult);
  	        break;
 }
 if((args.type&NEWLINE))
  printf("\n");
 if(need_to_be_created)
     free(calcule.format);
 return 0;
}
