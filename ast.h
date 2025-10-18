#ifndef AST_H
#define AST_H

#include <string>
#include <memory>
#include <sstream>

namespace calc {

    struct AST {
        enum Type { NUM, ID, BINOP, UNOP } type;
        double value = 0;
        char op = 0;
        std::shared_ptr<AST> left, right;
        std::shared_ptr<std::string> id;

        AST(double v);
        AST(char op, std::shared_ptr<AST> left);
        AST(char op, std::shared_ptr<AST> left, std::shared_ptr<AST> right);
        AST(const std::string &name);

        std::string to_json() const;
    };

    std::shared_ptr<AST> make_num(double v);
    std::shared_ptr<AST> make_unop(char op, std::shared_ptr<AST> a);
    std::shared_ptr<AST> make_binop(char op, std::shared_ptr<AST> l, std::shared_ptr<AST> r);
    std::shared_ptr<AST> make_id(const std::string &name);

}

#endif
