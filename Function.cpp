#include "Function.h"

Function::Function(TypeDescriptor *typeDescriptorPointer,
    string identifierName, vector<Variable*>* argumentList, BlockStatement *blockStatement)
{
    this->typeDescriptorPointer = typeDescriptorPointer;
    this->identifierName = identifierName;
    this->argumentList = argumentList;
    this->blockStatement = blockStatement;
}

Function::~Function()
{
    //dtor
}
