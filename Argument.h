#ifndef ARGUMENT_H
#define ARGUMENT_H

#include "header.h"

class TypeDescriptor;

class Argument
{
    public:
        Argument(TypeDescriptor *TypeDescriptorPointer, string identifierName);
        virtual ~Argument();

    protected:

    private:
        TypeDescriptor *typeDescriptorPointer;
        string identifierName;
};

#endif // ARGUMENT_H
