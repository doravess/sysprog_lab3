#ifndef DRIVER_H
#define DRIVER_H

#include "ast.h"
#include <string>
#include <map>
#include <memory>

namespace calc {

    class Driver {
    public:
        std::map<std::string, double> symtab; // таблиця змінних
        std::shared_ptr<AST> root;

        bool parseFile(const std::string &filename);
        void setVar(const std::string &name, double val);
        bool hasVar(const std::string &name) const;
        double getVar(const std::string &name) const;
    };

}

#endif
