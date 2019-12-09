%{
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
	
	
%}

%union
{
	int c_int;
	char* c_str;
	char c_char;
	struct List* list;	
	struct MacroNode* mnode;
}

//Tokens
%token <c_str> CLASS PUBLIC STATIC VOID EXTENDS RETURN INT STRING
%token <c_str> BOOLEAN IF ELSE WHILE TRUEVAL FALSEVAL
%token <c_str> THIS NEW MAIN SYSTEMOUTPRINTLN DEFINE LENGTH

%token <c_char> LEFTC RIGHTC LEFTB RIGHTB LEFTSQ RIGHTSQ DOT HASH SEMICOLON COMMA

%token <c_char> EQUAL AND OR NOT PLUS MINUS MULT DIV LESS

%token <c_int> Integer
%token <c_str> Identifier ANDAND OROR NOTEQUAL LESSEQUAL

//Non terminals
%start Goal;

%type <list> Goal TypeDeclarationStar MainClass TypeDeclaration
%type <list> Type_Identifier_SemicolonStar MethodDeclarationStar MethodDeclaration
%type <list> MethodArgument Comma_Type_IdentifierStar StatementStar Type Statement
%type <list> MacroArgument Comma_ExpressionStar Comma_ExpressionStar1 Expression ExpressionArgument
%type <list> PrimaryExpression IdentifierArgument Comma_IdentifierStar
 
%type <mnode> MacroDefinitionStar MacroDefinition MacroDefStatement MacroDefExpression

%%	
Goal : 
	MacroDefinitionStar MainClass TypeDeclarationStar
	{
		$$ = newList();
		//concatList($$,$1);
		concatList($$,$2);
		concatList($$,$3);
		printList($$);
		//printMacroList($$);
	};

MacroDefinitionStar : 
	MacroDefinition MacroDefinitionStar
	{
		$$ = newMNode();
		addToGlobalList($1);
	}
	|//epsilon
	{
		$$ = newMNode();
	}; 
					 
TypeDeclarationStar :
	TypeDeclarationStar TypeDeclaration 
	{
		$$ = newList();
		concatList($$,$1);
		concatList($$,$2);
	}
	|
	{
		$$ = newList();
	};
	
MainClass : 
	CLASS Identifier LEFTB PUBLIC STATIC VOID MAIN LEFTC STRING LEFTSQ RIGHTSQ Identifier 
	RIGHTC LEFTB SYSTEMOUTPRINTLN LEFTC Expression RIGHTC SEMICOLON RIGHTB RIGHTB
	{
		$$ = newList();
		concatString($$,"class");//class
		concatString($$,$2);//id
		concatChar($$,'{');//leftb
		concatString($$,"public");//public
		concatString($$,"static");//static
		concatString($$,"void");//void
		concatString($$,"main");//main
		concatChar($$,'(');
		concatString($$,"String");//string
		concatChar($$,'[');
		concatChar($$,']');
		concatString($$,$12);//args
		concatChar($$,')');//)
		concatChar($$,'{');//{
		concatString($$,"System.out.println");//sop
		concatChar($$,'(');//(
		concatList($$,$17);//exp
		concatChar($$,')');
		concatChar($$,';');
		concatChar($$,'}');
		concatChar($$,'}');
	};

TypeDeclaration : 	
	CLASS Identifier LEFTB Type_Identifier_SemicolonStar MethodDeclarationStar RIGHTB
	{
		$$ = newList();
		concatString($$,"class");//class
		concatString($$,$2);//id
		concatChar($$,'{');//leftb
		concatList($$,$4);//(t i;)*
		concatList($$,$5);
		concatChar($$,'}');
	}
	|CLASS Identifier EXTENDS Identifier LEFTB Type_Identifier_SemicolonStar MethodDeclarationStar RIGHTB
	{
		$$ = newList();
		concatString($$,"class");//class
		concatString($$,$2);//id
		concatString($$,"extends");
		concatString($$,$4);
		concatChar($$,'{');//leftb
		concatList($$,$6);//(t i;)*
		concatList($$,$7);
		concatChar($$,'}');
	};

