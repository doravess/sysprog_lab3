#include "driver.h"
#include "parser.hpp"
#include "lexer.hpp"
#include <fstream>
#include <iostream>

namespace calc {

    bool Driver::parseFile(const std::string &filename) {
        std::ifstream f(filename);
        if(!f){ std::cerr << "Cannot open " << filename << std::endl; return false; }
        Lexer scanner(&f);
        Parser parser(scanner, *this);
        return parser.parse() == 0;
    }

    void Driver::setVar(const std::string &name, double val) {
        symtab[name] = val;
    }

    bool Driver::hasVar(const std::string &name) const {
        return symtab.find(name) != symtab.end();
    }

    double Driver::getVar(const std::string &name) const {
        auto it = symtab.find(name);
        if(it == symtab.end()) throw std::runtime_error("Undefined variable: " + name);
        return it->second;
    }

}
