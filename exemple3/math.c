#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <argp.h>
#include <stdarg.h>
#include <string.h>

#define PI 3.141592653589793

const char *argp_program_version= "math-0.1";
const char *argp_program_bug_address = "zoeurk@gmail.com";
static char doc[] = "Simple program which use some function of 'math.h.'\"(gcc -lm)\"";

static struct argp_option
options[] = {	{"double",'d', NULL,0,"uliser une valeur double", 0},
		{"float",'F',NULL,0,"utiliser une valeur float", 0},
		{"dlong",'D',NULL,0,"utiliser une valeur double long", 0},
		{"cos",'c',"X",0,"cosinus d'un nombre X", 1},
		{"sin",'s',"X",0,"sinus d'un nombre X", 1},
		{"tan",'t',"X",0,"tangente d'un nombre X",1},
		{"acos",'a',"X",0,"cosinus d'un nombre X", 1},
		{"asin",'A',"X",0,"sinus d'un nombre X", 1},
		{"atan",'T',"X",0,"tangente d'un nombre X",1},
		{"sqrt",'S',"X",0,"carré d'un nombre X",1},
		{"exp",'e',"X",0,"valeur exponentiel d' un nombre X",1},
		{"log",'l',"X",0,"logarithme naturel (en base 'e') d'un nombre X", 1},
		{"log10",'L',"X",0,"logarithme naturel (en base 10) d'un nombre X", 1},
		{"fabs",'f',"X",0,"valeur absolue d'un nombre X", 1},
		{"ceil",'C',"X",0,"arrondi un nombre X à un entier plus petit", 1},
		{"floor",'o',"X",0,"arrondi un nombre X à un entier plus grand", 1},
		{"pow",'p',"X:Y",0,"puissance d'une valeur X élevé à la valeur Y",2},
		{"fmod",'m',"X:Y",0,"reste de X/Y",2},
		{"virgule",'O',"FORMAT",0,"afficher nombre de chiffre après la virgule",4},
		{"Radian",'R',NULL,0,"afficher le résultat en radian plutôt quand degrès",3},
		{"radian",'r',NULL,0,"les entrées sont en radian plutôt quand degrès",3},
		{"odegres",'x',NULL,0,"la sortie en degrès",3},
		{"newline",'N',NULL,0,"affiche le resultat avec un nouvelle ligne: \"result\\n\"", 5},
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
 FMOD	= 1024,
 ACOS	= 2048,
 ASIN	= 4096,
 ATAN	= 8192

}functions;
enum type
{
 FLOAT   = 0,
 DOUBLE  = 1,
 LDOUBLE = 2,
 IRADIAN = 4,
 ORADIAN = 8,
 ODEGRES = 16,
 NEWLINE = 32
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
static error_t
parse_opt(int key, char *arg, struct argp_state *state)
{
 struct arguments *args = state->input;
 int i;
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
  case 'a': args->function = ACOS;
  	    args->numbers[0] = arg;
  	    break;
  case 'A': args->function = ASIN;
  	    args->numbers[0] = arg;
  	    break;
  case 'T': args->function = ATAN;
  	    args->numbers[0] = arg;
  	    break;
  case 'p': args->function = POW;
  	    if(comput_two_numbers(&args,arg) < 0)
	    {
	     fprintf(stderr,"Missing(/Bad) arguments for \"-%c\".\n",key);
	     argp_usage(state);
	     exit(EXIT_FAILURE);
	    }
  	    break;
  case 'm': args->function = FMOD;
  	    if(comput_two_numbers(&args,arg) < 0)
	    {
	     fprintf(stderr,"Missing(/Bad) arguments for \"-%c\".\n",key);
	     argp_usage(state);
	     exit(EXIT_FAILURE);
	    }
  	    break;
  case 'F': args->type |= FLOAT;
  	    break;
  case 'd': args->type |= DOUBLE;
  	    break;
  case 'D': args->type |= LDOUBLE;
  	    break;
  case 'r': args->type |= IRADIAN;
  	    break;
  case 'R': args->type |= ORADIAN;
  	    break;
  case 'x': args->type |= ODEGRES;
  	    break;
  case 'N': args->type |= NEWLINE;
  	    break;
  case 'O': for(i = 0; (unsigned long int)i <strlen(arg); i++){
	     if(arg[i] < 48 || arg[i] > 57){
		     fprintf(stderr,"Bad value for format:\'%s\'.\n",arg);
		     args->format = NULL;
		     i = 0;
		     break;
	     }
	    }
	    if((unsigned long int)i == strlen(arg))args->format = arg;
	    else	args->format = NULL;
  	    break;
  case ARGP_KEY_END:
  	    break;
  case ARGP_KEY_ARG:
  	    if( (arg && strlen(arg) > 0)|| &state->argv[state->next])
	    {
	     argp_usage(state);
	     break;
	    }
  	    state->next = state->argc;
	    break;
  default:
  	    return ARGP_ERR_UNKNOWN;
 }
 return 0;
}
static struct argp argp = { options, parse_opt, NULL, doc, NULL, NULL, NULL };
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
/*int
check_virgule(char *buffer, char *string)
{
 char buffer[1024];
 if(strlen(string) > 1023 || sscanf(string,"%[0-9]*",buffer) ==0)
 {
  fprintf(stderr, "Bad format: \'%s\'.\n", string);
  return -1;
 }
 printf("=>%s\n", buffer);
 strcpy(string,buffer);
 return 0;
}*/
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
 argp_parse(&argp, argc, argv, 0, 0, &args);
 if((int)args.function == INIT)
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
     case ACOS :  calcule.d.dfn = &acos;
     		  n = 1;
     		  break;
     case ASIN :  calcule.d.dfn = &asin;
     		  n = 1;
     		  break;
     case ATAN :  calcule.d.dfn = &atan;
     		  n = 1;
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
     case ACOS :  calcule.f.ffn = &acosf;
     		  n = 1;
     		  break;
     case ASIN :  calcule.f.ffn = &asinf;
     		  n = 1;
     		  break;
     case ATAN :  calcule.f.ffn = &atanf;
     		  n = 1;
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
     case ACOS :  calcule.l.ldfn = &acosl;
     		  n = 1;
     		  break;
     case ASIN :  calcule.l.ldfn = &asinl;
     		  n = 1;
     		  break;
     case ATAN :  calcule.l.ldfn = &atanl;
     		  n = 1;
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
    if(!(args.type&ORADIAN) && !(args.type&IRADIAN))
     calcule.value.dnumber[i] = calcule.value.dnumber[i]*PI/180;
    else
     if(((args.type&ORADIAN) && !(args.type&IRADIAN)) || (!(args.type&ORADIAN) && (args.type&IRADIAN)))
      calcule.value.dnumber[i] = calcule.value.dnumber[i];
     else
      if((args.type&ORADIAN) && (args.type&IRADIAN))
       calcule.value.dnumber[i] = calcule.value.dnumber[i]*180/PI;
      /*else
       if(!(args.type&ORADIAN) && (args.type&IRADIAN))
        calcule.value.dnumber[i] = calcule.value.dnumber[i];*/
    }
   }
   format_tmp = (char *)format[set];
   /*if(!args.format || check_virgule(args.format))*/
   if(!args.format)
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
      if(!(args.type&ORADIAN) && !(args.type&IRADIAN))
       calcule.value.fnumber[i] = calcule.value.fnumber[i]*PI/180;
      else
       if(((args.type&ORADIAN) && !(args.type&IRADIAN)) || (!(args.type&ORADIAN) && (args.type&IRADIAN)))
        calcule.value.fnumber[i] = calcule.value.fnumber[i];
       else
        if((args.type&ORADIAN) && (args.type&IRADIAN))
         calcule.value.fnumber[i] = calcule.value.fnumber[i]*180/PI;
        /*else
         if(!(args.type&ORADIAN) && (args.type&IRADIAN))
          calcule.value.fnumber[i] = calcule.value.fnumber[i];*/
    }
   }
   format_tmp = (char *)format[set];
   /*if(!args.format || check_virgule(args.format))*/
   if(!args.format)
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
     if(!(args.type&ORADIAN) && !(args.type&IRADIAN))
      calcule.value.ldnumber[i] = calcule.value.ldnumber[i]*PI/180;
     else
      if(((args.type&ORADIAN) && !(args.type&IRADIAN)) || (!(args.type&ORADIAN) && (args.type&IRADIAN)))
       calcule.value.ldnumber[i] = calcule.value.ldnumber[i];
      else
       if((args.type&ORADIAN) && (args.type&IRADIAN))
        calcule.value.ldnumber[i] = calcule.value.ldnumber[i]*180/PI;
       /*else
        if(!(args.type&ORADIAN) && (args.type&IRADIAN))
         calcule.value.ldnumber[i] = calcule.value.ldnumber[i];*/
    }
   }
   format_tmp = (char *)format[set];
   /*if(!args.format || check_virgule(args.format))*/
   if(!args.format)
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
  if((calcule.format = calloc(16+1+calcule.formatlen,sizeof(char))) == NULL)
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
    		  if((args.type&IRADIAN) == IRADIAN && (args.type&ODEGRES) == ODEGRES)
    		  	calcule.result.dresult = calcule.result.dresult *180/PI;
    		  break;
    case FLOAT: calcule.result.fresult = calcule.f.ffn2(calcule.value.fnumber[0],calcule.value.fnumber[1]);
    		  if((args.type&IRADIAN) == IRADIAN && (args.type&ODEGRES) == ODEGRES)
    		  	calcule.result.fresult = calcule.result.fresult *180/PI;
    		  break;
    case LDOUBLE: calcule.result.ldresult = calcule.l.ldfn2(calcule.value.ldnumber[0],calcule.value.ldnumber[1]);
    		  if((args.type&IRADIAN) == IRADIAN && (args.type&ODEGRES) == ODEGRES)
    		  	calcule.result.ldresult = calcule.result.ldresult *180/PI;
    		  break;
   }
   break;
  default:
   switch(set)
   {
    case DOUBLE : calcule.result.dresult = calcule.d.dfn(calcule.value.dnumber[0]);
    		  if((args.type&IRADIAN) == IRADIAN && (args.type&ODEGRES) == ODEGRES)
    		  	calcule.result.dresult = calcule.result.dresult *180/PI;
 		  break;
    case FLOAT  : calcule.result.fresult = calcule.f.ffn(calcule.value.fnumber[0]);
    		  if((args.type&IRADIAN) == IRADIAN && (args.type&ODEGRES) == ODEGRES)
    		  	calcule.result.fresult = calcule.result.fresult *180/PI;
 		  break;
    case LDOUBLE: calcule.result.ldresult = calcule.l.ldfn(calcule.value.ldnumber[0]);
    		  if((args.type&IRADIAN) == IRADIAN && (args.type&ODEGRES) == ODEGRES)
    		  	calcule.result.ldresult = calcule.result.ldresult *180/PI;
 		  break;
   }
   break;
 }
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
