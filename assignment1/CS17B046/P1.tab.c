/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "P1.y" /* yacc.c:339  */

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	int DEBUG=0;
	int yyerror();
	int yylex(void);
	
	//defining a linked list
	struct Node
	{
		char str[1000];
		struct Node* next;	
	};
	
	struct List
	{
		struct Node* head;
		struct Node* tail;
	};
	
	int isEmpty(struct List* l)
	{
		if(l->head == NULL && l->tail==NULL) {
			return 1;
		}else{
			return 0;
		}
	};
	
	struct List* newList()
	{
		struct List* tmp = (struct List*)malloc(sizeof(struct List));
		tmp->head = NULL;
		tmp->tail = NULL;
		return tmp;
	};
	
	//linked list is pass by ref
	void concatList(struct List* l1, struct List* l2)
	{
		if(!isEmpty(l2)){
			if(isEmpty(l1)){
				//l1 is zero
				l1->head = l2->head;
				l1->tail = l2->tail;
				l2->head = NULL;
				l2->tail = NULL;
			}else{
				//both non zero
				l1->tail->next = l2->head;
				l1->tail = l2->tail;
				l2->head = NULL;
				l2->tail = NULL;
			}
		}else{
			//l1 is unchanged
		}
	};
	
	void concatString(struct List* l1, char* inp)
	{
		//initialize temp
		struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
		sprintf(temp->str,"%s",inp);
		temp->next = NULL;
		if(isEmpty(l1)){
			l1->head = temp;
			l1->tail = temp;
		}else{
			l1->tail->next = temp;
			l1->tail = temp;
		}
	};
	
	void concatChar(struct List* l1, char ch)
	{
		//initialize temp
		struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
		sprintf(temp->str, "%c", ch);
		temp->next = NULL;
		if(isEmpty(l1)){
			l1->head = temp;
			l1->tail = temp;
		}else{
			l1->tail->next = temp;
			l1->tail = temp;
		}
	};
	
	void concatInt(struct List* l1, int x)
	{
		struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
		sprintf(temp->str, "%d", x);
		temp->next = NULL;
		if(isEmpty(l1)){
			l1->head = temp;
			l1->tail = temp;
		}else{
			l1->tail->next = temp;
			l1->tail = temp;
		}
	};
	
	
	struct MacroNode
	{
		char name[100];//assume macro cant have name > 100 characters
		int n_args;
		struct List* args;
		struct List* substitute;
		struct MacroNode* next;
	};
	
	struct MacroList
	{
		struct MacroNode* head;
		struct MacroNode* tail;
	};

	int isEmptyMList(struct MacroList* gmlist)
	{
		if(gmlist->head==NULL && gmlist->tail==NULL){
			return 1;
		}else{
			return 0;
		}
	}

	struct MacroNode* newMNode()
	{
		struct MacroNode* tmp = (struct MacroNode*)malloc(sizeof(struct MacroNode));
		tmp->n_args=0;
		tmp->args = newList();
		tmp->substitute = newList();
		tmp->next = NULL;
		return tmp;
	}
	struct MacroList* newMList()
	{
		struct MacroList* tmp = (struct MacroList*)malloc(sizeof(struct MacroList));
		tmp->head = NULL;
		tmp->tail = NULL;
		return tmp;
	};

	struct MacroList* GMList;
	
	
	void addToGlobalList(struct MacroNode* m)
	{
		if(GMList==NULL)
		{
			GMList = newMList();
		}
		
		if(isEmptyMList(GMList)){
			GMList->head = m;
			GMList->tail = m;
		}
		else{
			struct MacroNode* ptr = NULL;
			ptr = GMList->head;
		
			while(ptr!=NULL)
			{
				if(strcmp(ptr->name,m->name) == 0)
				{
					break;
				}
				ptr = ptr->next;
			}
			
			if(ptr==NULL){
			GMList->tail->next = m;
			GMList->tail = GMList->tail->next;
			}else{
			;
			}
		}
	};
	
	void printList(struct List* l)
	{
		struct Node* itr = NULL;
		itr = l->head;
		
		while(itr!=NULL)
		{
			if(itr->str[0] == '}'){
				printf("\n");
			}
			printf("%s ",itr->str);
			if(itr->str[0] == '}')
			{
				printf("\n");
			}
			if(itr->str[0] == '{' || itr->str[0]== ';')
			{
				printf("\n");
			}
			itr = itr->next;
		}
	}
	
	struct Node* getCompaction(struct List* l)
	{
		//printf("I am here\n");
		//compacts all characters of l into one string and returns it
		struct Node* tmp = (struct Node*)malloc(sizeof(struct Node));
		tmp->next = NULL;
		struct Node* ptr = l->head;
		//print initial string into tmp
		while(ptr!=NULL)
		{
			strcat(tmp->str, ptr->str);
			ptr=ptr->next;
		}
		
		//preserve tail condition
		//printf("Vimarsh:%s\n",tmp->str);
		return tmp;
		
	}
	
	int checkMacroList(char* chk_name)
	{
		struct MacroNode* ptr=NULL;
		ptr = GMList->head;
		int flag=0;
		while(ptr!=NULL)
		{
			if(strcmp(ptr->name,chk_name) == 0)
			{
				flag=1;
				break;			
			}
			ptr = ptr->next;
		}
		return flag;
		
	}
	
	struct List* copyList(struct List* l)
	{
		struct List* copy = newList();
		struct Node* ptr1 = l->head;
		while(ptr1!=NULL)
		{
			concatString(copy, ptr1->str);
			ptr1 = ptr1->next;
		}	
		return copy;
	}
	
	struct List* substituteMacro(char* name, struct List* rep_arg)
	{
		
		//search for macro
		struct MacroNode* ptr = NULL;
		ptr = GMList->head;
		
		while(ptr!=NULL)
		{
			if(strcmp(ptr->name,name) == 0)
			{
				break;
			}
			ptr = ptr->next;
		}
		
		if(ptr==NULL){
			yyerror(NULL);
		}
		
		struct List* ans = NULL;
		ans = copyList(ptr->substitute);
		
		struct Node* slow = NULL;
		struct Node* fast = NULL;
		struct Node* slow_rep = NULL;
		
		slow = ptr->args->head;
		slow_rep = rep_arg->head;
		
		while(slow!=NULL && slow_rep!=NULL)
		{
			fast = NULL;
			fast = ans->head;
			while(fast!=NULL)
			{
				if(strcmp(slow->str, fast->str) == 0)
				{
					//replace here inside ans
					strcpy(fast->str,slow_rep->str);
				}
				fast = fast->next;
			}
			
			slow = slow->next;
			slow_rep = slow_rep->next;
		}
		
		return ans;
	}
	
	void printMacroList(struct List* l)
	{
		struct MacroNode* ptr = NULL;
		ptr = GMList->head;
		int c=1;
		while(ptr!=NULL)
		{
			printf("Macro %d :::: \n Name: %s\n", c,ptr->name);
			printf("No of args: %d \nArguments: ", ptr->n_args);
			printList(ptr->args);
			printf("\nSubstitute: ");
			printList(ptr->substitute);
			printf("\n");
			c++;
			ptr = ptr->next;
		}
	}
	
	

