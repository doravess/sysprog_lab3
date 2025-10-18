#include "ast.h"
#include <sstream>
#include <string>

using namespace calc;

static void gen_expr(const AST* n, std::ostringstream &out){
    if(!n) return;
    switch(n->type){
        case AST::NUM: out << n->value; break;
        case AST::ID: out << *n->id; break;
        case AST::UNOP: out << "(" << n->op; gen_expr(n->left.get(), out); out << ")"; break;
        case AST::BINOP:
            out << "("; gen_expr(n->left.get(), out); out << " " << n->op << " "; gen_expr(n->right.get(), out); out << ")";
            break;
    }
}

std::string generate_c_function(const AST* root){
    std::ostringstream out;
    out << "#include <math.h>\\n";
    out << "double expr() { return ";
    gen_expr(root, out);
    out << "; }\\n";
    return out.str();
}
