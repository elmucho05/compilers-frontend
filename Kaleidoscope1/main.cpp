#include <iostream>
#include "tokens.h"
/* Forward declarations */
extern std::string IdentifierStr; // Filled in if tok_identifier
extern double NumVal;             // Filled in if tok_number
int gettok();

int main(int argc, char **argv) {
    int t = gettok();
    while (t != tok_eof) {
        switch (t) {
            case tok_identifier:
                std::cout << "Ide: " + IdentifierStr << std::endl; break;
            case tok_number:
                std::cout << "Num: " << NumVal << std::endl; break;
            case tok_def:
                std::cout << "Keyword: def" << std::endl; break;
            case tok_extern:
                std::cout << "Keyword: extern" << std::endl; break;
            default: 
                 std::cout << char(t) << std::endl; break;           
        }
        t = gettok();
    }
}