%option c++
%option noyywrap
%option nounput
%option noinput

%{
#include "parser.hpp"
#include "ast.h"
#include <string>
using namespace calc;
%}

DIGIT [0-9]
ID [a-zA-Z_][a-zA-Z_0-9]*
NUMBER {DIGIT}+(\.{DIGIT}+)?

%%

[ \t\r]+   ;
\n          ;
"print"     return yy::Parser::token_type::PRINT;
{NUMBER}    { yylval = make_num(atof(yytext)); return yy::Parser::token_type::NUMBER; }
{ID}        { yylval = make_id(std::string(yytext)); return yy::Parser::token_type::IDENTIFIER; }

"(" return '(';
")" return ')';
"*" return '*';
"/" return '/';
"+" return '+';
"-" return '-';
"^" return '^';
"=" return '=';
";" return ';';

.   { std::cerr << "Unknown: " << yytext << std::endl; }

%%
