#ifndef VARIABLE_H
#define VARIABLE_H

#include "header.h"

class TypeDescriptor;
class Value;

class Variable
{
    public:
        Variable(TypeDescriptor *typeDescriptorPointer, string identifierName);
        Variable(const Variable& variable);
        virtual ~Variable();

        TypeDescriptor *typeDescriptorPointer;
        string identifierName;
        void setValue(Value* value);
        Value* getValue();

    protected:

    private:
        Value *value;
};

#endif // VARIABLE_H