#line 394 "P1.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "P1.tab.h".  */
#ifndef YY_YY_P1_TAB_H_INCLUDED
# define YY_YY_P1_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CLASS = 258,
    PUBLIC = 259,
    STATIC = 260,
    VOID = 261,
    EXTENDS = 262,
    RETURN = 263,
    INT = 264,
    STRING = 265,
    BOOLEAN = 266,
    IF = 267,
    ELSE = 268,
    WHILE = 269,
    TRUEVAL = 270,
    FALSEVAL = 271,
    THIS = 272,
    NEW = 273,
    MAIN = 274,
    SYSTEMOUTPRINTLN = 275,
    DEFINE = 276,
    LENGTH = 277,
    LEFTC = 278,
    RIGHTC = 279,
    LEFTB = 280,
    RIGHTB = 281,
    LEFTSQ = 282,
    RIGHTSQ = 283,
    DOT = 284,
    HASH = 285,
    SEMICOLON = 286,
    COMMA = 287,
    EQUAL = 288,
    AND = 289,
    OR = 290,
    NOT = 291,
    PLUS = 292,
    MINUS = 293,
    MULT = 294,
    DIV = 295,
    LESS = 296,
    Integer = 297,
    Identifier = 298,
    ANDAND = 299,
    OROR = 300,
    NOTEQUAL = 301,
    LESSEQUAL = 302
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 330 "P1.y" /* yacc.c:355  */

	int c_int;
	char* c_str;
	char c_char;
	struct List* list;	
	struct MacroNode* mnode;