Type_Identifier_SemicolonStar:
	Type_Identifier_SemicolonStar Type Identifier SEMICOLON
	{
		$$ = newList();
		concatList($$,$1);
		concatList($$,$2);
		concatString($$,$3);//identifier
		concatChar($$,';');
	}
	|
	{
		//epsilon
		$$ = newList();
	};

MethodDeclarationStar:
	MethodDeclarationStar MethodDeclaration
	{
		$$ = newList();
		concatList($$,$1);
		concatList($$,$2);
	}
	|
	{
		$$ = newList();
	};
	
MethodDeclaration :
 	PUBLIC Type Identifier LEFTC MethodArgument RIGHTC LEFTB Type_Identifier_SemicolonStar StatementStar 
 	RETURN Expression SEMICOLON RIGHTB
 	{
 		$$ = newList();
 		concatString($$,"public");
 		concatList($$,$2);
 		concatString($$,$3);
 		concatChar($$,'(');
 		concatList($$,$5);
 		concatChar($$,')');
 		concatChar($$,'{');
 		concatList($$, $8);
 		concatList($$,$9);
 		concatString($$,"return");
 		concatList($$,$11);
 		concatChar($$,';');
 		concatChar($$,'}');
 	};

MethodArgument: 
	Type Identifier Comma_Type_IdentifierStar
	{
		$$ = newList();
		concatList($$,$1);
		concatString($$,$2);
		concatList($$,$3);
	}
	|
	{
		$$ = newList();
	};

Comma_Type_IdentifierStar:
	Comma_Type_IdentifierStar COMMA Type Identifier
	{
		$$ = newList();
		concatList($$,$1);
		concatChar($$,',');
		concatList($$,$3);
		concatString($$,$4);
	}
	|
	{
		$$ = newList();
	};
	
StatementStar:
	Statement StatementStar
	{ 
		$$ = newList();
		concatList($$,$1);
		concatList($$,$2);
	}
	|
	{
		$$ = newList();
	};
	
Type : 	
	INT LEFTSQ RIGHTSQ
	{
		$$ = newList();
		concatString($$,"int");
		concatChar($$,'[');
		concatChar($$,']');
	}
	|BOOLEAN
	{
		$$ = newList();
		concatString($$,"boolean");
	}
	|INT
	{
		$$ = newList();
		concatString($$,"int");
	}
	|Identifier
	{
		$$ = newList();
		concatString($$,$1);
	};
	
Statement : 	
	LEFTB StatementStar RIGHTB
	{
		$$ = newList();
		concatChar($$, '{');
		concatList($$, $2);
		concatChar($$,'}');
	}
	|SYSTEMOUTPRINTLN LEFTC Expression RIGHTC SEMICOLON
	{
		$$ = newList();
		concatString($$,"System.out.println");
		concatChar($$,'(');
		concatList($$,$3);
		concatChar($$,')');
		concatChar($$,';');
	}
	|Identifier EQUAL Expression SEMICOLON
	{
		$$ = newList();
		concatString($$,$1);
		concatChar($$,'=');
		concatList($$,$3);
		concatChar($$,';');
	}
	
	|Identifier LEFTSQ Expression RIGHTSQ EQUAL Expression SEMICOLON
	{
		$$ = newList();
		concatString($$,$1);
		concatChar($$,'[');
		concatList($$,$3);
		concatChar($$,']');
		concatChar($$,'=');
		concatList($$,$6);
		concatChar($$,';');
	}
	|IF LEFTC Expression RIGHTC Statement
	{
		$$ = newList();
		concatString($$,"if");
		concatChar($$,'(');
		concatList($$,$3);
		concatChar($$,')');
		concatList($$,$5);
		
	
	}
	|IF LEFTC Expression RIGHTC Statement ELSE Statement
	{	
		$$ = newList();
		concatString($$,"if");//if
		concatChar($$,'(');
		concatList($$,$3);
		concatChar($$,')');
		concatList($$,$5);//st
		concatString($$,"else");//else
		concatList($$,$7);
	
	}
	|WHILE LEFTC Expression RIGHTC Statement
	{	
		$$ = newList();
		concatString($$,"while");
		concatChar($$,'(');
		concatList($$,$3);
		concatChar($$,')');
		concatList($$,$5);	
	}
	|Identifier LEFTC MacroArgument RIGHTC SEMICOLON
	{
		
		$$ = newList();
		int arg_freq = 0;
		struct Node* ptr = NULL;
		ptr = $3->head;
		while(ptr!=NULL)
		{
			ptr = ptr->next;
			arg_freq++;
		}
		int isPresent = 0;
		
		isPresent = checkMacroList($1);
		if(isPresent==0){
			yyerror();
		}else{
			$$ = substituteMacro($1,$3);
		}
	};

