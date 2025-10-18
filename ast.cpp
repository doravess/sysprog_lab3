#include "ast.h"
#include <sstream>

using namespace calc;

AST::AST(double v) : type(NUM), value(v) {}
AST::AST(char op_, std::shared_ptr<AST> left_) : type(UNOP), op(op_), left(std::move(left_)) {}
AST::AST(char op_, std::shared_ptr<AST> left_, std::shared_ptr<AST> right_) : type(BINOP), op(op_), left(std::move(left_)), right(std::move(right_)) {}
AST::AST(const std::string &name) : type(ID), id(std::make_shared<std::string>(name)) {}

std::shared_ptr<AST> make_num(double v){ return std::make_shared<AST>(v); }
std::shared_ptr<AST> make_unop(char op, std::shared_ptr<AST> a){ return std::make_shared<AST>(op, std::move(a)); }
std::shared_ptr<AST> make_binop(char op, std::shared_ptr<AST> l, std::shared_ptr<AST> r){ return std::make_shared<AST>(op, std::move(l), std::move(r)); }
std::shared_ptr<AST> make_id(const std::string &name){ return std::make_shared<AST>(name); }

static void ast_to_json(const AST* n, std::ostringstream &out){
    if(!n){ out<<"null"; return; }
    out<<"{\"type\":\"";
    switch(n->type){
        case AST::NUM: out<<"num\",\"value\":"<<n->value; break;
        case AST::ID: out<<"id\",\"name\":\""<<*n->id<<"\""; break;
        case AST::UNOP:
            out<<"unop\",\"op\":\""<<n->op<<"\",\"child\":"; ast_to_json(n->left.get(), out); break;
        case AST::BINOP:
            out<<"binop\",\"op\":\""<<n->op<<"\",\"left\":"; ast_to_json(n->left.get(), out);
            out<<",\"right\":"; ast_to_json(n->right.get(), out); break;
    }
    out<<"}";
}

std::string AST::to_json() const {
    std::ostringstream out;
    ast_to_json(this, out);
    return out.str();
}