#line 490 "P1.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_P1_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 507 "P1.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   169

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  181

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   363,   363,   374,   380,   385,   392,   397,   425,   435,
     449,   458,   464,   471,   476,   496,   504,   509,   518,   523,
     530,   535,   542,   547,   552,   559,   566,   575,   584,   595,
     606,   618,   627,   650,   668,   673,   687,   692,   701,   706,
     713,   720,   727,   734,   741,   748,   755,   762,   770,   777,
     782,   792,   814,   821,   826,   831,   836,   841,   846,   851,
     860,   869,   875,   884,   889,   896,   919,   947,   955,   960,
     969
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CLASS", "PUBLIC", "STATIC", "VOID",
  "EXTENDS", "RETURN", "INT", "STRING", "BOOLEAN", "IF", "ELSE", "WHILE",
  "TRUEVAL", "FALSEVAL", "THIS", "NEW", "MAIN", "SYSTEMOUTPRINTLN",
  "DEFINE", "LENGTH", "LEFTC", "RIGHTC", "LEFTB", "RIGHTB", "LEFTSQ",
  "RIGHTSQ", "DOT", "HASH", "SEMICOLON", "COMMA", "EQUAL", "AND", "OR",
  "NOT", "PLUS", "MINUS", "MULT", "DIV", "LESS", "Integer", "Identifier",
  "ANDAND", "OROR", "NOTEQUAL", "LESSEQUAL", "$accept", "Goal",
  "MacroDefinitionStar", "TypeDeclarationStar", "MainClass",
  "TypeDeclaration", "Type_Identifier_SemicolonStar",
  "MethodDeclarationStar", "MethodDeclaration", "MethodArgument",
  "Comma_Type_IdentifierStar", "StatementStar", "Type", "Statement",
  "MacroArgument", "Comma_ExpressionStar", "Comma_ExpressionStar1",
  "Expression", "ExpressionArgument", "PrimaryExpression",
  "MacroDefinition", "MacroDefStatement", "MacroDefExpression",
  "IdentifierArgument", "Comma_IdentifierStar", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302
};
# endif

