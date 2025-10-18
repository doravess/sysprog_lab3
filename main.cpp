#include "driver.h"
#include "eval.cpp"
#include "gen.cpp"
#include <iostream>
#include <fstream>

using namespace calc;

int main(int argc, char** argv){
    if(argc < 2){ std::cerr<<"Usage: calc <file>\n"; return 1; }

    Driver drv;
    if(!drv.parseFile(argv[1])) return 2;

    std::ofstream("ast.json") << drv.root->to_json();
    std::ofstream("expr.c") << generate_c_function(drv.root.get());
    std::cout << "AST and C code generated.\n";
}