MacroArgument: 
	Expression Comma_ExpressionStar
	{
		//we dont need the comma in macroargument
		$$ = newList();
		//concat $1 into a string
		struct Node * huffman = NULL;
		huffman = getCompaction($1);
		//printf("%s\n",huffman->str);
		struct List* huffmanlist = (struct List*)malloc(sizeof(struct List));
		
		huffmanlist->head = huffman;
		huffmanlist->tail = huffman;
		
		concatList($$,huffmanlist);
		concatList($$,$2);	
	
	}	
	|
	{
		$$ = newList();
	};

Comma_ExpressionStar:
	Comma_ExpressionStar COMMA Expression
	{
		//DEBUG=4;
		$$ = newList();
		concatList($$,$1);
		
		struct Node* huffman = NULL;
		huffman = getCompaction($3);
		struct List* huffmanlist = (struct List*)malloc(sizeof(struct List));
		huffmanlist->head = huffman;
		huffmanlist->tail = huffman;
		concatList($$,huffmanlist);
	}
	|
	{
		$$ = newList();
	};

Comma_ExpressionStar1:
	Comma_ExpressionStar1 COMMA Expression
	{
		//not a macro expression
		$$ = newList();
		concatList($$,$1);
		concatChar($$,',');
		concatList($$,$3);
	}
	|
	{
		$$ = newList();
	};

Expression : 	
	PrimaryExpression ANDAND PrimaryExpression
	{
		$$ = newList();
		concatList($$,$1);
		concatString($$,"&&");
		concatList($$,$3);
	}
	|PrimaryExpression OROR PrimaryExpression
	{
		$$ = newList();
		concatList($$,$1);
		concatString($$,"||");
		concatList($$,$3);
	}
	|PrimaryExpression NOTEQUAL PrimaryExpression
	{
		$$ = newList();
		concatList($$,$1);
		concatString($$,"!=");
		concatList($$,$3);
	}
	|PrimaryExpression LESSEQUAL PrimaryExpression
	{
		$$ = newList();
		concatList($$,$1);
		concatString($$,"<=");
		concatList($$,$3);
	}
	|PrimaryExpression PLUS PrimaryExpression
	{
		$$ = newList();
		concatList($$,$1);
		concatChar($$,'+');
		concatList($$,$3);
	}
	|PrimaryExpression MINUS PrimaryExpression
	{
		$$ = newList();
		concatList($$,$1);
		concatChar($$,'-');
		concatList($$,$3);
	}
	|PrimaryExpression MULT PrimaryExpression
	{
		$$ = newList();
		concatList($$,$1);
		concatChar($$,'*');
		concatList($$,$3);
	}
	|PrimaryExpression DIV PrimaryExpression
	{
		$$ = newList();
		concatList($$,$1);
		concatChar($$,'/');
		concatList($$,$3);
	}
	|PrimaryExpression LEFTSQ PrimaryExpression RIGHTSQ
	{
		$$ = newList();
		concatList($$,$1);
		concatChar($$,'[');
		concatList($$,$3);
		concatChar($$,']');
	}
	|PrimaryExpression DOT LENGTH
	{
		$$ = newList();
		concatList($$,$1);
		concatChar($$,'.');
		concatString($$,"length");
	}
	|PrimaryExpression
	{
		$$ = newList();
		concatList($$,$1);
	}
	|PrimaryExpression DOT Identifier LEFTC ExpressionArgument RIGHTC
	{
		$$ = newList();
		concatList($$,$1);
		concatChar($$,'.');
		concatString($$,$3);
		concatChar($$,'(');
		concatList($$,$5);
		concatChar($$,')');
	}
	|Identifier LEFTC MacroArgument RIGHTC
	{
		$$ = newList();
		int arg_freq = 0;
		struct Node* ptr = NULL;
		ptr = $3->head;
		while(ptr!=NULL)
		{
			ptr = ptr->next;
			arg_freq++;
		}
		int isPresent = 0;
		
		isPresent = checkMacroList($1);
		if(!isPresent){
			yyerror();
		}else{
			$$ = substituteMacro($1,$3);
		}
	};