#define YYPACT_NINF -115

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-115)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -21,     8,    23,    29,   -21,  -115,  -115,   -10,  -115,    -6,
    -115,  -115,    21,    25,    51,    10,    56,    12,  -115,  -115,
      39,    64,    18,    38,    13,    65,    31,  -115,    32,    41,
       2,    53,    54,    -4,  -115,  -115,  -115,  -115,    -3,    41,
      41,  -115,    55,    52,    83,    57,    58,    62,     2,     1,
      61,     2,    66,  -115,    63,  -115,  -115,     4,    45,    67,
      68,    81,  -115,    41,  -115,    50,    -1,    50,    50,    50,
      50,    50,    50,    50,    50,    41,    41,    41,    80,    41,
      41,    41,  -115,  -115,    98,    -4,    85,    -4,  -115,  -115,
      78,    41,    91,  -115,    92,  -115,  -115,    89,  -115,    96,
    -115,  -115,  -115,  -115,  -115,  -115,  -115,  -115,   100,   102,
     107,  -115,   108,   105,   103,   109,    15,  -115,    94,  -115,
     111,  -115,  -115,   110,  -115,    41,     2,     2,   104,   113,
     112,  -115,   118,  -115,   117,  -115,    41,  -115,   123,   128,
    -115,  -115,  -115,    41,   106,    -4,  -115,   116,  -115,     2,
     119,   127,   129,   114,    41,  -115,  -115,   130,   131,  -115,
    -115,   132,  -115,   122,   135,     6,    -4,    41,     1,   151,
     120,   136,    41,  -115,   133,   134,   140,   141,   142,  -115,
    -115
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     0,     4,    64,    63,     0,     1,     0,
       6,     3,     0,     0,     2,    68,     0,     0,     5,    70,
       0,     0,     0,    67,     0,     0,     0,    11,     0,     0,
      20,     0,     0,    13,    69,    55,    56,    58,     0,     0,
       0,    54,    57,     0,    49,     0,     0,     0,    20,     0,
       0,    20,     0,    11,    23,    22,    24,     0,     0,     0,
       0,     0,    61,    34,    66,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
       0,     0,    65,    19,     0,    13,     0,     0,     8,    12,
       0,     0,     0,    62,     0,    36,    57,     0,    48,     0,
      43,    44,    45,    46,    39,    40,    41,    42,     0,     0,
       0,    25,     0,     0,     0,     0,     0,    21,     0,    10,
       0,    60,    51,    33,    47,    53,     0,     0,     0,     0,
       0,    27,     0,     9,     0,    59,     0,    38,     0,    29,
      31,    26,    32,     0,     0,    16,    35,    52,    50,     0,
       0,     0,     0,     0,     0,    30,    28,     0,     0,    18,
      37,     0,    11,    15,     0,    20,     0,     0,    24,     0,
       0,     0,     0,    17,     0,     0,     0,     0,     0,    14,
       7
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -115,  -115,   157,  -115,  -115,  -115,   -51,    77,  -115,  -115,
    -115,   -47,   -84,  -114,    90,  -115,  -115,   -29,  -115,    30,
    -115,  -115,  -115,  -115,  -115
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    14,    10,    18,    33,    57,    89,   152,
     163,    50,    58,    51,    94,   123,   147,    95,   138,    44,
       4,     5,     6,    20,    23
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      43,    78,    85,   118,    83,    54,    59,    55,    87,     1,
      61,    62,   139,   140,    45,    54,    46,    55,    45,    87,
      46,    98,    47,     8,    79,    26,    47,    48,    80,     7,
      88,    48,     9,    12,    81,   155,    29,    13,    30,    56,
      60,   133,    99,    27,    15,    49,   108,   109,   110,   168,
      16,   113,   114,    19,    17,    22,    35,    36,    37,    38,
      21,   153,   120,    24,    39,    35,    36,    37,    38,    25,
      28,    31,    52,    39,    32,    34,    64,    40,    63,    53,
      75,    76,   170,    41,    42,    77,    40,    82,    90,    84,
      86,    92,    41,    96,    91,    97,   137,   100,   101,   102,
     103,   104,   105,   106,   107,    93,   111,   146,   115,   119,
      65,   165,    66,   117,   150,   121,   122,   124,   169,   125,
      67,    68,    69,    70,   126,   160,   127,    71,    72,    73,
      74,   128,   129,   130,   131,   141,   132,   134,   171,   135,
     145,   149,   136,   175,   142,   143,   144,   148,   154,   151,
     156,   157,   164,   158,   166,   161,   162,   159,   167,   172,
     174,    11,   116,   173,   176,   177,   178,   179,   180,   112
};

