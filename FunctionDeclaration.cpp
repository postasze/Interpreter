#include "FunctionDeclaration.h"

FunctionDeclaration::FunctionDeclaration(TypeDescriptor *typeDescriptorPointer,
    Function *functionPointer)
{
    this->typeDescriptorPointer = typeDescriptorPointer;
    this->functionPointer = functionPointer;
}

FunctionDeclaration::~FunctionDeclaration()
{
    //dtor
}
