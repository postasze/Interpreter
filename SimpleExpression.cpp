#include "SimpleExpression.h"
#include "Term.h"
#include "Interpreter.h"
#include "MatrixType.h"
#include "Value.h"

SimpleExpression::SimpleExpression(TypeDescriptor *typeDescriptorPointer, vector<Term*> *termList,
            vector<TokenType> *additiveOperatorList, bool isNegative)
{
    this->typeDescriptorPointer = typeDescriptorPointer;
    this->isNegative = isNegative;
    this->termList = termList;
    this->additiveOperatorList = additiveOperatorList;
    this->value = nullptr;
}

SimpleExpression::SimpleExpression(const SimpleExpression& simpleExpression)
{
    this->typeDescriptorPointer = simpleExpression.typeDescriptorPointer;
    this->isNegative = simpleExpression.isNegative;
    this->value = nullptr;

    if(simpleExpression.termList != nullptr)
    {
        this->termList = new vector<Term*>();

        for(unsigned int i = 0; i < simpleExpression.termList->size(); i++)
            this->termList->push_back(new Term(*simpleExpression.termList->at(i)));
    }
    else
        this->termList = nullptr;

    this->additiveOperatorList = new vector<TokenType>(*simpleExpression.additiveOperatorList);
}


SimpleExpression::~SimpleExpression()
{
    if(this->value != nullptr)
        delete this->value;
    if(termList != nullptr)
    {
        termList->clear();
        delete termList;
    }
    if(additiveOperatorList != nullptr)
    {
        additiveOperatorList->clear();
        delete additiveOperatorList;
    }
}

Value* SimpleExpression::evaluate(Interpreter& interpreter)
{
    Value *nextValue;

    if(this->value != nullptr)
        delete this->value;

    this->value = new Value(*termList->at(0)->evaluate(interpreter));
    this->typeDescriptorPointer = termList->at(0)->typeDescriptorPointer;

    if(isNegative)
    {
        if(this->typeDescriptorPointer == interpreter.integerType)
            value->SetIntValue((-1) * value->GetIntValue());
        else
        {
            vector<int> *matrixValue = this->value->GetMatrixValue();
            MatrixType *matrixType = (MatrixType*) this->typeDescriptorPointer;

            for(int i = 0; i < matrixType->firstRange; i++)
                for(int j = 0; j < matrixType->secondRange; j++)
                    matrixValue->at(i*matrixType->firstRange+j) *= (-1);
        }
    }

    for(unsigned int i = 1; i < termList->size(); i++)
    {
        nextValue = termList->at(i)->evaluate(interpreter);

        if(!((Compatible(this->typeDescriptorPointer, interpreter.integerType) &&
              Compatible(termList->at(i)->typeDescriptorPointer, interpreter.integerType)) ||
              Compatible(this->typeDescriptorPointer, termList->at(i)->typeDescriptorPointer))) // drugi przypadek dla macierzy
            interpreter.SemanticError(IncompatibleTypesForOperands, true);

        if(termList->at(0)->typeDescriptorPointer == interpreter.integerType)
        {
            if(additiveOperatorList->at(i-1) == Plus)
                value->SetIntValue(value->GetIntValue() + nextValue->GetIntValue());
            else if(additiveOperatorList->at(i-1) == Minus)
                value->SetIntValue(value->GetIntValue() - nextValue->GetIntValue());
        }
        else // przypadek macierzy
        {
            vector<int> *matrixValue = this->value->GetMatrixValue();
            MatrixType *matrixType = (MatrixType*) this->typeDescriptorPointer;

            if(additiveOperatorList->at(i-1) == Plus)
                for(int i = 0; i < matrixType->firstRange; i++)
                    for(int j = 0; j < matrixType->secondRange; j++)
                        matrixValue->at(i*matrixType->firstRange+j) +=
                            nextValue->GetMatrixValue()->at(i*matrixType->firstRange+j);

            else if(additiveOperatorList->at(i-1) == Minus)
                for(int i = 0; i < matrixType->firstRange; i++)
                    for(int j = 0; j < matrixType->secondRange; j++)
                        matrixValue->at(i*matrixType->firstRange+j) -=
                            nextValue->GetMatrixValue()->at(i*matrixType->firstRange+j);
        }
    }
    return this->value;
}

void SimpleExpression::setValue(Value* value)
{
    if(this->value == nullptr)
        this->value = new Value();

    this->value->SetBoolValue(value->GetBoolValue());
    this->value->SetIntValue(value->GetIntValue());
    this->value->SetMatrixValue(value->GetMatrixValue());
}

Value* SimpleExpression::getValue()
{
    return this->value;
}
