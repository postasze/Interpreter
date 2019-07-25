#include "Constant.h"
#include "Value.h"

Constant::Constant()
{
    //ctor
}

Constant::Constant(TypeDescriptor *typeDescriptorPointer, int intValue)
{
    this->typeDescriptorPointer = typeDescriptorPointer;
    this->value = new Value();
    this->value->SetIntValue(intValue);
}

Constant::Constant(TypeDescriptor *typeDescriptorPointer, vector<int> *matrixValue)
{
    this->typeDescriptorPointer = typeDescriptorPointer;
    this->value = new Value();
    this->value->SetMatrixValue(matrixValue);
    matrixValue->clear();
    delete matrixValue;
}

Constant::Constant(const Constant& constant)
{
    this->typeDescriptorPointer = constant.typeDescriptorPointer;
    this->value = new Value(*constant.value);
}

Constant::~Constant()
{
    if(this->value != nullptr)
        delete this->value;
}

void Constant::setValue(Value* value)
{
    if(this->value == nullptr)
        this->value = new Value();

    this->value->SetBoolValue(value->GetBoolValue());
    this->value->SetIntValue(value->GetIntValue());
    this->value->SetMatrixValue(value->GetMatrixValue());
}

Value* Constant::getValue()
{
    return this->value;
}
