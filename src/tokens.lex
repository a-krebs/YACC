%{
/
********************************************************************************
                       Lexical Entites for YACC-PAL
                        
                        
********************************************************************************

%}

%%
[\t]                            { ; }
"//"[^\n]*                      { ; }
^[a-zA-Z][a-zA-Z0-9]*$          { yylval.id = strdup(yytext);
                                  return(ID); }
^[-+]?[0-9]*\.?[0-9]+([E][-+]?[0-9]+)?$
                                { yylval.real = strdup(yytext); 
                                  return(REAL); }
"'"[^'\\]*(?:\\.[^'\\]*)*"'"    { yylval.string = strdup(yytext);
                                  return(STRING); }
":="                            { return(ASSIGN); }
"and"                           { return(AND); }
"continue"                      { return(CONTINUE); }
"end"                           { return(END); }
"mod"                           { return(MOD); }
"procedure"                     { return(PROCEDURE); }
"type"                          { return(TYPE); }
"array"                         { return(ARRAY); }
"div"                           { return(DIV); }
"exit"                          { return(EXIT); }
"not"                           { return(NOT); }
"program"                       { return(PROGRAM); }
"var"                           { return(VAR); }
"begin"                         { return(BEGIN); }
"do"                            { return(DO);}
"function"                      { return(FUNCTION); }
"of"                            { return(OF); }
"record"                        { return(RECORD); }
"while"                         { return(WHILE); }
"const"                         { return(CONST); }
"else"                          { return(ELSE); }
"if"                            { return(IF); }
"or"                            { return(OR); }
"then"                          { return(THEN); }
"="                             { return(EQUAL); }
"<>"                            { return(NOT_EQUAL); }
"<"                             { return(LESS); }
"<="                            { return(LESS_AND_EQUAL); }
">="                            { return(GREATER_AND_EQUAL); }
">"                             { return(GREATER); }
"+"                             { return(PLUS); }
"-"                             { return(MINUS); }
"*"                             { return(MULTIPLY); }
"/"                             { return(DIVIDE); }
"("                             { return(L_PAREN); } 
")"                             { return(R_PAREN); }
"."                             { return(PERIOD); }
";"                             { return(SEMICOLON); }
":"                             { return(COLON); }
"["                             { return(LS_BRACKET; }
"]"                             { return(RS_BRACKET; }
","                             { return(COMMA); }



