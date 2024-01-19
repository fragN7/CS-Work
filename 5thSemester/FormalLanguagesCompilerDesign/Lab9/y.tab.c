/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "lang.y"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYDEBUG 1

int yylex(void);
void yyerror(char *s);
#line 29 "y.tab.c"

#if ! defined(YYSTYPE) && ! defined(YYSTYPE_IS_DECLARED)
/* Default: YYSTYPE is the semantic value type. */
typedef int YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define Start 257
#define InBetween 258
#define Between 259
#define num 260
#define str 261
#define bol 262
#define Perhaps 263
#define Enter 264
#define Leave 265
#define identifier 266
#define constant 267
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    2,    2,    2,    3,    3,    1,    6,    6,    4,
    4,    4,    8,    8,    8,   10,   10,   11,   11,   12,
    7,    9,    9,    9,    5,    5,    5,    5,   14,   15,
   15,   15,   15,   16,   16,   13,   13,   13,   18,   18,
   18,   18,   19,   19,   19,   17,   20,   20,   20,   20,
   20,   20,
};
static const YYINT yylen[] = {                            2,
    2,    1,    1,    1,    1,    1,    3,    1,    3,    1,
    1,    1,    1,    1,    1,    3,    3,    4,    4,    3,
    3,    4,    3,    2,    1,    1,    1,    1,    7,    7,
    3,    3,    9,    3,   11,    3,    3,    1,    3,    3,
    3,    1,    3,    1,    1,    3,    1,    1,    1,    1,
    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,    1,    0,    0,    0,    0,    0,    0,
    0,   25,    0,    5,    6,    0,   10,   11,   12,   13,
   14,   15,   26,   27,   28,    0,    0,    0,    0,    0,
    0,    0,   24,    0,    0,    0,    0,    7,   34,    0,
   45,    0,    0,    0,    0,   42,   44,    0,    0,   23,
    0,    0,    0,    2,    3,    4,   20,   17,    0,    0,
    0,    9,    0,    0,    0,   47,   48,   49,   50,   51,
   52,    0,    0,    0,    0,    0,    0,   22,   18,   19,
    0,    0,   43,    0,    0,    0,    0,   39,   40,   41,
    0,    0,    0,    0,    0,    0,    0,   30,   29,    0,
    0,    0,    0,    0,   33,    0,   35,
};
static const YYINT yydgoto[] = {                          2,
   12,   57,   13,   14,   15,   16,   17,   18,   19,   20,
   21,   22,   43,   23,   24,   25,   44,   45,   46,   72,
};
static const YYINT yysindex[] = {                      -243,
 -105,    0, -118,    0, -101,  -98,  -92,  -74,  -51,  -57,
  -28,    0,   56,    0,    0,  -48,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -192, -116, -113, -187, -184,
  -83, -215,    0, -215,   25, -203, -118,    0,    0,    0,
    0, -113,  -41,  -36,  -13,    0,    0,  -35,  -34,    0,
    0, -174,  -17,    0,    0,    0,    0,    0, -215,   49,
   50,    0,  -30, -113, -113,    0,    0,    0,    0,    0,
    0, -113,  -27, -113, -113, -113,  -25,    0,    0,    0,
 -167, -166,    0,  -13,  -13,  -17, -118,    0,    0,    0,
 -118,   43,  -23,  -21,  -19, -215,  -18,    0,    0,  -16,
 -118,  -15,  -14, -118,    0,  -12,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   -9,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -10,
    0,    0,    0,    0,   -7,    0,    0,    0,    0,    0,
   33,    0,    1,    0,    0,    0,    0,    0,    0,    2,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   -4,   -1,   -8,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  106,  -11,    0,    0,    0,  -20,    0,    0,    0,    0,
    0,    0,   31,    0,    0,    0,   82,    4,   12,    0,
};
#define YYTABLESIZE 270
static const YYINT yytable[] = {                         31,
   32,   64,   38,   65,    3,   36,   42,   52,   37,   42,
   21,   32,   64,    1,   65,   36,   62,    3,   66,   68,
   71,   26,   58,   76,   27,   64,   44,   65,   74,   34,
   28,   44,   44,   75,   44,   38,   44,   38,   36,   42,
   36,   37,   16,   37,   54,   55,   56,   80,   29,   44,
   44,   44,   38,   38,   38,   36,   36,   36,   37,   37,
   37,   53,   60,   61,   35,   37,   94,   84,   85,   44,
   95,   30,   63,   39,   44,   44,   38,   44,   49,   44,
  103,   50,   59,  106,  100,   88,   89,   90,   73,   77,
   78,   79,   81,   82,   83,   87,   33,   91,   92,   93,
   96,   97,   86,   98,  101,   99,    4,  104,  102,   48,
  105,    0,  107,    0,   31,    8,   46,   38,    0,    0,
   36,    0,    0,   37,    0,   21,   32,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    5,
    6,    0,    0,    0,    7,    8,    9,   10,   11,   40,
   41,    0,   47,   41,    0,    0,    0,   16,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   51,   41,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   31,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   67,   69,   70,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   44,   44,
   44,   38,   38,   38,   36,   36,   36,   37,   37,   37,
};
static const YYINT yycheck[] = {                         10,
   58,   43,   10,   45,  123,   10,  123,   91,   10,  123,
   10,   10,   43,  257,   45,   44,   37,  123,   60,   61,
   62,  123,   34,   37,  123,   43,   37,   45,   42,   58,
  123,   42,   43,   47,   45,   43,   47,   45,   43,  123,
   45,   43,   10,   45,  260,  261,  262,   59,  123,   60,
   61,   62,   60,   61,   62,   60,   61,   62,   60,   61,
   62,   31,  266,  267,   93,   10,   87,   64,   65,   37,
   91,  123,   42,  266,   42,   43,  125,   45,  266,   47,
  101,  266,   58,  104,   96,   74,   75,   76,  125,  125,
  125,  266,   44,   44,  125,  123,  125,  123,  266,  266,
   58,  125,   72,  125,  123,  125,    1,  123,  125,   28,
  125,   -1,  125,   -1,  125,  125,  125,  125,   -1,   -1,
  125,   -1,   -1,  125,   -1,  125,  125,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  258,
  259,   -1,   -1,   -1,  263,  264,  265,  266,  267,  266,
  267,   -1,  266,  267,   -1,   -1,   -1,  125,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  266,  267,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  268,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  269,  270,  271,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  269,  270,
  271,  269,  270,  271,  269,  270,  271,  269,  270,  271,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 271
#define YYUNDFTOKEN 294
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'%'",0,0,0,0,"'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,
"':'",0,"'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",
0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"Start","InBetween","Between","num","str","bol",
"Perhaps","Enter","Leave","identifier","constant","\"<-\"","\"<=\"","\"<>\"",
"\">=\"",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : Start cmpdstmt",
"type : num",
"type : str",
"type : bol",
"stmt : simplstmt",
"stmt : structstmt",
"cmpdstmt : '{' stmtlist '}'",
"stmtlist : stmt",
"stmtlist : stmt '\\n' stmtlist",
"simplstmt : assignstmt",
"simplstmt : decl",
"simplstmt : iostmt",
"decl : normalDecl",
"decl : arrayDecl",
"decl : emptyDecl",
"normalDecl : identifier \"<-\" identifier",
"normalDecl : constant ':' type",
"arrayDecl : identifier \"<-\" '[' identifier",
"arrayDecl : constant ']' ':' type",
"emptyDecl : identifier ':' type",
"assignstmt : identifier \"<-\" expression",
"iostmt : Enter '{' identifier '}'",
"iostmt : Leave '{' identifier",
"iostmt : constant '}'",
"structstmt : cmpdstmt",
"structstmt : ifstmt",
"structstmt : whileforstmt",
"structstmt : arrayParsing",
"ifstmt : Perhaps '{' condition '}' '{' stmtlist '}'",
"whileforstmt : Between '{' condition '}' '{' stmtlist '}'",
"whileforstmt : Between '{' identifier",
"whileforstmt : constant ',' identifier",
"whileforstmt : constant ',' constant ',' identifier '}' '{' stmtlist '}'",
"arrayParsing : InBetween '{' identifier",
"arrayParsing : constant ',' identifier ',' identifier ':' type '}' '{' stmtlist '}'",
"expression : expression '+' term",
"expression : expression '-' term",
"expression : term",
"term : term '*' factor",
"term : term '/' factor",
"term : term '%' factor",
"term : factor",
"factor : '{' expression '}'",
"factor : identifier",
"factor : constant",
"condition : expression relation expression",
"relation : '<'",
"relation : \"<=\"",
"relation : '='",
"relation : \"<>\"",
"relation : \">=\"",
"relation : '>'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 71 "lang.y"

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

extern FILE *yyin;

int main(int argc, char **argv)
{
	if(argc>1) yyin :  fopen(argv[1],"r");
	if(argc>2 && !strcmp(argv[2],"-d")) yydebug = 1;
	if(!yyparse()) fprintf(stderr, "\tProgram is syntactically correct.\n");
}
#line 329 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