static const yytype_uint8 yycheck[] =
{
      29,    48,    53,    87,    51,     9,     9,    11,     4,    30,
      39,    40,   126,   127,    12,     9,    14,    11,    12,     4,
      14,    22,    20,     0,    23,     7,    20,    25,    27,    21,
      26,    25,     3,    43,    33,   149,    23,    43,    25,    43,
      43,    26,    43,    25,    23,    43,    75,    76,    77,    43,
      25,    80,    81,    43,     3,    43,    15,    16,    17,    18,
       4,   145,    91,    24,    23,    15,    16,    17,    18,     5,
      32,     6,    19,    23,    43,    43,    24,    36,    23,    25,
      23,    23,   166,    42,    43,    23,    36,    26,    43,    23,
      27,    23,    42,    43,    27,    65,   125,    67,    68,    69,
      70,    71,    72,    73,    74,    24,    26,   136,    10,    31,
      27,   162,    29,    28,   143,    24,    24,    28,   165,    23,
      37,    38,    39,    40,    24,   154,    24,    44,    45,    46,
      47,    24,    24,    28,    31,    31,    27,    43,   167,    28,
      23,    13,    32,   172,    31,    33,    28,    24,    32,    43,
      31,    24,    20,    24,    32,    25,    25,    43,    23,     8,
      24,     4,    85,    43,    31,    31,    26,    26,    26,    79
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    30,    49,    50,    68,    69,    70,    21,     0,     3,
      52,    50,    43,    43,    51,    23,    25,     3,    53,    43,
      71,     4,    43,    72,    24,     5,     7,    25,    32,    23,
      25,     6,    43,    54,    43,    15,    16,    17,    18,    23,
      36,    42,    43,    65,    67,    12,    14,    20,    25,    43,
      59,    61,    19,    25,     9,    11,    43,    55,    60,     9,
      43,    65,    65,    23,    24,    27,    29,    37,    38,    39,
      40,    44,    45,    46,    47,    23,    23,    23,    59,    23,
      27,    33,    26,    59,    23,    54,    27,     4,    26,    56,
      43,    27,    23,    24,    62,    65,    43,    67,    22,    43,
      67,    67,    67,    67,    67,    67,    67,    67,    65,    65,
      65,    26,    62,    65,    65,    10,    55,    28,    60,    31,
      65,    24,    24,    63,    28,    23,    24,    24,    24,    24,
      28,    31,    27,    26,    43,    28,    32,    65,    66,    61,
      61,    31,    31,    33,    28,    23,    65,    64,    24,    13,
      65,    43,    57,    60,    32,    61,    31,    24,    24,    43,
      65,    25,    25,    58,    20,    54,    32,    23,    43,    59,
      60,    65,     8,    43,    24,    65,    31,    31,    26,    26,
      26
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    50,    50,    51,    51,    52,    53,    53,
      54,    54,    55,    55,    56,    57,    57,    58,    58,    59,
      59,    60,    60,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    62,    63,    63,    64,    64,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    68,    68,    69,    70,    71,    71,    72,
      72
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     0,     2,     0,    21,     6,     8,
       4,     0,     2,     0,    13,     3,     0,     4,     0,     2,
       0,     3,     1,     1,     1,     3,     5,     4,     7,     5,
       7,     5,     5,     2,     0,     3,     0,     3,     0,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     3,     1,
       6,     4,     2,     0,     1,     1,     1,     1,     1,     5,
       4,     2,     3,     1,     1,     9,     9,     2,     0,     3,
       0
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 364 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		//concatList($$,$1);
		concatList((yyval.list),(yyvsp[-1].list));
		concatList((yyval.list),(yyvsp[0].list));
		printList((yyval.list));
		//printMacroList($$);
	}
#line 1712 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 375 "P1.y" /* yacc.c:1646  */
    {
		(yyval.mnode) = newMNode();
		addToGlobalList((yyvsp[-1].mnode));
	}
#line 1721 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 380 "P1.y" /* yacc.c:1646  */
    {
		(yyval.mnode) = newMNode();
	}
#line 1729 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 386 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-1].list));
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 1739 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 392 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
	}
#line 1747 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 399 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"class");//class
		concatString((yyval.list),(yyvsp[-19].c_str));//id
		concatChar((yyval.list),'{');//leftb
		concatString((yyval.list),"public");//public
		concatString((yyval.list),"static");//static
		concatString((yyval.list),"void");//void
		concatString((yyval.list),"main");//main
		concatChar((yyval.list),'(');
		concatString((yyval.list),"String");//string
		concatChar((yyval.list),'[');
		concatChar((yyval.list),']');
		concatString((yyval.list),(yyvsp[-9].c_str));//args
		concatChar((yyval.list),')');//)
		concatChar((yyval.list),'{');//{
		concatString((yyval.list),"System.out.println");//sop
		concatChar((yyval.list),'(');//(
		concatList((yyval.list),(yyvsp[-4].list));//exp
		concatChar((yyval.list),')');
		concatChar((yyval.list),';');
		concatChar((yyval.list),'}');
		concatChar((yyval.list),'}');
	}
#line 1776 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 426 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"class");//class
		concatString((yyval.list),(yyvsp[-4].c_str));//id
		concatChar((yyval.list),'{');//leftb
		concatList((yyval.list),(yyvsp[-2].list));//(t i;)*
		concatList((yyval.list),(yyvsp[-1].list));
		concatChar((yyval.list),'}');
	}
