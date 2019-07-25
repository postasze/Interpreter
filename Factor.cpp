#include "Factor.h"
#include "Variable.h"
#include "Constant.h"
#include "Expression.h"
#include "FunctionCallStatement.h"
#include "Interpreter.h"
#include "Scope.h"
#include "IdentifierDescriptor.h"
#include "Value.h"
#include "BlockStatement.h"

Factor::Factor(TypeDescriptor *typeDescriptorPointer, Variable *variablePointer,
        Constant *constantPointer, Expression *expressionPointer,
        Factor *notFactorPointer,
        FunctionCallStatement *functionCallStatementPointer)
{
    this->typeDescriptorPointer = typeDescriptorPointer;
    this->variablePointer = variablePointer;
    this->constantPointer = constantPointer;
    this->expressionPointer = expressionPointer;
    this->notFactorPointer = notFactorPointer;
    this->functionCallStatementPointer = functionCallStatementPointer;
    this->value = nullptr;
}

Factor::Factor(Variable *variablePointer)
{
    this->typeDescriptorPointer = nullptr;
    this->variablePointer = variablePointer;
    this->constantPointer = nullptr;
    this->expressionPointer = nullptr;
    this->notFactorPointer = nullptr;
    this->functionCallStatementPointer = nullptr;
    this->value = nullptr;
}

Factor::Factor(Constant *constantPointer)
{
    this->typeDescriptorPointer = constantPointer->typeDescriptorPointer;
    this->variablePointer = nullptr;
    this->constantPointer = constantPointer;
    this->expressionPointer = nullptr;
    this->notFactorPointer = nullptr;
    this->functionCallStatementPointer = nullptr;
    this->value = nullptr;
}

Factor::Factor(Expression *expressionPointer)
{
    this->typeDescriptorPointer = nullptr;
    this->variablePointer = nullptr;
    this->constantPointer = nullptr;
    this->expressionPointer = expressionPointer;
    this->notFactorPointer = nullptr;
    this->functionCallStatementPointer = nullptr;
    this->value = nullptr;
}

Factor::Factor(Factor *notFactorPointer)
{
    this->typeDescriptorPointer = nullptr;
    this->variablePointer = nullptr;
    this->constantPointer = nullptr;
    this->expressionPointer = nullptr;
    this->notFactorPointer = notFactorPointer;
    this->functionCallStatementPointer = nullptr;
    this->value = nullptr;
}

Factor::Factor(FunctionCallStatement *functionCallStatementPointer)
{
    this->typeDescriptorPointer = nullptr;
    this->variablePointer = nullptr;
    this->constantPointer = nullptr;
    this->expressionPointer = nullptr;
    this->notFactorPointer = nullptr;
    this->functionCallStatementPointer = functionCallStatementPointer;
    this->value = nullptr;
}

Factor::Factor(const Factor& factor)
{
    this->typeDescriptorPointer = factor.typeDescriptorPointer;
    if(factor.variablePointer != nullptr)
        this->variablePointer = new Variable(*factor.variablePointer);
    else
        this->variablePointer = nullptr;
    if(factor.constantPointer != nullptr)
        this->constantPointer = new Constant(*factor.constantPointer);
    else
        this->constantPointer = nullptr;
    if(factor.expressionPointer != nullptr)
        this->expressionPointer = new Expression(*factor.expressionPointer);
    else
        this->expressionPointer = nullptr;
    if(factor.notFactorPointer != nullptr)
        this->notFactorPointer = new Factor(*factor.notFactorPointer);
    else
        this->notFactorPointer = nullptr;
    if(factor.functionCallStatementPointer != nullptr)
        this->functionCallStatementPointer = new FunctionCallStatement(*factor.functionCallStatementPointer);
    else
        this->functionCallStatementPointer = nullptr;
    if(factor.value != nullptr)
        this->value = new Value(*factor.value);
    else
        this->value = nullptr;
}

Factor::~Factor()
{
    if(this->variablePointer != nullptr)
        delete this->variablePointer;
    if(this->constantPointer != nullptr)
        delete this->constantPointer;
    if(this->expressionPointer != nullptr)
        delete this->expressionPointer;
    if(this->notFactorPointer != nullptr)
        delete this->notFactorPointer;
    if(this->functionCallStatementPointer != nullptr)
        delete this->functionCallStatementPointer;
    if(this->value != nullptr)
        delete this->value;
}

Value* Factor::evaluate(Interpreter& interpreter)
{
    IdentifierDescriptor *identifierDescriptorPointer;

    if(this->value != nullptr)
        delete this->value;

    if(variablePointer != nullptr)
    {
        identifierDescriptorPointer = interpreter.currentScope->Search(
            variablePointer->identifierName, VariableIdentifier);
        if(variablePointer != identifierDescriptorPointer->variablePointer)
        { // przypadek gdy mamy do czynienia po raz pierwszy z odwolaniem sie do danej zmiennej z instrukcji spoza deklaracji zmiennej
            delete variablePointer;
            variablePointer = identifierDescriptorPointer->variablePointer;
        }
        if(variablePointer->getValue() == nullptr)
            interpreter.SemanticError(VariableNotInitialized, true);

        this->typeDescriptorPointer = variablePointer->typeDescriptorPointer;
        this->value = new Value(*variablePointer->getValue());
    }
    else if(constantPointer != nullptr)
    {
        this->typeDescriptorPointer = constantPointer->typeDescriptorPointer;
        this->value = new Value(*constantPointer->getValue());
    }
    else if(expressionPointer != nullptr)
    {
        expressionPointer->evaluate(interpreter);
        this->typeDescriptorPointer = expressionPointer->typeDescriptorPointer;
        this->value = new Value(*expressionPointer->getValue());
    }
    else if(notFactorPointer != nullptr)
    {
        notFactorPointer->evaluate(interpreter);
        this->typeDescriptorPointer = notFactorPointer->typeDescriptorPointer;
        this->value = new Value(*notFactorPointer->getValue());
    }
    else if(functionCallStatementPointer != nullptr)
    {
        functionCallStatementPointer->execute(interpreter);
        this->typeDescriptorPointer = functionCallStatementPointer->typeDescriptorPointer;
        this->value = new Value(*functionCallStatementPointer->getReturnValue());
    }
    return this->value;
}

void Factor::setValue(Value* value)
{
    if(this->value == nullptr)
        this->value = new Value();

    this->value->SetBoolValue(value->GetBoolValue());
    this->value->SetIntValue(value->GetIntValue());
    this->value->SetMatrixValue(value->GetMatrixValue());
}

Value* Factor::getValue()
{
    return this->value;
}
