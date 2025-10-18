%language "c++"
%define api.value.type {std::shared_ptr<AST>}
%define api.namespace {calc}
%define parse.error verbose
%define api.parser.class {Parser}

%code requires {
#include "ast.h"
#include "driver.h"
#include <memory>
#include <string>
namespace calc { class Lexer; }
}

%code {
#include "lexer.hpp"
using namespace calc;
}

%token <std::shared_ptr<AST>> NUMBER IDENTIFIER
%token PRINT
%left '+' '-'
%left '*' '/'
%right '^'
%right UMINUS
%type <std::shared_ptr<AST>> stmt expr term factor

%%

program:
    | program stmt
    ;

stmt:
      expr ';'              { driver.root = $1; double val = eval_ast(driver.root.get(), driver); std::cout << val << "\\n"; }
    | IDENTIFIER '=' expr ';' { double v = eval_ast($3.get(), driver); driver.setVar(*$1->id, v); }
    | PRINT '(' expr ')' ';' { double v = eval_ast($3.get(), driver); std::cout << "print: " << v << "\\n"; }
    ;

expr:
      term
    | expr '+' term { $$ = make_binop('+', $1, $3); }
    | expr '-' term { $$ = make_binop('-', $1, $3); }
    ;

term:
      factor
    | term '*' factor { $$ = make_binop('*', $1, $3); }
    | term '/' factor { $$ = make_binop('/', $1, $3); }
    ;

factor:
      NUMBER
    | IDENTIFIER { $$ = make_id(*$1->id); }
    | '(' expr ')' { $$ = $2; }
    | '-' factor %prec UMINUS { $$ = make_unop('-', $2); }
    ;

%%
