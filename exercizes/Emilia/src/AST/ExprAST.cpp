#include "ExprAST.hpp"

void ExprAST::toggle()
{
    top = top ? false : true;
};

void ExprAST::setIsSize()
{
    isSize = true;
};

bool ExprAST::getIsSize()
{
    return isSize;
};

bool ExprAST::gettop()
{
    return top;
};