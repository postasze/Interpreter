#ifndef FUNCTION_H
#define FUNCTION_H

#include "header.h"

class TypeDescriptor;
class Variable;
class BlockStatement;

class Function
{
    public:
        Function(TypeDescriptor *typeDescriptorPointer, string identifierName,
            vector<Variable*>* argumentList, BlockStatement *blockStatement);
        virtual ~Function();

        TypeDescriptor *typeDescriptorPointer;
        string identifierName;
        vector<Variable*>* argumentList;
        BlockStatement *blockStatement;
    protected:

    private:
};

#endif // FUNCTION_H