#line 1790 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 436 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"class");//class
		concatString((yyval.list),(yyvsp[-6].c_str));//id
		concatString((yyval.list),"extends");
		concatString((yyval.list),(yyvsp[-4].c_str));
		concatChar((yyval.list),'{');//leftb
		concatList((yyval.list),(yyvsp[-2].list));//(t i;)*
		concatList((yyval.list),(yyvsp[-1].list));
		concatChar((yyval.list),'}');
	}
#line 1806 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 450 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-3].list));
		concatList((yyval.list),(yyvsp[-2].list));
		concatString((yyval.list),(yyvsp[-1].c_str));//identifier
		concatChar((yyval.list),';');
	}
#line 1818 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 458 "P1.y" /* yacc.c:1646  */
    {
		//epsilon
		(yyval.list) = newList();
	}
#line 1827 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 465 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-1].list));
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 1837 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 471 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
	}
#line 1845 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 478 "P1.y" /* yacc.c:1646  */
    {
 		(yyval.list) = newList();
 		concatString((yyval.list),"public");
 		concatList((yyval.list),(yyvsp[-11].list));
 		concatString((yyval.list),(yyvsp[-10].c_str));
 		concatChar((yyval.list),'(');
 		concatList((yyval.list),(yyvsp[-8].list));
 		concatChar((yyval.list),')');
 		concatChar((yyval.list),'{');
 		concatList((yyval.list), (yyvsp[-5].list));
 		concatList((yyval.list),(yyvsp[-4].list));
 		concatString((yyval.list),"return");
 		concatList((yyval.list),(yyvsp[-2].list));
 		concatChar((yyval.list),';');
 		concatChar((yyval.list),'}');
 	}
#line 1866 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 497 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		concatString((yyval.list),(yyvsp[-1].c_str));
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 1877 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 504 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
	}
#line 1885 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 510 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-3].list));
		concatChar((yyval.list),',');
		concatList((yyval.list),(yyvsp[-1].list));
		concatString((yyval.list),(yyvsp[0].c_str));
	}
#line 1897 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 518 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
	}
#line 1905 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 524 "P1.y" /* yacc.c:1646  */
    { 
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-1].list));
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 1915 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 530 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
	}
#line 1923 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 536 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"int");
		concatChar((yyval.list),'[');
		concatChar((yyval.list),']');
	}
#line 1934 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 543 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"boolean");
	}
#line 1943 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 548 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"int");
	}
#line 1952 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 553 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),(yyvsp[0].c_str));
	}
#line 1961 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 560 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatChar((yyval.list), '{');
		concatList((yyval.list), (yyvsp[-1].list));
		concatChar((yyval.list),'}');
	}
#line 1972 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 567 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"System.out.println");
		concatChar((yyval.list),'(');
		concatList((yyval.list),(yyvsp[-2].list));
		concatChar((yyval.list),')');
		concatChar((yyval.list),';');
	}
#line 1985 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 576 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),(yyvsp[-3].c_str));
		concatChar((yyval.list),'=');
		concatList((yyval.list),(yyvsp[-1].list));
		concatChar((yyval.list),';');
	}
#line 1997 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 585 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),(yyvsp[-6].c_str));
		concatChar((yyval.list),'[');
		concatList((yyval.list),(yyvsp[-4].list));
		concatChar((yyval.list),']');
		concatChar((yyval.list),'=');
		concatList((yyval.list),(yyvsp[-1].list));
		concatChar((yyval.list),';');
	}
#line 2012 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 596 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"if");
		concatChar((yyval.list),'(');
		concatList((yyval.list),(yyvsp[-2].list));
		concatChar((yyval.list),')');
		concatList((yyval.list),(yyvsp[0].list));
		
	
	}
#line 2027 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 607 "P1.y" /* yacc.c:1646  */
    {	
		(yyval.list) = newList();
		concatString((yyval.list),"if");//if
		concatChar((yyval.list),'(');
		concatList((yyval.list),(yyvsp[-4].list));
		concatChar((yyval.list),')');
		concatList((yyval.list),(yyvsp[-2].list));//st
		concatString((yyval.list),"else");//else
		concatList((yyval.list),(yyvsp[0].list));
	
	}
