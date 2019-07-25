#include "Value.h"

Value::Value()
{
    intValue = 0;
    boolValue = false;
    matrixValue = new vector<int>();
}

Value::Value(const Value& value)
{
    this->intValue = value.intValue;
    this->boolValue = value.boolValue;
    if(value.matrixValue != nullptr)
        matrixValue = new vector<int>(*value.matrixValue);
    else
        this->matrixValue = nullptr;
}

Value::~Value()
{
    matrixValue->clear();
    delete matrixValue;
}

int Value::GetIntValue()
{
    return intValue;
}

void Value::SetIntValue(int val)
{
    intValue = val;
}

bool Value::GetBoolValue()
{
    return boolValue;
}

void Value::SetBoolValue(bool val)
{
    this->boolValue = val;
}

vector<int>* Value::GetMatrixValue()
{
    return matrixValue;
}

void Value::SetMatrixValue(vector<int>* val)
{
    *matrixValue = *val; // kopiowanie zawartosci jednego wektora do drugiego i usuwanie istniejacej zawartosci pierwszego wektora
}
