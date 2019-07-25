#include "Assignment.h"
#include "Interpreter.h"
#include "Variable.h"
#include "Expression.h"
#include "Scope.h"
#include "IdentifierDescriptor.h"
#include "Value.h"

Assignment::Assignment(Variable *variablePointer, Expression *expressionPointer)
{
    this->typeDescriptorPointer = expressionPointer->typeDescriptorPointer;
    this->variablePointer = variablePointer;
    this->identifierName = "";
    this->expressionPointer = expressionPointer;
}

Assignment::Assignment(string identifierName, Expression *expressionPointer, int statementPosition)
{
    this->typeDescriptorPointer = nullptr;
    this->variablePointer = nullptr;
    this->identifierName = identifierName;
    this->expressionPointer = expressionPointer;
    this->statementPosition = statementPosition;
}

Assignment::Assignment(const Assignment& assignment)
{
    this->typeDescriptorPointer = assignment.typeDescriptorPointer;
    this->variablePointer = nullptr;
    this->identifierName = assignment.identifierName;
    this->expressionPointer = new Expression(*expressionPointer);
    this->statementPosition = assignment.statementPosition;
}

Assignment::~Assignment()
{
    if(expressionPointer != nullptr)
        delete expressionPointer;
}

void Assignment::execute(Interpreter& interpreter)
{
    IdentifierDescriptor *identifierDescriptorPointer;

    expressionPointer->evaluate(interpreter);

    if(variablePointer == nullptr)
    {
        identifierDescriptorPointer = interpreter.currentScope->Search(
            this->identifierName, VariableIdentifier);
        variablePointer = identifierDescriptorPointer->variablePointer;
    }

    if(!Compatible(variablePointer->typeDescriptorPointer,
                   expressionPointer->typeDescriptorPointer))
        interpreter.SemanticError(IncompatibleTypesForExpressionAndVariable, true);
    else
        variablePointer->setValue(expressionPointer->getValue());
}