#line 2043 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 619 "P1.y" /* yacc.c:1646  */
    {	
		(yyval.list) = newList();
		concatString((yyval.list),"while");
		concatChar((yyval.list),'(');
		concatList((yyval.list),(yyvsp[-2].list));
		concatChar((yyval.list),')');
		concatList((yyval.list),(yyvsp[0].list));	
	}
#line 2056 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 628 "P1.y" /* yacc.c:1646  */
    {
		
		(yyval.list) = newList();
		int arg_freq = 0;
		struct Node* ptr = NULL;
		ptr = (yyvsp[-2].list)->head;
		while(ptr!=NULL)
		{
			ptr = ptr->next;
			arg_freq++;
		}
		int isPresent = 0;
		
		isPresent = checkMacroList((yyvsp[-4].c_str));
		if(isPresent==0){
			yyerror();
		}else{
			(yyval.list) = substituteMacro((yyvsp[-4].c_str),(yyvsp[-2].list));
		}
	}
#line 2081 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 651 "P1.y" /* yacc.c:1646  */
    {
		//we dont need the comma in macroargument
		(yyval.list) = newList();
		//concat $1 into a string
		struct Node * huffman = NULL;
		huffman = getCompaction((yyvsp[-1].list));
		//printf("%s\n",huffman->str);
		struct List* huffmanlist = (struct List*)malloc(sizeof(struct List));
		
		huffmanlist->head = huffman;
		huffmanlist->tail = huffman;
		
		concatList((yyval.list),huffmanlist);
		concatList((yyval.list),(yyvsp[0].list));	
	
	}
#line 2102 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 668 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
	}
#line 2110 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 674 "P1.y" /* yacc.c:1646  */
    {
		//DEBUG=4;
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		
		struct Node* huffman = NULL;
		huffman = getCompaction((yyvsp[0].list));
		struct List* huffmanlist = (struct List*)malloc(sizeof(struct List));
		huffmanlist->head = huffman;
		huffmanlist->tail = huffman;
		concatList((yyval.list),huffmanlist);
	}
#line 2127 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 687 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
	}
#line 2135 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 693 "P1.y" /* yacc.c:1646  */
    {
		//not a macro expression
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		concatChar((yyval.list),',');
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2147 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 701 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
	}
#line 2155 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 707 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		concatString((yyval.list),"&&");
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2166 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 714 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		concatString((yyval.list),"||");
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2177 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 721 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		concatString((yyval.list),"!=");
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2188 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 728 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		concatString((yyval.list),"<=");
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2199 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 735 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		concatChar((yyval.list),'+');
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2210 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 742 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		concatChar((yyval.list),'-');
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2221 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 749 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		concatChar((yyval.list),'*');
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2232 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 756 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		concatChar((yyval.list),'/');
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2243 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 763 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-3].list));
		concatChar((yyval.list),'[');
		concatList((yyval.list),(yyvsp[-1].list));
		concatChar((yyval.list),']');
	}
#line 2255 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 771 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		concatChar((yyval.list),'.');
		concatString((yyval.list),"length");
	}
#line 2266 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 778 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2275 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 783 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-5].list));
		concatChar((yyval.list),'.');
		concatString((yyval.list),(yyvsp[-3].c_str));
		concatChar((yyval.list),'(');
		concatList((yyval.list),(yyvsp[-1].list));
		concatChar((yyval.list),')');
	}
#line 2289 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 793 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		int arg_freq = 0;
		struct Node* ptr = NULL;
		ptr = (yyvsp[-1].list)->head;
		while(ptr!=NULL)
		{
			ptr = ptr->next;
			arg_freq++;
		}
		int isPresent = 0;
		
		isPresent = checkMacroList((yyvsp[-3].c_str));
		if(!isPresent){
			yyerror();
		}else{
			(yyval.list) = substituteMacro((yyvsp[-3].c_str),(yyvsp[-1].list));
		}
	}
#line 2313 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 815 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-1].list));
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2323 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 821 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
	}
#line 2331 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 827 "P1.y" /* yacc.c:1646  */
    {
 		(yyval.list) = newList();
 		concatInt((yyval.list),(yyvsp[0].c_int));
 	}
