#include "ReturnStatement.h"
#include "Expression.h"
#include "Interpreter.h"
#include "Scope.h"
#include "BlockStatement.h"
#include "Value.h"

ReturnStatement::ReturnStatement(Expression *expressionPointer, int statementPosition)
{
    this->expressionPointer = expressionPointer;
    this->statementPosition = statementPosition;
    this->returnValue = nullptr;
}

ReturnStatement::ReturnStatement(const ReturnStatement& returnStatement)
{
    this->expressionPointer = new Expression(*returnStatement.expressionPointer);
    this->statementPosition = returnStatement.statementPosition;
    this->returnValue = nullptr;
}

ReturnStatement::~ReturnStatement()
{
    //dtor
}

void ReturnStatement::execute(Interpreter& interpreter)
{
    this->setValue(this->expressionPointer->evaluate(interpreter));
    interpreter.currentScope->block->setReturnValue(this->returnValue);
    interpreter.currentScope->block->returnType = expressionPointer->typeDescriptorPointer;
}

void ReturnStatement::setValue(Value* value)
{
    if(this->returnValue == nullptr)
        this->returnValue = new Value();

    this->returnValue->SetBoolValue(value->GetBoolValue());
    this->returnValue->SetIntValue(value->GetIntValue());
    this->returnValue->SetMatrixValue(value->GetMatrixValue());
}

Value* ReturnStatement::getValue()
{
    return this->returnValue;
}
