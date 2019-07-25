#include "Term.h"
#include "Factor.h"
#include "Interpreter.h"
#include "Value.h"
#include "MatrixType.h"

Term::Term(TypeDescriptor *typeDescriptorPointer, vector<Factor*> *factorList,
    vector<TokenType> *multiplicativeOperatorList)
{
    this->typeDescriptorPointer = typeDescriptorPointer;
    this->factorList = factorList;
    this->multiplicativeOperatorList = multiplicativeOperatorList;
    this->value = nullptr;
}

Term::Term(const Term& term)
{
    this->typeDescriptorPointer = term.typeDescriptorPointer;
    this->value = nullptr;

    if(term.factorList != nullptr)
    {
        this->factorList = new vector<Factor*>();

        for(unsigned int i = 0; i < term.factorList->size(); i++)
            this->factorList->push_back(new Factor(*term.factorList->at(i)));
    }
    else
        this->factorList = nullptr;

    this->multiplicativeOperatorList = new vector<TokenType>(*term.multiplicativeOperatorList);
}

Term::~Term()
{
    if(this->value != nullptr)
        delete this->value;
    if(factorList != nullptr)
    {
        factorList->clear();
        delete factorList;
    }
    if(multiplicativeOperatorList != nullptr)
    {
        multiplicativeOperatorList->clear();
        delete multiplicativeOperatorList;
    }
}

Value* Term::evaluate(Interpreter& interpreter)
{
    Value *nextValue;

    if(this->value != nullptr)
        delete this->value;

    this->value = new Value(*factorList->at(0)->evaluate(interpreter));
    this->typeDescriptorPointer = factorList->at(0)->typeDescriptorPointer;

    for(unsigned int i = 1; i < factorList->size(); i++)
    {
        nextValue = factorList->at(i)->evaluate(interpreter);

        if(!((Compatible(this->typeDescriptorPointer, interpreter.integerType) &&
              Compatible(factorList->at(i)->typeDescriptorPointer, interpreter.integerType)) ||
              Compatible(this->typeDescriptorPointer, factorList->at(i)->typeDescriptorPointer))) // drugi przypadek dla macierzy
            interpreter.SemanticError(IncompatibleTypesForOperands, true);

        if(this->typeDescriptorPointer == interpreter.integerType)
        {
            switch(multiplicativeOperatorList->at(i-1))
            {
            case Multiplication:
                this->value->SetIntValue(value->GetIntValue() * nextValue->GetIntValue());
                break;
            case Division:
                this->value->SetIntValue(value->GetIntValue() / nextValue->GetIntValue());
                break;
            case Percent:
                this->value->SetIntValue(value->GetIntValue() % nextValue->GetIntValue());
                break;
            case Exponentiation:
                this->value->SetIntValue(pow(value->GetIntValue(), nextValue->GetIntValue()));
                break;
            default:
                break;
            }
        }
        else // przypadek macierzy
        {
            vector<int> *matrixValue;

            MatrixType *matrixType = (MatrixType*) this->typeDescriptorPointer;

            if(multiplicativeOperatorList->at(i-1) == Multiplication)
            {
                matrixValue = new vector<int>();

                for(int i = 0; i < matrixType->firstRange; i++)
                    for(int j = 0; j < matrixType->secondRange; j++)
                        matrixValue->push_back(0);

                for(int i = 0; i < matrixType->firstRange; i++)
                    for(int j = 0; j < matrixType->secondRange; j++)
                        for(int k = 0; k < matrixType->firstRange; k++)
                            matrixValue->at(i*matrixType->firstRange+j) +=
                                value->GetMatrixValue()->at(i*matrixType->firstRange+k) *
                                    nextValue->GetMatrixValue()->at(k*matrixType->firstRange+j);

                this->value->SetMatrixValue(matrixValue);
                matrixValue->clear();
                delete matrixValue;
            }
        }
    }
    return this->value;
}

void Term::setValue(Value* value)
{
    if(this->value == nullptr)
        this->value = new Value();

    this->value->SetBoolValue(value->GetBoolValue());
    this->value->SetIntValue(value->GetIntValue());
    this->value->SetMatrixValue(value->GetMatrixValue());
}

Value* Term::getValue()
{
    return this->value;
}