#line 2340 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 832 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"true");
	}
#line 2349 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 837 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"false");
	}
#line 2358 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 842 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),(yyvsp[0].c_str));
	}
#line 2367 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 847 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"this");
	}
#line 2376 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 852 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"new");
		concatString((yyval.list),"int");
		concatChar((yyval.list),'[');
		concatList((yyval.list),(yyvsp[-1].list));
		concatChar((yyval.list),']');
	}
#line 2389 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 861 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatString((yyval.list),"new");
		concatString((yyval.list),(yyvsp[-2].c_str));
		concatChar((yyval.list),'(');
		concatChar((yyval.list),')');
		
	}
#line 2402 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 870 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatChar((yyval.list),'!');
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2412 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 876 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
		concatChar((yyval.list),'(');
		concatList((yyval.list),(yyvsp[-1].list));
		concatChar((yyval.list),')');
	}
#line 2423 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 885 "P1.y" /* yacc.c:1646  */
    {
		(yyval.mnode) = NULL;
		(yyval.mnode) = (yyvsp[0].mnode);
	}
#line 2432 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 890 "P1.y" /* yacc.c:1646  */
    {
		(yyval.mnode) = NULL;
		(yyval.mnode) = (yyvsp[0].mnode);//$1 is of type MacroNode*
	}
#line 2441 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 897 "P1.y" /* yacc.c:1646  */
    {
 		//this should return a MacroNode
		DEBUG=1;
 		(yyval.mnode) = newMNode();
 		sprintf((yyval.mnode)->name,"%s",(yyvsp[-6].c_str)) ;
 		concatList((yyval.mnode)->args,(yyvsp[-4].list));
 		concatChar((yyval.mnode)->substitute,'{');
 		concatList((yyval.mnode)->substitute,(yyvsp[-1].list));
 		concatChar((yyval.mnode)->substitute,'}');
 		struct Node* ptr = NULL;
 		ptr = (yyval.mnode)->args->head;
 		int cnt=0;
 		while(ptr!=NULL)
 		{
 			ptr = ptr->next;
 			cnt++;
 		}
 		(yyval.mnode)->n_args = cnt;
 		//DEBUG=0;
 	}
#line 2466 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 920 "P1.y" /* yacc.c:1646  */
    {
 		DEBUG=2;
 		//This should return a MacroNode
 		(yyval.mnode) = newMNode();
 		sprintf((yyval.mnode)->name,"%s",(yyvsp[-6].c_str));
 		concatList((yyval.mnode)->args, (yyvsp[-4].list));
 		concatChar((yyval.mnode)->substitute,'(');
 		concatList((yyval.mnode)->substitute,(yyvsp[-1].list));
 		concatChar((yyval.mnode)->substitute,')');
 		struct Node* ptr = NULL;
 		
 		/*
 		ptr = $$->args->head;
 		int cnt=0;
 		while(ptr!=NULL)
 		{
 			ptr = ptr->next;
 			cnt++;
 		}
 		
 		$$->n_args = cnt;
 		*/
 		//printNodeDetails();
 		//DEBUG=0;
 	}
#line 2496 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 948 "P1.y" /* yacc.c:1646  */
    {
		//ignore the Comma
		(yyval.list) = newList();
		concatString((yyval.list),(yyvsp[-1].c_str));
		concatList((yyval.list),(yyvsp[0].list));
	}
#line 2507 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 955 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
	}
#line 2515 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 961 "P1.y" /* yacc.c:1646  */
    {
		//we dont need the comma for the argument list
		(yyval.list) = newList();
		concatList((yyval.list),(yyvsp[-2].list));
		//concatChar($$,',');
		concatString((yyval.list),(yyvsp[0].c_str));
	}
#line 2527 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 969 "P1.y" /* yacc.c:1646  */
    {
		(yyval.list) = newList();
	}
#line 2535 "P1.tab.c" /* yacc.c:1646  */
    break;


#line 2539 "P1.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 973 "P1.y" /* yacc.c:1906  */


int yyerror()
{
	printf ("// Failed to parse macrojava code.");
	return 0;  
}

int main ()
{
	GMList = NULL;
	yyparse();
	return 0;
}
