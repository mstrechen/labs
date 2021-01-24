%{
#define YYSTYPE UniversalType

#include <stdlib.h>
#include <iostream>
#include "src/universal_type.h"

void yyerror(char *);

#include "y.tab.h"

%}

%%

@[a-zA-Z0-9]+ {
    yylval = string(yytext + 1);
    return VARIABLE;
}
[A-Z]+ {
    yylval = string(yytext);
    return COMMAND;
}

[a-z]+ {
    yylval = string(yytext);
    return UNARY_FUNCTION;
}

[0-9]+(\.[0-9]+)? {
    yylval = UniversalType(FLOAT_TYPE(atof(yytext)));
    return NUMBER;
}

[-+()=/*^\n] {
    return *yytext; 
}

[ \t] ;

. yyerror("invalid character");

%%
int yywrap(void) {
    return 1;
}