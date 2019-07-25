#include "Variable.h"
#include "Value.h"

Variable::Variable(TypeDescriptor *typeDescriptorPointer, string identifierName)
{
    this->typeDescriptorPointer = typeDescriptorPointer;
    this->identifierName = identifierName;
    this->value = nullptr;
}

Variable::Variable(const Variable& variable)
{
    this->typeDescriptorPointer = variable.typeDescriptorPointer;
    this->identifierName = variable.identifierName;
    if(variable.value != nullptr)
        this->value = new Value(*variable.value);
    else
        this->value = nullptr;
}

Variable::~Variable()
{
    if(this->value != nullptr)
        delete this->value;
}

void Variable::setValue(Value* value)
{
    if(this->value == nullptr)
        this->value = new Value();

    this->value->SetBoolValue(value->GetBoolValue());
    this->value->SetIntValue(value->GetIntValue());
    this->value->SetMatrixValue(value->GetMatrixValue());
}

Value* Variable::getValue()
{
    return this->value;
}
