#ifndef CONSTANT_H
#define CONSTANT_H

#include "header.h"

class TypeDescriptor;
class Value;

class Constant
{
    public:
        Constant();
        Constant(TypeDescriptor *typeDescriptorPointer, int intValue);
        Constant(TypeDescriptor *typeDescriptorPointer, vector<int> *matrixValue);
        Constant(const Constant& constant);
        virtual ~Constant();

        TypeDescriptor *typeDescriptorPointer;
        void setValue(Value* value);
        Value* getValue();
    protected:

    private:
        Value *value;
};

#endif // CONSTANT_H
