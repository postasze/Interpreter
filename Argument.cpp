#include "Argument.h"

Argument::Argument(TypeDescriptor *TypeDescriptorPointer, string identifierName)
{
    this->typeDescriptorPointer = TypeDescriptorPointer;
    this->identifierName = identifierName;
}

Argument::~Argument()
{
    //dtor
}
