%token NUMBER
%token VARIABLE COMMAND UNARY_FUNCTION

%type <float_val> NUMBER 
%type <str_val> VARIABLE COMMAND UNARY_FUNCTION

%left '+' '-'
%left '*' '/'
%left '^'

%{
    #define YYSTYPE UniversalType
    #include "src/universal_type.h"
    #include "src/universal_type_math.h"
    #include "src/variable_manager.h"
    #include "src/function_executor.h"
    #include "src/command_executor.h"

    #include <iostream>
    #include "src/cui.h"

    using namespace std; 

    void yyerror(char *);
    int yylex(void);
%}

%%

program:
program statement '\n'
|
;

statement:
expr {
    CUI::print_result($1); 
}
| COMMAND { CommandExecutor::execute($1); }
| VARIABLE '=' expr { VAR_MANAGER[$1] = $3; CUI::newline(); }
| error '\n' { yyerrok; }
;

expr:
NUMBER
| VARIABLE { $$ = VAR_MANAGER[$1]; }
/* Binary operators */
| expr '+' expr { $$ = $1 + $3; }
| expr '-' expr { $$ = $1 - $3; }
| expr '*' expr { $$ = $1 * $3; }
| expr '/' expr { $$ = $1 / $3; }
| expr '^' expr { $$ = ($1).pow($3); }
/* Unary operators */
| '-' expr { $$ = - $2; }
| '+' expr { $$ = $2; }
| '(' expr ')' { $$ = $2; }
/* Functions  */
| UNARY_FUNCTION '(' expr ')' { $$ = FunctionExecutor::execute_unary($1, $3); }
;


%%

void yyerror(char *s) {
    CUI::show_error(s);
    CUI::newline();
}
int main(void) {
    CUI::setup();
    CUI::print_welcome_message();
    yyparse();
    return 0;
}