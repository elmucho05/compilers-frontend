#ifndef PROTOTYPE_AST_HPP
#define PROTOTYPE_AST_HPP

#include "RootAST.hpp"

class PrototypeAST : public RootAST
{
private:
    std::string Name;
    std::vector<std::string> Args;
    bool emit;

public:
    PrototypeAST(std::string Name, std::vector<std::string> Args);
    const std::string &getName() const;
    const std::vector<std::string> &getArgs() const;
    void visit() override;
    Function *codegen(driver &drv) override;
    void noemit();
    bool emitp();
};

#endif 