ExpressionArgument :
	Expression Comma_ExpressionStar1
	{
		$$ = newList();
		concatList($$,$1);
		concatList($$,$2);
	}
	|
	{
		$$ = newList();
	};
	
PrimaryExpression :
 	Integer
 	{
 		$$ = newList();
 		concatInt($$,$1);
 	}
	|TRUEVAL
	{
		$$ = newList();
		concatString($$,"true");
	}
	|FALSEVAL
	{
		$$ = newList();
		concatString($$,"false");
	}
	|Identifier
	{
		$$ = newList();
		concatString($$,$1);
	}
	|THIS
	{
		$$ = newList();
		concatString($$,"this");
	}
	|NEW INT LEFTSQ Expression RIGHTSQ
	{
		$$ = newList();
		concatString($$,"new");
		concatString($$,"int");
		concatChar($$,'[');
		concatList($$,$4);
		concatChar($$,']');
	}
	|NEW Identifier LEFTC RIGHTC
	{
		$$ = newList();
		concatString($$,"new");
		concatString($$,$2);
		concatChar($$,'(');
		concatChar($$,')');
		
	}
	|NOT Expression
	{
		$$ = newList();
		concatChar($$,'!');
		concatList($$,$2);
	}
	|LEFTC Expression RIGHTC
	{
		$$ = newList();
		concatChar($$,'(');
		concatList($$,$2);
		concatChar($$,')');
	};
	
MacroDefinition : 	
	MacroDefExpression
	{
		$$ = NULL;
		$$ = $1;
	}
	|MacroDefStatement
	{
		$$ = NULL;
		$$ = $1;//$1 is of type MacroNode*
	};
	
MacroDefStatement :
 	HASH DEFINE Identifier LEFTC IdentifierArgument RIGHTC LEFTB  StatementStar RIGHTB
 	{
 		//this should return a MacroNode
		DEBUG=1;
 		$$ = newMNode();
 		sprintf($$->name,"%s",$3) ;
 		concatList($$->args,$5);
 		concatChar($$->substitute,'{');
 		concatList($$->substitute,$8);
 		concatChar($$->substitute,'}');
 		struct Node* ptr = NULL;
 		ptr = $$->args->head;
 		int cnt=0;
 		while(ptr!=NULL)
 		{
 			ptr = ptr->next;
 			cnt++;
 		}
 		$$->n_args = cnt;
 		//DEBUG=0;
 	};

MacroDefExpression : 	
	HASH DEFINE Identifier LEFTC IdentifierArgument RIGHTC LEFTC Expression RIGHTC
 	{
 		DEBUG=2;
 		//This should return a MacroNode
 		$$ = newMNode();
 		sprintf($$->name,"%s",$3);
 		concatList($$->args, $5);
 		concatChar($$->substitute,'(');
 		concatList($$->substitute,$8);
 		concatChar($$->substitute,')');
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
 	};

IdentifierArgument:
	Identifier Comma_IdentifierStar
	{
		//ignore the Comma
		$$ = newList();
		concatString($$,$1);
		concatList($$,$2);
	}
	|
	{
		$$ = newList();
	};

Comma_IdentifierStar:
	Comma_IdentifierStar COMMA Identifier
	{
		//we dont need the comma for the argument list
		$$ = newList();
		concatList($$,$1);
		//concatChar($$,',');
		concatString($$,$3);
	}
	|
	{
		$$ = newList();
	};
	
%%

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
