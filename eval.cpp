#include "ast.h"
#include "driver.h"
#include <cmath>
#include <stdexcept>

namespace calc {

    double eval_ast(const AST* node, Driver &drv){
        if(!node) throw std::runtime_error("null node");
        switch(node->type){
            case AST::NUM: return node->value;
            case AST::ID:  return drv.getVar(*node->id);
            case AST::UNOP:
                if(node->op == '-') return -eval_ast(node->left.get(), drv);
                throw std::runtime_error("unknown unop");
            case AST::BINOP: {
                double l = eval_ast(node->left.get(), drv);
                double r = eval_ast(node->right.get(), drv);
                switch(node->op){
                    case '+': return l + r;
                    case '-': return l - r;
                    case '*': return l * r;
                    case '/': return l / r;
                    case '^': return pow(l, r);
                }
                throw std::runtime_error("unknown binop");
            }
        }
        return 0;
    }

}
